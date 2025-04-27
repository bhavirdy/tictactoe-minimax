# Tic Tac Toe with Minimax Algorithm

This project implements a Tic Tac Toe game with an AI powered by the Minimax algorithm. The AI ensures optimal moves for both players, making it unbeatable.

## Features

- **Minimax Algorithm**: Implements the Minimax algorithm to calculate the best possible moves for both players.
- **Terminal States**: Detects win, loss, or draw conditions.
- **Customizable Input**: Accepts a board state as input to start the game from any valid configuration.

## How to Run

1. **Compile the Code**:
   Use a C++ compiler to compile the program. For example, using `g++`:
   ```bash
   g++ -o tictactoe tictactoe_minimax.cpp
2. Run the program:
    ./tictactoe
3. Provide input: enter the board state as a single string of 9 characters:
- Use x for Player X's moves.
- Use o for Player O's moves.
- Use . for empty spaces.
- Example input:
x.o...o.x
4. View Results: The program will display the winner (X wins, O wins) or Draw if the game ends in a tie.