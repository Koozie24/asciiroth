#include <iostream>
#include <vector>
#include <string>

#define RESET "\033[0m"
#define RED "\033[31m" //RED
#define GREEN "\033[32m" //GREEN

std::string command = "";
std::vector <std::vector<char>> dot_map(100, std::vector<char>(100, '.'));

std::vector <std::pair<int, int>> arrow_coordinates = {
    {45, 50}, {46, 49}, {46, 51}, {47, 48}, {47, 52}, {48, 47}, {48, 53}, {49, 46}, {49, 54}
};

void clear_screen(){
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void draw_straight_line(int row, int start_column, int end_column, char replace_character){
    if(row, start_column, end_column <= 100 && row, start_column, end_column >= 0){
        for(int i = start_column; i < end_column; i++){
            dot_map[row][i] = replace_character;
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

void print_map(std::vector <std::vector<char>> dot_map, std::pair <int, int> player_location){
    int min = player_location.first - 25;
    int max = player_location.first + 25;
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
                std::cout << GREEN << dot_map[i][j] << RESET << ' ';
            }
            else{
                std::cout << dot_map[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

 std::string get_input(){
    std::getline(std::cin >> std::ws, command);

    std::string c = command;
    return c;
}

std::pair <int, int> handle_user_input(std::string command, std::pair <int, int> player_location){
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
                    std::cout << player_location.first << std::endl;
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

    draw_straight_line(50, 45, 56, 'x');
    
    insert_alternative_chars(arrow_coordinates, '^');
    insert_single_char(51, 52, '@');
    std::pair<int, int> player_location = {51, 52};
    print_map(dot_map, player_location);

    
    for(;;){
        command = get_input();
        player_location = handle_user_input(command, player_location);

        clear_screen();
        print_map(dot_map, player_location);
        command = "";
    }
}