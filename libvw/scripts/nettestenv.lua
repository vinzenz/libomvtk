package.name = "nettestenv"
package.kind = "exe"
package.language = "c++"

package.files = { 
   matchrecursive("../nettestenv/*.cpp", "../nettestenv/*.h")
}

package.config["Debug"].objdir = "obj/debug/nettestenv"
package.config["Release"].objdir = "obj/release/nettestenv"
package.buildflags = { "optimize-speed"}
package.includepaths = { 
	"../../3rdparty/logging"
} 

package.libpaths =  {
    "../../3rdparty/lib"
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
    package.defines = { "LIBVW_LINUX" }
    package.linkoptions = { AddLinkFlags }
    package.config["Debug"].defines = { "LIBVW_DEBUG" }
	SSLLIB1D = "ssl"
	SSLLIB1 = "ssl"
	SSLLIB2D = "ssl"
	SSLLIB2 = "ssl"
end
if (windows) then
    package.buildflags = { "optimize-speed", "static-runtime" }
    package.defines = { "WIN32", "POCO_NO_AUTOMATIC_LIBS", "LIBVW_WINDOWS" }
    package.config["Debug"].defines = { "_DEBUG" }
    package.config["Release"].defines = { "NDEBUG", "LIBVW_DEBUG"}
	SSLLIB1 = "ssleay32MT"
	SSLLIB1D = "ssleay32MTd"
	SSLLIB2 = "libseay32MT"
	SSLLIB2D = "libseay32MTd"
end



package.config["Debug"].links = { "vw++", "boost_system-mt", "ticppd", "boost_thread-mt", "boost_filesystem-mt", SSLLIB1D, SSLLIB2D }
package.config["Release"].links = { "vw++", "boost_system-mt", "ticpp", "boost_thread-mt", "boost_filesystem-mt" , SSLLIB1, SSLLIB2 }

