#include "TicTacToeBoard.h"

using namespace std;

TicTacToeBoard::TicTacToeBoard() {
   for (int row = 0; row < BOARDSIZE; row++) {
      for (int col = 0; col < BOARDSIZE; col++) {
         mBoard[row][col] = Player::EMPTY;
      }
   }
   mNextPlayer = Player::X;
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
   
   if (m->isPass()) {
      mPassCount++;
      mHistory.push_back(move);
   }
   else {
      mPassCount = 0;
      //cout << m->mRow << " " << m->mCol << endl;
      mHistory.push_back(move);
      mValue += GetNextPlayer();
      mBoard[m->mRow][m->mCol] = GetNextPlayer();
   }
   mNextPlayer = -mNextPlayer;
}

void TicTacToeBoard::UndoLastMove() {
   if (mHistory.size() > 0) {
      mNextPlayer = -mNextPlayer;
      TicTacToeMove *m = dynamic_cast<TicTacToeMove *>(mHistory.back());
      mBoard[m->mRow][m->mCol] = Player::EMPTY;

      delete m;
      mHistory.pop_back();
      mValue -= mNextPlayer;
   }

}