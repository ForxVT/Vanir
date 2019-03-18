# ----------------------------------------------------------------
# CMake build file for the Vanir project.
# ----------------------------------------------------------------
cmake_minimum_required(VERSION 3.13)

project(Vanir)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../Build/Lib/Vanir/${CMAKE_CXX_COMPILER_ID}_${CMAKE_SIZEOF_VOID_P}_${CMAKE_BUILD_TYPE})

set(VANIR_INCLUDES
        ${PROJECT_SOURCE_DIR}/../
        ${PROJECT_SOURCE_DIR}/../Dependencies/JSON/include/)
if(UNIX AND NOT APPLE)
    set(VANIR_LIBRARIES ${VANIR_LIBRARIES} stdc++fs)
endif()

add_library(Vanir
        ${PROJECT_SOURCE_DIR}/Callback.h
        ${PROJECT_SOURCE_DIR}/Factory.h
        ${PROJECT_SOURCE_DIR}/FactoryRegister.h
        ${PROJECT_SOURCE_DIR}/File.h
        ${PROJECT_SOURCE_DIR}/FileUtils.cpp
        ${PROJECT_SOURCE_DIR}/FileUtils.h
        ${PROJECT_SOURCE_DIR}/GenericFactory.h
        ${PROJECT_SOURCE_DIR}/Invokable.h
        ${PROJECT_SOURCE_DIR}/Logger.cpp
        ${PROJECT_SOURCE_DIR}/Logger.h
        ${PROJECT_SOURCE_DIR}/Macros.h
        ${PROJECT_SOURCE_DIR}/MathsUtils.cpp
        ${PROJECT_SOURCE_DIR}/MathsUtils.h
        ${PROJECT_SOURCE_DIR}/Singleton.h
        ${PROJECT_SOURCE_DIR}/StringUtils.cpp
        ${PROJECT_SOURCE_DIR}/StringUtils.h
        ${PROJECT_SOURCE_DIR}/LoggerColor.cpp
        ${PROJECT_SOURCE_DIR}/LoggerColor.h
        ${PROJECT_SOURCE_DIR}/LoggerColors.h
        ${PROJECT_SOURCE_DIR}/LoggerTypes.h
        ${PROJECT_SOURCE_DIR}/JSONFile.cpp
        ${PROJECT_SOURCE_DIR}/JSONFile.h
        ${PROJECT_SOURCE_DIR}/CommandLineOption.h
        ${PROJECT_SOURCE_DIR}/CommandLineOption.cpp
        ${PROJECT_SOURCE_DIR}/CommandLineOptionTypes.h
        ${PROJECT_SOURCE_DIR}/CommandLineUtils.cpp
        ${PROJECT_SOURCE_DIR}/CommandLineUtils.h)

target_include_directories(Vanir PUBLIC ${VANIR_INCLUDES})
target_link_libraries(Vanir LINK_PUBLIC ${VANIR_LIBRARIES})
