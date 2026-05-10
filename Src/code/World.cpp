/**
 * @file World.сpp
 */

#include "World.hpp"
#include <cctype>
#include <string>
#include <cassert>


World::World(uint32_t w, uint32_t h)
: width(w), height(h), generation(0) {
    assert(w > 0 && h > 0);
    size_t sz = static_cast<size_t>(w) * h;
    Space_0.assign(sz, {0, 0});
    Space_1.assign(sz, {0, 0});
    Space_2.assign(sz, {0, 0});
}

// Конструктор перемещения
World::World(World&& other) noexcept
: name(std::move(other.name)),
width(other.width),
height(other.height),
generation(other.generation),
Space_0(std::move(other.Space_0)),
Space_1(std::move(other.Space_1)),
Space_2(std::move(other.Space_2)) {}

World& World::operator=(World&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        width = other.width;
        height = other.height;
        generation = other.generation;
        Space_0 = std::move(other.Space_0);
        Space_1 = std::move(other.Space_1);
        Space_2 = std::move(other.Space_2);
    }
    return *this;
}

World& World::operator=(const World& other) {
    if (this != &other) {
        name = other.name;
        width = other.width;
        height = other.height;
        generation = other.generation;
        Space_0 = other.Space_0;
        Space_1 = other.Space_1;
        Space_2 = other.Space_2;
    }
    return *this;
}



bool World::is_world_identical() const{
    // Проверяем текущее состояние (0) против предыдущего (1)
    // и против позапрошлого (2) для поиска осцилляторов

    auto check = [&](const std::vector<Cell>& other) {
        for (size_t i = 0; i < Space_0.size(); ++i) {
            if (Space_0[i].is_alive != other[i].is_alive) return false;
        }
        return true;
    };

    return check(Space_1) || check(Space_2);
}




bool World::has_any_life() const{
    for (const auto& cell : Space_0) {
        if (cell.is_alive) return true;
    }
    return false;
}










