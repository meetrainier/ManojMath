#pragma once
////copyright(c) 2016 Manoj Lnu 
// Time :  3:10 - 4:40 
//         9:30 -11:20
#include <algorithm>
#include <iostream>
#include <vector>
extern void sudoku_test1(); 
using namespace std;

class MnjSudoku {

public:

  using vi = vector<int>;
  //using v99 = vector<v9>; 
  //using v999 = vector<v99>;
  const vi tmp{ 1,2,3,4,5,6,7,8,9 };//imp: This may be made
                                    //list , since elemenst will be removed from random places

  MnjSudoku() {

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        board[i][j] = tmp;
      }
    }
  }

  void Read() {

  }

  class Test {

    //checks that the enture board is in a valid state.
    void Check();
    //checks that state of a column is valid
    void CheckColumn();
    //checks that state of a row is valid
    void CheckRow();

    //counts how many houses have unique value
    int GetUniqueValHouseCount();

  };

  class Debug {
    MnjSudoku *mps;
  public:
    Debug(MnjSudoku *s) { mps = s; }
    void Print();
  };

  void Solve();
  void Solve1();
  auto ApplySmallSquareConstraints(int i, int j);
  auto ApplyColumnConstraints(int i, int j);
  auto ApplyRowConstraints(int i, int j);
  bool IsComplete()const;
  bool ApplyConstraints();
  void SetElement(const int row, const int column, const int value);
  void SetElementFromIndex1(const int r, const int c, const int val);

  int GetElementFromIndex1(const int r, const int c) const;
  int GetElement(const int r, const int c) const;

private:
  //v999 board;
  vi board[9][9];
};
