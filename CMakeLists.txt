cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(Worc13_Game_of_Life       VERSION 13.1.0)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Установить пути для выходных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)




add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/External/FTXUI")


# Найти все исходные файлы (более явный способ)
file(GLOB_RECURSE APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Src/code/*.c**" "${CMAKE_CURRENT_SOURCE_DIR}/Src/include/*.h**")

add_executable(${PROJECT_NAME} ${APP_SOURCES})

# Указать директории для поиска заголовочных файлов
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/include"
)




# ЛИНКОВКА БИБЛИОТЕК ---
target_link_libraries(${PROJECT_NAME} PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)




# Копирование файла при каждой сборке (на случай изменений в исходнике)
# Копирование всей папки Sorce при каждой сборке
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Source"
    COMMENT "Copying resources to output directory..."
)
