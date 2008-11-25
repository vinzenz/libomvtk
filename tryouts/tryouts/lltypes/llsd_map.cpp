#include "stdafx.h"
#include "llsd_map.h"

namespace LLSD
{
	Map::Map()
		: Value(VTID_MAP)
		, m_value()
	{
	}

	Map::Map(Container const & c)
		: Value(VTID_MAP)
		, m_value(c)
	{
	}

	Map::Map(Map const & o)
		: Value(VTID_MAP)
		, m_value(o.m_value)
	{
	}

	Map::Map(MapPtr const & p)
		: Value(VTID_MAP)
		, m_value(p ? p->m_value : Container())
	{
	}

	Map::~Map()
	{
	}


	Map & Map::operator=(Map o)
	{
		o.m_value.swap(o.m_value);
		return *this;
	}


	Map::ValueType & Map::operator[](KeyType const & k)
	{
		return m_value[k];
	}

	void Map::insert(KeyType const & k, ValueType const & v)
	{
		m_value.insert(Container::value_type(k,v));
	}

	std::size_t Map::size() const
	{
		return m_value.size();
	}


	Map::iterator Map::begin()
	{
		return m_value.begin();
	}

	Map::const_iterator Map::begin() const
	{
		return m_value.begin();
	}

	Map::iterator Map::end()
	{
		return m_value.end();
	}

	Map::const_iterator Map::end() const
	{
		return m_value.end();
	}


	bool Map::has_key(KeyType const & k)
	{
		return m_value.count(k) != 0;
	}

	Map::iterator Map::find(KeyType const & k)
	{
		return m_value.find(k);
	}

	Map::const_iterator Map::find(KeyType const & k) const
	{
		return m_value.find(k);
	}

	MapPtr Map::ToMap() const
	{
		return MapPtr(new Map(*this));
	}
}