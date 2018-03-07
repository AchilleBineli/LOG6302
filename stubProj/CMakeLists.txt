# Minimum CMake required
cmake_minimum_required(VERSION 2.8)

# Project
project(Polyland)

# does this system provide the log and exp functions?
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
 
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/main.cpp
src/AttaqueMagiqueConfusion.cpp src/Creature.cpp src/Dresseur.h src/PolyLand.h src/AttaqueMagiqueConfusion.h src/Creature.h	src/Pouvoir.cpp src/AttaqueMagique.h src/CreatureMagique.cpp src/ObjetMagique.cpp src/Pouvoir.h src/AttaqueMagiquePoison.cpp src/CreatureMagique.h src/ObjetMagique.h src/AttaqueMagiquePoison.h	     src/Dresseur.cpp src/PolyLand.cpp
)
add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS )
add_executable(Polyland ${SOURCE_FILES})
target_link_libraries (Polyland  ${EXTRA_LIBS})


target_link_libraries(
        ${PROJECT_NAME}
        pthread
        dl
        z
)
