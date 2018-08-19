cmake_minimum_required(VERSION 3.12)
project(File_Maker)

set(CMAKE_CXX_STANDARD 17)

add_executable(File_Maker main.cpp Source.h ArticleData.cpp ArticleData.h Source.cpp CurlWrapper.cpp CurlWrapper.h FileGenerator.cpp FileGenerator.h)
target_link_libraries(File_Maker curl pthread)
