#include "TicTacToeView.h"

using namespace std;

void TicTacToeView::PrintBoard(ostream &s) const {
   s << "- ";
   for (int i = 0; i < BOARDSIZE; i++) {
      s << i << " ";
   }
   for (int row = 0; row < BOARDSIZE; row++) {
      s << endl << row << " ";
      for (int col = 0; col < BOARDSIZE; col++) {
         if (mTicTacToeBoard->mBoard[row][col] == 0)
            s << ". ";
         else if (mTicTacToeBoard->mBoard[row][col] == 1)
            s << "0 ";
         else if (mTicTacToeBoard->mBoard[row][col] == -1)
            s << "X ";
      }
   }
   s << endl << endl;
}