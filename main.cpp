/**
 * @mainpage Программа "Работа с файлами"
 * @section desc Описание
 * Программа открывает файл in.txt и выводит каждое слово с новой строки.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout, std::cerr)
#include <fstream>  // Для работы с файловыми потоками (std::ifstream)
#include <string>   // Для работы со строками std::string
#include <clocale>  // Для настройки локали
#include <cstdlib>  // Для макроса EXIT_SUCCESS


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Попытка открытия файла "in.txt".
 * 2. Потоковое чтение слов до конца файла.
 * 3. Вывод каждого слова в стандартный поток вывода.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {

    // Устанавливаем локаль для корректного вывода кириллицы в консоль
    std::setlocale(LC_ALL, "Russian");

    // Инициализация файлового потока на чтение
    std::ifstream file("in.txt");

    // Проверка успешности открытия
    if (!file.is_open()) {
        // Используем std::cerr для ошибок — это хороший тон системного программиста
        std::cerr << "Ошибка: файл in.txt не найден!" << std::endl;
        return 1;
    }

    std::string word;

    while (file >> word) {
        std::cout << word << "\n";
    }

    file.close();

     return EXIT_SUCCESS;
}

