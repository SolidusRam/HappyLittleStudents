cmake_minimum_required(VERSION 3.26)
project(HappyLittleStudents C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HappyLittleStudents
        main.c
        Strutture/Strutture.h
        Input/file_reading.h
        Input/file_reading.c
        Strutture/Strutture.c
        Game/game.c
        Game/game.h
        Input/user_input.c
        Input/user_input.h
        Output/stampe.c
        Output/stampe.h
        Input/salvataggi.c
        Input/salvataggi.h
        Game/game_mechanics.c
        Game/game_mechanics.h
        Game/effects.c
        Game/effects.h
)
