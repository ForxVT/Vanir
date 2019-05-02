#==================================================================================#
#                                                                                  #
#  Copyright (c) 2019 Hugo Kindel <kindelhugo@gmail.com>                           #
#                                                                                  #
#  This file is part of the Vanir project.                                         #
#  Licensed under MIT License:                                                     #
#                                                                                  #
#  Permission is hereby granted, free of charge, to any person obtaining           #
#  a copy of this software and associated documentation files (the "Software"),    #
#  to deal in the Software without restriction, including without limitation       #
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,        #
#  and/or sell copies of the Software, and to permit persons to whom the           #
#  Software is furnished to do so, subject to the following conditions:            #
#                                                                                  #
#  The above copyright notice and this permission notice shall be included in      #
#  all copies or substantial portions of the Software.                             #
#                                                                                  #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   #
#  SOFTWARE.                                                                       #
#                                                                                  #
#==================================================================================#

#===--------- Vanir Build System -----------------------------------------------===#
#                                                                                  #
# CMake build file for Vanir.                                                      #
#                                                                                  #
#==================================================================================#

# TODO: Better CMake handling, with install.
cmake_minimum_required(VERSION 3.14)

project(Vanir LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

include(Config)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(VANIR_SHARED "Enable this to build Vanir as a shared library (static otherwise)" ON)
option(VANIR_BUILD_JSON "Enable this to build the JSON utilities" OFF)
option(VANIR_BUILD_PROFILER "Enable this to build the profiling macros" ON)

if (VANIR_BUILD_JSON)
    find_package(nlohmann_json 3.2.0 REQUIRED)
endif()

set(VANIR_INCLUDES ${VANIR_INCLUDES} Include/)

if (VANIR_BUILD_PROFILER)
    if (NOT VANIR_EASYPROFILER_INCLUDES)
        message(FATAL_ERROR "You need to specify a EasyProfiler include path")
    endif()

    set(VANIR_INCLUDES ${VANIR_INCLUDES} ${VANIR_EASYPROFILER_INCLUDES})
endif()

if(WIN32)
    set(VANIR_LIBRARIES ${VANIR_LIBRARIES} rpcrt4)
endif()
if (VANIR_BUILD_JSON)
    set(VANIR_LIBRARIES ${VANIR_LIBRARIES} nlohmann_json::nlohmann_json)
endif()
if (VANIR_BUILD_PROFILER)
    set(VANIR_LIBRARIES ${VANIR_LIBRARIES} easy_profiler)
endif()

set(VANIR_COMPILEDEFINITIONS
        VANIR_VERSION_MAJOR=${VANIR_VERSION_MAJOR}
        VANIR_VERSION_MINOR=${VANIR_VERSION_MINOR}
        VANIR_VERSION_PATCH=${VANIR_VERSION_PATCH}
        VANIR_VERSION="${VANIR_VERSION_MAJOR}.${VANIR_VERSION_MINOR}.${VANIR_VERSION_PATCH}\\0")

if (VANIR_SHARED)
    set(VANIR_COMPILEDEFINITIONS ${VANIR_COMPILEDEFINITIONS} VANIR_LIB_SHARED)
endif()
if (VANIR_BUILD_JSON)
    set(VANIR_COMPILEDEFINITIONS ${VANIR_COMPILEDEFINITIONS} VANIR_BUILD_JSON)
endif()
if (VANIR_BUILD_PROFILER)
    set(VANIR_COMPILEDEFINITIONS ${VANIR_COMPILEDEFINITIONS} BUILD_WITH_EASY_PROFILER VANIR_BUILD_PROFILER)
endif()

if (WIN32)
    set(VANIR_SOURCES ${VANIR_SOURCES} Include/Vanir/Platform/Windows/Version.rc)
endif()

set(VANIR_SOURCES ${VANIR_SOURCES}
        Include/Vanir/Common.h
        Include/Vanir/CLI/Argument.h
        Include/Vanir/CLI/ArgumentType.h
        Include/Vanir/CLI/CLI.h
        Include/Vanir/Error/Error.h
        Include/Vanir/Error/Exception.h
        Include/Vanir/Error/FatalError.h
        Include/Vanir/Event/ConnectionData.h
        Include/Vanir/Event/Event.h
        Include/Vanir/Event/EventHandle.h
        Include/Vanir/Event/EventInternalData.h
        Include/Vanir/Factory/Factory.h
        Include/Vanir/Factory/FactoryRegister.h
        Include/Vanir/Factory/GenericFactory.h
        Include/Vanir/FileSystem/FileSystem.h
        Include/Vanir/JSON/JSONFile.h
        Include/Vanir/Logger/LogColor.h
        Include/Vanir/Logger/Logger.h
        Include/Vanir/Logger/TerminalColor.h
        Include/Vanir/Math/Math.h
        Include/Vanir/Math/Random.h
        Include/Vanir/Math/Xorshift.h
        Include/Vanir/String/String.h
        Include/Vanir/Utility/Timer.h
        Include/Vanir/Utility/Utils.h
        Sources/CLI/Argument.cpp
        Sources/CLI/CLI.cpp
        Sources/Error/Exception.cpp
        Sources/Error/FatalError.cpp
        Sources/Event/ConnectionData.cpp
        Sources/Event/EventHandle.cpp
        Sources/Event/EventInternalData.cpp
        Sources/FileSystem/FileSystem.cpp
        Sources/JSON/JSONFile.cpp
        Sources/Logger/LogColor.cpp
        Sources/Logger/Logger.cpp
        Sources/Math/Math.cpp
        Sources/Math/Random.cpp
        Sources/Math/Xorshift.cpp
        Sources/String/String.cpp
        Sources/Utility/Timer.cpp
        Sources/Utility/Utils.cpp)

if (VANIR_SHARED)
    add_library(Vanir SHARED ${VANIR_SOURCES})
else()
    add_library(Vanir ${VANIR_SOURCES})
endif()

target_compile_definitions(Vanir PRIVATE ${VANIR_COMPILEDEFINITIONS})
target_include_directories(Vanir PRIVATE ${VANIR_INCLUDES})
target_link_libraries(Vanir PRIVATE ${VANIR_LIBRARIES})