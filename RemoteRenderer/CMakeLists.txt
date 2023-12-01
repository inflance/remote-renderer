cmake_minimum_required (VERSION 3.8)

project ("RemoteRenderer")

find_package(spdlog REQUIRED)

find_package(nlohmann_json REQUIRED)

find_package(imgui REQUIRED)

find_package(glfw3 REQUIRED)

file(GLOB_RECURSE  CPP_HEADER_FILES "./*.h" "./*.hpp")
file(GLOB_RECURSE  CPP_SOURCE_FILES "./*.cpp" "./*.cc")

add_executable (RemoteRenderer ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES} )

target_link_libraries(RemoteRenderer PRIVATE imgui::imgui glfw nlohmann_json::nlohmann_json  spdlog::spdlog)
