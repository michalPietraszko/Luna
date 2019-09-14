workspace "Luna"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Luna"
    location "Luna"
    kind "SharedLib"
    language "C++"

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
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
            "LN_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter "configurations:Debug"
        defines "LN_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"    
    language "C++"

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
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "LN_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        symbols "On"
