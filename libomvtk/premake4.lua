function standard_configuration()
		includedirs  {
			"../3rdparty/uuid",
			"../3rdparty/logging",
			"../3rdparty/uripp/src",
			"../3rdparty/tinyxml",
			"../3rdparty/tinyjson",
			"../3rdparty/utf8_cpp",
			"../3rdparty/libnetpp",
			"../3rdparty/tut-framework",
		}

		--- Define LIBOMVTK_WINDOWS 
		configuration { "windows" }
			defines { 
				"WIN32", 
				"LIBOMVTK_WINDOWS", 
				"_WIN32_WINNT=0x0501",
			}

		--- Define LIBOMVTK_POSIX not on windows
		configuration { "not windows" }
			defines { "LIBOMVTK_POSIX" }

		--- Define LIBOMVTK_LINUX on linux
		configuration { "linux" }
			defines { "LIBOMVTK_LINUX" }

		configuration "vs*"
		--- We always want a static runtime for VS for now
			flags { "StaticRuntime" }
		--- We always want symbols for VC
			flags { "Symbols" }
		--- Disable annoying warnings we know what we do (At least we're supposed to :P)
			defines { 
				"_CRT_SECURE_NO_WARNINGS",
				"_SCL_SECURE_NO_WARNINGS"
			}

		--- Set g++ options
		configuration { "gmake" }
			buildoptions { "-ansi", "-pedantic", "-W -Wall -Wno-long-long", "-std=c++98" }

		--- Set defines for Debug and Release
		--- For Debug enable symbols generation all compilers
		configuration "Debug"
			defines { "_DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
end

solution "omvtk"
	configurations { "Debug", "Release" }

	project "omvtk"
		kind "StaticLib"
		language "C++"
		basedir "libomvtk"
		targetdir "out/lib"
		files { "libomvtk/**.h", "libomvtk/**.cpp" }

		--- This needs to be called before any "configuration" call
		standard_configuration()

	project "omvtk_unittest"
		kind "ConsoleApp"
		language "C++"
		basedir "unit_tests"
		targetdir "out/bin"
		links { "omvtk"} --- , }
		libdirs { "../3rdparty/lib" }
		files { "unit_tests/**.h", "unit_tests/**.cpp" }

		--- This needs to be called before any "configuration" call
		standard_configuration()

		--- Link OpenSSL for Visual Studio
		configuration { "vs*", "Debug" }
			links { "libeay32MTd", "ssleay32MTd" }

		configuration { "vs*", "Release" }
			links { "libeay32MT", "ssleay32MT" }
			
		--- Link OpenSSL for mingw
		configuration { "windows", "gmake" }
			links { "libeay32.a", "ssleay32.a" }

		--- link SSL Library and boost on linux
		--- VC auto links the libs
		configuration { "linux" }
			links { 
				"ssl", 
				"boost_filesystem-mt",  
				"boost_system-mt",  
				"boost_thread-mt",
				"boost_regex-mt"
			}

		--- Link uripp and TinyXML++
		configuration "Debug"
			links { "urippd", "ticppd" }

		configuration "Release"
			defines { "NDEBUG" }

			
