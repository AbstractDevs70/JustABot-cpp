#include<nlohmann/json.hpp>
#include<iostream>
#include<fstream>
using json = nlohmann::json;
using namespace std;
json admins;

void loadadmins(){
    if(std::filesystem::exists("data/admins.json")){
        std::ifstream file("data/admins.json");
        admins = json::parse(file);
    }else{
        admins["everywhere"] = {0};
        std::cout << "Нет файла admins.json.json!";
    }
}