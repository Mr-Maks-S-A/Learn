#include "ConsoleUI.hpp"
#include <algorithm>

using namespace ftxui;

ConsoleUI::ConsoleUI(World& world, Rules& rules)
: world_(world), next_buffer_(world.width, world.height), rules_(rules) {}

ConsoleUI::~ConsoleUI() {
    thread_active_ = false;
}

void ConsoleUI::Run() {
    // 1. Поля ввода правил и СКОРОСТИ
    Component input_b = Input(&birth_str_, "3");
    Component input_s = Input(&survive_str_, "23");

    // 2. Слайдер для скорости (связан с sim_delay_ms_)
    auto slider_speed = Slider("Задержка: ", &sim_delay_ms_, 10, 500, 10);

    Component btn_apply = Button("Применить", [&] {
        parse_rules("B" + birth_str_ + "/S" + survive_str_, rules_);
    }, ButtonOption::Ascii());

    // Группируем настройки в контейнер для интерактивности
    auto settings_container = Container::Vertical({
        input_b,
        input_s,
        slider_speed,
        btn_apply
    });

    auto renderer = Renderer(settings_container, [&] {
        return hbox({
            vbox({
                text(" CONWAY'S GAME OF LIFE ") | bold | hcenter | color(Color::White) | bgcolor(Color::Blue),
                 RenderCanvas() | flex | reflect(canvas_box_) | borderHeavy
            }) | flex,
            // Передаем settings_container, чтобы отрендерить его внутри сайдбара
            RenderSidebar(settings_container) | size(WIDTH, EQUAL, 32)
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
        if (event == Event::Character('r')) { zoom_ = 1.0f; return true; }
        if (event == Event::Character('p')) { is_running_ = !is_running_; return true; }

        if (event == Event::Character('w')) cam_y_ -= 1;
        if (event == Event::Character('s')) cam_y_ += 1;
        if (event == Event::Character('a')) cam_x_ -= 1;
        if (event == Event::Character('d')) cam_x_ += 1;

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
                    Color col = cell.age > 10 ? Color::Blue : (cell.age > 0 ? Color::Cyan : Color::Green);
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
            separator(),
            center(settings->ChildAt(3)->Render()), // Кнопка
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
        int cw = 20;
        int ch = 8;
        for (int x = 0; x <= cw; ++x) {
            c.DrawPoint(x, 0, true, Color::GrayDark);
            c.DrawPoint(x, ch, true, Color::GrayDark);
        }
        for (int y = 0; y <= ch; ++y) {
            c.DrawPoint(0, y, true, Color::GrayDark);
            c.DrawPoint(cw, y, true, Color::GrayDark);
        }

        float visible_w_ratio = (canvas_box_.x_max - canvas_box_.x_min) * 2 / zoom_;
        float visible_h_ratio = (canvas_box_.y_max - canvas_box_.y_min) * 4 / zoom_;

        int viewport_w = std::clamp(static_cast<int>((visible_w_ratio / world_.width) * cw), 1, cw);
        int viewport_h = std::clamp(static_cast<int>((visible_h_ratio / world_.height) * ch), 1, ch);

        int vx = ((cam_x_ % (int)world_.width + (int)world_.width) % (int)world_.width) * cw / world_.width;
        int vy = ((cam_y_ % (int)world_.height + (int)world_.height) % (int)world_.height) * ch / world_.height;

        for (int x = 0; x < viewport_w; ++x) {
            c.DrawPoint((vx + x) % cw, vy, true, Color::Red);
            c.DrawPoint((vx + x) % cw, (vy + viewport_h) % ch, true, Color::Red);
        }
        for (int y = 0; y < viewport_h; ++y) {
            c.DrawPoint(vx, (vy + y) % ch, true, Color::Red);
            c.DrawPoint((vx + viewport_w) % cw, (vy + y) % ch, true, Color::Red);
        }
        c.DrawPoint((vx + viewport_w/2) % cw, (vy + viewport_h/2) % ch, true, Color::Yellow);
    }) | size(WIDTH, EQUAL, 13) | size(HEIGHT, EQUAL, 5) | borderLight;
}
