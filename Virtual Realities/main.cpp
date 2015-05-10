
#include "GameBoard.h"
#include "GameView.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
   
   do {
      GameBoard *board = nullptr;
      GameView *v = nullptr;
      string userInput;
      vector<GameMove *> possMoves;
      GameMove *m = nullptr;
      cout << "What game do you want to play?" << endl
         << "1) Othello; 2) Tic Tac Toe; 3) Connect Four; 4) Exit" << endl;
      getline(cin, userInput);
      if (userInput == "1") {
         cout << "User want to play Othello" << endl;
         board = new OthelloBoard();
         v = new OthelloView(board);
      }
      else if (userInput == "2") {
         cout << "User want to play Tic Tac Toe" << endl;
      }
      else if (userInput == "3") {
         cout << "User want to play Connect Four" << endl;
      }
      else if (userInput == "4") {
         break;
      }
      do {
         if (board == nullptr && v == nullptr)
            break;
         cout << *v << endl;
         board->GetPossibleMoves(&possMoves);
         cout << "Board Possible Move: ";
         for (GameMove* i : possMoves) {
            cout << (string)(*i) << " ";
         }
         cout << endl;
         if (board->GetNextPlayer() > 0) {

            cout << "Black Turn" << endl;
         }
         else
            cout << "White Turn" << endl;
         string command;
         getline(std::cin, command);
         stringstream ss(command);
         ss >> command;
         if (command == "move") {
            if (!ss.eof()) {
               ss >> command;
               m = board->CreateMove();
               try {
                  *m = command;
                  bool valid = false;

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
               catch (OthelloException &e) {
                  delete m;
                  cout << e.what() << endl;
               }
            }
            else
               cout << "Invalid input" << endl;
         }

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
         if (command == "showValue") {
            cout << "Board Value: " << board->GetValue() << endl;
         }
         if (command == "showHistory") {
            vector<GameMove*> lis(*(board->GetMoveHistory()));
            int turnCount = lis.size();
            for (int i = lis.size(); i > 0; i--) {
               if (i % 2 == 1) {
                  cout << "Black ";
               }
               else
                  cout << "White";
               cout << (string)(*lis[i - 1]) << endl;
            }
         }
         if (command == "quit") {
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
      delete board;
      delete v;

   } while (true);
   system("pause");
}