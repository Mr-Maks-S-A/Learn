/**
 * @mainpage Программа "Числа Фибоначчи"
 * @section desc Описание
 * Программа запрашивает у пользователя количество чисел и выводит
 * соответствующую последовательность Фибоначчи, используя рекурсию.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)



/**
 * @brief Рекурсивная функция для нахождения n-го числа Фибоначчи.
 * @param n Порядковый номер числа (начиная с 1).
 * @return unsigned long long Значение числа Фибоначчи.
 */
unsigned long long getFibonacci(int n) {
    // Базовые случаи: 1-е число = 0, 2-е число = 1
    if (n <= 1) return 0;
    if (n == 2) return 1;

    // Рекурсивный шаг: сумма двух предыдущих
    return getFibonacci(n - 1) + getFibonacci(n - 2);
}



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Запрос количества чисел у пользователя.
 * 2. Циклический вызов рекурсивной функции для формирования ряда.
 * 3. Вывод результата в консоль.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    int count = 0;
    std::cout << "Введите число: ";
    if (!(std::cin >> count) || count < 0) {
        std::cout << "Ошибка: введите положительное целое число." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Числа Фибоначчи: ";
    for (int i = 1; i <= count; ++i) {
        std::cout << getFibonacci(i);
        if (i < count) std::cout << " "; // Красивый отступ между числами
    }
    std::cout << std::endl;


    return EXIT_SUCCESS;
}
