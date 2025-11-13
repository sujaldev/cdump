#include <iostream>
#include <vector>

using Board = std::vector<std::vector<char> >;
constexpr char x = 'x', o = 'o';

class TicTacToe {
    Board board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

public:
    void printBoard() const {
        std::cout
                << "    0   1   2\n"
                << "  ┌───┬───┬───┐\n"
                << "0 │ " << board[0][0]
                << " │ " << board[0][1]
                << " │ " << board[0][2] << " │\n"
                << "  ├───┼───┼───┤\n"
                << "1 │ " << board[1][0]
                << " │ " << board[1][1]
                << " │ " << board[1][2] << " │\n"
                << "  ├───┼───┼───┤\n"
                << "2 │ " << board[2][0]
                << " │ " << board[2][1]
                << " │ " << board[2][2] << " │\n"
                << "  └───┴───┴───┘\n\n";
    }
};


int main() {
    TicTacToe game;
    game.printBoard();
    return 0;
}
