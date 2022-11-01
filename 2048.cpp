#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

/*
 * Problem statement:
 *
 * Create the game of 2048. Tiles will spawn randomly in the available spaces,
 * with the game starting with two 2 tiles randomly placed on the 4x4 grid.
 *
 * Inputs:
 *
 * vector<string> moves -> where moves[i] represents the ith move.
 *
 * Output:
 *
 * vector<vector<int>> -> the state of the board after all moves.
 */

using namespace std;

struct hashFunc {
    size_t operator()(const tuple<int, int> &x) const {
        return get<0>(x) ^ get<1>(x);
    }
};

class Game {

    static const int BOARD_SIZE = 4;

    vector<vector<int>> board;
    unordered_set<tuple<int, int>, hashFunc> freeSpaces;

    void spawnTile() {
        tuple<int, int> freeSpace = *freeSpaces.begin();
        int i = get<0>(freeSpace), j = get<1>(freeSpace);
        freeSpaces.erase(freeSpace);
        board[i][j] = 2;
    }

    void coalesceUp() {
        for (int j = 0; j < BOARD_SIZE; j++) {
            vector<int> coalesced = {};
            int prev = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board[i][j] == 0) {
                    continue;
                }
                if (prev == 0) {
                    prev = board[i][j];
                } else if (prev != board[i][j]) {
                    coalesced.push_back(prev);
                    prev = board[i][j];
                } else {
                    coalesced.push_back(prev * 2);
                    prev = 0;
                }
            }
            if (prev != 0) {
                coalesced.push_back(prev);
            }
            for (int i = 0; i < coalesced.size(); i++) {
                freeSpaces.erase(tuple<int, int>(i, j));
                board[i][j] = coalesced[i];
            }
            for (int i = coalesced.size(); i < BOARD_SIZE; i++) {
                freeSpaces.insert(tuple<int, int>(i, j));
                board[i][j] = 0;
            }
        }
    }

    void coalesceLeft() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            vector<int> coalesced = {};
            int prev = 0;
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0) {
                    continue;
                }
                if (prev == 0) {
                    prev = board[i][j];
                } else if (prev != board[i][j]) {
                    coalesced.push_back(prev);
                    prev = board[i][j];
                } else {
                    coalesced.push_back(prev * 2);
                    prev = 0;
                }
            }
            if (prev != 0) {
                coalesced.push_back(prev);
            }
            for (int j = 0; j < coalesced.size(); j++) {
                freeSpaces.erase(tuple<int, int>(i, j));
                board[i][j] = coalesced[j];
            }
            for (int j = coalesced.size(); j < BOARD_SIZE; j++) {
                freeSpaces.insert(tuple<int, int>(i, j));
                board[i][j] = 0;
            }
        }
    }

    void coalesceDown() {
        for (int j = 0; j < BOARD_SIZE; j++) {
            vector<int> coalesced = {};
            int prev = 0;
            for (int i = BOARD_SIZE - 1; i >= 0; i--) {
                if (board[i][j] == 0) {
                    continue;
                }
                if (prev == 0) {
                    prev = board[i][j];
                } else if (prev != board[i][j]) {
                    coalesced.push_back(prev);
                    prev = board[i][j];
                } else {
                    coalesced.push_back(prev * 2);
                    prev = 0;
                }
            }
            if (prev != 0) {
                coalesced.push_back(prev);
            }
            for (int i = 0; i < coalesced.size(); i++) {
                freeSpaces.erase(tuple<int, int>(BOARD_SIZE - 1 - i, j));
                board[BOARD_SIZE - 1 - i][j] = coalesced[i];
            }
            for (int i = coalesced.size(); i < BOARD_SIZE; i++) {
                freeSpaces.insert(tuple<int, int>(BOARD_SIZE - 1 - i, j));
                board[BOARD_SIZE - 1 - i][j] = 0;
            }
        }
    }

    void coalesceRight() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            vector<int> coalesced = {};
            int prev = 0;
            for (int j = BOARD_SIZE - 1; j >= 0; j--) {
                if (board[i][j] == 0) {
                    continue;
                }
                if (prev == 0) {
                    prev = board[i][j];
                } else if (prev != board[i][j]) {
                    coalesced.push_back(prev);
                    prev = board[i][j];
                } else {
                    coalesced.push_back(prev * 2);
                    prev = 0;
                }
            }
            if (prev != 0) {
                coalesced.push_back(prev);
            }
            for (int j = 0; j < coalesced.size(); j++) {
                freeSpaces.erase(tuple<int, int>(i, BOARD_SIZE - 1 - j));
                board[i][BOARD_SIZE - 1 - j] = coalesced[j];
            }
            for (int j = coalesced.size(); j < BOARD_SIZE; j++) {
                freeSpaces.insert(tuple<int, int>(i, BOARD_SIZE - 1 - j));
                board[i][BOARD_SIZE - 1 - j] = 0;
            }
        }
    }

    bool processMove(string move) {
        cout << move << endl;
        vector<vector<int>> oldBoard = board;
        if (move == "up") {
            coalesceUp();
        } else if (move == "right") {
            coalesceRight();
        } else if (move == "down") {
            coalesceDown();
        } else if (move == "left") {
            coalesceLeft();
        }
        if (oldBoard != board) {
            spawnTile();
        }
        printBoard();
        return freeSpaces.size();
    };

    bool playableState() {
        for (int i = 0; i < BOARD_SIZE - 1; i++) {
            for (int j = 0; j < BOARD_SIZE - 1; j++) {
                if (board[i][j] == board[i + 1][j] ||
                    board[i][j] == board[i][j + 1] || board[i][j] == 0 ||
                    board[i + 1][j] == 0 || board[i][j + 1] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

  public:
    Game() {
        this->board =
            vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
        this->freeSpaces = {};
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                freeSpaces.insert(tuple<int, int>(i, j));
            }
        }
        spawnTile();
        spawnTile();
    }

    void printBoard() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void processMoves(vector<string> moves) {
        for (string move : moves) {
            processMove(move);
            if (!playableState()) {
                cout << "Game over!" << endl;
                return;
            }
        }
    }
};

int main() {
    vector<string> moves = {
        "up",    "down",  "left",  "right", "right", "up",    "down",  "left",
        "up",    "down",  "up",    "down",  "left",  "right", "right", "up",
        "down",  "left",  "up",    "down",  "up",    "down",  "left",  "right",
        "right", "up",    "down",  "left",  "up",    "down",  "up",    "down",
        "left",  "right", "right", "up",    "down",  "left",  "up",    "down",
        "up",    "down",  "left",  "right", "right", "up",    "down",  "left",
        "up",    "down",  "up",    "down",  "left",  "right", "right", "up",
        "down",  "left",  "up",    "down",  "up",    "down",  "left",  "right",
        "right", "up",    "down",  "left",  "up",    "down",  "up",    "down",
        "left",  "right", "right", "up",    "down",  "left",  "up",    "down",
        "up",    "down",  "left",  "right", "right", "up",    "down",  "left",
        "up",    "down",  "up",    "down",  "left",  "right", "right", "up",
        "down",  "left",  "up",    "down",  "up",    "down",  "left",  "right",
        "right", "up",    "down",  "left",  "up",    "down",  "up",    "down",
        "left",  "right", "right", "up",    "down",  "left",  "up",    "down"};
    Game game = Game();
    game.processMoves(moves);
    return 0;
}

/*
 * Analysis:
 *
 * Time complexity - O(N^2) per move where N is the side length of the game
 * board. O(1) time to find a new spawning spot.
 *
 * Space complexity - O(N^2) as we maintain the game state and also the set of
 * free spaces.
 *
 */