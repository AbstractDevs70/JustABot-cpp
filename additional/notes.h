#include<nlohmann/json.hpp>
#include<fstream>
using json = nlohmann::json;

json notes;

void load_notes(){
    std::ifstream file("data/notes.json");
    notes = json::parse(file);
}