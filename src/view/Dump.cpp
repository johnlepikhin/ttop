
#include "Dump.h"
#include "../ParserDescription.h"

namespace ttop {
namespace view {

template <typename IN>
std::string Dump<IN>::TypeID()
{
	return ((std::string)"dump");
}

template <typename IN>
Dump<IN>::Dump(std::shared_ptr<logic::Logic<IN> > parser)
	: View<IN>(parser)
{

}

template <typename IN>
Dump<IN>::~Dump() {
	if (OutputStream.is_open())
		OutputStream.close();
};

template <typename IN>
void Dump<IN>::Output()
{
	std::ostream &o = (OutputStream.is_open()) ? OutputStream : std::cout;

	for (auto g_it = this->Selection.begin(); g_it!=this->Selection.end(); ++g_it) {
		bool isFirst = true;
		for (auto it = g_it->second.begin(); it!=g_it->second.end(); ++it) {
			if (!isFirst)
				o << FieldSeparator;
			o << (*it).Val;
			isFirst = false;
		}
		o << RecordSeparator;
	}
	o << GroupSeparator;
}

template <typename IN>
void Dump<IN>::ParseParams(tinyxml2::XMLElement *node)
{
	const char *_attr = node->Attribute("output");
	if (_attr) {
		OutputFile = _attr;
		if ((std::string)"-" != _attr) {
			OutputStream.open(_attr, std::ios::out | std::ios::app);
		}
	}
	_attr = node->Attribute("rseparator");
	if (_attr) {
		RecordSeparator = _attr;
	}
	_attr = node->Attribute("fseparator");
	if (_attr) {
		FieldSeparator = _attr;
	}
	_attr = node->Attribute("gseparator");
	if (_attr) {
		GroupSeparator = _attr;
	}
}

template class Dump<ChunkEtherNet>;
template class Dump<ChunkEtherNetDIX>;
template class Dump<ChunkEtherNetSNAP>;
template class Dump<ChunkEtherNetRAW>;
template class Dump<ChunkEtherNet802LLC>;

template class Dump<ChunkIPv4>;
template class Dump<ChunkIPv6>;
template class Dump<ChunkTCP>;
template class Dump<ChunkUDP>;
template class Dump<PacketIPv4>;
template class Dump<PacketIPVariant>;
template class Dump<SessionTCP>;
template class Dump<EndPoint>;


} /* namespace view */
} /* namespace ttop */
