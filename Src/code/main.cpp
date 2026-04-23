#include "World.hpp"
#include "Loader.hpp"
#include "ConsoleUI.hpp"

int main() {
    // 1. Инициализация (200x200 - золотая середина)
    World world(200, 200);
    Rules rules;
    parse_rules("B3/S23", rules);

    // 2. Загрузка сохранения (если есть)
    load_world(world, "Sorce/world_save.txt");

    // 3. Запуск интерфейса
    ConsoleUI ui(world, rules);
    ui.Run();

    // 4. Автосохранение при выходе
    save_world(world, "Sorce/world_save.txt");

    return EXIT_SUCCESS;
}

