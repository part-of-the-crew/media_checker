cmake_minimum_required(VERSION 3.16)

project(media_checker VERSION 1.0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g -std=c++23")
set(CMAKE_CXX_COMPILER g++-13)

find_library(-lcrypto REQUIRED)

#target_include_directories(media_checker PUBLIC /usr/include)

#set( REQUIRED_LIBRARIES crypto)

#find_library(CRYPTO crypto HINTS /usr/local/lib REQUIRED)

#Вызываем встроенный скрипт FindBullet.cmake
#find_package(crypto REQUIRED)

#Добавляем пути поиска заголовков к цели my_app
#target_include_directories(media_checker ${CRYPTO_INCLUDE_DIRS})

#Добавляем список библиотек для компоновки с целью my_app
#target_link_libraries(media_checker ${CRYPTO_LIBRARIES})

#set(CRYPTO_DIR /lib/x86_64-linux-gnu/libcrypto.a)


file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.h"
        )

#message(++++PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}", ${all_SRCS})

add_executable(media_checker ${all_SRCS})
target_link_libraries(media_checker -lcrypto)
