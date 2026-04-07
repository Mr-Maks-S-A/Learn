/**
 * @mainpage Программа "Вывода массива"
 * @section desc Описание
 * Программа содержит функцию print, которая выводит элементы массива произвольного типа
 * и размера на экран, разделяя их пробелами.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для // Для std::is_arithmetic
#include <concepts> // Для std::derived_from, std::integral и т.д.


/**
 * @brief Выводит элементы массива на экран.
 * @tparam T Тип элементов массива (должен поддерживать оператор <<).
 * @param arr Указатель на первый элемент массива.
 * @param size Количество элементов в массиве.
 * @note Ограничение: T должен быть арифметическим типом (целое или число с
 * плавающей точкой).
 */
template <typename T>
requires std::is_arithmetic_v<T>
void print(const T* arr, size_t size) {
    //проверка на пустой указатель
    if (!arr) return;

    //вывод массива в строку путём итерации
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i != size - 1) std::cout << ' ';
    }
    std::cout << std::endl;
}



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация локали и тестовых массивов.
 * 2. Вызов шаблонной функции для вывода масивов
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif


    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double arr2[] = {6.5, 5.2, 4.0, 8.8}; // Пример с double
    int arr3[] = {1, 4, 3, 7, 5};


    // В C++17 и выше можно использовать std::size() вместо sizeof
    print(arr1, std::size(arr1));
    print(arr2, std::size(arr2));
    print(arr3, std::size(arr3));

    // Старый стиль (опасно: если arr станет указателем, результат будет неверным)
    // size_t s1 = sizeof(arr) / sizeof(arr[0]);

    // Новый стиль (безопасно: не скомпилируется, если это не массив)
    // size_t s2 = std::size(arr);

    return EXIT_SUCCESS;
}
