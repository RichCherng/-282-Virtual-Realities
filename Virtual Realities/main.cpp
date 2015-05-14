
#include "GameBoard.h"
#include "GameView.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "TicTacToeBoard.h"
#include "TicTacToeView.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {

   //---------Main loop----------------------
   do {
      //Declaring Variable
      GameBoard *board = nullptr;
      GameView *v = nullptr;
      vector<GameMove *> possMoves;
      GameMove *m = nullptr;
      string gameType;
      cout << "What game do you want to play?" << endl
         << "1) Othello; 2) Tic Tac Toe; 3) Connect Four; 4) Exit" << endl;
      getline(cin, gameType);
      //Initialize Othello Game
      if (gameType == "1") {
         cout << "User want to play Othello" << endl;
         board = new OthelloBoard();
         v = new OthelloView(board);
      }
      //Initialize Tic Tac Toe Game
      else if (gameType == "2") {
         cout << "User want to play Tic Tac Toe" << endl;
         board = new TicTacToeBoard();
         v = new TicTacToeView(board);
      }
      //Initialize Connect Four
      else if (gameType == "3") {
         cout << "User want to play Connect Four" << endl;
      }
      //Quit Game
      else if (gameType == "4") {
         break;
      }
      //Game loop
      bool quit = false;
      do {
         //If the game hasn't been chosen then quit
         if (board == nullptr && v == nullptr)
            break;
         //Print out the board
         cout << *v << endl;
         //Get Possible Moves
         board->GetPossibleMoves(&possMoves);
         cout << "Board Possible Move: ";
         //cout << possMoves.size();
         for (GameMove* i : possMoves) {
            cout << (string)(*i) << " ";
         }
         cout << endl;
         //-------Display Next Player---------
         cout << board->GetPlayerString(board->GetNextPlayer()) + " Turn" << endl;

         //------Reading in input--------------------
         string command;
         getline(std::cin, command);
         stringstream ss(command);
         ss >> command;
         //Reading in input
         if (command == "move") {
            if (!ss.eof()) {
               ss >> command;
               m = board->CreateMove();
               try {
                  *m = command;
                  bool valid = false;
                  //Check for possible move
                  for (GameMove* i : possMoves) {
                     if ((*m).Equals(*(i))) {
                        valid = true;
                        board->ApplyMove(m);
                     }
                  }
                  if (!valid) {
                     delete m;
                     cout << "Invalid move" << endl;
                  }
               }
               catch (GameException &e) {
                  delete m;
                  cout << e.what() << endl;
               }
            }
            else
               cout << "Invalid input" << endl;
         }
         //---------Undo move-----------
         if (command == "undo") {
            if (!ss.eof()) {
               ss >> command;
               istringstream buffer(command);
               int undoMove;
               buffer >> undoMove;
               for (int i = 0; i < undoMove; i++) {
                  board->UndoLastMove();
               }
            }
         }
         //----------Show Value----------
         if (command == "showValue") {
            cout << "Board Value: " << board->GetValue() << endl;
         }
         //-----------Show History--------
         if (command == "showHistory") {
            vector<GameMove*> lis(*(board->GetMoveHistory()));
            int turnCount = lis.size();
            for (int i = lis.size(); i > 0; i--) {
               /* if (i % 2 == 1) {
                   cout << "Black ";
                   }
                   else
                   cout << "White";*/
               cout << board->GetPlayerString(i);
               cout << (string)(*lis[i - 1]) << endl;
            }
         }
         //-----------Quit-------------
         if (command == "quit") {
            quit = true;
            for (GameMove* i : possMoves) {
               delete i;
            }
            break;
         }
         for (GameMove* i : possMoves) {
            delete i;
         }
         possMoves.clear();
      } while (!board->IsFinished());
      if (!quit) {
         cout << *v << endl; 
         if (board->GetValue() == 0)
            cout << "TIE" << endl;
         else
            cout << board->GetPlayerString(board->GetValue()) + " Win" << endl;
      }
      delete board;
      delete v;
      //possMoves.clear();

   } while (true);
   system("pause");
}