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
#include <filesystem> // Для проверки путей
#include "World.hpp"
#include "Loader.hpp"
#include "ConsoleUI.hpp"

int main(int argc, char* argv[]) {
    // 1. Настройки по умолчанию
    uint32_t width = 600;
    uint32_t height = 600;
    Rules rules;
    parse_rules("B3/S23", rules);

    World world(width, height);

    // Определение пути к файлу
    std::string target_file;
    const std::string default_path = "Source/world_save.txt";

    if (argc > 1) {
        // Если передан аргумент — используем его
        target_file = argv[1];
    } else {
        // Иначе используем путь по умолчанию
        target_file = default_path;
    }

    // 2. Попытка загрузки мира
    // Если мы используем путь по умолчанию, и файла нет — это не ошибка, просто создаем новый мир
    if (std::filesystem::exists(target_file)) {
        if (load_world(world, target_file)) {
            // Файл успешно загружен
        } else {
            std::cerr << "Ошибка: Не удалось прочитать файл " << target_file << std::endl;
            return 1;
        }
    } else {
        // Если файла нет (особенно по умолчанию), генерируем случайный мир
        for (uint32_t i = 0; i < (world.width * world.height) / 5; ++i) {
            world.matrix[rand() % (world.width * world.height)].is_alive = 1;
        }
    }

    // 3. Запуск UI
    try {
        ConsoleUI ui(world, rules);
        ui.Run();

        // 4. Сохранение при выходе
        // Сохраняем в тот же файл, из которого загружались (или в Source/world_save.txt)

        // На всякий случай создаем папку, если её нет
        std::filesystem::path p(target_file);
        if (p.has_parent_path()) {
            std::filesystem::create_directories(p.parent_path());
        }

        if (save_world(world, target_file)) {
            std::clog << "Мир успешно сохранён в : " << target_file << std::endl;
        } else {
            std::cerr << "Предупреждение: Не удалось сохранить состояние в " << target_file << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка UI: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
