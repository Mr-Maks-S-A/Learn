/**
 * @file ConsoleUI.hpp
 * @brief Графический интерфейс на базе библиотеки FTXUI.
 * Класс отвечает за визуализацию мира в терминале, обработку ввода
 * (мышь, клавиатура) и управление потоком симуляции.
 */

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


/**
 * @brief Главный класс интерфейса симуляции.
 * Реализует концепцию бесконечного холста с зумом и перемещением.
 */
class ConsoleUI {
public:

    /**
     * @brief Создает объект UI.
     * @param world Ссылка на активный мир.
     * @param rules Ссылка на текущие правила симуляции.
     */
    ConsoleUI(World& world, Rules& rules);
    ~ConsoleUI();

    /**
     * @brief Запускает главный цикл FTXUI и поток вычислений.
     */
    void Run();

private:
    World& world_;            ///< Ссылка на данные мира.
    World next_buffer_;       ///< Вспомогательный буфер для расчетов.
    Rules& rules_;            ///< Ссылка на активные правила.

    int sim_delay_ms_ = 50;   ///< Задержка между поколениями (мс).
    std::atomic<bool> is_running_{false}; ///< Флаг активности симуляции (пауза/пуск).
    std::atomic<bool> thread_active_{true}; ///< Флаг жизни фонового потока.

    float zoom_ = 1.0f;       ///< Коэффициент масштабирования.
    const float BLOCK_MODE_THRESHOLD = 0.5f; ///< Порог переключения режима отрисовки.
    int cam_x_{0};            ///< Смещение камеры по горизонтали.
    int cam_y_{0};            ///< Смещение камеры по вертикали.

    ftxui::Box canvas_box_;   ///< Координаты отрисованного элемента холста на экране.

    std::string birth_str_ = "3";   ///< Буфер ввода для правил рождения.
    std::string survive_str_ = "23"; ///< Буфер ввода для правил выживания.

    ftxui::ScreenInteractive screen_ = ftxui::ScreenInteractive::Fullscreen(); ///< Основной экран FTXUI.

    /** @name Методы рендеринга */
    ///@{

    /**
     * @brief Отрисовка панели управления.
     */
    ftxui::Element RenderSidebar(ftxui::Component settings);
    /**
     * @brief Отрисовка игрового поля.
     * * @details Метод использует два режима:
     * 1. **Детальный**: При зуме >= @ref BLOCK_MODE_THRESHOLD рисует каждую клетку
     * точкой `Canvas` с учетом её возраста (цвет меняется от Green до Blue).
     * 2. **Обзорный**: При малом зуме рисует клетки блоками 2x4 для экономии ресурсов.
     * * Использует тороидальную проекцию координат мира на холст.
     */
    ftxui::Element RenderCanvas();
    /**
     * @brief Отрисовка компаса (миникарты).
     * * Визуализирует положение текущего вьюпорта (красная рамка)
     * относительно всего игрового поля (серая рамка).
     * Желтая точка обозначает центр камеры.
     */
    ftxui::Element RenderCompass();

    ///@}
};
