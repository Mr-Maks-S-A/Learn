/**
 * @mainpage Программа "Считывание двумерного массива из файла"
 * @section desc Описание
 * Программа считывает размеры и содержимое двумерного массива из файла in.txt,
 * после чего выводит его в консоль, разворачивая каждую строку задом наперед.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода
#include <fstream>  // Для работы с файловыми потоками
#include <string>   // Для работы со строками
#include <clocale>  // Библиотека для работы с локалью
#include <cstdlib>  // Для макросов EXIT_SUCCESS
#include <algorithm>// Для std::reverse
#include <iomanip>  // Для std::cout << std::left << std::setw(width) << arr[i];


/**
 * @brief Выводит элементы массива на экран с выравниванием.
 * @tparam T Тип элементов.
 * @param arr Указатель на массив.
 * @param size Размер массива.
 * @param width Ширина колонки (по умолчанию 5).
 */
template <typename T>
void print(const T* arr, size_t size, int width = 5) {
    if (!arr) return;

    for (size_t i = 0; i < size; ++i) {
        // std::left выравнивает по левому краю, std::setw задает ширину
        std::cout << std::left << std::setw(width) << arr[i];
    }
    std::cout << std::endl;
}




/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {

    // Устанавливаем локаль для корректного вывода кириллицы в консоль
    std::setlocale(LC_ALL, "Russian");

    std::ifstream file("in.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка: файл in.txt не найден!" << std::endl;
        return EXIT_FAILURE;
    }

    int rows = 0, cols = 0;
    if (!(file >> rows >> cols) || rows <= 0 || cols <= 0) {
        std::cerr << "Ошибка в структуре файла." << std::endl;
        return EXIT_FAILURE;
    }

    // Выделение памяти
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    // Чтение
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }

    // Вывод с выравниванием и реверсом
    std::cout << "Результат обработки матрицы:\n" << std::endl;
    for (int i = 0; i < rows; ++i) {
        std::reverse(matrix[i], matrix[i] + cols);
        print(matrix[i], static_cast<size_t>(cols));
    }

    //альтернативный вариант
    //for (int i = 0; i < rows; ++i) {
    // Итерируемся по столбцам в обратном порядке:
    // Начинаем с последнего индекса (cols - 1) и идем до 0 включительно.
    // for (int j = cols - 1; j >= 0; --j) {
    //    //std::setw(6) задает фиксированную ширину колонки,
    //    //чтобы числа не "слипались" и таблица была ровной.
    //    std::cout << std::left << std::setw(6) << matrix[i][j];
    // }
    //    //Переход на новую строку после вывода всех столбцов текущей строки
    //    std::cout << "\n";
    // }

    // Очистка
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;

    file.close();

    file.close();


     return EXIT_SUCCESS;
}

