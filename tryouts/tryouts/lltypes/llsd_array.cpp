#include "stdafx.h"
#include "llsd_array.h"

namespace LLSD
{
	Array::Array()
		: Value(VTID_ARRAY)
		, m_value()
	{
	}

	Array::Array(Container const & value)
		: Value(VTID_ARRAY)
		, m_value(value)
	{

	}

	Array::Array(Array const & o)
		: Value(VTID_ARRAY)
		, m_value(o.m_value)
	{
	}

	Array::Array(ArrayPtr const & p)
		: Value(VTID_ARRAY)
		, m_value(p ? p->m_value : Container())
	{
	}

	Array::~Array()
	{
	}


	Array & Array::operator=(Array o)
	{
		assign(o.m_value);
		return *this;
	}


	void Array::push_back(const_reference v)
	{
		m_value.push_back(v);
	}

	void Array::push_back(Value const & v)
	{
		m_value.push_back(v.Clone());
	}

	void Array::pop_back()
	{
		m_value.pop_back();
	}


	std::size_t Array::size() const
	{
		return m_value.size();
	}


	Array::const_iterator Array::begin() const
	{
		return m_value.begin();
	}

	Array::iterator Array::begin()
	{
		return m_value.begin();
	}


	Array::const_iterator Array::end() const
	{
		return m_value.end();
	}

	Array::iterator Array::end()
	{
		return m_value.end();
	}


	void Array::assign(Array const & o)
	{
		m_value = o.m_value;
	}


	Array::reference Array::operator[](size_t index)
	{
		return m_value[index];
	}

	Array::const_reference Array::operator[](size_t index) const
	{
		return m_value[index];
	}


	Array::reference Array::at(size_t index)
	{
		return m_value.at(index);
	}

	Array::const_reference Array::at(size_t index) const
	{
		return m_value.at(index);
	}

	ArrayPtr Array::ToArray() const
	{
		return ArrayPtr(new Array(*this));
	}
}