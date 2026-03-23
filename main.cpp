/**
 * @mainpage Программа "Максимум и минимум"
 * @section desc Описание
 * Программа создает массив из 10 целых чисел, выводит их на экран,
 * после чего находит наименьшее и наибольшее значения в этом массиве.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация массива данных.
 * 2. Вывод массива в консоль.
 * 3. Поиск min и max элементов через итерацию.
 * 4. Вывод результатов.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // Инициализация массива
    int numbers[10] = {42, 12, 7, 99, 3, 56, 1, 88, 24, 15};

    // 1. Вывод массива на экран
    std::cout << "Массив: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    // 2. Инициализация переменных min и max первым элементом
    int min = numbers[0];
    int max = numbers[0];

    // 3. Поиск (начинаем со второго элемента, индекс 1)
    for (int i = 1; i < 10; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    // 4. Вывод результатов
    std::cout << "Минимальный элемент: " << min << std::endl;
    std::cout << "Максимальный элемент: " << max << std::endl;

    return EXIT_SUCCESS;
}
