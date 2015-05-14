#ifndef __TICTACTOEMOVE_H
#define __TICTACTOEMOVE_H

#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>


class TicTacToeMove : public GameMove {
private:
   friend class TicTacToeBoard;

   int mRow, mCol;

   //Default constructor 
   TicTacToeMove();

   TicTacToeMove(int row, int col);

public:
   static int mOnHeap;

   static void* operator new(std::size_t sz){ 
      mOnHeap++;
      std::cout << "operator new: " << mOnHeap << " TicTacToeMoves on the heap" << std::endl;
      return ::operator new(sz);
   }

      static void operator delete(void* ptr, std::size_t sz) {
      mOnHeap--;
      std::cout << "operator delete: " << mOnHeap << " TicTacToeMoves on the heap" << std::endl;
      ::operator delete(ptr);
   }

   virtual GameMove& operator=(const std::string &);

   virtual bool Equals(const GameMove &other) const;

   virtual operator std::string() const;

   inline bool isPass() const { return mRow == -1 && mCol == -1; }

};
#endif