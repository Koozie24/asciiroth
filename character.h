#include <iostream>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m" //RED
#define GREEN "\033[32m" //GREEN
#define YELLOW "\033[33m" //YELLOW
#define BLUE "\033[34m" //BLUE
#define MAGENTA "\033[35m" //MAGENTA
#define CYAN "\033[36m" //CYAN

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
        std::string player_race;
        //y,x
        std::pair <int, int> player_location = {51, 50};

        Player_Character(){
            for(;;){
                int has_digit = 0;
                int max_consecutive = 0;

                std::cout << "Welcome adventurer! This is Northshire Valley. What shall we call you?" <<std::endl;
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
                    break;
                }
            }

            for(;;){
                std::cout << player_name << "? Well, not what I would have stuck with that, but I suppose thats what we will call you. Now, what sort of adventurer should we train you as? You may choose: " << std::endl;

                std::cout << RED << "Warrior <w>" << RESET << std::endl;
                std::cout << GREEN << "Hunter <h>" << RESET << std::endl;
                std::cout << CYAN << "Mage <m>" << RESET << std::endl;
                std::cout << YELLOW << "Rogue <r>" << RESET << std::endl;
                std::cout << MAGENTA << "Paladin <p>" << RESET << std::endl;
                std::cout << std::endl;

                std::cin >> player_class;

                char class_char = player_class[0];

                switch(class_char){
                    case 'w':
                    case 'W':
                        player_class = "Warrior";
                        break;
                    case 'h':
                    case 'H':
                        player_class = "Hunter";
                        break; 
                    case 'm':
                    case 'M':
                        player_class = "Mage";
                        break;
                    case 'r':
                    case 'R':
                        player_class = "Rogue";
                        break;
                    case 'p':
                    case 'P':
                        player_class = "Paladin";
                        break;

                }

                if(player_class[0] == 'H' || player_class[0] == 'R' || player_class[0] == 'M' || player_class[0] == 'P' || player_class[0] == 'W'){
                    clear_screen();
                    std::cout << "Hmm, I'm not sure that I would guess you have what is takes to be a " << player_class << ", " << player_name << ", but we will see what the trainers can make of you yet. Off with you now, scum and go seek out Marshall McBride! You will find him due north just a little ways." << std::endl;
                    break;
                }

                clear_screen();
            }
        }
};