cmake_minimum_required(VERSION 3.20)
SET(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")
project(SDL2Experiment)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")

#Set SRC, build and bin folders
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#add all files from SRC folder
add_executable(${PROJECT_NAME} ${SRC}) 

#foreach(cppfile IN LISTS SRC)  
#    get_filename_component(filename ${cppfile} NAME_WE)  
#    add_executable(${filename} ${cppfile})  
#endforeach()  

