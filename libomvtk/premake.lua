project.name = "libvw++"

project.config["Debug"].bindir = "bin/debug"
project.config["Release"].bindir = "bin/release"
project.config["Debug"].libdir = "lib/debug"
project.config["Release"].libdir = "lib/release"


addoption("compiler_flags", "Additional C++ Compiler flags (like alternative Include paths")
addoption("linker_flags", "Additional Linker flags (like alternative Library paths")

dopackage("scripts/unit_tests.lua")
dopackage("scripts/libvw.lua")
dopackage("scripts/packetgen.lua")
dopackage("scripts/nettestenv.lua")

