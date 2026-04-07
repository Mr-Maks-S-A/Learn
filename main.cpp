/**
 * @mainpage Программа "Динамическая таблица умножения"
 * @section desc Описание
 * Программа создает двумерный массив в куче, заполняет* его значениями
 * таблицы умножения и корректно освобождает память.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для is_copy_assignable_v/is_copy_constructible_v
#include <concepts> // Для std::derived_from, std::integral и т.д.
#include <limits> // Обязательно для std::numeric_limits
#include <iomanip> // Для std::setw (красивое выравнивание колонок)


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
 * @brief Создаёт двумерный динамический массив в куче.
 * @param[in] rows Количество строк.
 * @param[in] cols Количество столбцов.
 * @return Указатель на массив указателей (int**).
 * @note Память выделяется в два этапа: сначала массив указателей, затем строки.
 */
int** create_two_dim_array(int rows, int cols) {
    int** arr = new int*[rows]; // Массив указателей на строки
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols]; // Сами строки
    }
    return arr;
}

/**
 * @brief Заполняет массив значениями таблицы умножения.
 * @details Каждый элемент получает значение (номер_строки * номер_столбца).
 * @param[out] arr Указатель на двумерный массив.
 * @param[in]  rows Количество строк.
 * @param[in]  cols Количество столбцов.
 */
void fill_two_dim_array(int** arr, int rows, int cols) {
    if (!arr) return;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = (i + 1) * (j + 1);
        }
    }
}

/**
 * @brief Выводит двумерный массив в консоль в виде таблицы.
 * @param[in] arr  Указатель на двумерный массив.
 * @param[in] rows Количество строк.
 * @param[in] cols Количество столбцов.
 * @note Использует std::setw для выравнивания колонок.
 */
void print_two_dim_array(int** arr, int rows, int cols) {
    if (!arr) return;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(4) << arr[i][j];
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Каскадно освобождает память двумерного массива.
 * @param[in,out] arr  Указатель на массив (после удаления зануляется).
 * @param[in]     rows Количество строк, которые нужно очистить.
 * @warning Порядок удаления обратен порядку создания во избежание утечек памяти.
 */
void delete_two_dim_array(int** arr, int rows) {
    if (!arr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i]; // Удаляем каждую строку
        arr[i] = nullptr;
    }
    delete[] arr; // Удаляем массив указателей
}



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Ожидаем ввод пользователя для строк и столбцов
 * 2. Инициализируем таблицу/матрицу
 * 3. Заполняем таблицу/матрицу
 * 4. Выводим заполненную таблицу/матрицу
 * 5. Освобождаем и зануляем память
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // 1. Получаем размерность
    int rows = get_input<int>("Введите количество строк: ", 1);
    int cols = get_input<int>("Введите количество столбцов: ", 1);

    // 2. Создание
    int** table = create_two_dim_array(rows, cols);

    // 3. Заполнение
    fill_two_dim_array(table, rows, cols);

    // 4. Вывод
    std::cout << "Таблица умножения:" << std::endl;
    print_two_dim_array(table, rows, cols);

    // 5. Очистка (ВАЖНО: удаляем в порядке, обратном созданию)
    delete_two_dim_array(table, rows);
    table = nullptr;

    return EXIT_SUCCESS;
}
