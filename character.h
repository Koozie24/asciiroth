#include <iostream>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m" //RED
#define GREEN "\033[32m" //GREEN
#define YELLOW "\033[33m" //YELLOW
#define BLUE "\033[34m" //BLUE
#define MAGENTA "\033[35m" //MAGENTA
#define CYAN "\033[36m" //CYAN
#define BOLD "\033[1m"  // Bold text


void clear_screen(){
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

class Player_Character{
    public:
        std::string player_name;
        std::string player_class;
        int player_level = 1;
        std::string class_color;
        int stamina = 5;
        int strength = 5;
        int intellect  = 5;
        int hit_points = (stamina * 10) + (50 * player_level);
        int max_hp = (stamina * 10) + (50 * player_level);
        int experience_points = 0;
        std::vector <std::string> class_abilities;

        std::vector <std::pair<int,int>> xp_per_level = {{1, 250}, {2, 650}, {3, 1265}, {4, 2085}, {5, 3240}};
        //y,x
        std::pair <int, int> player_location = {51, 50};
        
        virtual int primary_ability(){
            return 0;
        }
        virtual int self_healing(){
            return 0;
        }
        //virtual deconstructor for polymorphic class type
        virtual ~Player_Character(){}

        Player_Character(){
            for(;;){
                int has_digit = 0;
                int max_consecutive = 0;
                
                clear_screen();
                std::cout << "Welcome to Northshire Valley. What shall we call you?" <<std::endl;
                std::cin >> player_name;
                std::cout << std::endl;
                clear_screen();

                //validating users input checking for length and no digits or repeating characters.
                char temp = '\0';
                int count_repeating = 0;

                for(char c: player_name){
                    if(isdigit(int(c))){
                        has_digit = 1;
                    }
                    //check for repeating characters in name input
                    if(temp == c){
                        count_repeating++;
                    }
                    else{
                        count_repeating = 0;
                    }

                    if(count_repeating == 2){
                        max_consecutive == 1;
                    }
                    temp = c;
                }

                if(player_name.length() >= 3 && player_name.length() < 13 && has_digit == 0 && max_consecutive == 0){
                    std::cout << "Hmm, I'm not sure that I would guess you have what is takes to be a " << player_class << ", " << player_name << ", but we will see what the trainers can make of you yet. Off with you now, scum and go seek out Marshall McBride! You will find him due north just a little ways." << std::endl;
                    break;
                }
            }
        }
};

class Warrior : public Player_Character{
    public:
        Warrior(){
            player_class = "Warrior";
            class_color = RED;
            class_abilities =  {"Heroic Strike", "Bandage"};
        }

        int primary_ability() override{
            int base_damage = player_level * ((rand() % 10) + 15);

            return base_damage;
        }
        int self_healing() override{
            int bandage_heal = (max_hp / 10);

            return bandage_heal;
        }
};

Player_Character* create_player(){
    Player_Character* player = nullptr;

    for(;;){
        
        std::cout << "What sort of adventurer are you? You may choose: " << std::endl;

        std::cout << RED << "Warrior <w>" << RESET << std::endl;
        std::cout << GREEN << "Hunter <h>" << RESET << std::endl;
        std::cout << CYAN << "Mage <m>" << RESET << std::endl;
        std::cout << YELLOW << "Rogue <r>" << RESET << std::endl;
        std::cout << MAGENTA << "Paladin <p>" << RESET << std::endl;
        std::cout << std::endl;

        char class_character = '0';
        std::cin >> class_character;

        switch(class_character){
            case 'w':
            case 'W':
                player = new Warrior();
                return player;
            case 'h':
            case 'H':
                break; 
            case 'm':
            case 'M':
                break;
            case 'r':
            case 'R':
                break;
            case 'p':
            case 'P':
                break;

        }

        if(class_character == 'H' || class_character == 'R' || class_character == 'M' || class_character == 'P' || class_character == 'W'){
            clear_screen();
            break;
        }

        clear_screen();
    }

    return player;
}