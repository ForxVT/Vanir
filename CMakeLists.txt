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

cmake_minimum_required(VERSION 3.14)

project(Vanir LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(VANIR_BUILD_JSON "Enable this to build the JSON utilities" OFF)

if (VANIR_BUILD_JSON)
    find_package(nlohmann_json 3.2.0 REQUIRED)
endif()

add_library(Vanir
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Common.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/CommandLine/CommandLineOption.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/CommandLine/CommandLineOptionTypes.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/CommandLine/CommandLineUtils.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Event/Callback.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Event/Invokable.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Factory/Factory.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Factory/FactoryRegister.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Factory/GenericFactory.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/File/FileUtils.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/JSON/JSONFile.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Logger/Logger.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Logger/LoggerColor.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Logger/LoggerColors.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Logger/LoggerTypes.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Maths/MathsUtils.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/Singleton/Singleton.h
        ${PROJECT_SOURCE_DIR}/Include/Vanir/String/StringUtils.h
        ${PROJECT_SOURCE_DIR}/Sources/File/FileUtils.cpp
        ${PROJECT_SOURCE_DIR}/Sources/JSON/JSONFile.cpp
        ${PROJECT_SOURCE_DIR}/Sources/Logger/LoggerColor.cpp
        ${PROJECT_SOURCE_DIR}/Sources/Logger/Logger.cpp
        ${PROJECT_SOURCE_DIR}/Sources/Maths/MathsUtils.cpp
        ${PROJECT_SOURCE_DIR}/Sources/String/StringUtils.cpp
        ${PROJECT_SOURCE_DIR}/Sources/CommandLine/CommandLineOption.cpp
        ${PROJECT_SOURCE_DIR}/Sources/CommandLine/CommandLineUtils.cpp)

target_include_directories(Vanir PRIVATE ${PROJECT_SOURCE_DIR}/Include/)

if (VANIR_BUILD_JSON)
    target_compile_definitions(Vanir PRIVATE VANIR_BUILD_JSON)
    target_link_libraries(Vanir PRIVATE nlohmann_json::nlohmann_json)
endif()