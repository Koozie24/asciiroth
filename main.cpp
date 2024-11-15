#include <iostream>
#include <vector>
#include <string>
#include "character.h"
#include "npc.h"

std::string command = "";
std::vector <Enemy> in_range_enemies;
std::vector <std::vector<char>> dot_map(100, std::vector<char>(100, '.'));
std::vector <std::pair<int, int>> arrow_coordinates = {
    {45, 50}, {46, 49}, {46, 51}, {47, 48}, {47, 52}, {48, 47}, {48, 53}, {49, 46}, {49, 54}
};

void draw_horizontal_line(int row, int start_column, int end_column, char replace_character){
    if(row, start_column, end_column <= 100 && row, start_column, end_column >= 0){
        for(int i = start_column; i < end_column; i++){
            dot_map[row][i] = replace_character;
        }
    }
}

void draw_vertical_line(int column, int start_row, int end_row, char replace_character){
    if(column, start_row, end_row <= 100 && column, start_row, end_row >= 0){
        for(int i = end_row; i < start_row; i++){
            dot_map[i][column] = replace_character;
        }
    }
}

void insert_alternative_chars(std::vector <std::pair<int, int>> coordinates, char new_character){
    for(const auto& coord : coordinates){
        dot_map[coord.first][coord.second] = new_character;
   }
}

void insert_single_char(int y_coord, int x_coord, char new_character){
    dot_map[y_coord][x_coord] = new_character;
}

void insert_npc(std::vector <Enemy> store_enemy_npc){
    for(int i=0; i < store_enemy_npc.size(); i++){
        dot_map[store_enemy_npc[i].npc_position.first][store_enemy_npc[i].npc_position.second] = store_enemy_npc[i].npc_icon;
    }
}

void check_in_range_npc(std::pair <int, int> player_location, std::vector <Enemy> store_enemy_npc){
    std::vector <std::pair<int, int>> check_coords = {
        {player_location.first + 1, player_location.second}, {player_location.first - 1, player_location.second}, {player_location.first, player_location.second + 1}, {player_location.first, player_location.second - 1},
        {player_location.first + 1, player_location.second + 1}, {player_location.first - 1, player_location.second - 1}, {player_location.first + 1, player_location.second - 1}, {player_location.first - 1, player_location.second + 1}
    };

    for(const auto& coord : check_coords){
        if(dot_map[coord.first][coord.second] != '.' && dot_map[coord.first][coord.second] != 'x'){
            char in_range = dot_map[coord.first][coord.second];
            for(int i=0; i < store_enemy_npc.size(); i++){
                if(store_enemy_npc[i].npc_position == coord){
                    in_range_enemies.push_back(store_enemy_npc[i]);
                }
            }
        }
    }
}

/*printer function to show the map*/
void print_map(std::vector <std::vector<char>> dot_map, std::pair <int, int> player_location, Player_Character player){
    int min = player_location.first - 10;
    int max = player_location.first + 10;
    if(min < 0){
        min = 0;
    }
    else if(max > 100){
        max = 100;
    }

    for(int i = min; i < max; i++){
        for(int j = 0; j < dot_map[i].size(); j++){
            if(dot_map[i][j] == 'x' || dot_map[i][j] == '^'){
                std::cout << RED << dot_map[i][j] << RESET << ' ';
            }
            else if(dot_map[i][j] == '@'){
                std::cout << player.class_color << dot_map[i][j] << RESET << ' ';
            }
            else if(dot_map[i][j] == 'W'){
                std::cout << BRIGHT_RED << dot_map[i][j] << RESET << ' ';
            }
            else{
                std::cout << dot_map[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << " ________________________________________________________" << std::endl;
    std::cout << "|              " << player.class_color << player.player_name << " Level " << player.player_level << " " << player.player_class << RESET << std::endl;
    std::cout << "|              " << BLUE << "Current Location: [" << player.player_location.second << "," << player.player_location.first << "]" << RESET << std::endl;
    std::cout << "|________________________________________________________" << std::endl;

    std::cout << "You are in range of the following creatures: ";

    for(int i=0; i < in_range_enemies.size(); i++){
        std::cout << in_range_enemies[i].npc_name << std::endl;
    }
}

 std::string get_input(){
    std::getline(std::cin >> std::ws, command);

    std::string c = command;
    return c;
}

/*function handles users' movement command. Updates the map if move is legal. returns pair of ints denoting player location*/
std::pair <int, int> handle_user_move(std::string command, std::pair <int, int> player_location){
    int cmd_length = command.size();

    if(cmd_length == 1){
        switch(command[0]){
            case 'w':
            case 'W':
                if(player_location.first - 1 >= 0 && dot_map[player_location.first - 1][player_location.second] == '.'){
                    dot_map[player_location.first][player_location.second] = '.';
                    player_location.first -= 1;
                    dot_map[player_location.first][player_location.second] = '@';
                }
                break;
            case 's':
            case 'S':
                if(player_location.first + 1 < 100 && dot_map[player_location.first + 1][player_location.second] == '.'){
                    dot_map[player_location.first][player_location.second] = '.';
                    player_location.first += 1;
                    dot_map[player_location.first ][player_location.second] = '@';
                }
                break;
            case 'a':
            case 'A':
                if(player_location.second - 1 >= 0 && dot_map[player_location.first][player_location.second - 1] == '.'){
                    dot_map[player_location.first][player_location.second] = '.';
                    player_location.second -= 1;
                    dot_map[player_location.first][player_location.second] = '@';
                }
                break;
            case 'd':
            case 'D':
                if(player_location.second + 1 < 100 && dot_map[player_location.first][player_location.second + 1] == '.'){
                    dot_map[player_location.first][player_location.second] = '.';
                    player_location.second += 1;
                    dot_map[player_location.first][player_location.second] = '@';
                }
                break;
        }
    }

    return player_location;
}

int main(){
    int game_active = 1;
    Player_Character player;
    //draw friendly base
    draw_horizontal_line(44, 40, 61, 'x');
    draw_horizontal_line(50, 40, 50, 'x');
    draw_horizontal_line(50, 51, 61, 'x');
    draw_vertical_line(40, 50, 44, 'x');
    draw_vertical_line(60, 50, 44, 'x');
    
    //set player start and draw initial map
    insert_single_char(player.player_location.first, player.player_location.second, '@');
    initialize_young_wolves();
    insert_npc(Enemy::enemy_npc_vector);
    print_map(dot_map, player.player_location, player);

    
    for(;;){
        command = get_input();
        int cmd_length = command.size();

        //parse input command
        if(cmd_length == 1){
            char char_command = command[0];
            if(isdigit(char_command)){ //targeting command?
                break;
            }
            //quit game
            if(command == "q" || command == "q"){
                game_active = 0;
            }
            else{ //handle movement and display in range npc's
                std::pair temp_loc = player.player_location;
                player.player_location = handle_user_move(command, player.player_location);
                clear_screen();

                //check if player has moved to trigger range check
                if(temp_loc.first != player.player_location.first || temp_loc.second != player.player_location.second){
                    check_in_range_npc(player.player_location, Enemy::enemy_npc_vector);
                }

                print_map(dot_map, player.player_location, player);
            }
        }

        command = "";
        if(game_active == 0){
            break;
        }
    }
}