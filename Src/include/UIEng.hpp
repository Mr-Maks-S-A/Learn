#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "World.hpp"

class Renderer {
public:
    bool useClear = true; // Флаг: очищать экран или печатать потоком
    virtual ~Renderer() = default;
    virtual void clear() = 0;
    virtual void render(const World& world) = 0;
};

class PrimitiveRenderer : public Renderer {
public:
    void clear() override {
        if (useClear) {// Очистка экрана и возврат курсора в начало
            std::cout << "\033[H\033[2J";
        }
    }

    void render(const World& world) override {
        size_t aliveCount = 0;

        std::cout << "\nПоколение: " << world.generation << "\n";

        for (uint32_t y = 0; y < world.height; ++y) {
            for (uint32_t x = 0; x < world.width; ++x) {
                if (world.Space_0[y * world.width + x].is_alive) {
                    std::cout << "* ";
                    aliveCount++;
                } else {
                    std::cout << "- ";
                }
            }
            std::cout << "\n";
        }

        std::cout << "Живых клеток: " << aliveCount << "\n";

        if (aliveCount == 0) {
            std::cout << "Мир умер!\n";
        }
        std::flush(std::cout);
    }
};


