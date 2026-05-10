/**
 * @file EvolutionEng.inl
 * @brief Инлайновая реализация критических для производительности методов движка.
 */

#pragma once

/**
 * @brief Подсчет соседей по принципу тора (Toroidal Topology).
 *
 * @details Реализация имитирует поверхность тора: если сосед находится за пределами массива,
 * индекс "зацикливается" и переходит на противоположную сторону поля.
 */
inline int EvolutionEng::count_neighbors_toroidal(const World& world, uint32_t x, uint32_t y) {
    const uint32_t w = world.width;
    const uint32_t h = world.height;

    // Предвычисляем индексы строк (с учетом тора)
    uint32_t prev_y = (y == 0) ? (h - 1) * w : (y - 1) * w;
    uint32_t curr_y = y * w;
    uint32_t next_y = (y == h - 1) ? 0 : (y + 1) * w;

    // Предвычисляем индексы столбцов (с учетом тора)
    uint32_t prev_x = (x == 0) ? (w - 1) : (x - 1);
    uint32_t next_x = (x == w - 1) ? 0 : (x + 1);

    const auto& data = world.Space_1;

    // Суммируем 8 соседей напрямую.
    // Операция с битовым полем .is_alive вернет 0 или 1.
    int count = data[prev_y + prev_x].is_alive +
    data[prev_y + x].is_alive +
    data[prev_y + next_x].is_alive +
    data[curr_y + prev_x].is_alive +
    // пропускаем data[curr_y + x] (саму клетку)
    data[curr_y + next_x].is_alive +
    data[next_y + prev_x].is_alive +
    data[next_y + x].is_alive +
    data[next_y + next_x].is_alive;

    return count;
}

/**
 * @details Если ячейка находится на границе, циклы просто пропускают несуществующие координаты.
 */
inline int EvolutionEng::count_neighbors_bounded(const World& world, uint32_t x, uint32_t y) {
    int count = 0;
    const uint32_t w = world.width;
    const uint32_t h = world.height;

    for (int dy = -1; dy <= 1; ++dy) {
        int ny = (int)y + dy;
        if (ny < 0 || ny >= (int)h) continue;

        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int nx = (int)x + dx;
            if (nx < 0 || nx >= (int)w) continue;

            if (world.Space_1[ny * w + nx].is_alive) count++;
        }
    }
    return count;
}

/**
 * @details Клетка выживает, если индекс neighbors отмечен true в rules.survive.
 * Клетка рождается, если индекс отмечен в rules.birth.
 * Возраст ограничен значением 127 (7 бит).
 */
inline void EvolutionEng::apply_rules(const Cell& old_c, Cell& new_c, int neighbors) {
    if (old_c.is_alive) {
        new_c.is_alive = rules.survive[neighbors];
        new_c.age = new_c.is_alive ? (old_c.age < 127 ? old_c.age + 1 : 127) : 0;
    } else {
        new_c.is_alive = rules.birth[neighbors];
        new_c.age = 0;
    }
}
