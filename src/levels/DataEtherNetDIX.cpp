// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataEtherNetDIX.h"

namespace ttop {
namespace level_data {

typename logic::Logic<ChunkEtherNetDIX>::t_string_value DataEtherNetDIX::ParseStringCustom(const tinyxml2::XMLElement &elt)
{
	return (Traits.ParseStringCustom(elt));
}

typename logic::Logic<ChunkEtherNetDIX>::t_longlong_value DataEtherNetDIX::ParseLongLongCustom(const tinyxml2::XMLElement &elt)
{
	return (Traits.ParseLongLongCustom(elt));
}

typename logic::Logic<ChunkEtherNetDIX>::t_bool_value DataEtherNetDIX::ParseBoolCustom(const tinyxml2::XMLElement &elt)
{
	return (Traits.ParseBoolCustom(elt));
}

} /* namespace level_data */
} /* namespace ttop */
