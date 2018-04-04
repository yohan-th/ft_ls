cmake_minimum_required(VERSION 3.9)
project(ft_ls)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -Werror -Wall")

file(GLOB LIBFT
        Libft/*/*.c)

file(GLOB SRCS
        Sources/*.c
        Include/*.h)

add_executable(ft_ls ${SRCS} ${LIBFT})
