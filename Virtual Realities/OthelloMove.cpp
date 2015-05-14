#include <sstream>
#include "OthelloMove.h"
#include "OthelloBoard.h"

int OthelloMove::mOnHeap = 0;

using namespace std;

OthelloMove::OthelloMove()
   :mRow(-1), mCol(-1) {

}

OthelloMove::OthelloMove(int row, int col)
   : mRow(row), mCol(col) {

}

GameMove& OthelloMove::operator=(const std::string &move) {
   if (move == "pass") {
      mRow = -1;
      mCol = -1;
      return *this;
   }
   else {
      char temp;
      istringstream ss(move);
      ss >> temp >> mRow >> temp >> mCol >> temp;
      if (!OthelloBoard::InBounds(mRow, mCol)) {
         throw OthelloException("Out of BOUND!");
      }
      return *this;
   }
}

/*bool operator==(const OthelloMove &lhs, const OthelloMove &rhs) {
   return (lhs.mRow == rhs.mRow) && (lhs.mCol == rhs.mCol);
}*/

bool OthelloMove::Equals(const GameMove &other) const {
   //OthelloMove &m = dynamic_cast<OthelloMove &>(other);
   //cannot cast away constant ^
   const OthelloMove *m = dynamic_cast<const OthelloMove *>(&other);
   return mRow == m->mRow && mCol == m->mCol;
}

OthelloMove::operator std::string() const {
   if (mRow == -1 && mCol == -1) {
      return "pass";
   }
   std::ostringstream s;
   s << "(" << mRow << ", " << mCol << ")";
   return s.str();
}