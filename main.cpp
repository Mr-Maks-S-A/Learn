/**
 * @mainpage Программа "Compare_numbers"
 * @section desc Описание
 * Программа сравнивает два целых числа в диапазоне (-100, 100).
 * Особенность программы заключается в выводе результата сравнения
 * исключительно в текстовом (словесном) виде.
 *
 * @section notes Примечания
 * Поддерживаются отрицательные числа. Реализована базовая проверка на корректность ввода.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)


/**
 * @brief Преобразует число от -99 до 99 в текстовое представление на русском языке.
 * @param n Целое число для преобразования.
 * @return std::string Строка с текстовым описанием числа (например, "минус пятьдесят три").
 */
std::string numberToText(int n) {
    if (n == 0) return "ноль";

    // Обработка отрицательного знака
    std::string result = "";
    if (n < 0) {
        result += "минус ";
        n = -n;
    }

    // Справочники числительных
    const char* units[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    const char* teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    const char* tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};

    // Логика формирования фразы
    if (n >= 10 && n <= 19) {
        result += teens[n - 10];
    } else {
        if (n >= 20) {
            result += tens[n / 10];
            if (n % 10 != 0) result += " ";
        }
        result += units[n % 10];
    }
    return result;
}




/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Считывание двух целых чисел с проверкой на валидность (числовой ввод).
 * 2. Проверка вхождения чисел в допустимый диапазон (-100 < n < 100).
 * 3. Конвертация чисел в строковый формат через numberToText().
 * 4. Сравнение значений и вывод итоговой фразы в консоль.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    int first_namber, second_namber;

    // Ввод первого числа
    std::cout << "Введите целое число: ";
    if (!(std::cin >> first_namber)) {
        std::cerr << "Ошибка: введено не числовое значение!" << std::endl;
        // Необязательная, но полезная проверка на корректность ввода
        return EXIT_FAILURE;
    }


    // Ввод второго числа
    std::cout << "Введите целое число: ";
    if (!(std::cin >> second_namber)) {
        std::cerr << "Ошибка: введено не числовое значение!" << std::endl;
        // Необязательная, но полезная проверка на корректность ввода
        return EXIT_FAILURE;
    }

    std::cout << "\n";

    // Проверка бизнес-логики: диапазон (-100, 100)
    if (first_namber <= -100 || first_namber >= 100 || second_namber <= -100 || second_namber >= 100) {
        std::cout << "Ошибка! Одно из чисел вне диапазона!" << std::endl;
        return EXIT_SUCCESS;
    }

    // Получение текстовых представлений
    std::string textA = numberToText(first_namber);
    std::string textB = numberToText(second_namber);

    // Сравнение и финальный вывод
    if (first_namber > second_namber) {
        std::cout << textA << " больше чем " << textB << std::endl;
    } else if (first_namber < second_namber) {
        std::cout << textA << " меньше чем " << textB << std::endl;
    } else {
        std::cout << textA << " равно " << textB << std::endl;
    }



    return EXIT_SUCCESS;
}
