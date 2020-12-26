#include <iostream>

enum Player {
    PL_1,
    PL_2,
    PL_EMPTY
};

void display_gameboard(Player **pptr_board);
void add_player_selection(Player **pptr_board, Player player, int col);

std::string get_current_player(Player player);
std::string get_player_character(Player player);

Player check_for_winner(Player **pptr_board);
Player check_cols_for_winner(Player **pptr_board);
Player check_rows_for_winner(Player **pptr_board);
Player check_diagonals_for_winner(Player **pptr_board);
Player walk_ltr_dialgonal_row(Player **pptr_board, int start_row);
Player walk_rtl_dialgonal_row(Player **pptr_board, int start_row);

int num_rows = 0;
int num_cols = 0;
int slots_filled = 0;
int total_slots;

int main() {

    while (num_rows < 4) {
        std::cout << "Enter number of rows for gameboard (4 min): ";
        std::cin >> num_rows;
    }

    while (num_cols < 4) {
        std::cout << "Enter number of columns for gameboard (4 min): ";
        std::cin >> num_cols;
    }

    total_slots = num_rows * num_cols;

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
    Player winner;
    int col;

    while (true) {
        display_gameboard(pptr_board);
        std::cout << "\n" << get_current_player(current_player) << "'s turn\n";
        std::cout << "Which column do you want to add your player to? (-1 to quit) ";
        std::cin >> col;
        if (col == -1) break;
        add_player_selection(pptr_board, current_player, col);
        winner = check_for_winner(pptr_board);
        if (winner != PL_EMPTY) {
            std::cout << "\n" << get_current_player(current_player) << " wins!\n\n";
            break;
        }
        if (slots_filled == total_slots) {
            std::cout << "\nIt's a tie!\n\n";
            break;
        }
        current_player = current_player == PL_1 ? PL_2 : PL_1;
    }

    display_gameboard(pptr_board);

    std::cout << std::endl;
    return 0;
}

Player check_for_winner(Player **pptr_board) {
    Player winner; 
    winner = check_rows_for_winner(pptr_board);
    if ( winner != PL_EMPTY) {
        return winner;
    }
    winner = check_cols_for_winner(pptr_board);
    if ( winner != PL_EMPTY) {
        return winner;
    }
    winner = check_diagonals_for_winner(pptr_board);
    if (winner != PL_EMPTY) {
        return winner;
    }
    return PL_EMPTY;
}

Player walk_ltr_dialgonal_row(Player **pptr_board, int start_row) {
    Player last_player;
    Player current_player;
    int current_col;
    for (int col = 0; col < num_cols - 3; col++) {
        int similar_count = 0;
        last_player = PL_EMPTY;
        current_col = col;
        for (int row = start_row; row < num_rows; row++) {
            current_player = pptr_board[row][current_col];
            if (current_player == last_player && current_player != PL_EMPTY) {
                similar_count++;
                if (similar_count == 3) {
                    return current_player;
                }
            } else {
                similar_count = 0;
            }
            last_player = current_player;
            current_col++;
        }
    }
    return PL_EMPTY;   
}

Player walk_rtl_dialgonal_row(Player **pptr_board, int start_row) {
    Player last_player;
    Player current_player;
    int current_col;
    for (int col = num_cols - 1; col > 2; col--) {
        int similar_count = 0;
        last_player = PL_EMPTY;
        current_col = col;
        for (int row = start_row; row < num_rows; row++) {
            current_player = pptr_board[row][current_col];
            if (current_player == last_player && current_player != PL_EMPTY) {
                similar_count++;
                if (similar_count == 3) {
                    return current_player;
                }
            } else {
                similar_count = 0;
            }
            last_player = current_player;
            current_col--;
        }
    }
    return PL_EMPTY;   
}

Player check_diagonals_for_winner(Player **pptr_board) {
    Player winner;

    // 0,0  1,1  2,2  3,3
    // 0,1  1,2  2,3  3,4
    // break

    // 1,0  2,1  3,2  4,3
    for (int row = 0; row < num_rows - 3; row++) {
        winner = walk_ltr_dialgonal_row(pptr_board, row);
        if (winner != PL_EMPTY) return winner;
    }

    for (int row = 0; row < num_rows - 3; row++) {
        winner = walk_rtl_dialgonal_row(pptr_board, row);
        if (winner != PL_EMPTY) return winner;
    }

    return PL_EMPTY;
}

Player check_cols_for_winner(Player **pptr_board) {
    Player last_player;
    Player current_player;
    for (int col = 0; col < num_cols; col++) {
        int similar_count = 0;
        // get the first row before we walk the rest
        last_player = pptr_board[0][col];
        for (int row = 1; row < num_rows; row++) {
            current_player = pptr_board[row][col];
            if (current_player == last_player && current_player != PL_EMPTY) {
                similar_count++;
                if (similar_count == 3) {
                    return current_player;
                }
            } else {
                similar_count = 0;
            }
            last_player = current_player;
        }
    }
    return PL_EMPTY;  
}

Player check_rows_for_winner(Player **pptr_board) {
    Player last_player;
    Player current_player;
    for (int row = 0; row < num_rows; row++) {
        int similar_count = 0;
        // get the first column before we walk the rest
        last_player = pptr_board[row][0];
        for (int col = 1; col < num_cols; col++) {
            current_player = pptr_board[row][col];
            if (current_player == last_player && current_player != PL_EMPTY) {
                similar_count++;
                if (similar_count == 3) {
                    return current_player;
                }
            } else {
                similar_count = 0;
            }
            last_player = current_player;
        }
    }
    return PL_EMPTY;
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
    slots_filled++;
}

std::string get_current_player(Player player) {
    if (player == PL_1) {
        return "Player 1";
    } else {
        return "Player 2";
    }
}

std::string get_player_character(Player player) {
    switch (player) {
        case PL_1:
            return "&";
            break;
        case PL_2:
            return "*";
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
