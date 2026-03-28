/**
 * @mainpage Программа "Адреса переменных"
 * @section desc Описание
 * Программа выводит в консоль адреса оперативной памяти и размеры основных типов данных.
 * Используются оператор взятия адреса (&) и встроенная функция sizeof().
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Объявление переменных разных типов.
 * 2. Вывод адреса каждой переменной через оператор &.
 * 3. Вывод размера каждого типа через sizeof().
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // 1. Объявление переменных
    int i = 0;
    short s = 0;
    long l = 0;
    long long ll = 0;
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    bool b = false;

    // 2. Вывод данных (тип: адрес размер)
    // Используем (void*), чтобы адрес выводился именно как число, а не как строка (актуально для char, но полезно для единообразия)
    std::cout << "short: " << &s << " " << sizeof(s) << std::endl;
    std::cout << "int: " << &i << " " << sizeof(i) << std::endl;
    std::cout << "long: " << &l << " " << sizeof(l) << std::endl;
    std::cout << "long long: " << &ll << " " << sizeof(ll) << std::endl;
    std::cout << "float: " << &f << " " << sizeof(f) << std::endl;
    std::cout << "double: " << &d << " " << sizeof(d) << std::endl;
    std::cout << "long double: " << &ld << " " << sizeof(ld) << std::endl;
    std::cout << "bool: " << (void*)&b << " " << sizeof(b) << std::endl;



    return EXIT_SUCCESS;
}
