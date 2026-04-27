/**
 * @file main.cpp
 * @brief Точка входа в программу.
 * * @details Данный файл выполняет следующие задачи:
 * 1. Установка начальных параметров симуляции (размер поля, правила).
 * 2. Инициализация объекта игрового мира @ref World.
 * 3. Обработка аргументов командной строки для загрузки файлов через @ref Loader.
 * 4. Создание и запуск графического интерфейса пользователя @ref ConsoleUI.
 */

#include <iostream>
#include "World.hpp"
#include "Loader.hpp"
#include "ConsoleUI.hpp"

int main(int argc, char* argv[]) {
    // 1. Настройки мира по умолчанию
    uint32_t width = 160;
    uint32_t height = 90;
    Rules rules;

    // Инициализация правил классической игры "Жизнь" (B3/S23)
    parse_rules("B3/S23", rules);

    // 2. Создание объекта мира
    World world(width, height);

    // 3. Опциональная загрузка из файла, если передан аргумент
    if (argc > 1) {
        std::string filename = argv[1];
        if (load_world(world, filename)) {
            // Файл успешно загружен, параметры w/h/gen обновились внутри load_world
        } else {
            std::cerr << "Ошибка: Не удалось загрузить файл " << filename << std::endl;
            return 1;
        }
    } else {
        // Если файла нет, можно создать случайное начальное заполнение
        // (Опционально, для теста)
        for (uint32_t i = 0; i < (width * height) / 5; ++i) {
            world.matrix[rand() % (width * height)].is_alive = 1;
        }
    }

    // 4. Запуск UI
    try {
        ConsoleUI ui(world, rules);
        ui.Run();
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка UI: " << e.what() << std::endl;
        return 1;
    }

    // 5. Предложение сохранить результат перед выходом (опционально)
    // save_world(world, "autosave.gol");

    return 0;
}
