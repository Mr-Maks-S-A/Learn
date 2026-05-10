/**
 * @file Loader.cpp
 * @brief Реализация функций сохранения и загрузки.
 */

#include "Loader.hpp"
#include <fstream>
#include <sstream>

bool save_world(const World& world, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    // Записываем имя (если пустое — ставим "Unnamed"), высоту и ширину
    out << (world.name.empty() ? "Unnamed" : world.name) << "\n";
    out << world.height << " " << world.width << "\n";

    // Запись координат живых клеток из текущего слоя Space_0
    for (uint32_t y = 0; y < world.height; ++y) {
        for (uint32_t x = 0; x < world.width; ++x) {
            if (world.Space_0[y * world.width + x].is_alive) {
                out << y << " " << x << "\n"; // По ТЗ: сначала строка, потом столбец
            }
        }
    }
    return true;
}

bool load_world(World& world, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    std::string name;
    uint32_t h = 0, w = 0;

    // Читаем метаданные
    if (!(in >> h >> w)) {
        // Если первое чтение не числа, значит в начале идет имя мира
        in.clear();
        in.seekg(0);
        std::getline(in, name);
        if (!(in >> h >> w)) return false;
    }

    // Реинициализация мира под новые размеры
    world.width = w;
    world.height = h;
    world.name = name;
    world.generation = 0;

    size_t total_cells = static_cast<size_t>(w) * h;
    world.Space_0.assign(total_cells, {0, 0});
    world.Space_1.assign(total_cells, {0, 0});
    world.Space_2.assign(total_cells, {0, 0});

    // Читаем пары координат
    uint32_t r, c;
    while (in >> r >> c) {
        if (r < h && c < w) {
            world.Space_0[r * w + c] = {1, 0};
        }
    }
    return true;
}
