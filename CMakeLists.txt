cmake_minimum_required(VERSION 3.14)

#задаем используемый стандарт —++
set(CMAKE_CXX_STANDARD 17)

#TODO: переименовать проект
project(22210_VB)

#задаем им€ исполн€емого файла основной программы
set(exe_name ${PROJECT_NAME})

#¬ключаем отслеживание всех предупреждений (warnings) и запрещаем компил€цию при наличии предупреждений.
#—читаетс€ хорошим тоном, когда программа собираетс€ без предупрреждений.
#Ќо вы можете убрать /WX и -Werror (разрешив компил€цию с предупреждени€ми), если сможете разумно объ€снить своЄ решение.
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# описываем исполн€емый файл основной программы: это main.cpp + основна€ библиотека
add_executable(${exe_name} main.cpp)