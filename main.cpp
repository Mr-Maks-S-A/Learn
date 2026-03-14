/**
 * @mainpage Программа "Таблица истинности"
 * @section desc Описание
 * Программа демонстрирует построение таблиц истинности для логических операторов И (AND) и ИЛИ (OR).
 * Данные хранятся в оптимизированном виде с использованием контейнера std::bitset.
 *
 * @section notes Примечания
 * - Используется структура std::bitset для эффективного хранения бит.
 * - Демонстрируется работа с логическими операторами над элементами bitset.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <bitset>   // Для подключения структуры для более оптимального хранения битовых данных
#include <initializer_list> // Для шаблонного метода инициализации bitset


/**
 * @brief Создает std::bitset из списка инициализации bool.
 * * Данная функция позволяет удобно инициализировать bitset синтаксисом {true, false...}.
 * Заполнение происходит от младшего значащего бита (LSB) к старшему (MSB).
 *
 * @tparam N Размер создаваемого bitset (количество бит).
 * @param list Список логических значений (например, {true, false, true}).
 * @return std::bitset<N> Объект bitset с установленными значениями.
 * @note Если список list длиннее, чем N, лишние элементы будут проигнорированы.
 * Если список короче, оставшиеся биты останутся в состоянии false.
 */
template<size_t N>
std::bitset<N> make_bitset(std::initializer_list<bool> list) {
    std::bitset<N> bits;
    size_t i = 0;
    for (bool b : list) {
        if (i >= N) break;
        if (b) bits.set(i); // Заполняем от младшего к старшему
        ++i;
    }
    return bits;
}


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация "матрицы" входных данных (пары значений для проверки) через bitset.
 * 2. Итерация по битам с шагом 2 (так как работаем с парами).
 * 3. Вычисление и вывод результатов операций логического ИЛИ (||) и логического И (&&).
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    /// @brief Количество строк в логической матрице
    const int rows = 4;
    /// @brief Количество столбцов (входных аргументов для операции)
    const int cols = 2;

    // Матрица входных данных, упакованная в bitset.
    // Каждые два бита представляют собой пару значений для логической операции.
    auto matrix = make_bitset<(rows*cols)>(
        {    true   ,true   // Строка 0
            ,false  ,true   // Строка 1
            ,true   ,false  // Строка 2
            ,false  ,false  // Строка 3
        });


    // Итерируемся по парам бит.
    std::cout << "Оператор: || \n";
    for(int8_t i = 0;i < matrix.size(); i+=cols) {
            // Выводим значение бита (используем boolalpha для наглядности)
                std::cout   << std::boolalpha
                            << matrix[i] << "\t"
                            << matrix[i+1] << "\t"
                            << (matrix[i] || matrix[i+1]);
                std::cout << "\n";
    }


    // Итерируемся по парам бит.
    std::cout << "\nОператор: && \n";
    for(int8_t i = 0;i < matrix.size(); i+=cols) {
        // Выводим значение бита (используем boolalpha для наглядности)
        std::cout   << std::boolalpha
        << matrix[i] << "\t"
        << matrix[i+1] << "\t"
        << (matrix[i] && matrix[i+1]);
        std::cout << "\n";
    }


    return EXIT_SUCCESS;
}
