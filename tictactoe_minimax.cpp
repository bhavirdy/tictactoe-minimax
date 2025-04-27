#include <iostream>
#include <vector>
#include <limits>

using namespace std;
using Player = char;
using Utility = double;

const char EMPTY = '_';
const char PLAYER_X = 'x';
const char PLAYER_O = 'o';

struct Action {
    char player;
    int row;
    int col;

    Action(char p, int r, int c) : player(p), row(r), col(c) {}

    Action() {}
};

class State {
    public:
        char board[3][3];

        State(string inputBoard) {
            setBoard(inputBoard);
        }

        State() {}

        void setBoard(const string& inputBoard) {
            int index = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (inputBoard[index] == '.') {
                        board[i][j] = '_';
                    }
                    else if (inputBoard[index] == 'o') {
                        board[i][j] = 'o';
                    }
                    else if (inputBoard[index] == 'x') {
                        board[i][j] = 'x';
                    }
                    index++;
                }
            }
        }

        void displayBoard() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (j == 2) {
                        cout << board[i][j];
                    }
                    else {
                        cout << board[i][j] << " ";
                    }
                }
                if (i == 2){
                    break;
                }
                cout << endl;
            }
            cout << endl;
        }
};

class TicTacToeGame {
    public:

        TicTacToeGame() {}

        Player player(const State& state) {
            int counter = 0;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (state.board[i][j] == 'x' || state.board[i][j] == 'o') {
                        counter++;
                    }
                }
            }

            if (counter % 2 == 0) {
                return PLAYER_X;
            }

            return PLAYER_O;
        }

        vector<Action> actions(const State& state) {
            vector<Action> actions;

            Player p = player(state);

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (state.board[i][j] == '_') {
                        Action a(p, i, j);
                        actions.push_back(a);
                    }
                }
            }

            return actions;
        }

        State result(const State& state, const Action& action) {
            State newState = state;
            newState.board[action.row][action.col] = action.player;
            return newState;
        }

        bool gameWon(State& state, Player player) {
            for (int i = 0; i < 3; ++i) {
                if (state.board[i][0] == player && state.board[i][1] == player && state.board[i][2] == player)
                    return true;

                if (state.board[0][i] == player && state.board[1][i] == player && state.board[2][i] == player)
                    return true;
            }

            if (state.board[0][0] == player && state.board[1][1] == player && state.board[2][2] == player)
                return true;
            if (state.board[0][2] == player && state.board[1][1] == player && state.board[2][0] == player)
                return true;

            return false;
        }

        bool boardFull(State& state) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (state.board[i][j] == EMPTY) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool terminalTest(State& state) {
            if (gameWon(state, PLAYER_X) || gameWon(state, PLAYER_O)) {
                return true;
            }

            if (boardFull(state)) {
                return true;
            }

            return false;
        }

        Utility utility(State& state, Player player) {
            if (gameWon(state, PLAYER_X)) {
                return 1;
            }

            if (gameWon(state, PLAYER_O)) {
                return -1;
            }

            return 0;
        }
};

class Minimax {
    public:
        TicTacToeGame game;

        Minimax(TicTacToeGame game) {
            this->game = game;
        }

        Action minimaxDecisionForX(State& state) {
            vector<Action> actions = game.actions(state);
            if (actions.empty()) {
                return Action();
            }

            Action bestAction = actions[0];
            Utility bestUtility = numeric_limits<Utility>::lowest();

            for (const Action& a : actions) {
                State resultState = game.result(state, a);
                Utility utility = minValue(resultState);
                if (utility > bestUtility) {
                    bestUtility = utility;
                    bestAction = a;
                }
            }

            return bestAction;
        }

        Action minimaxDecisionForO(State& state) {
            vector<Action> actions = game.actions(state);
            if (actions.empty()) {
                return Action();
            }

            Action bestAction = actions[0];
            Utility bestUtility = numeric_limits<Utility>::max();

            for (const Action& a : actions) {
                State resultState = game.result(state, a);
                Utility utility = maxValue(resultState);
                if (utility < bestUtility) {
                    bestUtility = utility;
                    bestAction = a;
                }
            }

            return bestAction;
        }

        Utility maxValue(State state) {
            if (game.terminalTest(state)) {
                return game.utility(state, PLAYER_X);
            }

            Utility v = numeric_limits<Utility>::lowest();
            vector<Action> actions = game.actions(state);

            for (Action& a : actions) {
                State resultState = game.result(state, a);
                v = max(v, minValue(resultState));
            }

            return v;
        }

        Utility minValue(State state) {
            if (game.terminalTest(state)) {
                return game.utility(state, PLAYER_X);
            }

            Utility v = numeric_limits<Utility>::max();
            vector<Action> actions = game.actions(state);

            for (Action& a : actions) {
                State resultState = game.result(state, a);
                v = min(v, maxValue(resultState));
            }

            return v;
        }
};

class GameLoop {
    public:
        TicTacToeGame game;
        State currentState;
        Minimax minimax;

        GameLoop(TicTacToeGame game, Minimax minimax, State currentState) : game(game), minimax(minimax), currentState(currentState) {}

        void play() {
            //currentState.displayBoard();
            while (!game.terminalTest(currentState)) {
                Player p = game.player(currentState);

                Action a;
                if (p == PLAYER_X) {
                    a = minimax.minimaxDecisionForX(currentState);
                }
                else if (p == PLAYER_O) {
                    a = minimax.minimaxDecisionForO(currentState);
                }

                currentState = game.result(currentState, a);
                //currentState.displayBoard();
            }

            if (game.gameWon(currentState, PLAYER_X)) {
                cout << "X wins";
            } else if (game.gameWon(currentState, PLAYER_O)) {
                cout << "O wins";
            } else {
                cout << "Draw";
            }
        }
};

int main()
{
    string inputBoard;
    cin >> inputBoard;

    State state(inputBoard);
    TicTacToeGame game;
    Minimax minimax(game);
    GameLoop loop(game, minimax, state);
    loop.play();

    return 0;
}
