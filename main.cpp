/**
 * @mainpage Программа "Устранение дублирования"
 * @section desc Описание
 * Программа демонстрирует использование функций для устранения дублирования кода
 * на примере возведения числа в целую положительную степень.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)

/**
 * @brief Функция для возведения числа в степень и вывода результата.
 * @param value Основание степени.
 * @param power Показатель степени (целое число).
 */
void printPower(int value, int power) {
    int result = 1;

    // Алгоритм возведения в степень через цикл
    for (int i = 0; i < power; ++i) {
        result *= value;
    }

    // Вывод согласно требуемому формату
    std::cout << value << " в степени " << power << " = " << result << std::endl;
}
/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1.Вызов функции для чисел 5, 3 и 4 с соответствующими степенями.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // Вызываем функцию вместо дублирования кода
    printPower(5, 2);
    printPower(3, 3);
    printPower(4, 4);


    return EXIT_SUCCESS;
}
