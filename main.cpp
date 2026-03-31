/**
 * @mainpage Программа "Считающая функция"
 * @section desc Описание
 * Программа вызывает функцию в цикле,
 * а функция ведет внутренний учет количества вызовов
 * при помощи статичесской переменной.
 *
 * @note Примечание
 *
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
// #include <type_traits> // Необходимо для std::is_copy_assignable и других проверок


/**
 * @brief Функция, отслеживающая количество своих вызовов.
 * * @details Использует внутреннюю статическую переменную @c counter.
 * При каждом вызове значение увеличивается на единицу и выводится в консоль.
 * * @return void
 */
void counting_function() {
    /** * @brief Статический счетчик вызовов.
     * Инициализируется нулем только при первом обращении к функции.
     */
    static int counter = 0;
    counter++;
    std::cout << "Количество вызовов функции counting_function(): " << counter << std::endl;
}


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Запуск цикла от 0 до 14 (всего 15 итераций).
 * 2. Вызов функции counting_function() на каждой итерации.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif


    for (int i = 0; i < 15; i++) {
        counting_function();
    }

    return EXIT_SUCCESS;
}
