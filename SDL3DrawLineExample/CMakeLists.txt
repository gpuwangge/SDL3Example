cmake_minimum_required(VERSION 3.20)
SET(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")
project(DrawLineSDL3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")

#Set SRC, build and bin folders
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories($ENV{INCLUDE})

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/)     

#an alternative way is to link libs for all t argets
#link_libraries(SDL3) 

#add all files from SRC folder
add_executable(${PROJECT_NAME} ${SRC}) 
 
target_link_libraries( ${PROJECT_NAME} SDL3)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SDL3.dll
    DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)


