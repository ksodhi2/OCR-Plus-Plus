cmake_minimum_required(VERSION 3.11...3.16)
if (${CMAKE_VERSION} VERSION_LESS 3.11)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

cmake_policy(SET CMP0054 NEW)

message("CMake Version: ${CMAKE_VERSION}.")

# This is a magic line. Don't mess with this.
# Essentially, each library needs to be built either dynamically or statically,
# but it needs to be built in a consistent manner. This is for MSVC.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(FinalProject
        VERSION 1.0
        DESCRIPTION "CS 126 Final Project"
        LANGUAGES CXX)

find_package(OpenCV REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


include(ExternalProject)
# Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

set(CMAKE_CXX_STANDARD 14)
# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
# You can set a release configuration through CLion.
set(CMAKE_BUILD_TYPE Debug)
# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)
# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Allow code coverage.
if("{CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
    OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
    message("Building with llvm Code Coverage Tools")
    set(CMAKE_CXX_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    message("Building with lcov Code Coverage Tools")
    set(CMAKE_CXX_FLAGS "--coverage")
endif()

# Docs only available if this is the main app
find_package(Doxygen)
if(Doxygen_FOUND)
    add_subdirectory(docs)
else()
    # This is the message that some of you were seeing. It's not really an error or anything.
    message(STATUS "Doxygen not found, not building docs")
endif()


# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

# The library code is here.
add_subdirectory(src)

# The Cinder executable code is here.
add_subdirectory(apps)

# The tests are here.
add_subdirectory(tests)

############## Third-party Libraries #####################

# Testing library. Header-only.
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.11.1
)

# Adds catch2 library. This is a header only library.
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    # This is overkill since we only need a single file. Though it is a clean solution.
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

FetchContent_Declare(
        portable-file-dialogs
        GIT_REPOSITORY https://github.com/ksodhi2/portable-file-dialogs.git
)

# Adds catch2 library. This is a header only library.
FetchContent_GetProperties(portable-file-dialogs)
if(NOT portable-file-dialogs_POPULATED)
    FetchContent_Populate(portable-file-dialogs)
    # This is overkill since we only need a single file. Though it is a clean solution.
    add_library(portable-file-dialogs INTERFACE)
    target_include_directories(portable-file-dialogs INTERFACE ${portable-file-dialogs_SOURCE_DIR}/include)
endif()

if(NOT TARGET OpenMP::OpenMP_CXX)
    find_package(Threads REQUIRED)
    add_library(OpenMP::OpenMP_CXX IMPORTED INTERFACE)
    set_property(TARGET OpenMP::OpenMP_CXX
            PROPERTY INTERFACE_COMPILE_OPTIONS ${OpenMP_CXX_FLAGS})
    # Only works if the same flag is passed to the linker; use CMake 3.9+ otherwise (Intel, AppleClang)
    set_property(TARGET OpenMP::OpenMP_CXX
            PROPERTY INTERFACE_LINK_LIBRARIES ${OpenMP_CXX_FLAGS} Threads::Threads)
endif()
target_link_libraries(mylibrary OpenMP::OpenMP_CXX)

# Add more CMake libraries here ...

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(mylibrary ${OpenCV_LIBS} ${OpenMP_CXX})
target_link_libraries(test ${OpenCV_LIBS})
target_link_libraries(cinder-OCR++ ${OpenCV_LIBS})