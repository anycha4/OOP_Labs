cmake_minimum_required(VERSION 3.24)

project(oop_labs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4 /WX /permissive-)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    )
    add_link_options(
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
endif()

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp"
)

if(NOT CORE_SOURCES)
    set(CORE_PLACEHOLDER "${CMAKE_CURRENT_BINARY_DIR}/core_placeholder.cpp")
    file(WRITE "${CORE_PLACEHOLDER}" "")
    set(CORE_SOURCES "${CORE_PLACEHOLDER}")
endif()

add_library(core_lib STATIC ${CORE_SOURCES})
target_include_directories(core_lib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/core"
)
target_compile_features(core_lib PUBLIC cxx_std_20)

add_executable(app app/main.cpp)
target_link_libraries(app PRIVATE core_lib)
target_compile_features(app PRIVATE cxx_std_20)

include(CTest)

if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()
