/**
 * @mainpage Программа "Снова swap"
 * @section desc Описание
 * Реализация функции swap с использованием указателей и шаблонов.
 * Включена проверка на нулевые указатели и самообмен.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для is_copy_assignable_v/is_copy_constructible_v


/**
 * @brief Обменивает значения двух переменных через указатели.
 * @tparam T Тип обмениваемых значений.
 * @param a Указатель на первую переменную.
 * @param b Указатель на вторую переменную.
 */
template <typename T>
void swap(T* a, T* b) {
    // Проверка на этапе компиляции: можно ли этот тип копировать?
    // Если нет — код даже не соберется, выдав понятную ошибку.
    static_assert(std::is_copy_assignable_v<T>, "Тип T должен поддерживать оператор присваивания!");
    static_assert(std::is_copy_constructible_v<T>, "Тип T должен иметь конструктор копирования!");

    // Ранний выход, если указатели невалидны или указывают на одно место
    if (!a || !b || a == b) return;

    // 3. Классический обмен через разыменование
    T temp = *a;
    *a = *b;
    *b = temp;
}



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация локали
 * 2. Проведение теста функции swap с указателями int
 * 3. Проведение теста функции swap с указателями double
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif


    int a = 5, b = 8;

    std::cout << "a = " << a << ", b = " << b << std::endl;

    // Передаем адреса переменных через оператор &
    swap(&a, &b);

    std::cout << "a = " << b << ", b = " << a << " (исходные имена для примера)" << std::endl;
    std::cout << "Результат: a = " << a << ", b = " << b << std::endl;

    // Дополнительный тест с double (благодаря шаблону)
    double x = 1.5, y = 9.9;
    std::cout << "x = " << x << ", y = " << y << " (исходные значения)"<< std::endl;
    swap(&x, &y);
    std::cout << "Результат: x = " << x << ", y = " << y << std::endl;

    return EXIT_SUCCESS;
}
