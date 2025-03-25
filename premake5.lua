-- ADD EXTERNAL LIBRARIES HERE:
local serverLibraries = {
	"crow",
	"sqlite-modern-cpp",
	"jwt-cpp",
	"cpr",
}

-- User-configurable code ends here.

local function cloneExternalLibraries()
	-- Clone vcpkg package manager
	os.execute("git clone --depth=1 https://github.com/microsoft/vcpkg.git")
	os.chdir("vcpkg")
	os.execute("bootstrap-vcpkg.bat")

	-- Install each external library
	table.foreachi(serverLibraries, function(library)
		os.execute("vcpkg install " .. library)
	end)

	-- Add bcrypt (not from vcpkg)
	if not os.isdir("packages/bcrypt") then
		os.execute("git clone --depth=1 https://github.com/hilch/Bcrypt.cpp.git packages/bcrypt")
		os.rename("packages/bcrypt/include/bcrypt.h", "packages/bcrypt/include/bcryptcpp.h")
		local code = io.readfile("packages/bcrypt/src/bcrypt.cpp")
		code = table.implode(string.explode(code, "bcrypt.h"), "", "", "bcryptcpp.h")
		io.writefile("packages/bcrypt/src/bcrypt.cpp", code)
	end
	includedirs "packages/bcrypt/src"
	files "packages/bcrypt/src/*"

	-- Link libraries
	table.foreachi(os.matchfiles("packages/*/lib/*.lib"), function(lib)
		links(path.getbasename(lib))
	end)

	-- Copy dlls to exe's directory
	table.foreachi(os.matchfiles("packages/*/bin/*.dll"), function(dll)
		prebuildcommands("{COPYFILE} %[" .. path.getabsolute(dll) .. "] %[%{cfg.buildtarget.directory}/" .. path.getname(dll) .. "]")
	end)

	-- Return to root directory
	os.chdir("..")

	-- Define where external library headers and code are
	includedirs "vcpkg/packages/*/include"
	libdirs     "vcpkg/packages/*/lib"
end

workspace "aperture-notepad"
	configurations { "Debug", "Release" }

	system "Windows"
	architecture "x86_64"

	language "C++"
	cppdialect "C++23"

project "aperture-notepad"
	kind "ConsoleApp"

	location "sprint-eschool-aperture"

	files "sprint-eschool-aperture/*"

	cloneExternalLibraries()