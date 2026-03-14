/**
 * @mainpage Программа "Гороскоп"
 * @section desc Описание
 * Программа запрашивает данные пользователя (пол, знак зодиака, возраст)
 * и выводит персональное предсказание на основе заданных критериев.
 *
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream> // Для потоков ввода/вывода (std::cout)
#include <cstdlib>  // Для макроса EXIT_SUCCESS
#include <clocale>  // Библиотека для работы с локалью (setlocale)
#include <string>   // Для работы со строками
#include <vector>   // Для работы с векторами
#include <algorithm> // Для std::find


/**
 * @brief Точка входа в программу.
 * * @details Процесс работы:
 * 0. Инициализация допустимых списков (пол, знаки).
 * 1. Поэтапный ввод данных с валидацией.
 * 2. Логическая группировка знаков по стихиям.
 * 3. Вывод предсказания на основе комбинированных условий.
 *
 * @return int Статус завершения программы (EXIT_SUCCESS в случае успеха).
 */
int main() {
    // Проверка на Windows (макрос _WIN32 определен и в 32, и в 64-битных системах)
    #ifdef _WIN32
    std::setlocale(LC_ALL, "Russian");
    #endif

    /** @name База данных допустимых значений */
    ///@{
    std::vector<std::string> base_zodiac = {
        "овен", "телец", "близнецы"
        ,"рак", "лев", "дева"
        ,"весы", "скорпион", "змееносец"
        ,"стрелец", "козерог", "водолей"
        , "рыбы"
    };
    std::vector<std::string> base_gender = {"м", "ж"};
    ///@}

    /** @name Данные пользователя */
    ///@{
    std::string person_gender; ///< Пол пользователя
    std::string person_zodiac; ///< Знак зодиака пользователя
    int32_t person_age;        ///< Возраст пользователя
    ///@}


    // 1. Ввод и проверка пола
    std::cout << "Введите пол (м/ж): ";
    std::cin >> person_gender;
    if (std::find(base_gender.begin(), base_gender.end(), person_gender) == base_gender.end()) {
        std::cerr << "Ошибка: некорректный пол! Используйте 'м' или 'ж'." << std::endl;
        return EXIT_FAILURE;
    }


    // 2. Ввод и проверка знака зодиака
    std::cout << "Введите знак зодиака: ";
    std::cin >> person_zodiac;

    // Проверка наличия в списке
    auto it = std::find(base_zodiac.begin(), base_zodiac.end(), person_zodiac);
    if (it == base_zodiac.end()) {
        std::cerr << "Ошибка: знак зодиака '" << person_zodiac << "' не найден в базе!\nВведите один из этих вариантов:\n";
        for (int i = 0; i < base_zodiac.size(); ++i){
            std::cout<<base_zodiac[i]<<" ";
            if((i+1)%3 == 0)std::cout<<"\n";
        }
        return EXIT_FAILURE;
    }

    // 3. Ввод и проверка возраста
    std::cout << "Введите возраст: ";
    if (!(std::cin >> person_age)) {
        std::cerr << "Ошибка: возраст должен быть числом!" << std::endl;
        return EXIT_FAILURE;
    }

    if (person_age < 0 || person_age > 120) {
        std::cerr << "Ошибка: указан нереальный возраст!" << std::endl;
        return EXIT_FAILURE;
    }



    /** @name Классификация по стихиям */
    ///@{
    bool isWater = (person_zodiac == "рак" || person_zodiac == "скорпион" || person_zodiac == "рыбы");
    bool isEarth = (person_zodiac == "телец" || person_zodiac == "дева" || person_zodiac == "козерог");
    bool isFire  = (person_zodiac == "овен" || person_zodiac == "лев" || person_zodiac == "стрелец");
    bool isAir   = (person_zodiac == "близнецы" || person_zodiac == "весы" || person_zodiac == "водолей");
    ///@}






    // --- Вывод результата ---

    // Условие 1: Мужчины, Вода, < 40
    if (person_gender == "м" && isWater && person_age < 40) {
        std::cout << "Сегодня очень плодотворный день. Можно добиться того, что прежде казалось почти невозможным." << std::endl;
    }
    // Условие 2: Женщины, Земля, 15-30
    else if (person_gender == "ж" && isEarth && person_age >= 15 && person_age <= 30) {
        std::cout << "Сегодняшний вечер подходит для общения с друзьями, проведения домашних праздников и импровизированных вечеринок.\nБудет не только весело, но и интересно: найдётся дело, которое увлечёт всех." << std::endl;
    }
    // Условие 3: Все остальные Огненные знаки
    else if (isFire) {
        std::cout << "Огненная энергия поможет вам в решении старых проблем." << std::endl;
    }
    // Условие 4: Все остальные Воздушные знаки
    else if (isAir) {
        std::cout << "Воздушным знакам сегодня стоит прислушаться к интуиции." << std::endl;
    }
    // Условие 5: Змееносец (не входит в стихии)
    else if (person_zodiac == "Змееносец") {
        std::cout << "Для Змееносца наступает время редких возможностей." << std::endl;
    }
    // Условие 6: Те, кто попал в Воду/Землю, но не подошел по возрасту/полу
    else if (isWater || isEarth) {
        std::cout << "Будет не только весело, но и интересно: найдётся дело, которое увлечёт всех." << std::endl;
    }
    // Финал: Если что-то пошло совсем не так
    else {
        std::cout << "Гороскоп для вас находится в разработке. Приходите чуточку позже ;)" << std::endl;
    }

    return EXIT_SUCCESS;
}
