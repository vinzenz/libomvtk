
package.name = "omvtk"
package.kind = "lib"
package.language = "c++"
package.config["Debug"].objdir = "obj/debug/libomvtk"
package.config["Release"].objdir = "obj/release/libomvtk"
package.buildflags = { "optimize-speed"}


package.includepaths = { 
	"../../3rdparty/uuid",
	"../../3rdparty/logging"
}

AddCompFlags = ""
if(options["compiler_flags"]) then
    AddCompFlags = options["compiler_flags"]
end
 
if (linux) then
    package.buildoptions = { "-W -Wall -Wno-long-long --std=c++98 -pedantic -O3 " , AddCompFlags }
    package.defines = { "LIBOMVTK_LINUX" }
end
if (windows) then
    package.buildflags = { "static-runtime" }
    package.defines = { "WIN32", "LIBOMVTK_LINUX" }
    package.config["Debug"].defines = { "_DEBUG" }
    package.config["Release"].defines = { "NDEBUG" }
end

package.files = { 
    matchrecursive("../libomvtk/*.cpp", "../libomvtk/*.h" )
}

