#include "ConsoleUI.hpp"
#include <algorithm>

using namespace ftxui;

ConsoleUI::ConsoleUI(World& world, Rules& rules)
: world_(world), next_buffer_(world.width, world.height), rules_(rules) {
    // Центрируем камеру при запуске
    cam_x_ = world_.width / 2;
    cam_y_ = world_.height / 2;
}

ConsoleUI::~ConsoleUI() {
    thread_active_ = false;
}

void ConsoleUI::Run() {
    // 1. Поля ввода правил и СКОРОСТИ
    // Опция фильтрации: разрешаем только цифры и ограничиваем длину (0-8 соседей, макс 9 символов)
    InputOption numeric_option;
    numeric_option.on_change = [&] {
        auto filter = [](std::string& s) {
            // 1. Оставляем только цифры
            s.erase(std::remove_if(s.begin(), s.end(),
                                   [](char c) { return !std::isdigit(c); }), s.end());

            // 2. Ограничиваем длину до 8 символов
            if (s.length() > 8) {
                s = s.substr(0, 8);
            }
        };

        filter(birth_str_);
        filter(survive_str_);
    };

    Component input_b = Input(&birth_str_, "3", numeric_option);
    Component input_s = Input(&survive_str_, "23", numeric_option);

    // 2. Слайдер для скорости (связан с sim_delay_ms_)
    auto slider_speed = Slider("Задержка: ", &sim_delay_ms_, 10, 500, 10);

    auto slider_cam_speed = Slider("Скорость камеры: ", &cam_speed_, 1, 50, 1);

    // Добавим переменную для отслеживания ошибки валидации
    static std::string error_msg = "";

    Component btn_apply = Button("Применить", [&] {
        if (birth_str_.empty() || survive_str_.empty()) {
            error_msg = "Ошибка: Поля не могут быть пустыми!";
        } else {
            error_msg = "";
            parse_rules("B" + birth_str_ + "/S" + survive_str_, rules_);
        }
    }, ButtonOption::Ascii());

    // Группируем настройки в контейнер для интерактивности
    auto settings_container = Container::Vertical({
        input_b,
        input_s,
        slider_speed,
        slider_cam_speed,
        btn_apply
    });

    auto main_container = Container::Vertical({
        settings_container
    });

    settings_container->SetActiveChild(slider_speed);

    auto renderer = Renderer(settings_container, [&] {
        return hbox({
            vbox({
                text(" CONWAY'S GAME OF LIFE ") | bold | hcenter | color(Color::White) | bgcolor(Color::Blue),
                 RenderCanvas() | flex | reflect(canvas_box_) | borderHeavy
            }) | flex,

            vbox({
                RenderSidebar(settings_container) | size(WIDTH, EQUAL, 32),
                 // Вывод ошибки валидации под сайдбаром
                 text(error_msg) | color(Color::Red) | hcenter
            })
        });
    });

    // 4. Обработка событий
    auto main_component = CatchEvent(renderer, [&](Event event) {
        // --- ВЫХОД ---
        if (event == Event::Character('q') || event == Event::Escape) {
            screen_.ExitLoopClosure()();
            return true;
        }

        // --- РИСОВАНИЕ МЫШЬЮ ---
        if (event.is_mouse()) {
            auto m = event.mouse();
            if (m.button == Mouse::Left || m.button == Mouse::Right) {
                int canvas_w = (canvas_box_.x_max - canvas_box_.x_min) * 2;
                int canvas_h = (canvas_box_.y_max - canvas_box_.y_min) * 4;
                int half_w = canvas_w / 2;
                int half_h = canvas_h / 2;

                int cx = (m.x - canvas_box_.x_min) * 2;
                int cy = (m.y - canvas_box_.y_min) * 4;

                int world_x = static_cast<int>((cx - half_w) / zoom_) + cam_x_;
                int world_y = static_cast<int>((cy - half_h) / zoom_) + cam_y_;

                uint32_t gx = (world_x % (int)world_.width + world_.width) % world_.width;
                uint32_t gy = (world_y % (int)world_.height + world_.height) % world_.height;

                world_.matrix[gy * world_.width + gx].is_alive = (m.button == Mouse::Left);
                if (m.button == Mouse::Left) world_.matrix[gy * world_.width + gx].age = 0;

                return true;
            }
        }

        // --- УПРАВЛЕНИЕ КАМЕРОЙ И СИМУЛЯЦИЕЙ ---
        if (event == Event::Character('+') || event == Event::Character('=')) { zoom_ *= 1.2f; return true; }
        if (event == Event::Character('-') || event == Event::Character('_')) { zoom_ /= 1.2f; return true; }

        if (event == Event::Character('r')) {
            zoom_ = 1.0f;
            cam_x_ = world_.width / 2;
            cam_y_ = world_.height / 2;
            return true;
        }
        if (event == Event::Character('p')) { is_running_ = !is_running_; return true; }

        if (event == Event::Character('w')) cam_y_ -= cam_speed_;
        if (event == Event::Character('s')) cam_y_ += cam_speed_;
        if (event == Event::Character('a')) cam_x_ -= cam_speed_;
        if (event == Event::Character('d')) cam_x_ += cam_speed_;

        return false;
    });

    // 5. Поток вычислений (использует sim_delay_ms_)
    std::thread sim_thread([&] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        screen_.PostEvent(Event::Custom);

        while (thread_active_) {
            if (is_running_) {
                update_world(world_, next_buffer_, rules_);
                world_ = next_buffer_;
                screen_.PostEvent(Event::Custom);
            }
            // Динамическая задержка
            std::this_thread::sleep_for(std::chrono::milliseconds(sim_delay_ms_));
        }
    });

    screen_.Loop(main_component);
    thread_active_ = false;
    sim_thread.join();
}

Element ConsoleUI::RenderCanvas() {
    int screen_w = (canvas_box_.x_max - canvas_box_.x_min);
    int screen_h = (canvas_box_.y_max - canvas_box_.y_min);

    if (screen_w <= 0 || screen_h <= 0) return text("Инициализация...");

    int canvas_w = screen_w * 2;
    int canvas_h = screen_h * 4;
    int half_w = canvas_w / 2;
    int half_h = canvas_h / 2;
    auto c = Canvas(canvas_w, canvas_h);

    if (zoom_ >= BLOCK_MODE_THRESHOLD) {
        for (int y = 0; y < canvas_h; ++y) {
            for (int x = 0; x < canvas_w; ++x) {
                int world_x = static_cast<int>((x - half_w) / zoom_) + cam_x_;
                int world_y = static_cast<int>((y - half_h) / zoom_) + cam_y_;

                uint32_t gx = (world_x % (int)world_.width + world_.width) % world_.width;
                uint32_t gy = (world_y % (int)world_.height + world_.height) % world_.height;

                const auto& cell = world_.matrix[gy * world_.width + gx];
                if (cell.is_alive) {
                    Color col;

                    if (cell.age == 0) {
                        col = Color::GreenLight; // Только что родилась
                    } else if (cell.age < 5) {
                        col = Color::Green;      // Молодая
                    } else if (cell.age < 15) {
                        col = Color::Cyan;       // Стабильная
                    } else if (cell.age < 30) {
                        col = Color::BlueLight;  // Взрослая
                    } else if (cell.age < 60) {
                        col = Color::Blue;       // Старая
                    } else if (cell.age < 100) {
                        col = Color::Magenta;    // Долгожитель
                    } else {
                        col = Color::Purple;     // "Древняя" клетка
                    }

                    c.DrawPoint(x, y, true, col);
                }
            }
        }
    } else {
        for (int y = 0; y < screen_h; ++y) {
            for (int x = 0; x < screen_w; ++x) {
                int world_x = static_cast<int>((x * 2) / zoom_) + cam_x_;
                int world_y = static_cast<int>((y * 4) / zoom_) + cam_y_;

                uint32_t gx = (world_x % (int)world_.width + world_.width) % world_.width;
                uint32_t gy = (world_y % (int)world_.height + world_.height) % world_.height;

                if (world_.matrix[gy * world_.width + gx].is_alive) {
                    for(int bx = 0; bx < 2; ++bx)
                        for(int by = 0; by < 4; ++by)
                            c.DrawPoint(x * 2 + bx, y * 4 + by, true);
                }
            }
        }
    }
    return canvas(std::move(c));
}

Element ConsoleUI::RenderSidebar(Component settings) {
    float scroll_x = (float)((cam_x_ % (int)world_.width + (int)world_.width) % (int)world_.width) / world_.width;
    float scroll_y = (float)((cam_y_ % (int)world_.height + (int)world_.height) % (int)world_.height) / world_.height;

    return vbox(
        window(text(" СТАТИСТИКА "), vbox(
            hbox(text("Поколение: "), text(std::to_string(world_.generation)) | color(Color::Yellow)),
                                          hbox(text("Статус:    "), text(is_running_ ? "RUNNING" : "PAUSED") | color(is_running_ ? Color::Green : Color::Red))
        )),
        window(text(" НАСТРОЙКИ "), vbox({
            hbox(text(" Рождение (B):") | size(WIDTH, EQUAL, 15), settings->ChildAt(0)->Render() | border),
            hbox(text(" Выживание (S):") | size(WIDTH, EQUAL, 15), settings->ChildAt(1)->Render() | border),
            separator(),
            settings->ChildAt(2)->Render(), // Слайдер
            settings->ChildAt(3)->Render(), // Слайдер
            separator(),
            center(settings->ChildAt(4)->Render()), // Кнопка
            separator(),
            hbox(text(" Текущий тик: "), text(std::to_string(sim_delay_ms_) + "ms") | color(Color::Cyan))
        })),
        window(text(" НАВИГАЦИЯ "), vbox(
            center(RenderCompass()),
            separator(),
            hbox(text("X: "), gauge(scroll_x) | color(Color::Blue)),
            hbox(text("Y: "), gauge(scroll_y) | color(Color::Blue)),
            separator(),
            hbox(text("Зум: "), text(std::to_string((int)(zoom_ * 100)) + "%") | color(Color::Magenta))
        )),
        filler(),
                window(text(" УПРАВЛЕНИЕ "), vbox(
                    text(" [P]      Пауза/Старт"),
                                                  text(" [WASD]   Сдвиг камеры"),
                                                  text(" [+/-/R]  Зум/Сброс"),
                                                  text(" [⭡⭣/⮂]     Настройки"),
                                                  text(" [Mouse]  Рисовать"),
                                                  separator(),
                                                  text(" [Q/ESC]  Выход") | color(Color::RedLight)
                ))
    );
}

Element ConsoleUI::RenderCompass() {
    return canvas([&](Canvas& c) {
        const int cw = 40; // Немного увеличим разрешение для точности
        const int ch = 20;

        // 1. Рисуем границы мира (серый прямоугольник)
        for (int x = 0; x <= cw; ++x) {
            c.DrawPoint(x, 0, true, Color::GrayDark);
            c.DrawPoint(x, ch, true, Color::GrayDark);
        }
        for (int y = 0; y <= ch; ++y) {
            c.DrawPoint(0, y, true, Color::GrayDark);
            c.DrawPoint(cw, y, true, Color::GrayDark);
        }

        // 2. Считаем, какую область мира мы сейчас видим
        // Учитываем, что 1 единица холста = 0.5 символа по X и 0.25 по Y
        float screen_w = (canvas_box_.x_max - canvas_box_.x_min) * 2.0f;
        float screen_h = (canvas_box_.y_max - canvas_box_.y_min) * 4.0f;

        float world_visible_w = screen_w / zoom_;
        float world_visible_h = screen_h / zoom_;

        // Переводим размеры вьюпорта в координаты компаса
        int vw = std::clamp(static_cast<int>((world_visible_w / world_.width) * cw), 2, cw);
        int vh = std::clamp(static_cast<int>((world_visible_h / world_.height) * ch), 2, ch);

        // Переводим положение камеры (центра) в координаты компаса
        // Используем нормализацию, чтобы камера всегда была внутри [0, cw]
        auto normalize = [](int val, int max) {
            return ((val % max) + max) % max;
        };

        // Центр вьюпорта на компасе
        int n_cam_x = normalize(cam_x_, world_.width);
        int n_cam_y = normalize(cam_y_, world_.height);

        int center_x = (n_cam_x * cw) / world_.width;
        int center_y = (n_cam_y * ch) / world_.height;

        // Координаты верхнего левого угла рамки
        int x0 = center_x - vw / 2;
        int y0 = center_y - vh / 2;

        // 3. Рисуем рамку вьюпорта (красная)
        // Рисуем попиксельно, чтобы корректно обрабатывать выход за края миникарты
        for (int dx = 0; dx < vw; ++dx) {
            int px = (x0 + dx + cw) % cw;
            c.DrawPoint(px, (y0 + ch) % ch, true, Color::Red);
            c.DrawPoint(px, (y0 + vh + ch) % ch, true, Color::Red);
        }
        for (int dy = 0; dy < vh; ++dy) {
            int py = (y0 + dy + ch) % ch;
            c.DrawPoint((x0 + cw) % cw, py, true, Color::Red);
            c.DrawPoint((x0 + vw + cw) % cw, py, true, Color::Red);
        }

        // 4. Желтая точка — точный центр камеры
        c.DrawPoint(center_x, center_y, true, Color::Yellow);

    }) | size(WIDTH, EQUAL, 22) | size(HEIGHT, EQUAL, 7) | borderLight;
}
