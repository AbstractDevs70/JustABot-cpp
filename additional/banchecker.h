#include<fstream>
#include<filesystem>

long int blacklist [] = {909825566969045083};

bool bancheck(long int user){
    int restricted = 0;
    for (int i = 0; i < std::size(blacklist); i++){
        if (user == blacklist[i]){
            restricted++;
        }
    }
    switch (restricted){
    case 1:
        return false;
        break;
    
    default:
        return true;
        break;
    }
}