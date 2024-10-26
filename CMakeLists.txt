cmake_minimum_required(VERSION 3.30.0)
project(miniftp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
aux_source_directory(./src ftp_src)

add_executable(miniftp ${ftp_src})


find_package(asio CONFIG REQUIRED)
target_link_libraries(miniftp PRIVATE asio::asio)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(miniftp PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(miniftp PRIVATE ./include)
