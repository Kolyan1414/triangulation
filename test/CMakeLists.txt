cmake_minimum_required(VERSION 2.8)	# Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(triangulation)			# Название проекта

set(SOURCE_EXE test_main.cpp)		# Установка переменной со списком исходников для исполняемого файла

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lGL -lglut -lGLU")	#Эта команда добавит к флагам, используемым при сборке c++-кода, флаги -std=c++11 и -pthread -lGL -lglut -lGLU

set(SOURCE_LIB point.cpp add_from_console.cpp Graphics.h receive_verified.cpp)			# Тоже самое, но для библиотеки

add_library(lib STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

target_link_libraries(main lib)		# Линковка программы с библиотекой
