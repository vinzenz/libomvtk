solution "uripp"
    configurations {"Debug", "Release"}
    
    project "uripp"
        kind "StaticLib"
        language "C++"        
        files { "src/*.cpp" }
        targetdir "../lib"
	configuration "vs*"
	    flags "StaticRuntime"
	configuration "Release"
	    targetname "uripp"
            flags {"OptimizeSpeed"}
        configuration "Debug"
	    targetname "urippd"
            flags {"Symbols"}

    project "uripp_test"
        kind "ConsoleApp"
        language "C++"        
        files { "test/*.cpp" }
        links "uripp"
	configuration "vs*"
	    flags "StaticRuntime"
        configuration "Release"
            flags {"OptimizeSpeed"}
        configuration "Debug"
            flags {"Symbols"}

