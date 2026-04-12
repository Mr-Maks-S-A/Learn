/**
 * @mainpage Программа "Угадайка"
 * @section desc Описание
 * Игра, в которой нужно угадать слово. При ошибке выводятся подсказки
 *@note Примечание
 * Реализован достойный рандобизатор основанный на энтропии времени и просто мусора системы
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода
#include <string>   // Для работы со строками из с++
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <cwctype>  // Для std::iswalpha (аналог isalpha для широких символов)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <algorithm> // Для std::min
#include <vector>
#include <random>   // Для генерации случайных чисел
#include <chrono> // Для использования времени как дополнительного зерна

/**
 * @brief Проверяет, состоит ли строка только из букв (поддерживает кириллицу).
 * @param str Широкая строка для проверки.
 * @return true, если в строке только буквы, иначе false.
 */
bool is_alpha_string(const std::wstring& str) {
    if (str.empty()) return false;

    for (wchar_t c : str) {
        // iswalpha корректно обрабатывает Unicode-символы при установленной локали
        if (!std::iswalpha(c)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Безопасный ввод текстовых данных через широкие потоки.
 * @param prompt Сообщение для пользователя.
 * @return Валидная широкая строка.
 */
std::wstring get_string_input(const std::wstring& prompt) {
    std::wstring value;
    while (true) {
        std::wcout << prompt;

        if (!(std::wcin >> value)) {
            std::wcin.clear();
            std::wcin.ignore(10000, L'\n');
            std::wcout << L"Ошибка ввода. Попробуйте снова." << std::endl;
            continue;
        }

        if (!is_alpha_string(value)) {
            std::wcout << L"Ошибка: используйте только буквы." << std::endl;
            continue;
        }

        return value;
    }
}

/**
 * @brief Выводит расширенные подсказки: длину, количество совпадений и "маску" слова.
 * @param target Загаданное слово.
 * @param input Ввод пользователя (уже приведенный к нижнему регистру).
 */
void print_hint(const std::wstring& target, const std::wstring& input) {
    std::wcout << L"\n--- [ АНАЛИЗ ПОПЫТКИ ] ---" << std::endl;

    // 1. Сравнение длины
    if (input.length() < target.length()) {
        std::wcout << L"- Загаданное слово длиннее." << std::endl;
    } else if (input.length() > target.length()) {
        std::wcout << L"- Загаданное слово короче." << std::endl;
    }

    // 2. Формирование маски (угаданные буквы на своих местах)
    std::wstring mask(target.length(), L'*'); // Создаем строку из звёздочек
    int correct_positions = 0;
    size_t min_len = std::min(input.length(), target.length());

    for (size_t i = 0; i < min_len; ++i) {
        if (input[i] == target[i]) {
            mask[i] = target[i]; // Открываем букву в маске
            correct_positions++;
        }
    }

    // 3. Вывод результата анализа
    std::wcout << L"- Совпадений по позициям: " << correct_positions << std::endl;
    std::wcout << L"- Текущий прогресс: ";

    // Выводим маску через пробел для красоты: м * л * * а
    for (wchar_t c : mask) {
        std::wcout << c << L" ";
    }

    std::wcout << L"\n--------------------------\n" << std::endl;
}


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Запрашиваем Имя и сохраняем его в переменную
 * 2. Запрашиваем Фамилию и сохраняем его в переменную
 * 3. Выводим конкатенацию
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Настройка локали для корректной работы с кириллицей
    // Берём настройки языка из операционной системы (LC_CTYPE)
    std::setlocale(LC_ALL, "");
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // 1. Наш запас слов
    std::vector<std::wstring> word_bank = {
        L"малина", L"арбуз", L"клубника", L"программист",
        L"ноутбук", L"алгоритм", L"система", L"ядро"
    };


    // 2. Настройка рандома (современный подход)
    // std::random_device генерирует зерно (seed) на основе энтропии системы
    // но если он "подведет", подстраховываемся временем системы.
    // Это создает максимально непредсказуемое зерно для mt19937.
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::random_device rd;

    // Используем seed_seq для качественной инициализации mt19937
    std::seed_seq seed{
        static_cast<uint32_t>(now & 0xFFFFFFFF),
        static_cast<uint32_t>(rd()),
        static_cast<uint32_t>(reinterpret_cast<std::uintptr_t>(&now)) // Адрес из стека (ASLR)
    };

    std::mt19937 gen(seed); // Вихрь Мерсенна (надежный ГПСЧ)
    //В тиории можно былобы использовать просто не инициализированную пременную забитую мусором
    //но я решил пойти по так сказать более правельному пути


    // Определяем диапазон индексов от 0 до размера вектора - 1
    std::uniform_int_distribution<size_t> dist(0, word_bank.size() - 1);

    // Выбираем случайное слово
    const std::wstring secret_word = word_bank[dist(gen)];


    std::wcout << L"Добро пожаловать в игру Угадайка!" << std::endl;
    std::wcout << L"Я загадал слово, попробуй его отгадать." << std::endl;

    std::wstring user_guess;
    do {
        std::wstring raw_input = get_string_input(L"Введите слово: ");

        // Сразу в нижний регистр для корректного сравнения и в подсказках тоже
        std::wstring lower_guess = raw_input;
        for (auto& c : lower_guess) c = std::towlower(c);

        if (lower_guess == secret_word) {
            std::wcout << L"Победа! Это было слово: " << secret_word << std::endl;
            break;
        } else {
            std::wcout << L"Мимо." << std::endl;
            print_hint(secret_word, lower_guess);
        }
    } while (true);

     return EXIT_SUCCESS;
}

