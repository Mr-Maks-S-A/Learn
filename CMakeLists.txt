cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(Worc7_Variable_addresses      VERSION 7.1.0)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Установить пути для выходных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Опция выбора архитектуры ---
option(ARCH_32 "Собрать 32-битную версию" OFF)

# Найти все исходные файлы (более явный способ)
# file(GLOB_RECURSE APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c**" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h**")

# Создать исполняемый файл
# add_executable(${PROJECT_NAME} ${APP_SOURCES})
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Указать директории для поиска заголовочных файлов
# target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" )


if(ARCH_32)
    if(MSVC)
        # Для MSVC в CMake архитектура обычно задается через генератор (-A Win32),
        # но можно форсировать флаги, если нужно:
        target_compile_options(${PROJECT_NAME} PRIVATE /arch:IA32)
    else()
        # Для GCC и Clang на Linux (твой случай)
        target_compile_options(${PROJECT_NAME} PUBLIC -m32)
        target_link_options(${PROJECT_NAME} PUBLIC -m32)
    endif()
    message(STATUS "Конфигурация: 32-битная архитектура")
else()
    message(STATUS "Конфигурация: 64-битная архитектура (по умолчанию)")
endif()
