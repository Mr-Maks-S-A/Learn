/**
 * @mainpage Программа "Упорядочить числа"
 * @section desc Описание

 *
 * @section notes Примечания

 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <bitset>   // Для подключения структуры для более оптимального хранения битовых данных
#include <initializer_list> // Для шаблонного метода инициализации bitset

/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1.
 * 2.
 * 3.
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
