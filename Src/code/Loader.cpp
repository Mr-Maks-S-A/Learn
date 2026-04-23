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
    out << "высота:" << world.height << "\n";
    out << "ширина:" << world.width << "\n";
    out << "итерация:" << world.generation << "\n";
    out << "=клетки(x,y)=\n";

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

    std::string line;
    uint32_t h = 0, w = 0, gen = 0;

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        // Ищем позицию двоеточия
        size_t colon_pos = line.find(':');

        if (line.find("высота") != std::string::npos && colon_pos != std::string::npos) {
            h = std::stoul(line.substr(colon_pos + 1));
        }
        else if (line.find("ширина") != std::string::npos && colon_pos != std::string::npos) {
            w = std::stoul(line.substr(colon_pos + 1));
        }
        else if (line.find("итерация") != std::string::npos && colon_pos != std::string::npos) {
            gen = std::stoul(line.substr(colon_pos + 1));
        }
        else if (line.find("=клетки") != std::string::npos) {
            break;
        }
    }

    if (w == 0 || h == 0) return false;

    world.width = w;
    world.height = h;
    world.generation = gen;
    world.matrix.assign(w * h, {0, 0});

    uint32_t x, y;
    while (in >> x >> y) {
        if (x < w && y < h) {
            world.matrix[y * w + x].is_alive = 1;
            world.matrix[y * w + x].age = 0;
        }
    }

    return true;
}
