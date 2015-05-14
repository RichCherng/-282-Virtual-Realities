#ifndef __TICTACTOEBOARD_H
#define __TICTACTOEBOARD_H

#include <vector>
#include "GameBoard.h"
#include "GameMove.h"
#include "TicTacToeMove.h"


const int BOARDSIZE = 3;

class TicTacToeBoard : public GameBoard {

public: 
   enum Player { EMPTY = 0, X = 1, O = -1 };

   //Default constructor
   TicTacToeBoard();

   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;

   virtual void ApplyMove(GameMove *move);

   virtual void UndoLastMove();

   virtual GameMove *CreateMove() const { return new TicTacToeMove; }

   inline static bool InBounds(int row, int col) {
      return row >= 0 && row < BOARDSIZE && col >= 0 && col < BOARDSIZE;
   }

   virtual bool IsFinished() const {
      return mPassCount == 2;
   }

private:
   friend class TicTacToeView;
   char mBoard[BOARDSIZE][BOARDSIZE];
   int mPassCount;
};

#endif