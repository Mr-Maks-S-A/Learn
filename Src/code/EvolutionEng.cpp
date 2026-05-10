/**
 * @file EvolutionEng.сpp
 */
#include "EvolutionEng.hpp"

bool Rules::parse_rules(const std::string& input) {
    // Сброс данных перед заполнением
    for (int i = 0; i < 9; ++i) {
        birth[i] = survive[i] = false;
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
                if (mode == 'B') birth[n] = true;
                else survive[n] = true;
            }
        }
    }
    return found;
}






EvolutionEng::EvolutionEng() = default;
EvolutionEng::~EvolutionEng() = default;



bool EvolutionEng::step(World & world) {
    // 1. Ротация слоев
    std::swap(world.Space_2, world.Space_1);
    std::swap(world.Space_1, world.Space_0);

    // Быстрое зануление Space_0 (будущего поколения)
    // Используем memset через std::fill для типобезопасности
    std::fill(world.Space_0.begin(), world.Space_0.end(), Cell{0, 0});

    const uint32_t w = world.width;
    const uint32_t h = world.height;



    world.alive_count = 0; // Сбрасываем счетчик

    if (topology == Topology::Toroidal) {
        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                int n = count_neighbors_toroidal(world, x, y);
                apply_rules(world.Space_1[y * w + x], world.Space_0[y * w + x], n);
                if (world.Space_0[y * w + x].is_alive) world.alive_count++;
            }
        }
    } else {
        // Аналогично для Bounded
        for (uint32_t y = 0; y < h; ++y) {
            for (uint32_t x = 0; x < w; ++x) {
                int n = count_neighbors_bounded(world, x, y);
                apply_rules(world.Space_1[y * w + x], world.Space_0[y * w + x], n);
                if (world.Space_0[y * w + x].is_alive) world.alive_count++;
            }
        }
    }

    world.generation++;
    world.is_alive = (world.alive_count > 0);
    world.is_stagnated = world.is_world_identical();

    // Возвращаем true, если симуляция может продолжаться
    return world.is_alive && !world.is_stagnated;
}
