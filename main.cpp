/**
 * @mainpage Программа ""
 * @section desc Описание
 *
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для // Для std::is_arithmetic




/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация локали и тестовых переменных x и y.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif


    return EXIT_SUCCESS;
}
