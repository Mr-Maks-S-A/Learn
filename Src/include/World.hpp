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


/**
 * @brief Правила эволюции (B/S).
 * Рождение (Birth) и Выживание (Survival).
 */
struct Rules {
    bool birth[9]   = {false}; ///< Клетка рождается, если у нее N соседей
    bool survive[9] = {false}; ///< Клетка выживает, если у нее N соседей
};


bool parse_rules(const std::string& input, Rules& rules);




#pragma pack(push, 1)
/**
 * @brief Структура клетки, упакованная в 1 байт.
 * Использует битовые поля для эффективного хранения состояния и возраста.
 */
struct Cell {
    uint8_t is_alive : 1; ///< Статус: 1 - жива, 0 - мертва
    uint8_t age      : 7; ///< Возраст: количество пережитых итераций (0-127)
};
#pragma pack(pop)

/**
 * @brief Контейнер игрового поля и его метаданных.
 */
struct World {
    uint32_t width;       ///< Ширина поля
    uint32_t height;      ///< Высота поля
    uint32_t generation;  ///< Номер текущего поколения
    std::vector<Cell> matrix; ///< Плоский массив данных (размер width * height)

    /**
     * @brief Создает новый мир заданного размера.
     * @param w Ширина
     * @param h Высота
     */
    World(uint32_t w, uint32_t h);
};

/**
 * @brief Рассчитывает следующее поколение симуляции.
 * Применяет правила "Игры в жизнь" ко всем клеткам поля одновременно.
 * Использует тороидальную топологию (края поля соединены).
 * @param current Состояние мира в текущем кадре.
 * @param next Буфер для записи результатов следующего кадра.
 * @param rules Набор правил для применения.
 */
void update_world(const World& current, World& next, const Rules& rules);
