#include<nlohmann/json.hpp>
#include<iostream>
#include<fstream>
#include<random>
#include<time.h>
using json = nlohmann::json;
using namespace std;

json blackfile;
int bans;
string banwords[] = {"Ты забанен", "ты в бане", "Заметка для дебила: Ты забанен!","ТЫ ЗАБАНЕН БЛЯТЬ!","Абстракт презирает ваше отношение к боту","Отвали","...","неа",u8"🐑","Это не работает для вас"};

void load_blacklist(){
    if(std::filesystem::exists("additional/banlist.json")){
        std::ifstream file("additional/banlist.json");
        blackfile = json::parse(file);
        bans = std::size(blackfile["list"]);
    }else{
        blackfile["list"] = {0};
        std::cout << "Нет файла banlist.json!";
    }
}

std::string prikol(){
    srand(time(NULL));
    int word = rand() % size(banwords) - 1;
    return banwords[word];
}

bool bancheck(long int user){
    load_blacklist();
    int restricted = 0;
    for (int i = 0; i < std::size(blackfile["list"]); i++){
        if (user == blackfile["list"][i]){
            restricted++;
        }
    }
    switch (restricted){
    case  !0:
        return false;
        break;
    
    default:
        return true;
        break;
    }
}