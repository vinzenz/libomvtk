all_includes = {
	"../3rdparty/uuid",
	"../3rdparty/logging",
	"../3rdparty/uripp/src",
	"../3rdparty/tinyxml",
	"../3rdparty/tinyjson",
	"../3rdparty/utf8_cpp",
	"../3rdparty/libnetpp",
	"../3rdparty/tut-framework",
}

solution "omvtk"
	configurations { "Debug", "Release" }

	project "omvtk"
		kind "StaticLib"
		language "C++"
		basedir "libomvtk"
		targetdir "out/lib"
		includedirs(all_includes)
		files { "libomvtk/**.h", "libomvtk/**.cpp" }
		
		configuration "windows"
			flags { "StaticRuntime" }
			defines { "WIN32", "LIVOMVTK_WINDOWS" }

		configuration "vs*"
		--- We always want symbols for VC
			flags { "Symbols" }

		configuration { "gmake" }
			buildoptions { "-ansi", "-pedantic", "-W -Wall -Wno-long-long", "-std=c++98" }

		configuration "Debug"
			defines { "_DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }

	project "omvtk_unittest"
		kind "ConsoleApp"
		language "C++"
		basedir "unit_tests"
		targetdir "out/bin"
		links { "omvtk"} --- , "boost_filesystem-mt",  "boost_system-mt",  "boost_thread-mt"}
		libdirs { "../3rdparty/lib" }
		includedirs(all_includes)

		files { "unit_tests/**.h", "unit_tests/**.cpp" }
		
		configuration "windows"
			flags { "StaticRuntime" }
			defines { "WIN32", "LIVOMVTK_WINDOWS" }

		configuration "vs*"
		--- We always want symbols for VC
			flags { "Symbols" }

		configuration { "gmake" }
			buildoptions { "-ansi", "-pedantic", "-W -Wall -Wno-long-long", "-std=c++98" }

		configuration "Debug"
			defines { "_DEBUG" }
			flags { "Symbols" }
			links { "urippd", "ticppd" }

		configuration "Release"
			links { "uripp", "ticpp" }
			defines { "NDEBUG" }

			
