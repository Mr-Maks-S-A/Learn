/**
 * @file World.hpp
 * @brief Определение структур данных и системы эволюции для клеточного автомата.
 * Данный файл содержит компактное представление клетки с поддержкой системы
 * старения и структуру игрового мира.
 */

#pragma once
#include <vector>
#include <cstdint>
#include <string>



struct Cell {
    uint8_t is_alive : 1; ///< Статус: 1 - жива, 0 - мертва
    uint8_t age      : 7; ///< Возраст: количество пережитых итераций (0-127)
};

enum class WorldState {
    Active,     // Мир развивается
    Stagnated,  // Мир зациклился или остановился
    Empty       // Все клетки погибли
};



class World {
public:
    std::string name;
    uint32_t width;
    uint32_t height;

    bool is_alive = true;    // Есть ли живые клетки в текущем Space_0
    bool is_stagnated = false; // Зациклился ли мир на этом шаге
    size_t alive_count = 0;    // Количество живых для вывода

    uint32_t generation;

    std::vector<Cell> Space_0;
    std::vector<Cell> Space_1;
    std::vector<Cell> Space_2;


    World(uint32_t w, uint32_t h);
    ~World()= default;


    // Правило пяти
    World(const World& other) = default;
    World(World&& other) noexcept;
    World& operator=(World&& other) noexcept;
    World& operator=(const World& other);


    bool is_world_identical() const;

    bool has_any_life() const;
};

