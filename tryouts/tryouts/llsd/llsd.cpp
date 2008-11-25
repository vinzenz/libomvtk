#include "stdafx.h"
#include "llsd.h"
#include "xml.h"
#include "binary.h"
#include "notation.h"
#include "../throw.h"

namespace LLSD
{
	ValuePtr ParseXml(std::string const & data)
	{
		return detail::XML::Parser::Parse(data.begin(), data.end());
	}

	std::string BuildXml(ValuePtr const & value)
	{
		return detail::XML::Build(value);
	}

	ValuePtr ParseNotation(std::string const & data)
	{
		return detail::Notation::Parser::Parse(data.begin(), data.end());
	}

	std::string BuildNotation(ValuePtr const & data)
	{
		return detail::Notation::Build(data);
	}

	ValuePtr ParseBinary(std::vector<boost::uint8_t> const & data)
	{
		return detail::Binary::Parser::Parse(data.begin(), data.end());
	}

	std::vector<boost::uint8_t> BuildBinary(ValuePtr const & data)
	{
		return detail::Binary::Build(data);
	}
}