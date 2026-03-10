/**
 * @mainpage Программа "Повторите слово"
 * 
 * @section desc Описание
 * Программа запрашивает у пользователя слово и выводит его обратно на экран.
 * через стандартные потоки ввода (std::cin) и вывода (std::cout).
 * 
 * @section notes Примечания
 * - Используется тип std::string для хранения текстовых данных.
 * - Демонстрируется работа с потоковым вводом до первого пробела.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <string>   // Для работы со строками std::string
#include <cstdlib>  // Для макроса EXIT_SUCCESS (изучил недавно https://en.cppreference.com/w/cpp/utility/program/EXIT_status.html)
#include <clocale> // Библиотека для работы с локалью (setlocale)


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Объявление строковой переменной.
 * 2. Вывод приглашения к вводу.
 * 3. Чтение слова из консоли.
 * 4. Форматированный вывод результата.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // 1. Инициализация строковой переменной
    std::string word;

    // 2. Запрос данных
    std::cout << "Введите слово:" << std::endl;

    // 3. Считывание слова
    // Оператор >> считывает данные до первого пробела.
    // Если нужно считать целую строку с пробелами, используют std::getline(std::cin, word).
    if (!(std::cin >> word)) {
        std::cerr << "Ошибка ввода!" << std::endl;
        return EXIT_FAILURE;
    }

    // 4. Вывод результата
    std::cout << "Вы ввели:\n"
              << word << std::endl;


    return EXIT_SUCCESS;
}
