/**
 * @mainpage Программа "Одинаковые, но разные функции"
 * @section desc Описание
 * Программа демонстрирует использование пространств имен (namespace) для создания
 * функций с идентичными сигнатурами, выполняющих различные арифметические операции.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <type_traits> // Необходимо для // Для std::is_arithmetic



/** @namespace Addition Содержит реализацию сложения */
namespace Addition {
    template <typename T>
    T calc(T x, T y) {
        static_assert(std::is_arithmetic<T>::value, "Тип должен быть числовым!");
        return x + y;
    }
}

/** @namespace Subtraction Содержит реализацию вычитания */
namespace Subtraction {
    template <typename T>
    T calc(T x, T y) {
        static_assert(std::is_arithmetic<T>::value, "Тип должен быть числовым!");
        return x - y;
    }
}

/** @namespace Multiplication Содержит реализацию умножения */
namespace Multiplication {
    template <typename T>
    T calc(T x, T y) {
        static_assert(std::is_arithmetic<T>::value, "Тип должен быть числовым!");
        return x * y;
    }
}

/** @namespace Division Содержит реализацию деления */
namespace Division {
    template <typename T>
    T calc(T x, T y) {
        static_assert(std::is_arithmetic<T>::value, "Тип должен быть числовым!");
        if (y == 0) return 0; // Базовая защита от деления на ноль
        return x / y;
    }
}



/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Инициализация локали и тестовых переменных x и y.
 * 2. Последовательный вызов функций calc из разных пространств имен.
 * 3. Вывод результатов арифметических действий в консоль.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif


    int x = 6;
    int y = 9;

    std::cout << "x = " << x << ", y = " << y << std::endl;

    // Вызовы функций с указанием конкретного пространства имен
    std::cout << "Сложение: " << Addition::calc(x, y) << std::endl;
    std::cout << "Вычитание: " << Subtraction::calc(x, y) << std::endl;
    std::cout << "Умножение: " << Multiplication::calc(x, y) << std::endl;
    std::cout << "Деление: "   << Division::calc(x, y) << std::endl;

    return EXIT_SUCCESS;
}
