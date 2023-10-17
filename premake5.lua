-- premake5.lua

workspace "3DOpenSimpleMaze"
    location "."
    configurations { "Debug", "Release" }
    platforms { "Win32", "x64" }

project "3DOpenGLEntry"
    kind "ConsoleApp"
    language "C++"
    location "."
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}"
    files { "./include/headers/**.h", "./src/**.cpp", "./src/glad.c" } -- Add glad.c here

    externalincludedirs {  
        "./include/headers",
        "./dependencies/include"
    }

    vpaths {
        ["Headers"] = { 
            "./include/headers",
            "./dependencies/include",
        }
    }

    includedirs {
        "./include/headers",
        "./dependencies/include",
    }

    links {
        "glfw3",
        "opengl32",
        "user32",
        "gdi32",
        "shell32",        
    }

    libdirs { 
        "./dependencies/lib",
    }

    syslibdirs {   
        "./dependencies/lib",
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    -- Add these lines to set the VC++ directories
    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"

    filter { "platforms:x64" }
        system "Windows"
        architecture "x86_64"

    filter { }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

        filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"