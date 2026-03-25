cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(Worc6_Arithmetic_functions       VERSION 6.1.0)

option(GENERATE_ASSEMBLY "Генерировать ассемблерный код (.s)" OFF)
option(USE_CONSTEXPR "Использовать constexpr для вычислений" ON)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Установить пути для выходных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)





# Найти все исходные файлы (более явный способ)
# file(GLOB_RECURSE APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c**" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h**")

# Создать исполняемый файл
# add_executable(${PROJECT_NAME} ${APP_SOURCES})
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Указать директории для поиска заголовочных файлов
# target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" )






# --- Логика для Ассемблера ---
if(GENERATE_ASSEMBLY)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /Fa"${CMAKE_BINARY_DIR}/asm/")
    else()
        # В GCC/Clang флаг -S заставляет компилятор выдать .s файл вместо .o
        #target_compile_options(${PROJECT_NAME} PRIVATE -S -fverbose-asm)

        # -save-temps сохранит .s файл, не ломая процесс сборки бинарника
        # -fverbose-asm добавит понятные комментарии в ассемблер
        target_compile_options(${PROJECT_NAME} PRIVATE -save-temps=obj -fverbose-asm)
    endif()
    message(STATUS ">>> Сборка в режиме генерации ассемблера включена")
endif()

# --- Логика для constexpr ---
if(USE_CONSTEXPR)
    # Для функций и для переменных используем constexpr
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        FUNC_CONSTEXPR=constexpr
        VAR_CONSTEXPR=constexpr
    )
else()
    #inline явно разрешает функции существовать в нескольких единицах трансляции, и линковщик просто выберет одну из них.
    # Для функций используем inline, а для переменных - ничего (или const)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        FUNC_CONSTEXPR=inline
        VAR_CONSTEXPR=const
    )
    message(STATUS ">>> constexpr заменен на inline/const")
endif()
