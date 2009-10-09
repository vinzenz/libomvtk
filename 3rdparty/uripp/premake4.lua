solution "uripp"
    configurations {"Debug", "Release"}
    
    project "uripp"
        kind "StaticLib"
        language "C++"        
        files { "src/*.cpp" }
        targetdir "../lib"        
        configuration "Release"
            flags {"OptimizeSpeed"}
