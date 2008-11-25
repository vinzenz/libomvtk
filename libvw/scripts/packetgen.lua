package.name = "packetgen"
package.kind = "exe"
package.language = "c++"

package.files = { 
   "../packetgen/main.cpp"
}

package.config["Debug"].objdir = "obj/debug/packetgen"
package.config["Release"].objdir = "obj/release/packetgen"
package.buildflags = { "optimize-speed"}
package.includepaths = { 
} 

AddCompFlags = ""
if(options["compiler_flags"]) then
    AddCompFlags = options["compiler_flags"]
end

AddLinkFlags = ""
if(options["linker_flags"]) then
    AddLinkFlags = options["linker_flags"]
end

if (linux) then
    package.buildoptions = { "-W -Wall -Wno-long-long -pedantic " , AddCompFlags }
    package.linkoptions = { AddLinkFlags }
end
if (windows) then
    package.buildflags = { "optimize-speed", "static-runtime" }
    package.defines = { "WIN32", "POCO_NO_AUTOMATIC_LIBS" }
    package.config["Debug"].defines = { "_DEBUG" }
    package.config["Release"].defines = { "NDEBUG" }
end

