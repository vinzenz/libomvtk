#pragma once 
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

/*
Boolean - true or false 
Integer - a 32 bit signed integer 
Real - a 64 bit IEEE 754 floating point value 
UUID - a 128 bit unique value 
String - a sequence of zero or more Unicode chracters 
Date - an absolute point in time, UTC, with resolution to the second 
URI - a String that is a URI 
Binary - a sequence of zero or more octets (unsigned bytes)
Array and Map
*/

namespace LLSD
{
	struct Integer;
	struct Real;
	struct String;
	struct Date;
	struct UUID;
	struct Boolean;
	struct Binary;
	struct Uri;
	struct Map;
	struct Array;
	struct Value;

	typedef boost::shared_ptr<Integer>	IntegerPtr;
	typedef boost::shared_ptr<Real>		RealPtr;
	typedef boost::shared_ptr<String>	StringPtr;
	typedef boost::shared_ptr<Date>		DatePtr;
	typedef boost::shared_ptr<UUID>		UUIDPtr;
	typedef boost::shared_ptr<Boolean>	BooleanPtr;
	typedef boost::shared_ptr<Binary>	BinaryPtr;
	typedef boost::shared_ptr<Uri>		UriPtr;
	typedef boost::shared_ptr<Map>		MapPtr;
	typedef boost::shared_ptr<Array>	ArrayPtr;
	typedef boost::shared_ptr<Value>	ValuePtr;

	enum ValueType
	{
		VTID_UNDEFINED,
		VTID_INTEGER,
		VTID_REAL,
		VTID_STRING,
		VTID_DATE,
		VTID_UUID,
		VTID_BOOLEAN,
		VTID_BINARY,
		VTID_URI,
		VTID_MAP,
		VTID_ARRAY
	};

	struct Value
	{
		Value();
		Value(ValueType);
		virtual ~Value();

		virtual ValueType GetType() const;

		virtual IntegerPtr ToInteger() const;
		virtual RealPtr ToReal() const;
		virtual StringPtr ToString() const;
		virtual DatePtr ToDate() const;
		virtual UUIDPtr ToUUID() const;
		virtual BooleanPtr ToBoolean() const;
		virtual BinaryPtr ToBinary() const;
		virtual UriPtr ToUri() const;
		virtual MapPtr ToMap() const;
		virtual ArrayPtr ToArray() const;
		virtual ValuePtr Clone() const;
		
		// This might throw if the type is not the type you want to cast it to
		static IntegerPtr AsInteger(ValuePtr ptr);
		static RealPtr AsReal(ValuePtr ptr);
		static StringPtr AsString(ValuePtr ptr);
		static DatePtr AsDate(ValuePtr ptr);
		static UUIDPtr AsUUID(ValuePtr ptr);
		static BooleanPtr AsBoolean(ValuePtr ptr);
		static BinaryPtr AsBinary(ValuePtr ptr);
		static UriPtr AsUri(ValuePtr ptr);
		static MapPtr AsMap(ValuePtr ptr);
		static ArrayPtr AsArray(ValuePtr ptr);		
	protected:
		ValueType m_type;
	};	
}