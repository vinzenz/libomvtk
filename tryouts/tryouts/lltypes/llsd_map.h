#pragma once

#include "llsd_value.h"
#include <map>
#include <string>

namespace LLSD
{
	struct Map : Value
	{
		typedef std::string KeyType;
		typedef ValuePtr ValueType;
		typedef std::pair<KeyType, ValueType> PairType;
		typedef std::map<KeyType, ValueType> Container;
		typedef Container::iterator iterator;
		typedef Container::const_iterator const_iterator;

		Map();
		Map(Container const &);
		Map(Map const &);
		Map(MapPtr const &);
		virtual ~Map();

		Map & operator=(Map);

		ValueType & operator[](KeyType const &);

		void insert(KeyType const &, ValueType const &);
		std::size_t size() const;

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		bool has_key(KeyType const &);
		iterator find(KeyType const &);
		const_iterator find(KeyType const &) const;

		virtual	MapPtr ToMap() const;
	protected:
		Container m_value;
	};
}