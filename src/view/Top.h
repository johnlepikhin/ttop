
#ifndef SRC_VIEW_TOP_H_
#define SRC_VIEW_TOP_H_

#include "View.cpp"
#include <ncurses.h>
#include <thread>
#include <condition_variable>

namespace ttop {
namespace view {

struct ColumnInfo {
	uint16_t Width;
	uint16_t WindowPosition;
	uint16_t Position;
	std::string Name;
};

template <typename IN>
class Top: public View<IN> {
	std::thread CursesThread;
	bool IsPaused = false;
	uint16_t CurrentColumn = 0;
	uint16_t FirstVisibleColumn = 0;
	uint16_t FirstVisibleRow = 0;
	uint16_t RowsFitsOnScreen = 0;
	std::mutex PauseMutex;
	std::mutex RedrawMutex;
	void PrintHeader() const;
	void PrintValue(const ColumnInfo &col, const std::string &value, bool isHeader) const;
	void RecalculateColumns();
	void ResizeColumn(ColumnInfo &col, uint16_t newWidth);
	void SetFirstVisibleColumn(uint16_t col);
	void SetFirstVisibleRow(int16_t row);
	void ChangeActiveColumn(int8_t offset);
	std::vector<ColumnInfo> Columns;
	std::vector<typename View<IN>::t_selection> SavedOutput;
public:
	std::string TypeID();
	Top(std::shared_ptr<logic::Logic<IN> > parser);
	void DoOutput(const std::vector<typename View<IN>::t_selection> &output);
	void ParseParams(const tinyxml2::XMLElement *node);
	void Redraw();
	void NCursesListenser();
	void TogglePause();
	~Top();
};

} /* namespace view */
} /* namespace ttop */

#endif /* SRC_VIEW_TOP_H_ */
