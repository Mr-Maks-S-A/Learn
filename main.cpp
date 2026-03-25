/**
 * @mainpage Программа "Арифметические функции"
 * @section desc Описание
 * Учебный проект для реализации базовых вычислений (сумма, разность, умножение, деление)
 *
 * @note **Оптимизация с constexpr и шаблонами**
 * Функции помечены ключевым словом `constexpr`, что позволяет производить
 * вычисления на этапе компиляции, если аргументы являются константами.
 * Использование шаблонов `<typename T>` обеспечивает универсальность типов.
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)


/**
 * @brief Складывает два числа.
 * @tparam T Тип операндов (числовой тип).
 * @param a Первое слагаемое.
 * @param b Второе слагаемое.
 * @return Сумма a и b.
 */
template <typename T>
FUNC_CONSTEXPR T sum(T a, T b) {
    return a + b;
}

/**
 * @brief Вычисляет разность двух чисел.
 * @tparam T Тип операндов.
 * @param a Уменьшаемое.
 * @param b Вычитаемое.
 * @return Результат вычитания (a - b).
 */
template <typename T>
FUNC_CONSTEXPR T diff(T a, T b) {
    return a - b;
}

/**
 * @brief Вычисляет произведение двух чисел.
 * @tparam T Тип операндов.
 * @param a Первый множитель.
 * @param b Второй множитель.
 * @return Результат умножения.
 */
template <typename T>
FUNC_CONSTEXPR T multiplication(T a, T b) {
    return a * b;
}

/**
 * @brief Выполняет деление первого числа на второе.
 * @details Функция выполняет приведение типов к double, чтобы избежать
 * потери дробной части при делении целых чисел.
 * @tparam T Тип операндов.
 * @param a Делимое.
 * @param b Делитель.
 * @return Частное в формате числа с плавающей запятой (double).
 */
template <typename T>
FUNC_CONSTEXPR double division(T a, T b) {
    return static_cast<double>(a) / b;
}






/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация целочисленных переменных.
 * 2. Последовательный вызов функций вычисления.
 * 3. Форматированный вывод результатов.
 *
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    // Инициализация базовых переменных как констант времени компиляции
    VAR_CONSTEXPR int a = 5, b = 10;

    // Вызовы функций
    VAR_CONSTEXPR int s = sum(a, b);
    VAR_CONSTEXPR int dif = diff(a, b);
    VAR_CONSTEXPR int mult = multiplication(a, b);
    VAR_CONSTEXPR double div = division(a, b);

    std::cout << a << " + " << b << " = " << s << std::endl;
    std::cout << a << " - " << b << " = " << dif << std::endl;
    std::cout << a << " * " << b << " = " << mult << std::endl;
    std::cout << a << " / " << b << " = " << div << std::endl;


    return EXIT_SUCCESS;
}
