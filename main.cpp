/**
 * @mainpage Программа "Двумерный массив"
 * @section desc Описание
 * Программа создает массив 3x6, выводит его и находит индексы min/max элементов.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация двумерного массива 3x6.
 * 2. Вывод массива в виде таблицы с использованием табуляции.
 * 3. Поиск минимального и максимального значений и их индексов.
 * 4. Вывод найденных индексов на экран.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // 1. Создание и инициализация массива 3x6
    int matrix[3][6] = {
        {12, 45, 7, 23, 56, 18},
        {90, 3, 34, 11, 67, 21},
        {5, 88, 42, 99, 14, 30}
    };

    // Переменные для хранения экстремумов и их координат
    int minVal = matrix[0][0];
    int maxVal = matrix[0][0];
    int minRow = 0, minCol = 0;
    int maxRow = 0, maxCol = 0;

    // 2. Вывод массива и поиск индексов
    std::cout << "Массив:" << std::endl;
    for (int i = 0; i < 3; ++i) {      // Цикл по строкам
        for (int j = 0; j < 6; ++j) {  // Цикл по столбцам
            // Вывод элемента
            std::cout << matrix[i][j] << "\t";

            // Логика поиска минимума
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minRow = i;
                minCol = j;
            }

            // Логика поиска максимума
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
        std::cout << std::endl; // Переход на новую строку после вывода всех столбцов
    }

    // 3. Вывод результатов
    std::cout << "\nИндекс минимального элемента: " << minRow << " " << minCol << std::endl;
    std::cout << "Индекс максимального элемента: " << maxRow << " " << maxCol << std::endl;


    return EXIT_SUCCESS;
}
