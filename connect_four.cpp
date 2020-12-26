#include <iostream>

enum Player {
    PL_1,
    PL_2,
    PL_EMPTY
};

int main() {
    int num_rows = 4;
    int num_cols = 5;
    Player **pptr_board = new Player*[num_rows];

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            pptr_board[i][j] = PL_EMPTY;
        }
    }

    std::cout << std::endl;
    return 0;
}
