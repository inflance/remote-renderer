cmake_minimum_required (VERSION 3.8)

project ("RemoteRenderer")

find_package(spdlog REQUIRED)

find_package(nlohmann_json REQUIRED)

find_package(imgui REQUIRED)

find_package(glfw3 REQUIRED)

file(GLOB_RECURSE  CPP_HEADER_FILES "./*.h" "./*.hpp")
file(GLOB_RECURSE  CPP_SOURCE_FILES "./*.cpp" "./*.cc")
foreach(FILE ${CPP_HEADER_FILES})
    file(RELATIVE_PATH RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${FILE}")
    get_filename_component(PARENT_DIR "${RELATIVE_PATH}" DIRECTORY)
    string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

foreach(FILE ${CPP_SOURCE_FILES})
    file(RELATIVE_PATH RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${FILE}")
    get_filename_component(PARENT_DIR "${RELATIVE_PATH}" DIRECTORY)
    string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
    source_group("${GROUP}" FILES "${FILE}")
endforeach()
add_executable (RemoteRenderer ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES} )

target_link_libraries(RemoteRenderer PRIVATE imgui::imgui glfw nlohmann_json::nlohmann_json  spdlog::spdlog)
target_include_directories(RemoteRenderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
