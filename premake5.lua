workspace "Luna"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Luna/vendor/GLFW/include"
IncludeDir["Glad"] = "Luna/vendor/Glad/include"
IncludeDir["ImGui"] = "Luna/vendor/imgui"

group "Dependencies"
 	include "Luna/vendor/GLFW"
 	include "Luna/vendor/Glad"
 	include "Luna/vendor/imgui"

 group ""

project "Luna"
    location "Luna"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lnpch.h"
    pchsource "Luna/src/lnpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }
    
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
            "LN_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }
    
    filter "configurations:Debug"
        defines "LN_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        runtime "Release"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"    
    language "C++"
    staticruntime "off"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Luna/vendor/spdlog/include",
        "Luna/src"
    }

    links
    {
        "Luna"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "LN_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        runtime "Release"
        symbols "On"
