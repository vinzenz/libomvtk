//
// BinaryWriter.cpp
//
// $Id: //poco/1.3/Foundation/src/BinaryWriter.cpp#2 $
//
// Library: Foundation
// Package: Streams
// Module:  BinaryReaderWriter
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include <cstring>
#include "Poco/BinaryWriter.h"
#include "Poco/ByteOrder.h"


namespace Poco {


BinaryWriter::BinaryWriter(std::ostream& ostr, StreamByteOrder byteOrder):
	_ostr(ostr)
{
#if defined(POCO_ARCH_BIG_ENDIAN)
	_flipBytes = (byteOrder == LITTLE_ENDIAN_BYTE_ORDER);
#else
	_flipBytes = (byteOrder == BIG_ENDIAN_BYTE_ORDER);
#endif
}


BinaryWriter::~BinaryWriter()
{
}


BinaryWriter& BinaryWriter::operator << (bool value)
{
	_ostr.write((const char*) &value, sizeof(value));
	return *this;
}


BinaryWriter& BinaryWriter::operator << (char value)
{
	_ostr.write((const char*) &value, sizeof(value));
	return *this;
}


BinaryWriter& BinaryWriter::operator << (unsigned char value)
{
	_ostr.write((const char*) &value, sizeof(value));
	return *this;
}


BinaryWriter& BinaryWriter::operator << (signed char value)
{
	_ostr.write((const char*) &value, sizeof(value));
	return *this;
}


BinaryWriter& BinaryWriter::operator << (short value)
{
	if (_flipBytes)
	{
		short fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (unsigned short value)
{
	if (_flipBytes)
	{
		unsigned short fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (int value)
{
	if (_flipBytes)
	{
		int fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (unsigned int value)
{
	if (_flipBytes)
	{
		unsigned int fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (long value)
{
	if (_flipBytes)
	{
#if defined(POCO_LONG_IS_64_BIT)
		long fValue = ByteOrder::flipBytes((Int64) value);
#else
		long fValue = ByteOrder::flipBytes((Int32) value);
#endif
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (unsigned long value)
{
	if (_flipBytes)
	{
#if defined(POCO_LONG_IS_64_BIT)
		long fValue = ByteOrder::flipBytes((UInt64) value);
#else
		long fValue = ByteOrder::flipBytes((UInt32) value);
#endif
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (float value)
{
	if (_flipBytes)
	{
		const char* ptr = (const char*) &value;
		ptr += sizeof(value);
		for (unsigned i = 0; i < sizeof(value); ++i)
			_ostr.write(--ptr, 1);
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (double value)
{
	if (_flipBytes)
	{
		const char* ptr = (const char*) &value;
		ptr += sizeof(value);
		for (unsigned i = 0; i < sizeof(value); ++i)
			_ostr.write(--ptr, 1);
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


#if defined(POCO_HAVE_INT64) && !defined(POCO_LONG_IS_64_BIT)


BinaryWriter& BinaryWriter::operator << (Int64 value)
{
	if (_flipBytes)
	{
		Int64 fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


BinaryWriter& BinaryWriter::operator << (UInt64 value)
{
	if (_flipBytes)
	{
		UInt64 fValue = ByteOrder::flipBytes(value);
		_ostr.write((const char*) &fValue, sizeof(fValue));
	}
	else
	{
		_ostr.write((const char*) &value, sizeof(value));
	}
	return *this;
}


#endif


BinaryWriter& BinaryWriter::operator << (const std::string& value)
{
	UInt32 length = (UInt32) value.size();
	write7BitEncoded(length);
	_ostr.write(value.data(), length);
	return *this;
}


BinaryWriter& BinaryWriter::operator << (const char* value)
{
	poco_check_ptr (value);
	UInt32 length = (UInt32) std::strlen(value);
	write7BitEncoded(length);
	_ostr.write(value, length);
	return *this;
}


void BinaryWriter::write7BitEncoded(UInt32 value)
{
	do
	{
		unsigned char c = (unsigned char) (value & 0x7F);
		value >>= 7;
		if (value) c |= 0x80;
		_ostr.write((const char*) &c, 1);
	}
	while (value);
}


#if defined(POCO_HAVE_INT64)


void BinaryWriter::write7BitEncoded(UInt64 value)
{
	do
	{
		unsigned char c = (unsigned char) (value & 0x7F);
		value >>= 7;
		if (value) c |= 0x80;
		_ostr.write((const char*) &c, 1);
	}
	while (value);
}


#endif


void BinaryWriter::writeRaw(const std::string& rawData)
{
	_ostr.write(rawData.data(), (std::streamsize) rawData.length());
}


void BinaryWriter::writeBOM()
{
	UInt16 value = 0xFEFF;
	if (_flipBytes) value = ByteOrder::flipBytes(value);
	_ostr.write((const char*) &value, sizeof(value));
}


void BinaryWriter::flush()
{
	_ostr.flush();
}


} // namespace Poco
