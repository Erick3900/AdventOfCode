cmake_minimum_required(VERSION 3.10)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    AOC-2022
    VERSION 0.0.1
    DESCRIPTION ""
    LANGUAGES CXX
)

set(PROJECT_AUTHOR "Erick Saúl")
set(PROJECT_AUTHOR_GITHUB "@Erick3900")

add_subdirectory(configured_files)

find_package(fmt CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "*/solution.cpp")

foreach(FILE IN LISTS SOURCES)
    cmake_path(GET FILE PARENT_PATH FILE_PARENT)
    cmake_path(GET FILE_PARENT STEM PROBLEM_NAME)

    add_executable(
        ${PROBLEM_NAME}
            ${FILE}
    )
    
    target_link_libraries(
        ${PROBLEM_NAME} PRIVATE
            fmt::fmt
            range-v3::range-v3
            cryptopp::cryptopp
            nlohmann_json::nlohmann_json
    )

    set_target_properties(
        ${PROBLEM_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${FILE_PARENT}
            RUNTIME_OUTPUT_NAME "solution"
            SUFFIX ""
    )

    target_include_directories(
        ${PROBLEM_NAME} PRIVATE
            ${CMAKE_BINARY_DIR}/configured_files/include
    )
endforeach()

