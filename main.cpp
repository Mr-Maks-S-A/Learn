/**
 * @mainpage Программа "Ввод массива с консоли"
 * @section desc Описание
 * Программа позволяет пользователю задать размер массива и заполнить его
 * значениями с консоли. Используется динамическое выделение памяти.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для is_copy_assignable_v/is_copy_constructible_v
#include <concepts> // Для std::derived_from, std::integral и т.д.
#include <limits> // Обязательно для std::numeric_limits


/**
 * @brief Универсальная функция безопасного ввода числа с консоли.
 * @tparam T Тип вводимого значения (должен быть арифметическим).
 * @param prompt Сообщение для пользователя.
 * @param min_val Минимально допустимое значение.
 * @return Считанное и проверенное значение.
 */
template <typename T>
requires std::is_arithmetic_v<T>
T get_input(const std::string& prompt, T min_val = std::numeric_limits<T>::lowest()) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите корректное число.\n";
            continue;
        }

        if (value < min_val) {
            std::cout << "Ошибка: значение должно быть не меньше " << min_val << ".\n";
            continue;
        }

        // Очищаем буфер от лишних символов после ввода числа (на случай ввода "10 abc")
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}



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
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Ожидаем ввод пользователя
 * 2. Инициализируем масив
 * 3. Заполняем масив
 * 4. Выводим заполненный масив
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // 1. Получаем размер массива (минимум 1)
    int size = get_input<int>("Введите размер массива: ", 1);

    // 2. Выделяем память под динамический массив
    int* arr = new int[size];

    // 3. Заполняем массив, используя ту же функцию get_input
    for (int i = 0; i < size; ++i) {
        std::string prompt = "arr[" + std::to_string(i) + "] = ";
        arr[i] = get_input<int>(prompt);
    }

    // 4. Вывод результата (используем нашу наработку)
    std::cout << "Введённый массив: ";
    print(arr, static_cast<size_t>(size));

    // 5. Обязательная очистка памяти
    delete[] arr;
    arr = nullptr; // Хорошая практика: зануляем указатель после удаления


    return EXIT_SUCCESS;
}
