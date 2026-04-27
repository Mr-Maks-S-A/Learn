/**
 * @file Loader.cpp
 * @brief Реализация функций сохранения и загрузки.
 */

#include "Loader.hpp"
#include <fstream>
#include <sstream>

bool save_world(const World& world, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }

    // Запись метаданных
    out << world.height << " ";
    out << world.width << "\n";

    // Запись координат только живых клеток
    for (uint32_t y = 0; y < world.height; ++y) {
        for (uint32_t x = 0; x < world.width; ++x) {
            if (world.matrix[y * world.width + x].is_alive) {
                out << x << " " << y << "\n";
            }
        }
    }

    out.close();
    return true;
}

bool load_world(World& world, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    uint32_t h = 0, w = 0;

    // Читаем первые два числа: высоту и ширину
    if (!(in >> h >> w)) return false;

    // Сбрасываем мир под новые размеры
    world.width = w;
    world.height = h;
    world.generation = 0; // В новом формате итерация не хранится
    world.matrix.assign(w * h, {0, 0});

    // Читаем пары координат до конца файла
    uint32_t x, y;
    while (in >> x >> y) {
        if (x < w && y < h) {
            world.matrix[y * w + x].is_alive = 1;
            world.matrix[y * w + x].age = 0;
        }
    }

    return true;
}
