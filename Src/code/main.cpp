#include <iostream>
#include <thread>
#include <clocale>
#include <memory>
#include <iomanip> // Для красивого вывода конфига
#include "ConfigParser.hpp"
#include "World.hpp"
#include "EvolutionEng.hpp"
#include "UIEng.hpp"
#include "Loader.hpp"

/**
 * @brief Вспомогательная функция для вывода текущей конфигурации
 */
void print_session_info(const std::string& path, const Config& cfg) {
    std::cout << "=== Запуск симуляции ===" << std::endl;
    std::cout << "Файл мира: " << path << std::endl;
    std::cout << "Правила:    " << cfg.rulesStr << std::endl;
    std::cout << "Геометрия:  " << (cfg.topology == Topology::Toroidal ? "Toroidal" : "Bounded") << std::endl;
    std::cout << "Макс. шагов:" << (cfg.maxSteps == -1 ? "Бесконечно" : std::to_string(cfg.maxSteps)) << std::endl;
    std::cout << "------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "");

    Config cfg = ConfigParser::parse(argc, argv);
    if (cfg.helpRequested) {
        ConfigParser::printHelp(argv[0]);
        return EXIT_SUCCESS;
    }

    EvolutionEng engine;
    engine.topology = cfg.topology;
    if (!engine.rules.parse_rules(cfg.rulesStr)) {
        engine.rules.parse_rules("B3S23");
    }

    std::unique_ptr<Renderer> renderer = std::make_unique<PrimitiveRenderer>();
    renderer->useClear = (cfg.printMode != "last" && !cfg.noClear);

    for (size_t i = 0; i < cfg.filePaths.size(); ++i) {
        const auto& path = cfg.filePaths[i];

        // Разделение между файлами пробелом (пустой строкой)
        if (i > 0) std::cout << "\n\n";

        World world(1, 1);
        if (!load_world(world, path)) {
            std::cerr << "Ошибка загрузки: " << path << std::endl;
            continue;
        }

        // Вывод инфо на первой итерации загрузки файла
        print_session_info(path, cfg);

        bool wasPrinted = false;
        bool canContinue = true;

        // Внутри цикла по файлам (main.cpp)
        while (true) {
            // 1. Определяем, нужно ли печатать ТЕКУЩЕЕ состояние
            bool isLastStep = (cfg.maxSteps != -1 && world.generation >= (uint32_t)cfg.maxSteps);
            bool shouldPrint = (cfg.printMode == "all") ||
            (cfg.printMode == "interval" && world.generation % cfg.printInterval == 0);

            if (shouldPrint) {
                renderer->clear();
                renderer->render(world);
                wasPrinted = true;
            }

            // 2. Если достигли лимита шагов — СТОП (до вычисления нового шага)
            if (isLastStep) {
                if (cfg.printMode == "last") { // Для режима last печатаем только в самом конце
                    renderer->clear();
                    renderer->render(world);
                }
                std::cout << "\n[Результат]: Остановка по лимиту шагов.\n";
                break;
            }

            // 3. Делаем шаг
            canContinue = engine.step(world);

            // 4. Если мир стабилизировался (стагнация или смерть) — СТОП
            if (!canContinue) {
                // Отрисовываем финальный результат, если он еще не был отрисован
                renderer->clear();
                renderer->render(world);

                size_t finalAlive = 0;
                for(const auto& cell : world.Space_0) if(cell.is_alive) finalAlive++;

                std::cout << "\n[Результат]: " << (finalAlive == 0 ? "Мир мёртв." : "Стагнация.") << std::endl;
                break;
            }

            if (cfg.printMode != "last") {
                std::this_thread::sleep_for(std::chrono::milliseconds(cfg.speedMs));
            }
        }
    }

    return EXIT_SUCCESS;
}
