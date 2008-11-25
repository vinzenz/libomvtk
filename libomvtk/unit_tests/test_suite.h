#ifndef GUARD_LIBOMVTK_UNIT_TESTS_H_INCLUDED
#define GUARD_LIBOMVTK_UNIT_TESTS_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <tut/tut.hpp>
#include <boost/preprocessor/cat.hpp>

#define DEFINE_TEST_GROUP(DATATYPE,GROUPNAME) \
	typedef test_group<DATATYPE> tg; \
	tg BOOST_PP_CAT(test_group_,DATATYPE)(GROUPNAME); \
	typedef tg::object object

#define DEF_TEST(NR) \
	template<> \
	template<> \
	void object::test<NR>()

#endif //GUARD_LIBOMVTK_UNIT_TESTS_H_INCLUDED
