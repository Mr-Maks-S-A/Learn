/**
 * @mainpage Программа "Переворот массива"
 * @section desc Описание
 * Программа реализует разворот массива на месте, используя кастомный шаблонный swap
 * и вывод через функцию print.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для is_copy_assignable_v/is_copy_constructible_v
#include <concepts> // Для std::derived_from, std::integral и т.д.



/**
 * @brief Выводит элементы массива на экран.
 * @tparam T Тип элементов массива (должен поддерживать оператор <<).
 * @param arr Указатель на первый элемент массива.
 * @param size Количество элементов в массиве.
 */
template <typename T>
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
 * @brief Переворачивает массив, меняя порядок элементов на обратный.
 * @param arr  Указатель на массив (изменяется внутри функции).
 * @param size Размер массива.
 * @note Если передан NULL или размер < 2, функция не выполняет никаких действий.
 * @note Требует, чтобы тип T поддерживал копирование и присваивание.
 */
template <typename T>
void reverse(T* arr, size_t size) {

    if (!arr || size < 2) return;

    for (size_t i = 0; i < size / 2; ++i) {
        // Вызываем swap, передавая адреса элементов
        swap(&arr[i], &arr[size - 1 - i]);
    }
}

/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация локали и масиива
 * 2. вывод масиива до разворота
 * 3. разворот
 * 4. вывод масиива после разворота
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    //C++17 сохраняю чтобы не первычислять хотя компилятор скорей всего и без меня так же бы сделал
    const size_t size = std::size(arr);

    std::cout << "До функции reverse: ";
    print(arr, size);

    reverse(arr, size);

    std::cout << "После функции reverse: ";
    print(arr, size);

    return EXIT_SUCCESS;
}
