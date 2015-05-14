#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include <sstream>

int TicTacToeMove::mOnHeap = 0;

using namespace std;

TicTacToeMove::TicTacToeMove()
   :mRow(-1), mCol(-1){

}

TicTacToeMove::TicTacToeMove(int row, int col)
   :mRow(row), mCol(col){

}


GameMove& TicTacToeMove::operator=(const string &move) {
   if (move == "pass") {
      mRow = -1;
      mCol = -1;
      return *this;
   }
   else {
      char temp;
      istringstream ss(move);
      ss >> temp >> mRow >> temp >> mCol >> temp;
      if (!TicTacToeBoard::InBounds(mRow, mCol)) {
         throw GameException("Out of BOUND!");
      }
      return *this;
   }
}

bool TicTacToeMove::Equals(const GameMove &other) const {
   const TicTacToeMove *m = dynamic_cast<const TicTacToeMove *>(&other);
   return mRow == m->mRow && mCol == m->mCol;
}

TicTacToeMove::operator string() const {
   if (mRow == -1 && mCol == -1) {
      return "pass";
   }
   ostringstream s;
   s << "(" << mRow << ", " << mCol << ")";
   return s.str();
}
