cmake_minimum_required(VERSION 3.21)

# Set your project name. This will be the name of your SKSE .dll file.
project(SkyrimLightsMenu VERSION 0.0.1 LANGUAGES CXX)


# CHANGE ME IF YOU DON'T USE MO2'!!!
set(OUTPUT_FOLDER "C:/Modding/MO2/mods/Skyrim Lights Menu")

# Get the .cpp files from your src/ directory
# to be passed into add_commonlibsse_plugin
file(GLOB_RECURSE source_files src/*.cpp)

# Setup your SKSE plugin as an SKSE plugin!
find_package(CommonLibSSE CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog REQUIRED CONFIG)

add_compile_definitions(SKYRIM_AE)

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

add_library(
    ${PROJECT_NAME} 
    SHARED 
    ${source_files} 
    plugin.cpp 
    ${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23) # <--- use C++23 standard
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h) # <--- PCH.h is required!
target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
        include
        ${CMAKE_CURRENT_BINARY_DIR}/include
)



target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CommonLibSSE::CommonLibSSE
        spdlog::spdlog
        imgui::imgui
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
        VERBATIM
    )

    # If you perform a "Debug" build, also copy .pdb file (for debug symbols)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(
            TARGET "${PROJECT_NAME}"
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
            VERBATIM
        )
    endif()
endif()
