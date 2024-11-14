#include <iostream>
#include <string.h>
#include <vector>
#include "character.h"

class NPC{
    public: 
        int npc_id;
        std::string npc_name;
        std::pair <int, int> npc_position;
        int unique_id;
        int level;
        int hit_points;
        int disposition;

};

class Enemy: public NPC{
    public:
        static std::vector<Enemy> store_enemy_npc;
        std::string enemy_color = BRIGHT_RED;
        
        Enemy(std::string name, std::pair <int, int> position, int disposition, int level, int unique_id){
            npc_name = name;
            disposition = disposition;
            npc_position = position;
            level = level;
            unique_id = unique_id;
            hit_points = 50 + ((level - 1) * 25);

            store_enemy_npc.push_back(*this);
        }
};