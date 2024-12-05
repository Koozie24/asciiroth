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

    //empty in range before new check
    in_range_enemies.clear();

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
void print_map(std::vector <std::vector<char>> dot_map, std::pair <int, int> player_location, Player_Character& player){
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
    std::cout << "|              " << player.class_color << player.player_name << " Level " << player.player_level << " " << player.player_class << RESET << BOLD << MAGENTA << " XP: " << player.experience_points << "/"<< player.xp_per_level[player.player_level - 1].second << RESET << GREEN << " HP: " << player.hit_points << RESET << std::endl;
    std::cout << "|              " << BLUE << "Current Location: [" << player.player_location.second << "," << player.player_location.first << "]" << RESET << std::endl;
    std::cout << "|________________________________________________________" << std::endl;

    std::cout << "You are in range of the following creatures: ";

    for(int i=0; i < in_range_enemies.size(); i++){
        std::cout << i << ": " << in_range_enemies[i].npc_name;
    }
    std::cout << std::endl;
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

int check_npc_is_in_range(int index_to_check){
    int check_flag = 0;
    if(index_to_check <= in_range_enemies.size()){
        check_flag = 1;
    }
    return check_flag;
}

void display_combat_interaction(int in_range_index, Player_Character& player, std::pair<int, std::string> previous = {-1, "null"}, int turn = 1){
    clear_screen();
    int count = 0;
    std::string enemy_name = in_range_enemies[in_range_index].get_name();
    for(char c : enemy_name){
        count++;
    }
    if(turn == 0){
        std::cout << BOLD << BRIGHT_RED << "You are in combat! Win or die." << RESET << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "Target: Level " << in_range_enemies[in_range_index].level << " " << in_range_enemies[in_range_index].get_name() <<  std::string(count, '\0') << std::endl;
        std::cout << "HP: " << BRIGHT_RED <<  in_range_enemies[in_range_index].hit_points << RESET << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout <<player.class_color << player.player_name << "'s HP: " << RESET << BRIGHT_GREEN << player.hit_points << RESET << std::endl;
    }
    else{
        std::cout << BOLD << BRIGHT_RED << "You are in combat! Win or die." << RESET << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "Target: Level " << in_range_enemies[in_range_index].level << " " << in_range_enemies[in_range_index].get_name() <<  std::string(count, '\0') << "| You dealt " << previous.first << " damage with " << previous.second <<  std::endl;
        std::cout << "HP: " << BRIGHT_RED <<  in_range_enemies[in_range_index].hit_points << RESET << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout <<player.class_color << player.player_name << "'s HP: " << RESET << BRIGHT_GREEN << player.hit_points << RESET << std::endl;
    }
}

std::pair <int, std::string> handle_player_attack_inputs(std::string command, Player_Character& player, int in_range_index){
    int c = command[0] - '0';
    std::pair <int, std::string> combat_log;
    std::string ability_name;
    int amount_healed, damage_dealt_to_npc;

    switch(c){
        case(2):
            amount_healed = player.self_healing();

            player.hit_points += amount_healed;
            ability_name = player.class_abilities[1];
            combat_log = {amount_healed, ability_name};
            break;
        case(1):
            damage_dealt_to_npc = player.primary_ability();
            ability_name = player.class_abilities[0];
            in_range_enemies[in_range_index].hit_points -= damage_dealt_to_npc;

            player.hit_points -= in_range_enemies[in_range_index].get_damage();
            std::cout << in_range_enemies[in_range_index].get_damage() << std::endl;
            //std::cin >> damage_dealt_to_npc;
            combat_log = {damage_dealt_to_npc, ability_name};
            break;
    }

    //checking for player/npc death. -2 code indicates dead string indicates who
    if(player.hit_points <= 0){
        combat_log.first = -2;
        combat_log.second = "player";
    }
    if(in_range_enemies[in_range_index].hit_points <= 0){
        combat_log.first = -2;
        combat_log.second = "npc";
    }
    return combat_log;
}

void handle_npc_kill(Player_Character& player, int enemy_npc_id){
    for(int i =0; i < Enemy::enemy_npc_vector.size(); i++){
        if(Enemy::enemy_npc_vector[i].get_id() == enemy_npc_id){
            int level_difference = Enemy::enemy_npc_vector[i].get_level() - player.player_level;
            int exp_gain =  25 + (level_difference * 5);
            player.experience_points += exp_gain;

            dot_map[Enemy::enemy_npc_vector[i].npc_position.first][Enemy::enemy_npc_vector[i].npc_position.second] = '.';
            Enemy::enemy_npc_vector.erase(Enemy::enemy_npc_vector.begin() + i);
            break;
        }
    }
}

void player_xp_check(Player_Character& player){
    int current_level = player.player_level;
    int current_xp = player.experience_points;
    int required_xp = player.xp_per_level[current_level - 1].second;
    if(current_xp >= required_xp){
        player.player_level += 1;
        player.experience_points = current_xp - required_xp;
    }
}

int main(){
    int game_active = 1;
    Player_Character* player = create_player();
    //draw friendly base
    draw_horizontal_line(44, 40, 61, 'x');
    draw_horizontal_line(50, 40, 50, 'x');
    draw_horizontal_line(50, 51, 61, 'x');
    draw_vertical_line(40, 50, 44, 'x');
    draw_vertical_line(60, 50, 44, 'x');
    
    //set player start and draw initial map
    insert_single_char(player->player_location.first, player->player_location.second, '@');
    initialize_young_wolves();
    insert_npc(Enemy::enemy_npc_vector);
    print_map(dot_map, player->player_location, *player);

    
    for(;;){
        command = get_input();
        int cmd_length = command.size();

        //parse input command
        if(cmd_length == 1){
            char char_command = command[0];
            if(isdigit(char_command)){ //targeting command
                int in_range_index = char_command - '0';
                
                int check_target_in_range = check_npc_is_in_range(in_range_index);
                //check in range
                if(check_target_in_range == 1){
                    //get npc disposition & id
                    int target_dispostion = in_range_enemies[in_range_index].disposition;
                    int target_id = in_range_enemies[in_range_index].npc_id;
                    switch(target_dispostion){
                        //friendly
                        case(0):
                        //enemy
                        case(1):
                            int in_combat = 1;
                            int turn = 0;
                            std::pair <int, std::string> previous_turn_results;

                            for(;;){
                                command = "";
                                //first turn before 
                                if(turn == 0){
                                    std::pair<int, std::string> previous = {-1, "null"};
                                    display_combat_interaction(in_range_index, *player, previous, turn);
                                    command = get_input();
                                    turn++;
                                    previous_turn_results = handle_player_attack_inputs(command, *player, in_range_index);
                                    display_combat_interaction(in_range_index, *player);
                                }
                                else{
                                    command = get_input();
                                    previous_turn_results = handle_player_attack_inputs(command, *player, in_range_index);
                                    turn++;
                                    display_combat_interaction(in_range_index, *player, previous_turn_results);
                                }   
                                
                                //check for a kill
                                in_combat = previous_turn_results.first == -2 ? 0 : 1;

                                if(in_combat == 0){
                                    if(in_range_enemies[in_range_index].hit_points <= 0){
                                        handle_npc_kill(*player, target_id);
                                    }
                                    if(player->hit_points <= 0){
                                        std::cout << RED << "You have been slain by " << in_range_enemies[in_range_index].get_name() << ". Your character made it to level " << player->player_level << std::endl;
                                        game_active = 0;
                                    }
                                    command = "";
                                    break;
                                }
                            }
                    }
                }   
            }

            //bandage/heal
            if(command == "h"){
                int amount_healed = player->self_healing();
                int current_hp = player->hit_points;

                if(amount_healed + current_hp > player->max_hp){
                    player->hit_points == player->max_hp;
                }
                else{
                    player->hit_points += amount_healed;
                }
            }

            //quit game
            if(command == "q" || command == "q"){
                game_active = 0;
            }
            else{ //handle movement and display in range npc's
                std::pair temp_loc = player->player_location;
                player->player_location = handle_user_move(command, player->player_location);
                clear_screen();

                //check if player has moved to trigger range check
                if(temp_loc.first != player->player_location.first || temp_loc.second != player->player_location.second){
                    check_in_range_npc(player->player_location, Enemy::enemy_npc_vector);
                }

                print_map(dot_map, player->player_location, *player);
            }
        }

        
        player_xp_check(*player);

        command = "";
        if(game_active == 0){
            break;
        }
    }
}