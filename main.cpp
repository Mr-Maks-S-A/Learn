/**
 * @mainpage Программа "Обмен значениями"
 * @section desc Описание
 * Демонстрация работы ссылок в C++ на примере функции swap.
 *
 * @note Примечание
 * Реализованы алгоритмы обмена значений без использования временной переменной.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для std::is_copy_assignable и других проверок


/**
 * @brief Классический шаблонный обмен через временную переменную.
 * @param a Ссылка на первую переменную.
 * @param b Ссылка на вторую переменную.
 * @details Самый безопасный и универсальный метод.
 * Работает с любыми типами, поддерживающими копирование.
 */
template <typename T>
void swapBasic(T& a, T& b) {
    // Проверяем, можно ли копировать и присваивать данный тип
    static_assert(std::is_copy_assignable<T>::value, "Тип должен поддерживать присваивание!");

    if (&a == &b) return;

    T temp = a;
    a = b;
    b = temp;
}

/**
 * @brief Шаблонная функция обмена через XOR.
 * @param a Ссылка на первую переменную.
 * @param b Ссылка на вторую переменную.
 * @note ВНИМАНИЕ: Небезопасно, если &a == &b (переменная занулятся).
 * @details Ограничение: типы должны быть целочисленными (XOR не работает с float/double).
 */
template <typename T>
void swapInPlace(T& a, T& b) {
    static_assert(std::is_integral<T>::value, "XOR-обмен работает только с целыми числами!");
    if (&a == &b) return;

    a ^= b;
    b ^= a;
    a ^= b;
}

/**
 * @brief Шаблонная функция арифметического обмена между двумя переменными.
 * @param a Ссылка на первую переменную.
 * @param b Ссылка на вторую переменную.
 * @note Ограничение: типы должны быть арифметическими (числами).
 * @details Использует арифметический метод обмена (без буфера).
 */
template <typename T>
void swapArith(T& a, T& b) {
    static_assert(std::is_arithmetic<T>::value, "Тип должен быть числовым!");
    if (&a == &b) return;

    a = a + b;
    b = a - b;
    a = a - b;
}



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация целочисленных переменных.
 * 2. Вывод исходных значений в консоль.
 * 3. Вызов функций swap с передачей аргументов по ссылке.
 * 4. Вывод измененных значений для проверки результата.
 * 5. Повтор пунктов 2,3,4 но с разными функциями.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // Данные для тестов
    int a = 5, b = 8;
    long long x = 100, y = 200;
    double da = 1.1, db = 2.2;

    std::cout << "--- Тест 1: Классический swap (double) ---" << std::endl;
    std::cout << "До: da = " << da << ", db = " << db << std::endl;
    swapBasic(da, db);
    std::cout << "После: da = " << da << ", db = " << db << std::endl;

    std::cout << "\n--- Тест 2: Арифметический swap (int) ---" << std::endl;
    std::cout << "До: a = " << a << ", b = " << b << std::endl;
    swapArith(a, b);
    std::cout << "После: a = " << a << ", b = " << b << std::endl;

    std::cout << "\n--- Тест 3: XOR swap (long long) ---" << std::endl;
    std::cout << "До: x = " << x << ", y = " << y << std::endl;
    swapInPlace(x, y);
    std::cout << "После: x = " << x << ", y = " << y << std::endl;

    return EXIT_SUCCESS;
}
