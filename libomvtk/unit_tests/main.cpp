// Disable warning about not being able to generate assignment operator
// we don't copy it anyway
#ifdef _MSC_VER 
#	pragma warning(push)
#	pragma warning(disable: 4512)
#endif

#include <tut/tut.hpp>
#include <tut/tut_reporter.hpp>
#include <iostream>

using std::exception;
using std::cerr;
using std::endl;

namespace tut
{
	test_runner_singleton runner;
}

int main()
{
	tut::reporter reporter;
	tut::runner.get().set_callback(&reporter);

	tut::runner.get().run_tests();

	return !reporter.all_ok();
}

// restoring disabled warning
#ifdef _MSC_VER 
#	pragma warning(pop)
#endif
