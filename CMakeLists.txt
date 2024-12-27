cmake_minimum_required(VERSION 3.21)
set(AE_VERSION 1)

option(BUILD_SKYRIMVR "Build for Skyrim VR" OFF)
option(BUILD_SKYRIMAE "Build for Skyrim AE" OFF)



macro(set_from_environment VARIABLE)
	if (NOT DEFINED ${VARIABLE} AND DEFINED ENV{${VARIABLE}})
		set(${VARIABLE} $ENV{${VARIABLE}})
	endif ()
endmacro()

macro(find_commonlib_path)
	if (CommonLibName AND NOT ${CommonLibName} STREQUAL "")
		# Check extern
		find_path(CommonLibPath
		include/REL/Relocation.h
		PATHS extern/${CommonLibName})
		if (${CommonLibPath} STREQUAL "CommonLibPath-NOTFOUND")
			#Check path
			set_from_environment(${CommonLibName}Path)
			set(CommonLibPath ${${CommonLibName}Path})
		endif()
	endif()
endmacro()

set_from_environment(VCPKG_ROOT)
if(BUILD_SKYRIMAE)
	add_compile_definitions(SKYRIM_AE)
	add_compile_definitions(SKYRIM_SUPPORT_AE)
	set(CommonLibName "CommonLibSSE")
	set_from_environment(SkyrimAEPath)
	set(SkyrimPath ${SkyrimAEPath})
	set(SkyrimVersion "Skyrim AE")
	set(VERSION ${VERSION}.${AE_VERSION})
elseif(BUILD_SKYRIMVR)
	add_compile_definitions(SKYRIMVR)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	set(CommonLibName "CommonLibVR")
	set_from_environment(SkyrimVRPath)
	set(SkyrimPath ${SkyrimVRPath})
	set(SkyrimVersion "Skyrim VR")
	set(VERSION ${VERSION}.${VR_VERSION})
else()
	set(CommonLibName "CommonLibSSE")
	set_from_environment(Skyrim64Path)
	set(SkyrimPath ${Skyrim64Path})
	set(SkyrimVersion "Skyrim SSE")
endif()


find_commonlib_path()

message(
	STATUS
	"Building ${NAME} ${VERSION} for ${SkyrimVersion} at ${SkyrimPath} with ${CommonLibName} at ${CommonLibPath}."
)

if (DEFINED VCPKG_ROOT)
	set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
	set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
else ()
	message(
		WARNING
		"Variable VCPKG_ROOT is not set. Continuing without vcpkg."
	)
endif ()

set(Boost_USE_STATIC_RUNTIME OFF CACHE BOOL "")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "")

# Set your project name. This will be the name of your SKSE .dll file.
project(SkyrimLightsMenu VERSION 0.0.1 LANGUAGES CXX)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.h.in
	${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
	@ONLY
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.rc.in
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	@ONLY
)

if (DEFINED CommonLibPath AND NOT ${CommonLibPath} STREQUAL "" AND IS_DIRECTORY ${CommonLibPath})
	add_subdirectory(${CommonLibPath} ${CommonLibName})
else ()
	message(
		FATAL_ERROR
		"Variable ${CommonLibName}Path is not set or in extern/. ${CommonLibPath}"
	)
endif()





# CHANGE ME IF YOU DON'T USE MO2'!!!
set(OUTPUT_FOLDER "C:/Modding/MO2/mods/Skyrim Lights Menu")

# Get the .cpp files from your src/ directory
# to be passed into add_commonlibsse_plugin
file(GLOB_RECURSE source_files src/*.cpp)

find_package(imgui CONFIG REQUIRED)
#find_package(spdlog REQUIRED CONFIG)
find_package(nlohmann_json CONFIG REQUIRED)

add_compile_definitions(SKYRIM_AE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()




add_library(
    ${PROJECT_NAME} 
    SHARED 
    ${source_files}
	${header_files}
    plugin.cpp 
    ${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23) # <--- use C++23 standard
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h) # <--- PCH.h is required!
target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include
)



target_link_libraries(
	${PROJECT_NAME}
    PRIVATE
        ${CommonLibName}::${CommonLibName}
        imgui::imgui
        nlohmann_json 
        nlohmann_json::nlohmann_json
)


# When your SKSE .dll is compiled, this will automatically copy the .dll into your mods folder.
# Only works if you configure DEPLOY_ROOT above (or set the SKYRIM_MODS_FOLDER environment variable)
if(DEFINED OUTPUT_FOLDER)
    # If you specify an <OUTPUT_FOLDER> (including via environment variables)
    # then we'll copy your mod files into Skyrim or a mod manager for you!

    # Copy the SKSE plugin .dll files into the SKSE/Plugins/ folder
    set(DLL_FOLDER "${OUTPUT_FOLDER}/SKSE/Plugins")

    message(STATUS "SKSE plugin output folder: ${DLL_FOLDER}")

    add_custom_command(
        TARGET "${PROJECT_NAME}"
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${DLL_FOLDER}"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
		COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
        VERBATIM
    )
endif()
