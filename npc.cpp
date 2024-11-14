#include <iostream>
#include "npc.h"
#include <random>
#include <vector>

int unique_id = 0;
std::vector <Enemy> Enemy::enemy_npc_vector;

void initialize_young_wolves(){
    int disposition = 1;

    for(int i = 1; i < 18; i++){
        std::string wolf_name = "Young Wolf";
        int wolf_level = rand() % 3 + 1;
        int y = rand() % 100 + 0;
        int x = rand() % 100 + 0;
        std::pair <int, int> location = {y, x};
        char icon = 'W';
        new Enemy(wolf_name, location, disposition, wolf_level, unique_id, icon);
        unique_id++;
    }
}