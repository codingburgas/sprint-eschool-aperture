-- ADD EXTERNAL LIBRARIES HERE:
local serverLibraries = {
	"crow",
	"sqlite3",
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
		if os.isfile("packages/" .. library .. "_x64-windows/lib/" .. library .. ".lib") then links(library) end
	end)

	-- Copy dlls to exe's directory
	table.foreachi(os.matchfiles("../packages/*/bin/*.dll"), function(dll)
		prebuildcommands("{COPYFILE} %[" .. dll .. "] %[%{cfg.buildtarget.directory}/" .. path.getname(dll) .. "]")
	end)

	-- Return to root directory
	os.chdir("..")
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
	includedirs "vcpkg/packages/*/include"
	libdirs     "vcpkg/packages/*/lib"