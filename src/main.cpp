//для арта использовал
//ref: https://patorjk.com/software/taag/#p=display&f=Larry+3D&t=Hello+world&x=none&v=4&h=4&w=80&we=false

//для .gitignore
//ref: https://github.com/github/gitignore/blob/main/C%2B%2B.gitignore

/**
 * @mainpage Программа с ASCII-артом
 * 
 * Эта программа выводит ASCII-арт:
 * - Арт с текстовый логотип Hello world
 * 
 * @author Салакатов Максим Альбертович aka (Jarko || Mr-Maks-S-A)
 */


#include <iostream>
#include <string_view>

int main() {
    const std::string_view art = R"(
__  __          ___    ___                                          ___       __     
/\ \/\ \        /\_ \  /\_ \                                        /\_ \     /\ \    
\ \ \_\ \     __\//\ \ \//\ \     ___       __  __  __    ___   _ __\//\ \    \_\ \   
 \ \  _  \  /'__`\\ \ \  \ \ \   / __`\    /\ \/\ \/\ \  / __`\/\`'__\\ \ \   /'_` \  
  \ \ \ \ \/\  __/ \_\ \_ \_\ \_/\ \L\ \   \ \ \_/ \_/ \/\ \L\ \ \ \/  \_\ \_/\ \L\ \ 
   \ \_\ \_\ \____\/\____\/\____\ \____/    \ \___x___/'\ \____/\ \_\  /\____\ \___,_\
    \/_/\/_/\/____/\/____/\/____/\/___/      \/__//__/   \/___/  \/_/  \/____/\/__,_ /
                                                                                      
)";

    // Выводим арт
    std::cout << art << std::endl;
    //Завершаем программу без ошибок
    return EXIT_SUCCESS;
}