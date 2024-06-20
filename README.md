# Требует библиотеки:
- DPP

# Зависимости:
- calc
- echo

# Компиляция:
- Скопируйте репозиторий
- Создайте в папке additional файл `bot_token.h` и напишите туда

```cpp
std::string BOT_TOKEN = "ваш токен";
```
- Скомпилируйте и запустите

```
g++ -std=c++17 bot.cpp -o executable -ldpp && ./executable
```
