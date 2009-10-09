solution "uripp"
    configurations {"Debug", "Release"}
    
    project "uripp"
        kind "StaticLib"
        language "C++"        
        files { "src/*.cpp" }
        targetdir "../lib"        
        configuration "Release"
            flags {"OptimizeSpeed"}
        configuration "Debug"
            flags {"Symbols"}

    project "uripp_test"
        kind "ConsoleApp"
        language "C++"        
        files { "test/*.cpp" }
        links "uripp"
        configuration "Release"
            flags {"OptimizeSpeed"}
        configuration "Debug"
            flags {"Symbols"}

