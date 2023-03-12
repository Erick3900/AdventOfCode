cmake_minimum_required(VERSION 3.10)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conan)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    AOC-2016
    VERSION 0.0.1
    DESCRIPTION ""
    LANGUAGES CXX
)

find_package(fmt CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "Day*/p*/solution.cpp")

foreach(FILE IN LISTS SOURCES)
    cmake_path(GET FILE PARENT_PATH FILE_PARENT)
    cmake_path(GET FILE_PARENT STEM PROBLEM_PART)
    cmake_path(GET FILE_PARENT PARENT_PATH PROBLEM_PATH)
    cmake_path(GET PROBLEM_PATH STEM PROBLEM_DAY)

    add_executable(
        ${PROBLEM_DAY}-${PROBLEM_PART}
            ${FILE}
    )
    
    target_link_libraries(
        ${PROBLEM_DAY}-${PROBLEM_PART} PRIVATE
            fmt::fmt
            range-v3::range-v3
            cryptopp::cryptopp
            nlohmann_json::nlohmann_json
    )

    set_target_properties(
        ${PROBLEM_DAY}-${PROBLEM_PART} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${FILE_PARENT}
            RUNTIME_OUTPUT_NAME "solution"
            SUFFIX ""
    )
endforeach()

