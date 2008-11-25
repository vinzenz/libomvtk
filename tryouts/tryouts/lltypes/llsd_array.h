#pragma once

#include "llsd_value.h"
#include <vector>

namespace LLSD
{
	struct Array : Value
	{
		typedef std::vector<ValuePtr> Container;

		typedef Container::iterator iterator;
		typedef Container::const_iterator const_iterator;
		typedef Container::value_type value_type;
		typedef Container::const_reference const_reference;
		typedef Container::reference reference;
		typedef Container::pointer pointer;
		typedef Container::const_pointer const_pointer;

		Array();
		Array(Container const & value);
		Array(Array const &);
		Array(ArrayPtr const & array);
		virtual ~Array();

		Array & operator=(Array);

		void push_back(const_reference v);
		void push_back(Value const & v);
		void pop_back();
		
		std::size_t size() const;

		const_iterator begin() const;
		iterator begin();

		const_iterator end() const;
		iterator end();

		void assign(Array const & );

		reference operator[](size_t index);
		const_reference operator[](size_t index) const;

		reference at(size_t index);
		const_reference at(size_t index) const;

		virtual ArrayPtr ToArray() const;
	protected:
		Container m_value;
	};
}