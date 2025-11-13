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

    std::pair<int, int> getMove(char player) {
        int row, col;
        char comma;

        while (true) {
            std::cout << "Move for player '" << player << "': ";

            std::cin >> row >> comma >> col;
            std::cout << "\n";

            if (row < 0 || row > 2 || col < 0 || col > 2) {
                std::cout << "Out of bounds move, please pick a valid cell.\n";
                continue;
            }

            if (board[row][col] != ' ') {
                std::cout << "Invalid move, cell is already occupied.\n";
                continue;
            }

            board[row][col] = player;
            break;
        }

        return {row, col};
    }

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

    void run() {
        while (true) {
            printBoard();
            getMove(x);
            printBoard();
            getMove(o);
        }
    }
};


int main() {
    TicTacToe game;
    game.run();
    return 0;
}
