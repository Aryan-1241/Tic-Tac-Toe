#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 3;

enum class Player
{
    NONE,
    X,
    O
};

class TicTacToe
{
public:
    TicTacToe() : board(BOARD_SIZE, vector<Player>(BOARD_SIZE, Player::NONE)), currentPlayer(Player::X) {}

    void play()
    {
        while (!isGameOver())
        {
            displayBoard();
            int row, col;
            cout << "Player " << playerToString(currentPlayer) << ", enter your move (row column): ";
            cin >> row >> col;

            if (isValidMove(row, col))
            {
                makeMove(row, col);
                if (checkWin(currentPlayer))
                {
                    displayBoard();
                    cout << "Player " << playerToString(currentPlayer) << " wins!" << endl;
                    return;
                }
                currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }
        }
        displayBoard();
        cout << "It's a draw!" << endl;
    }

private:
    vector<vector<Player>> board;
    Player currentPlayer;

    bool isValidMove(int row, int col) const
    {
        return (row >= 0 && row < BOARD_SIZE) && (col >= 0 && col < BOARD_SIZE) && (board[row][col] == Player::NONE);
    }

    void makeMove(int row, int col)
    {
        board[row][col] = currentPlayer;
    }

    bool checkWin(Player player) const
    {
        // Check rows, columns, and diagonals for a win
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            {
                return true; // Row win
            }
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            {
                return true; // Column win
            }
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        {
            return true; // Diagonal win (top-left to bottom-right)
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        {
            return true; // Diagonal win (top-right to bottom-left)
        }
        return false;
    }

    bool isGameOver() const
    {
        // Game is over if the board is full or there is a win
        return isBoardFull() || checkWin(Player::X) || checkWin(Player::O);
    }

    bool isBoardFull() const
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (board[i][j] == Player::NONE)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void displayBoard() const
    {
        cout << endl;
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                cout << playerToString(board[i][j]) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    string playerToString(Player player) const
    {
        if (player == Player::X)
        {
            return "X";
        }
        else if (player == Player::O)
        {
            return "O";
        }
        else
        {
            return " ";
        }
    }
};

int main()
{
    TicTacToe game;
    game.play();
    return 0;
}
