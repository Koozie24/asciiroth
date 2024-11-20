#include <iostream>
#include <vector>

#define BRIGHT_RED "\033[91m" // Bright Red
#define BRIGHT_GREEN "\033[92m" // Bright Green

class NPC{
    public: 
        int npc_id;
        std::string npc_name;
        std::pair <int, int> npc_position;
        int unique_id;
        int level;
        int hit_points;
        int disposition; //0 friendly 1 is aggressive
        char npc_icon;
        int damage;
};

class Enemy: public NPC{
    public:
        std::string enemy_color = BRIGHT_RED;
        static std::vector<Enemy> enemy_npc_vector;

        Enemy(std::string name, std::pair <int, int> position, int disposition, int level, int unique_id, char npc_icon){
            this->npc_name = name;
            this->disposition = disposition;
            this->npc_position = position;
            this->level = level;
            this->npc_id = unique_id;
            this->hit_points = 50 + ((level - 1) * 25);
            this->npc_icon = npc_icon;
            this->damage = level * ((rand() % 1) + 5);
            this->enemy_npc_vector.push_back(*this);

        }

        //char operator<<(const Enemy& other) const{
        //    return this->npc_icon;
        //}
        int get_level() const {return level;}
        char get_icon() const {return npc_icon;}
        std::string get_name() const {return npc_name;}
        int get_damage() const {return damage;}
        int get_disposition() const {return disposition;}
        int get_id() const {return npc_id;}

};

void initialize_young_wolves();