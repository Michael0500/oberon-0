cmake_minimum_required(VERSION 3.23)
project(oberon_0 C)

set(CMAKE_C_STANDARD 99)

add_executable(oberon_0 o.c text.c location.c error.c table.c scan.c pars.c table.c ovm.c gen.c)
