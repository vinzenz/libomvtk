#pragma once

#include "../lltypes/llsd_array.h"
#include "../lltypes/llsd_binary.h"
#include "../lltypes/llsd_boolean.h"
#include "../lltypes/llsd_date.h"
#include "../lltypes/llsd_integer.h"
#include "../lltypes/llsd_map.h"
#include "../lltypes/llsd_real.h"
#include "../lltypes/llsd_string.h"
#include "../lltypes/llsd_uri.h"
#include "../lltypes/llsd_uuid.h"
#include "../lltypes/llsd_value.h"

#include <boost/cstdint.hpp>
#include <vector>
#include <string>

namespace LLSD
{
	ValuePtr ParseXml(std::string const & data);
	std::string BuildXml(ValuePtr const & data);
	ValuePtr ParseNotation(std::string const & data);
	std::string BuildNotation(ValuePtr const & data);
	ValuePtr ParseBinary(std::vector<boost::uint8_t> const & data);
	std::vector<boost::uint8_t> BuildBinary(ValuePtr const & data);
}