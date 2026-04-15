/**
 * @mainpage Программа "Пользовательский массив в файл"
 * @section desc Описание
 * Программа запрашивает у пользователя данные, формирует динамический массив
 * и сохраняет его в файл out.txt в обратном порядке.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода
#include <fstream>  // Для работы с файловыми потоками
#include <string>   // Для работы со строками
#include <clocale>  // Библиотека для работы с локалью
#include <cstdlib>  // Для макросов EXIT_SUCCESS
#include <limits>
#include <concepts> // Для std::is_arithmetic_v в концептах



/**
 * @brief Универсальная функция безопасного ввода числа с консоли.
 * @note из старого кода : https://github.com/Mr-Maks-S-A/Learn/blob/v1.10.1/main.cpp
 */
template <typename T>
requires std::is_arithmetic_v<T>
T get_input(const std::string& prompt, T min_val = std::numeric_limits<T>::lowest()) {
    T value;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите корректное число.\n";
            continue;
        }

        if (value < min_val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: значение должно быть не меньше " << min_val << ".\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Ввод данных масиива  (размер и ячейки)
 * 2. открытие файла
 * 3. запись в файл
 * 4. закрытие файла
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {

    // Устанавливаем локаль для корректного вывода кириллицы в консоль
    std::setlocale(LC_ALL, "Russian");


    // Используем шаблон для получения размера (минимум 1 элемент)
    int size = get_input<int>("Введите размер массива: ", 1);

    int* arr = new int[size];

    // Заполнение
    for (int i = 0; i < size; ++i) {
        std::string p = "arr[" + std::to_string(i) + "] = ";
        arr[i] = get_input<int>(p);
    }

    std::ofstream file("out.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка записи!" << std::endl;
        delete[] arr;
        arr = nullptr;
        return EXIT_FAILURE;
    }

    file << size << "\n";
    for (int i = size - 1; i >= 0; --i) {
        file << arr[i] << (i == 0 ? "" : " ");
    }
    file << std::endl;

    file.close();
    delete[] arr;
    arr = nullptr;

    std::cout << "Файл успешно сохранен." << std::endl;


     return EXIT_SUCCESS;
}

