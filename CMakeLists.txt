#==================================================================================#
#                                                                                  #
#  Copyright (c) 2019 Hugo Kindel <kindelhugo.pro@gmail.com>                       #
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

cmake_minimum_required(VERSION 3.14)

project(Vanir LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(VANIR_VERSION_MAJOR 1)
set(VANIR_VERSION_MINOR 0)
set(VANIR_VERSION_PATCH 0)
set(VANIR_VERSION_BUILD 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(VANIR_BUILD_JSON "Enable this to build the JSON utilities" ON)
option(VANIR_BUILD_PROFILER "Enable this to build the profiling macros" ON)

set(VANIR_INCLUDES ${VANIR_INCLUDES} Include/)

if (VANIR_BUILD_PROFILER)
    if (NOT VANIR_PROFILER_INCLUDES)
        message(FATAL_ERROR "You need to specify a EasyProfiler include path")
    endif()

    set(VANIR_INCLUDES ${VANIR_INCLUDES} ${VANIR_PROFILER_INCLUDES})
endif()

if (VANIR_BUILD_JSON)
    if (NOT VANIR_JSON_INCLUDES)
        message(FATAL_ERROR "You need to specify a nlhomann JSON include path")
    endif()

    set(VANIR_INCLUDES ${VANIR_INCLUDES} ${VANIR_JSON_INCLUDES})
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
        VANIR_VERSION_BUILD=${VANIR_VERSION_BUILD}
        VANIR_VERSION="${VANIR_VERSION_MAJOR}.${VANIR_VERSION_MINOR}.${VANIR_VERSION_PATCH}.${VANIR_VERSION_BUILD}")

if (VANIR_BUILD_JSON)
    set(VANIR_COMPILEDEFINITIONS ${VANIR_COMPILEDEFINITIONS} VANIR_BUILD_JSON)
endif()
if (VANIR_BUILD_PROFILER)
    set(VANIR_COMPILEDEFINITIONS ${VANIR_COMPILEDEFINITIONS} BUILD_WITH_EASY_PROFILER VANIR_BUILD_PROFILER)
endif()

set(VANIR_SOURCES ${VANIR_SOURCES}
        Include/Vanir/Common.h
        Include/Vanir/CLI/CLI.h
        Include/Vanir/CLI/CLIOption.h
        Include/Vanir/CLI/CLIOptionType.h
        Include/Vanir/CLI/CLIParsingError.h
        Include/Vanir/CLI/CLIParsingResult.h
        Include/Vanir/Error/Error.h
        Include/Vanir/Error/Exception.h
        Include/Vanir/Error/FatalError.h
        Include/Vanir/Factory/Factory.h
        Include/Vanir/FileSystem/FileSystem.h
        Include/Vanir/JSON/JSONFile.h
        Include/Vanir/Logger/LogColor.h
        Include/Vanir/Logger/Logger.h
        Include/Vanir/Logger/TerminalColor.h
        Include/Vanir/Math/Math.h
        Include/Vanir/Math/Random.h
        Include/Vanir/Math/Xorshift.h
        Include/Vanir/Module/Module.h
        Include/Vanir/String/String.h
        Include/Vanir/Utility/NonCopyable.h
        Include/Vanir/Utility/Timer.h
        Include/Vanir/Utility/Utils.h
        Sources/CLI/CLI.cpp
        Sources/CLI/CLIOption.cpp
        Sources/CLI/CLIParsingResult.cpp
        Sources/Error/Exception.cpp
        Sources/Error/FatalError.cpp
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

add_library(Vanir ${VANIR_SOURCES})
target_compile_definitions(Vanir PRIVATE ${VANIR_COMPILEDEFINITIONS})
target_include_directories(Vanir PRIVATE ${VANIR_INCLUDES})
target_link_libraries(Vanir PRIVATE ${VANIR_LIBRARIES})