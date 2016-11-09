
#ifndef SRC_LEVELS_IPV4_H_
#define SRC_LEVELS_IPV4_H_

#include <levels/ParserIPv4.h>

#include "LevelTraits.h"

namespace ttop {
namespace level {

template <typename OUT>
class IfDataIPv4: public logic::Logic<ChunkIPv4, OUT>
{
public:
	IfDataIPv4(OUT defaultValue) : logic::Logic<ChunkIPv4, OUT>(defaultValue) {}

	virtual typename logic::Logic<ChunkIPv4, OUT>::t_string_value ParseStringCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "SourceIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (IPv4Addr::asString(c->SrcIP));
			};
			return (r);
		} else if (name == "DestinationIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (IPv4Addr::asString(c->DstIP));
			};
			return (r);
		}
		return (ttop::logic::Logic<ChunkIPv4, OUT>::ParseStringCustom(elt));
	}

	virtual typename logic::Logic<ChunkIPv4, OUT>::t_longlong_value ParseLongLongCustom(tinyxml2::XMLElement &elt)
	{
		std::string name(elt.Value());
		if (name == "IHL") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->IHL32bit);
			};
			return (r);
		} else if (name == "PktLength") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->PktLength);
			};
			return (r);
		} else if (name == "PayloadLength") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->PayloadLength);
			};
			return (r);
		} else if (name == "Protocol") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->Protocol);
			};
			return (r);
		} else if (name == "ID") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->ID);
			};
			return (r);
		} else if (name == "FragmentOffset") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->FragmentOffset);
			};
			return (r);
		} else if (name == "TTL") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->TTL);
			};
			return (r);
		} else if (name == "SourceIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->SrcIP);
			};
			return (r);
		} else if (name == "DestinationIP") {
			auto r = [](std::shared_ptr<ChunkIPv4> c) {
				return (c->DstIP);
			};
			return (r);
		}
		return (ttop::logic::Logic<ChunkIPv4, OUT>::ParseLongLongCustom(elt));
	}

	virtual ~IfDataIPv4() {};
};

class FilterIPv4 : public IfDataIPv4<bool> {
public:
	FilterIPv4() : IfDataIPv4<bool>(true) {}
};

class IPv4 : public LevelTraits<ParserIPv4> {
public:
	IPv4();
	parserDescription::info GetDescription();
};

} /* namespace level */
} /* namespace ttop */

#endif /* SRC_LEVELS_IPV4_H_ */
