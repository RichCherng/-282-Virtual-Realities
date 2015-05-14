#include "TicTacToeBoard.h"

using namespace std;

TicTacToeBoard::TicTacToeBoard() {
   for (int row = 0; row < BOARDSIZE; row++) {
      for (int col = 0; col < BOARDSIZE; col++) {
         mBoard[row][col] = Player::EMPTY;
      }
   }
}

void TicTacToeBoard::GetPossibleMoves(vector<GameMove *> *list) const {
   for (int row = 0; row < BOARDSIZE; row++) {
      for (int col = 0; col < BOARDSIZE; col++) {
         if (mBoard[row][col] == Player::EMPTY)
            (*list).push_back(new TicTacToeMove(row, col));
      }
   }
}

void TicTacToeBoard::ApplyMove(GameMove *move) {
   TicTacToeMove *m = dynamic_cast<TicTacToeMove *>(move);
   //cout << m->mRow << " " << m->mCol << endl;
   //------Apply the move-----
   mHistory.push_back(move);
   mBoard[m->mRow][m->mCol] = GetNextPlayer();
   //Check if this is the winning move
   bool check = false;
   for (int r = -1; r <= 1 && !check; r++) {
      for (int c = -1; c <= 1 && !check; c++) {
         int bRow = m->mRow + r, bCol = m->mCol + c;
         //look in one direction and check if it is the same piece
         if ((InBounds(bRow, bCol)) && mBoard[bRow][bCol] == mNextPlayer 
            && !(c == 0 && r == 0)) {
            //go one more step 
            bRow += r;
            bCol += c; 
            if (InBounds(bRow, bCol)) {
               //check if it is the same piece
               if (mBoard[bRow][bCol] == mNextPlayer) {
                  //cout << bRow << " " << bCol << endl;
                  mValue = mNextPlayer;
                  finish = true;
                  mValue = mNextPlayer;
                  check = true;
               }
            }
            //Check the opposite end
            else {
               bRow -= 3 * r;
               bCol -= 3 * c;
               /cout << bRow << " " << bCol << endl;
               if ((InBounds(bRow, bCol)) && mBoard[bRow][bCol] == mNextPlayer) {
                  mValue = mNextPlayer;
                  finish = true;
                  mValue = mNextPlayer;
                  check = true;
               }

            }

         }

      }
   }
   if (mHistory.size() >= BOARDSIZE * BOARDSIZE && !check) {
      mValue = Player::EMPTY;
      finish = true;
   }

   //switch the player
   mNextPlayer = -mNextPlayer;
}

void TicTacToeBoard::UndoLastMove() {
   if (mHistory.size() > 0) {
      mNextPlayer = -mNextPlayer;
      TicTacToeMove *m = dynamic_cast<TicTacToeMove *>(mHistory.back());
      mBoard[m->mRow][m->mCol] = Player::EMPTY;

      delete m;
      mHistory.pop_back();
   }

}