/**
 * @file World.cpp
 * @brief Реализация логики симуляции и работы с миром.
 */

#include "World.hpp"
#include <cctype>
#include <string>




bool parse_rules(const std::string& input, Rules& rules) {
    // Сброс данных перед заполнением
    for (int i = 0; i < 9; ++i) {
        rules.birth[i] = rules.survive[i] = false;
    }

    char mode = 0; // 'B' или 'S'
    bool found = false;

    for (char c : input) {
        char upper = std::toupper(c);
        if (upper == 'B' || upper == 'S') {
            mode = upper;
            found = true;
        } else if (std::isdigit(c) && mode != 0) {
            int n = c - '0';
            if (n >= 0 && n <= 8) {
                if (mode == 'B') rules.birth[n] = true;
                else rules.survive[n] = true;
            }
        }
    }
    return found;
}




World::World(uint32_t w, uint32_t h)
: width(w), height(h), generation(0), matrix(w * h, {0, 0}) {}



void update_world(const World& current, World& next, const Rules& rules) {
    // Увеличиваем счетчик поколений
    next.generation = current.generation + 1;

    const uint32_t w = current.width;
    const uint32_t h = current.height;

    for (uint32_t y = 0; y < h; ++y) {
        for (uint32_t x = 0; x < w; ++x) {

            /// 1. Сбор соседей с использованием тороидальной топологии (Wrap-around).
            // Поле математически сворачивается в тор: левый край соединен с правым,
            // верхний — с нижним. Это исключает "эффект границы" и позволяет
            // структурам бесконечно циркулировать по полю.
            int neighbors = 0;///< кол-во соседей
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;

                    // Формула (current + delta + size) % size гарантирует, что:
                    // -1 превращается в (size - 1) (переход влево/вверх на ту сторону)
                    // size превращается в 0 (переход вправо/вниз на начало)
                    uint32_t nx = (x + dx + w) % w;
                    uint32_t ny = (y + dy + h) % h;

                    if (current.matrix[ny * w + nx].is_alive) {
                        neighbors++;
                    }
                }
            }

            // 2. Обработка логики на основе текущего состояния
            const Cell& old_cell = current.matrix[y * w + x];
            Cell& new_cell = next.matrix[y * w + x];

            if (old_cell.is_alive) {
                // Если клетка жива, проверяем, выживет ли она
                if (rules.survive[neighbors]) {
                    new_cell.is_alive = 1;
                    // Увеличиваем возраст, не выходя за предел 7 бит (127)
                    new_cell.age = (old_cell.age < 127) ? (old_cell.age + 1) : 127;
                } else {
                    // Клетка умирает от одиночества или перенаселения
                    new_cell.is_alive = 0;
                    new_cell.age = 0;
                }
            } else {
                // Если клетка мертва, проверяем, не родится ли она
                if (rules.birth[neighbors]) {
                    new_cell.is_alive = 1;
                    new_cell.age = 0; // Новая жизнь всегда начинается с возраста 0
                } else {
                    // Остается мертвой
                    new_cell.is_alive = 0;
                    new_cell.age = 0;
                }
            }
        }
    }
}
