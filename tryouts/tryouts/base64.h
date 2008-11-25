#pragma once

#include <string>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

namespace encoding
{
	// This algorithm will decode std::string and std::wstring into any
	// type which takes input and end iterators for either any type or at least
	// for boost::uint8_t :)
	template<typename ReturnType, typename CharT>
	ReturnType base64_decode(std::basic_string<CharT> input)
	{
		input.append(input.size() % 4, CharT('='));
		typedef boost::archive::iterators::transform_width<
			boost::archive::iterators::binary_from_base64<CharT *>, 8, 6, boost::uint8_t
		> binary_t;

		std::basic_string<CharT>::size_type pos = input.find_last_not_of(CharT('='));		
		// calculate how many characters we need to process		
		pos = (pos == input.size() -1 ? input.size() : pos );		
		return ReturnType(binary_t(&input[0]), binary_t(&input[0] + pos));
	}

	// This algorithm will encode any container which has an index operator ([])	
	// and puts the result into any type which takes an input and and output iterator
	// for any or at least for boost::uint8_t types 
	// Since boost::uint8_t is convertible into char and wchar_t we can get it 
	// as strings too. Which will be the origial value. 
	// The return value is not padded on the 4Byte boundary with '=' signs
	// please do this if needed.
	template<typename ReturnType, typename InputContainerType>
	ReturnType base64_encode(InputContainerType const & input)
	{		
		using namespace boost::archive::iterators;
		typedef base64_from_binary<
			transform_width<
			typename InputContainerType::const_pointer, 6, 8, boost::uint8_t
			>
		> base64_t;
		return ReturnType(base64_t(&input[0]), base64_t(&input[0] + input.size()));
	}
}

