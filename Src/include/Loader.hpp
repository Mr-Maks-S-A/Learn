/**
 * @file Loader.hpp
 * @brief Модуль для сериализации и десериализации данных игрового мира.
 * * Содержит функции для сохранения текущего состояния системы в файл и
 * загрузки из формата COO (Coordinate List).
 */

#pragma once
#include "World.hpp"
#include <string>

/**
 * @brief Сохраняет мир в формате COO (координатный список).
 * * Формат файла включает метаданные (W, H, Gen) и список координат живых клеток.
 * @param world Мир для сохранения.
 * @param filename Имя файла.
 * @return true при успехе.
 */
bool save_world(const World& world, const std::string& filename);

/**
 * @brief Загружает мир из файла.
 * * Пересоздает структуру World в соответствии с метаданными файла.
 * @param world Объект мира для инициализации.
 * @param filename Путь к файлу.
 * @return true, если данные корректно считаны.
 */
bool load_world(World& world, const std::string& filename);
