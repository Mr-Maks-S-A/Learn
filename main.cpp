/**
 * @mainpage Программа "Чтение массива из файла"
 * @section desc Описание
 * Программа считывает размер массива и его элементы из файла in.txt,
 * после чего выводит элементы в консоль в обратном порядке.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */

#include <iostream> // Для потоков ввода/вывода (std::cout, std::cerr)
#include <fstream>  // Для работы с файловыми потоками (std::ifstream)
#include <clocale>  // Для настройки локали
#include <cstdlib>  // Для макроса EXIT_SUCCESSSS


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 1. Чтение первого числа — размера будущего массива.
 * 2. Выделение динамической памяти.
 * 3. Заполнение массива и вывод его задом наперед.
 * 4. Освобождение ресурсов.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {

    // Устанавливаем локаль для корректного вывода кириллицы в консоль
    std::setlocale(LC_ALL, "Russian");

    std::ifstream file("in.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл in.txt!" << std::endl;
        return EXIT_FAILURE;
    }

    int size = 0;
    if (!(file >> size) || size <= 0) {
        std::cerr << "Ошибка: некорректный размер массива." << std::endl;
        return EXIT_FAILURE;
    }

    int* arr = new int[size];

    for (int i = 0; i < size; ++i) {
        if (!(file >> arr[i])) {
            std::cerr << "Ошибка: данных в файле меньше, чем ожидалось." << std::endl;
            delete[] arr;
            arr = nullptr; // чтобы не оставить "висячий" указатель при выходе
            return EXIT_FAILURE;
        }
    }

    for (int i = size - 1; i >= 0; --i) {
        std::cout << arr[i] << (i == 0 ? "" : " ");
    }
    std::cout << std::endl;

    // Чистим память
    delete[] arr;
    arr = nullptr; // Хороший тон

    file.close();


     return EXIT_SUCCESS;
}

