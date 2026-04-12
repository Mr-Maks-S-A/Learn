/**
 * @mainpage Программа "Приветствие"
 * @section desc Описание
 * Программа релизует методы проверки ввода длятекстовых значений и потом выводит их
 *@note Примечание
 * В std::wstring один элемент (wchar_t) занимает больше места:
 *  В Windows: 2 байта (UTF-16*).
 *  В Linux: 4 байта (UTF-32).
 * Широкая строка выделяет достаточно места, чтобы любая буква (хоть русская, хоть иероглиф)
 * поместилась в один элемент массива. Теперь "Макс" — это  действительно 4 элемента,
 * и функция iswalpha() может корректно их распознать.
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода
#include <string>   // Для работы со строками из с++
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <cwctype>  // Для std::iswalpha (аналог isalpha для широких символов)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
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
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Запрашиваем Имя и сохраняем его в переменную
 * 2. Запрашиваем Фамилию и сохраняем его в переменную
 * 3. Выводим конкатенацию
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Берём настройки языка из операционной системы (LC_CTYPE)
    std::setlocale(LC_ALL, "");

   // Работаем с широкими потоками (wcout, wcin) для корректной обработки UTF-8/Unicode
    std::wstring first_name = get_string_input(L"Введите имя: ");
    std::wstring last_name = get_string_input(L"Введите фамилию: ");

    // Конкатенация широких строк
    std::wstring welcome_msg = L"Здравствуйте, " + first_name + L" " + last_name + L"!";

    std::wcout << welcome_msg << std::endl;

     return EXIT_SUCCESS;
}

