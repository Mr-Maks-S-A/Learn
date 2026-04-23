#include "ConsoleUI.hpp"
#include <algorithm>

using namespace ftxui;

ConsoleUI::ConsoleUI(World& world, Rules& rules)
: world_(world), next_buffer_(world.width, world.height), rules_(rules) {}

ConsoleUI::~ConsoleUI() {
    thread_active_ = false;
}

void ConsoleUI::Run() {
    // 1. Поля ввода
    Component input_b = Input(&birth_str_, "3");
    Component input_s = Input(&survive_str_, "23");

    // 2. Кнопка применения правил
    Component btn_apply = Button("Применить", [&] {
        parse_rules("B" + birth_str_ + "/S" + survive_str_, rules_);
    }, ButtonOption::Ascii());

    auto settings_container = Container::Vertical({ input_b, input_s, btn_apply });

    // 3. Основной рендерер
    auto renderer = Renderer(settings_container, [&] {
        return hbox({
            vbox({
                text(" CONWAY'S GAME OF LIFE ") | bold | hcenter | color(Color::White) | bgcolor(Color::Blue),
                 RenderCanvas() | flex | reflect(canvas_box_) | borderHeavy
            }) | flex,
            RenderSidebar() | size(WIDTH, EQUAL, 30)
        });
    });

    // 4. Обработка событий
    auto main_component = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            auto m = event.mouse();
            if (m.button == Mouse::Left && m.motion == Mouse::Pressed) {
                int mx = (m.x - canvas_box_.x_min) * 2;
                int my = (m.y - canvas_box_.y_min) * 4;
                uint32_t gx = (mx + cam_x_ + world_.width) % world_.width;
                uint32_t gy = (my + cam_y_ + world_.height) % world_.height;
                world_.matrix[gy * world_.width + gx].is_alive = !world_.matrix[gy * world_.width + gx].is_alive;
                return true;
            }
        }
        if (event == Event::Character('p')) is_running_ = !is_running_;
        if (event == Event::Character('w')) cam_y_ -= 4;
        if (event == Event::Character('s')) cam_y_ += 4;
        if (event == Event::Character('a')) cam_x_ -= 4;
        if (event == Event::Character('d')) cam_x_ += 4;
        return false;
    });

    // 5. Поток вычислений
    std::thread sim_thread([&] {
        while (thread_active_) {
            if (is_running_) {
                update_world(world_, next_buffer_, rules_);
                world_ = next_buffer_;
                screen_.PostEvent(Event::Custom);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });

    screen_.Loop(main_component);
    thread_active_ = false;
    sim_thread.join();
}

Element ConsoleUI::RenderCanvas() {
    int w = (canvas_box_.x_max - canvas_box_.x_min) * 2;
    int h = (canvas_box_.y_max - canvas_box_.y_min) * 4;
    if (w <= 0 || h <= 0) return text("Инициализация...");

    auto c = Canvas(w, h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            uint32_t gx = (x + cam_x_ + world_.width) % world_.width;
            uint32_t gy = (y + cam_y_ + world_.height) % world_.height;
            const auto& cell = world_.matrix[gy * world_.width + gx];
            if (cell.is_alive) {
                Color col = cell.age > 10 ? Color::Blue : (cell.age > 0 ? Color::Cyan : Color::Green);
                c.DrawPoint(x, y, true, col);
            }
        }
    }
    return canvas(std::move(c));
}

Element ConsoleUI::RenderSidebar() {
    return vbox({
        window(text(" СТАТИСТИКА "), vbox({
            hbox({ text("Поколение: "), text(std::to_string(world_.generation)) | color(Color::Yellow) }),
                                          hbox({ text("Статус:    "), text(is_running_ ? "RUNNING" : "PAUSED") | color(is_running_ ? Color::Green : Color::Red) }),
        })),
        window(text(" КОМПАС "), center(RenderCompass())),
                filler(),
                text(" Управление: ") | bold,
                text(" [P] Старт/Пауза"),
                text(" [WASD] Камера"),
                text(" [Click] Рисовать"),
    });
}

Element ConsoleUI::RenderCompass() {
    return canvas([&](Canvas& c) {
        c.DrawBlock(5, 2, true);
        int target_x = 5 + (cam_x_ * 5 / (int)world_.width);
        int target_y = 2 + (cam_y_ * 2 / (int)world_.height);
        c.DrawPointLine(5, 2, target_x, target_y, Color::Red);
    }) | size(WIDTH, EQUAL, 11) | size(HEIGHT, EQUAL, 5) | borderLight;
}
