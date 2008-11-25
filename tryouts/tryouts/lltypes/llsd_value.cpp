#include "stdafx.h"
#include "llsd_value.h"
#include "llsd_integer.h"
#include "llsd_real.h"
#include "llsd_boolean.h"
#include "llsd_string.h"
#include "llsd_uri.h"
#include "llsd_uuid.h"
#include "llsd_date.h"
#include "llsd_binary.h"
#include "llsd_map.h"
#include "llsd_array.h"

namespace LLSD
{
	Value::Value()
		: m_type(VTID_UNDEFINED)
	{

	}

	Value::Value(ValueType type)
		: m_type(type)
	{}

	Value::~Value()
	{

	}

	ValueType Value::GetType() const
	{
		return m_type;
	}

	IntegerPtr Value::ToInteger() const
	{
		return IntegerPtr(new Integer());
	}

	RealPtr Value::ToReal() const
	{
		return RealPtr(new Real());
	}

	StringPtr Value::ToString() const
	{
		return StringPtr(new String());
	}

	DatePtr Value::ToDate() const
	{
		return DatePtr(new Date());
	}

	UUIDPtr Value::ToUUID() const
	{
		return UUIDPtr(new UUID());
	}

	BooleanPtr Value::ToBoolean() const
	{
		return BooleanPtr(new Boolean());
	}

	BinaryPtr Value::ToBinary() const
	{
		return BinaryPtr(new Binary());
	}

	UriPtr Value::ToUri() const
	{
		return UriPtr(new Uri());
	}

	MapPtr Value::ToMap() const
	{
		return MapPtr(new Map());
	}

	ArrayPtr Value::ToArray() const
	{
		return ArrayPtr(new Array());
	}

	ValuePtr Value::Clone() const
	{
		switch(m_type)
		{
		case VTID_INTEGER:
			return ToInteger();
		case VTID_REAL:
			return ToReal();
		case VTID_STRING:
			return ToString();
		case VTID_DATE:
			return ToDate();
		case VTID_UUID:
			return ToUUID();
		case VTID_BOOLEAN:
			return ToBoolean();
		case VTID_BINARY:
			return ToBinary();
		case VTID_URI:
			return ToUri();
		case VTID_MAP:
			return ToMap();
		case VTID_ARRAY:
			return ToArray();
		case VTID_UNDEFINED:
		default:
			break;
		}
		return ValuePtr(new Value());
	}

	IntegerPtr Value::AsInteger(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_INTEGER);
		return boost::dynamic_pointer_cast<Integer>(ptr);
	}

	RealPtr Value::AsReal(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_REAL);
		return boost::dynamic_pointer_cast<Real>(ptr);
	}

	StringPtr Value::AsString(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_STRING);
		return boost::dynamic_pointer_cast<String>(ptr);
	}

	DatePtr Value::AsDate(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_DATE);
		return boost::dynamic_pointer_cast<Date>(ptr);
	}

	UUIDPtr Value::AsUUID(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_UUID);
		return boost::dynamic_pointer_cast<UUID>(ptr);
	}

	BooleanPtr Value::AsBoolean(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_BOOLEAN);
		return boost::dynamic_pointer_cast<Boolean>(ptr);
	}

	BinaryPtr Value::AsBinary(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_BINARY);
		return boost::dynamic_pointer_cast<Binary>(ptr);
	}

	UriPtr Value::AsUri(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_URI);
		return boost::dynamic_pointer_cast<Uri>(ptr);
	}

	MapPtr Value::AsMap(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_MAP);
		return boost::dynamic_pointer_cast<Map>(ptr);
	}
	
	ArrayPtr Value::AsArray(ValuePtr ptr)
	{
		assert(ptr && ptr->GetType() == VTID_ARRAY);
		return boost::dynamic_pointer_cast<Array>(ptr);
	}
}
