cmake_minimum_required(VERSION 3.14)

#������ ������������ �������� �++
set(CMAKE_CXX_STANDARD 17)

#TODO: ������������� ������
project(22210_VB)

#������ ��� ������������ ����� �������� ���������
set(exe_name ${PROJECT_NAME})

#�������� ������������ ���� �������������� (warnings) � ��������� ���������� ��� ������� ��������������.
#��������� ������� �����, ����� ��������� ���������� ��� ���������������.
#�� �� ������ ������ /WX � -Werror (�������� ���������� � ����������������), ���� ������� ������� ��������� ��� �������.
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# ��������� ����������� ���� �������� ���������: ��� main.cpp + �������� ����������
add_executable(${exe_name} main.cpp "createRandomArr.cpp")