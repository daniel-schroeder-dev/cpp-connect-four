#include <iostream>

enum Player {
    PL_1,
    PL_2,
    PL_EMPTY
};

void display_gameboard(Player **pptr_board);
std::string get_player_character(Player player);

int num_rows = 4;
int num_cols = 5;

int main() {
    Player **pptr_board = new Player*[num_rows];

    for (int i = 0; i < num_rows; i++) {
        pptr_board[i] = new Player[num_cols];
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            pptr_board[i][j] = PL_EMPTY;
        }
    }

    Player current = PL_1;
    int col;

    while (true) {
        display_gameboard(pptr_board);
        std::cout << "Which column do you want to add your player to? (-1 to quit)  ";
        std::cin >> col;
        if (col == -1) break;
        current = current == PL_1 ? PL_2 : PL_1;
    }

    std::cout << std::endl;
    return 0;
}

std::string get_player_character(Player player) {
    switch (player) {
        case PL_1:
            return "*";
            break;
        case PL_2:
            return "+";
            break;
        case PL_EMPTY:
            return " ";
            break;
        default:
            return "!";
            break;
    }
}

void display_gameboard(Player **pptr_board) {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            std::cout << " | " << get_player_character(pptr_board[row][col]);
        }
        std::cout << " | \n";
    }
}
