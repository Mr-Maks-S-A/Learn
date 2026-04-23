#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "World.hpp"
#include <atomic>
#include <string>
#include <thread>

class ConsoleUI {
public:
    ConsoleUI(World& world, Rules& rules);
    ~ConsoleUI();

    void Run(); // Запуск основного цикла интерфейса

private:
    // Ссылки на объекты движка
    World& world_;
    World next_buffer_; // Буфер для расчета следующего поколения
    Rules& rules_;

    // Состояние интерфейса
    std::atomic<bool> is_running_{false};
    std::atomic<bool> thread_active_{true};
    int cam_x_{0};
    int cam_y_{0};
    ftxui::Box canvas_box_;

    // Данные для ввода правил
    std::string birth_str_ = "3";
    std::string survive_str_ = "23";

    // Компоненты FTXUI
    ftxui::ScreenInteractive screen_ = ftxui::ScreenInteractive::Fullscreen();

    // Внутренние методы отрисовки
    ftxui::Element RenderSidebar();
    ftxui::Element RenderCanvas();
    ftxui::Element RenderCompass();
};
