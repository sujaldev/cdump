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
};


int main() {
    TicTacToe game;
    return 0;
}
