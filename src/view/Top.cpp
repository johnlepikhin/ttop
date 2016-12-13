// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Top.h"
#include "../ParserDescription.h"
#include "../Logic.h"
#include "../utils.h"
#include <algorithm>
#include <csignal>
#include <sys/ioctl.h>

namespace ttop {
namespace view {

bool isConstructed = false;

bool screenChanged = false;

std::vector<std::function<void()> > screenChangedHandlers;

void signal_handler (int) {
	screenChanged = true;

	struct winsize size;
	if (ioctl(fileno(stdout), TIOCGWINSZ, &size) == 0) { //-V111
		resize_term(size.ws_row, size.ws_col);
	}

	for (auto fn : screenChangedHandlers) {
		fn();
	}
}

template <typename IN>
std::string Top<IN>::TypeID()
{
	return ("top");
}

template <typename IN>
Top<IN>::Top(std::shared_ptr<logic::Logic<IN> > parser)
	: View<IN>(parser)
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	if(has_colors() == FALSE) {
		endwin();
		throw logic::ParseError("Cannot use view with type='top': your terminal does not support color");
	}

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE); //-V525
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);


	curs_set(0);

	ttop::utils::onExitHooks.push_back([](int) {
		endwin();
	});

	std::signal(SIGWINCH, signal_handler);
	screenChangedHandlers.push_back([=]() {
		Redraw();
	});

	CursesThread = std::thread( [=] { NCursesListenser(); } );
}

template <typename IN>
void Top<IN>::RecalculateColumns()
{
	uint16_t pos = 0;
	uint16_t windowPos = 0;
	for (auto i=Columns.begin(); i!=Columns.end(); ++i) {
		(*i).WindowPosition = windowPos;
		if (pos >= FirstVisibleColumn)
			windowPos += (*i).Width + 1;
		pos++;
	}
}

template <typename IN>
void Top<IN>::ChangeActiveColumn(int8_t offset)
{
	int16_t newCurrentPos = CurrentColumn + offset;
	if (newCurrentPos < 0) {
		FirstVisibleColumn = 0;
		RecalculateColumns();
		return;
	}
	if (newCurrentPos >= static_cast<int16_t>(Columns.size())) {
		FirstVisibleColumn = Columns.size()-1;
		RecalculateColumns();
		return;
	}

	ColumnInfo &newCurrent = Columns.at(newCurrentPos);
	ColumnInfo &current = Columns.at(CurrentColumn);

	int16_t newEndPos = newCurrent.WindowPosition + newCurrent.Width + 1;
	int16_t maxx = getmaxx(stdscr);
	if (offset > 0) {
		bool newIsVisible = newEndPos < maxx;
		if (!newIsVisible)
			FirstVisibleColumn = newCurrentPos;

		CurrentColumn = newCurrentPos;
		RecalculateColumns();
		return;
	} else if (offset < 0) {
		bool newIsVisible = newEndPos < getmaxx(stdscr) && FirstVisibleColumn <= newCurrentPos;
		if (newIsVisible) {
			CurrentColumn = newCurrentPos;
			RecalculateColumns();
			return;
		} else {
			int16_t sumWidth = 0;
			int16_t i = newCurrentPos;
			while (i && (sumWidth += Columns.at(i).Width + 1) && sumWidth < maxx) i--;
			FirstVisibleColumn = i;
			CurrentColumn = newCurrentPos;
			RecalculateColumns();
		}
	}
}

template <typename IN>
void Top<IN>::ResizeColumn(ColumnInfo &column, uint16_t newWidth)
{
	column.Width = newWidth;
	RecalculateColumns();
}

template <typename IN>
void Top<IN>::SetFirstVisibleColumn(uint16_t col)
{
	if (col > Columns.size())
		return;
	FirstVisibleColumn = col;
	RecalculateColumns();
}

template <typename IN>
void Top<IN>::SetFirstVisibleRow(int16_t row)
{
	if (row >= static_cast<int16_t>(SavedOutput.size())) {
		FirstVisibleRow = static_cast<int16_t>(SavedOutput.size()) - 1;
	} else if (row < 0) {
		FirstVisibleRow = 0;
	} else {
		FirstVisibleRow = row;
	}
	RecalculateColumns();
}

template <typename IN>
void Top<IN>::TogglePause()
{
	if (IsPaused) {
		PauseMutex.unlock();
	} else {
		PauseMutex.lock();
	}
	IsPaused = !IsPaused;
}

template <typename IN>
void Top<IN>::NCursesListenser()
{
	while (1) {
		int c = getch();

		if (c == 'q') {
			ttop::utils::requestExit(0);
		} else if (c == 'p') {
			TogglePause();
		} else if (c == '>') {
			ResizeColumn(Columns.at(CurrentColumn), Columns.at(CurrentColumn).Width+1);
			Redraw();
		} else if (c == '<') {
			if (Columns.at(CurrentColumn).Width > 2) {
				ResizeColumn(Columns.at(CurrentColumn), Columns.at(CurrentColumn).Width-1);
				RecalculateColumns();
				Redraw();
			}
		} else if (c == KEY_RIGHT) {
			ChangeActiveColumn(1);
			Redraw();
		} else if (c == KEY_LEFT) {
			ChangeActiveColumn(-1);
			Redraw();
		} else if (c == KEY_UP) {
			SetFirstVisibleRow(FirstVisibleRow-1);
			Redraw();
		} else if (c == KEY_DOWN) {
			SetFirstVisibleRow(FirstVisibleRow+1);
			Redraw();
		} else if (c == KEY_PPAGE) {
			SetFirstVisibleRow(FirstVisibleRow-RowsFitsOnScreen);
			Redraw();
		} else if (c == KEY_NPAGE) {
			SetFirstVisibleRow(FirstVisibleRow+RowsFitsOnScreen);
			Redraw();
		}
	}
}

template <typename IN>
void Top<IN>::PrintValue(const ColumnInfo &col, const std::string &value, bool isHeader) const
{
	if (col.Position < FirstVisibleColumn)
		return;

	uint16_t x, y;
	getyx(stdscr, y, x);
	uint16_t maxx = getmaxx(stdscr);
	uint16_t maxy = getmaxy(stdscr);
	uint16_t columns_count = static_cast<uint16_t>(Columns.size());
	bool isLastColumn = columns_count == col.Position+1;
	bool hasSpace = maxy - y > 0;

	if (!hasSpace)
		return;

	if (col.WindowPosition+1 > static_cast<int16_t>(maxx))
		return;

	uint16_t len = maxx - x - 1;

	if (!isLastColumn)
		len = std::min(len, col.Width);

	std::string out = value;

	out = ttop::utils::semiHexStr(out, len);

	out.resize(len, ' ');

	uint8_t color_pair;
	if (isHeader) {
		if (CurrentColumn == col.Position) {
			color_pair = 2;
		} else {
			color_pair = 1;
		}
	} else {
		color_pair = 3;
	}

	attron(COLOR_PAIR(color_pair));

	if (isLastColumn) {
		printw("%s\n", out.c_str()); //-V111
	} else {
		printw("%s ", out.c_str()); //-V111
	}
	attroff(COLOR_PAIR(color_pair));
}

template <typename IN>
void Top<IN>::PrintHeader() const
{
	printw("Use arrows to move over list and '<', '>' to resize columns\n");
	printw("Use 'p' to pause parser\n");

	attron(COLOR_PAIR(1));
	for (auto i=Columns.begin(); i!=Columns.end(); ++i)
		PrintValue((*i), (*i).Name, true);
	attroff(COLOR_PAIR(1));

	refresh();
}

template <typename IN>
void Top<IN>::Redraw()
{
	if (screenChanged) {
		clear();
		RecalculateColumns();
		screenChanged = false;
	}

	move(0, 0);

	PrintHeader();

	uint32_t rowpos = 0;
	uint16_t maxy = getmaxy(stdscr);
	uint16_t __attribute__((unused)) x;
	uint16_t y;

	getyx(stdscr, y, x);
	uint16_t firstY = y;
	for (auto const &row : SavedOutput) {
		uint16_t pos = 0;
		if (rowpos >= FirstVisibleRow) {
			for (auto const &field : row) {
				PrintValue(Columns.at(pos), field.Val, false);
				pos++;
			}
		}
		getyx(stdscr, y, x);
		if (y == maxy)
			break;

		rowpos++;
	}

	RowsFitsOnScreen = maxy - firstY;

	clrtobot();

	refresh();
}

template <typename IN>
void Top<IN>::DoOutput(const std::vector<typename View<IN>::t_selection> &output)
{
	if (IsPaused) {
		PauseMutex.lock();
		PauseMutex.unlock();
	}

	SavedOutput = output;
	Redraw();
}

template <typename IN>
void Top<IN>::ParseParams(const tinyxml2::XMLElement *node)
{
	if (isConstructed)
		throw logic::ParseError("Only one view with type='top' can be used");

	isConstructed = true;

	int pos=0;
	uint16_t windowPos=0;
	uint16_t defaultWidth = 15;
	for (auto i=this->Selection_source.begin(); i!=this->Selection_source.end(); ++i) {
		struct ColumnInfo col = {
				Width : defaultWidth,
				WindowPosition : windowPos,
				Position : static_cast<uint16_t>(pos),
				Name : (*i).Name
		};
		Columns.push_back(col);
		pos++;
		windowPos += defaultWidth+1;
	}

}

template <typename IN>
Top<IN>::~Top()
{
}

template class Top<ChunkEtherNet>;
template class Top<ChunkEtherNetDIX>;
template class Top<ChunkEtherNetSNAP>;
template class Top<ChunkEtherNetRAW>;
template class Top<ChunkEtherNet802LLC>;
template class Top<ChunkIPv4>;
template class Top<ChunkIPv6>;
template class Top<ChunkTCP>;
template class Top<ChunkUDP>;
template class Top<PacketIPv4>;
template class Top<PacketIPVariant>;
template class Top<SessionTCP>;
template class Top<EndPoint>;
template class Top<ChunkHTTP>;
template class Top<PacketMySQL>;
template class Top<ChunkSSL>;

} /* namespace view */
} /* namespace ttop */
