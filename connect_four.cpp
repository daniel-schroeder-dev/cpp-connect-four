#include <iostream>

enum Player {
    PL_1,
    PL_2,
    PL_EMPTY
};

void display_gameboard(Player **pptr_board);
void display_current_player(Player player);
void add_player_selection(Player **pptr_board, Player player, int col);
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

    Player current_player = PL_1;
    int col;

    while (true) {
        display_gameboard(pptr_board);
        display_current_player(current_player);
        std::cout << "Which column do you want to add your player to? (-1 to quit)  ";
        std::cin >> col;
        if (col == -1) break;
        add_player_selection(pptr_board, current_player, col);
        current_player = current_player == PL_1 ? PL_2 : PL_1;
    }

    std::cout << std::endl;
    return 0;
}

void add_player_selection(Player **pptr_board, Player player, int col) {
    if (col < 0 || col > num_cols - 1) {
        std::cout << "Invalid selection!\n";
        return;
    }
    int last_row = num_rows - 1;
    for (int row = 0; row < num_rows; row++) {
        // if we hit a non-empty row in this col
        if (pptr_board[row][col] != PL_EMPTY) {
            // add this player to the row above, but only if we're not on the 0th row
            if (row > 0) {
                pptr_board[row-1][col] = player;
            }
            break;
        } else if (row == last_row) {
            pptr_board[row][col] = player;
            break;
        }
    }
}

void display_current_player(Player player) {
    if (player == PL_1) {
        std::cout << "Player 1's turn\n";
    } else {
        std::cout << "Player 2's turn\n";
    }
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
