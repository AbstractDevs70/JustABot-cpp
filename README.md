Требует библиотеки:
- dpp
- nlohmann/json

Зависимости:
- calc
- echo

> Компиляция:
 - Скопируйте репозиторий
 - Создайте в папке additional файл
 - bot_token.h и задайте

 `std::string BOT_TOKEN = "ваш токен";`
 - Скомпилируйте и запустите
   
 `g++ -std=c++17 bot.cpp -o executable -ldpp && ./executable`

[ i ] Также можно использовать ./test.sh
