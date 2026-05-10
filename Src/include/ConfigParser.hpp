#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "EvolutionEng.hpp"

enum class RunMode { Primitive, Advanced };

struct Config {
    std::vector<std::string> filePaths;
    Topology topology = Topology::Bounded;
    RunMode runMode = RunMode::Primitive;
    int maxSteps = -1;
    int speedMs = 100;
    std::string printMode = "all";
    int printInterval = 1;
    bool helpRequested = false;
    bool noClear = false;
    std::string rulesStr = "B3S23"; // По умолчанию классические правила
};

class ConfigParser {
public:
    static Config parse(int argc, char* argv[]) {
        Config cfg;
        if (argc == 1) {
            cfg.helpRequested = true;
            return cfg;
        }

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];

            if (arg == "--help" || arg == "-h") {
                cfg.helpRequested = true;
            }
            else if (arg.find("--file=") == 0) {
                cfg.filePaths.push_back(arg.substr(7));
            }
            else if (arg.find("--files=") == 0) {
                auto multiple = parseFileList(arg.substr(8));
                cfg.filePaths.insert(cfg.filePaths.end(), multiple.begin(), multiple.end());
            }
            else if (arg.find("--Geometry=") == 0) {
                std::string g = arg.substr(11);
                cfg.topology = (g == "Bounded") ? Topology::Bounded : Topology::Toroidal;
            }
            else if (arg.find("--steps=") == 0) {
                try { cfg.maxSteps = std::stoi(arg.substr(8)); } catch (...) {}
            }
            else if (arg.find("--speed_iteration=") == 0) {
                try {
                    cfg.speedMs = std::clamp(std::stoi(arg.substr(18)), 0, 1000);
                } catch (...) { cfg.speedMs = 100; }
            }
            else if (arg.find("--rules=") == 0) {
                cfg.rulesStr = arg.substr(8);
            }
            else if (arg == "--no-clear") {
                cfg.noClear = true;
            }
            else if (arg.find("--print=") == 0) {
                std::string p = arg.substr(8);
                if (!p.empty() && p[0] == '%') {
                    cfg.printMode = "interval";
                    try { cfg.printInterval = std::max(1, std::stoi(p.substr(1))); } catch (...) {}
                } else {
                    cfg.printMode = p;
                }
            }
        }
        return cfg;
    }

    static void printHelp(const char* name) {
        std::cout << "====================================================\n"
        << "   Симулятор игры «Жизнь» (Conway's Game of Life)   \n"
        << "====================================================\n\n"
        << "Использование: " << name << " [ОПЦИИ]\n\n"
        << "ОСНОВНЫЕ ОПЦИИ:\n"
        << "  --file=\"путь\"                 Путь к файлу мира.\n"
        << "  --files={f1,f2}                 Запуск нескольких миров последовательно.\n"
        << "  --Geometry={Bounded,Toroidal}   Геометрия поля: Ограниченная или Тороидальная (зацикленная).\n"
        << "  --rules=\"B3S23\"               Правила рождения/выживания (Birth/Survive).\n"
        << "  --steps=N                       Ограничение количества шагов (по умолчанию: бесконечно).\n"
        << "  --speed_iteration=MS            Задержка между шагами в миллисекундах (0-1000).\n"
        << "\nВИЗУАЛИЗАЦИЯ:\n"
        << "  --print={all,last,%n}   Режим вывода: 'all' - каждый шаг, 'last' - только итог,\n"
        << "                          '%n' - каждый n-й шаг (например, %10).\n"
        << "  --no-clear              Не очищать консоль перед отрисовкой.\n"
        << "  --help, -h              Показать эту справку.\n"
        << "\nПРИМЕРЫ ЗАПУСКА:\n"
        << "  1. Простой запуск с глайдером:\n"
        << "     " << name << " --file=\"Source/Saves/glider.txt\" --speed_iteration=50\n\n"
        << "  2. Тороидальный мир на 100 шагов с выводом только результата:\n"
        << "     " << name << " --file=\"path/to/world.txt\" --Geometry=Toroidal --steps=100 --print=last\n\n"
        << "  3. Кастомные правила (HighLife) и запуск нескольких файлов:\n"
        << "     " << name << " --files={path/to/world1.txt,path/to/world2.txt} --rules=\"B36S23\"\n\n"
        << "  4. Отрисовка каждого 5-го поколения:\n"
        << "     " << name << " --file=\"path/to/heavy.txt\" --print=%5\n"
        << "----------------------------------------------------\n";
    }

private:
    static std::vector<std::string> parseFileList(std::string str) {
        std::vector<std::string> files;
        str.erase(std::remove_if(str.begin(), str.end(),
                                 [](char c) { return c == '{' || c == '}' || c == '\"'; }), str.end());
        std::stringstream ss(str);
        std::string item;
        while (std::getline(ss, item, ',')) {
            if (!item.empty()) files.push_back(item);
        }
        return files;
    }
};
