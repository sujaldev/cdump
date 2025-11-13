cmake_minimum_required(VERSION 3.31)
project(cdump)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_executable(seachat-client seachat/client.c)
add_executable(browser web-browser/http.c)
add_executable(tictactoe tictactoe/main.cpp)
