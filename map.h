#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <iostream>

class Map{
private:
    char map[30][50];
public:
    Map(){
        std::fstream fs("./map/map.map", std::ios::in);
        for (int i = 0; i < 30; i++){
            for (int j = 0; j < 50; j++){
                map[i][j]= static_cast<char>(fs.get());
            }
            fs.get();
        }
    }

    void mapDisplay() const{
        for (int i = 0; i < 30; i++){
            for (int j = 0; j < 50; j++)
                std::cout << map[i][j];
            std::cout << std::endl;
        }
    }

    void setMap(int row, int cul, char ch){
        map[row][cul] = ch;
    }

    void setMap(int* arr, char ch){
        map[arr[1]][arr[2]] = ch;
    }
};

#endif
