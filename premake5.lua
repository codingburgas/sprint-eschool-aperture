-- ADD EXTERNAL LIBRARIES HERE:
local serverLibraries = {
	"crow",
}

-- User-configurable code ends here.

local function cloneExternalLibraries()
	-- Clone vcpkg package manager
	os.execute("git clone --depth=1 https://github.com/microsoft/vcpkg.git")
	os.chdir("vcpkg")
	os.execute("bootstrap-vcpkg.bat")

	-- Install each external library
	table.foreachi(libraries, function(library)
		os.execute("vcpkg install " .. library)
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

project "vcpkg"
	kind "SharedItems"

	cloneExternalLibraries()

	files { "vcpkg/packages/*/include/*.h", "vcpkg/packages/*/include/*.hpp" }

project "aperture-notepad"
	kind "ConsoleApp"

	location "sprint-eschool-aperture"

	files "sprint-eschool-aperture/*"
	includedirs "vcpkg/packages/*/include"
	links "vcpkg"