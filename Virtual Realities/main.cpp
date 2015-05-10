
#include "GameBoard.h"
#include "GameView.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
   GameBoard *board;
   GameView *v;
   cout << "What game do you want to play?" << endl
      << "1) Othello; 2) Tic Tac Toe; 3) Connect Four; 4) Exit" << endl;
   string in;
   cin >> in;
   if (in == "1") {
      cout << "User want to play Othello" << endl;
   }
   else if (in == "2") {
      cout << "User want to play Tic Tac Toe" << endl;
   }
   else if (in == "3") {
      cout << "User want to play Connect Four" << endl;
   }

   system("pause");
}