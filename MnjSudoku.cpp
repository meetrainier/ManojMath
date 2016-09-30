//copyright(c) 2016 Manoj Lnu 
// Time :  3:10 - 4:40 
//         9:30 -11:20
// 9/29/2016: Manoj : Created the file.
//            
#include <algorithm>
#include <iostream>
#include <vector>
#include "MnjSudoku.h"

using namespace std;

bool MnjSudoku::ApplyConstraints() {
  
  bool shrunk = false;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      shrunk = ApplySmallSquareConstraints(i, j);
      if (shrunk) break;
      shrunk = ApplyColumnConstraints(i, j);
      if (shrunk) break; 
      shrunk = ApplyRowConstraints(i, j);
      if (shrunk) break;
    }
    if (shrunk) break;
  }

  return shrunk; 
}

void MnjSudoku::SetElement(int row, int column, int value) {
  vi vec{value};
  board[row][column] = vec; 
}
///////////////////////////////
void MnjSudoku::Solve1() {

  bool shrunk = false;
  bool solved = false;
  int count = 0; 

  while (!solved) {
    count++; 
    shrunk = ApplyConstraints();
    solved = IsComplete(); 
    if (!shrunk) {
      cerr <<"No shrinking in round " << count<< endl;
    }

    if (1000 == count ) {
      MnjSudoku::Debug d(this);
      cout << "It is iteration << " << count << endl;
      d.Print();
    }

    if (2000 == count) {
      MnjSudoku::Debug d(this);
      cout << "It is iteration << " << count << endl;
      d.Print();
    }

  }; 

}
/*
void MnjSudoku::Solve() {

  //Make sure each small square element is shrinked. b
  bool shrunk = false; 
  bool solved = false; 
  bool cont = false; 

  for (int i = 0; i < 9; ++i) {
    cont = false;
    for (int j = 0; j < 9; ++j){
      
      shrunk = ApplySmallSquareConstraints(i, j);
      
      if (shrunk) {
        solved = IsComplete();
        if (solved) {
          break;
        }
        else {
          //again loop from beginning
          i = 0; j = 0;
          cont = true;
          continue; 
        }
      }
      
      shrunk = ApplyColumnConstraints(i, j);
      if (shrunk) {
        solved = IsComplete();
        if (solved)
          break;
        else {
          //again loop from beginning
          i = 0; j = 0;
          cont = true;
          continue;
        }
      }
  
      shrunk = ApplyRowConstraints(i, j);
      if (shrunk) {
        solved = IsComplete();
        if (solved)
          break;
        else {
          //again loop from beginning
          i = 0; j = 0;
          cont = true;
          continue;
        }
      }

    }
    if (solved)
      break;
  }//outer for loop

}
*/
//////////////////////////////////////////////////////////
bool MnjSudoku::ApplySmallSquareConstraints(int row, int column) {
  bool shrunk = false;
  int r = 3 * (row / 3);//imp: can be cached
  int c = 3 * (column / 3);//imp: can be cached

  if (1 == board[row][column].size()) {
    int val = board[row][column][0];
    for (int i = r; i < r + 3; ++i) {
      for (int j = c; j < c + 3; ++j) {
        if (board[i][j].size() > 1) {
          auto it = remove_if(begin(board[i][j]), end(board[i][j]), [&val](int tmp) {return tmp == val; });
          if (it != end(board[i][j])) {
            board[i][j].erase(it, end(board[i][j]));
            shrunk = true;
          }
        }
      }
    }
  }
  return shrunk;
}
//////////////////////////////////////////////////////////
bool MnjSudoku::ApplyColumnConstraints(int row, int column) {
  
  bool shrunk = false; 

  if (1 == board[row][column].size()) {

    int val = board[row][column][0]; 
    for (int i = 0; i < 9; ++i) {
      if (board[row][i].size() > 1) {
       auto it = remove_if(begin(board[row][i]), end(board[row][i]), [&val](int tmp) {return tmp == val; });
       if (it != end(board[row][i]) ) {
         board[row][i].erase(it,end(board[row][i]));
         shrunk = true;
       }
      }//if the elements in the vec are more than one
    }// for each column member

  }// if the current index size is  exactly 1

  return shrunk;

}

bool MnjSudoku::ApplyRowConstraints(int row, int column) {

  bool shrunk = false; 

  if (1 == board[row][column].size()) {
    int val = board[row][column][0];

    for (int i = 0; i < 9; ++i) {

      if (board[i][column].size() > 1) {
        auto it = remove_if(begin(board[i][column]), end(board[i][column]), [&val](int tmp) {return tmp == val; });
        if (it != end(board[i][column])) {
          board[i][column].erase(it, end(board[i][column]));
          shrunk = true;
        }
      }
    }
  }
  return shrunk;
}

bool MnjSudoku::IsComplete() {

  bool result = true;
  
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j].size() > 1) {
        result = false;
      }
    }
  }

  return result; 

}

void MnjSudoku::SetElementFromIndex1(int r, int c, int val) {
  SetElement(r-1,c-1,val);
}
void MnjSudoku::Debug::Print() {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (mps->board[i][j].size() > 1) {
        cout << "M\t"; 
      }
      else if (1==mps->board[i][j].size()) {
        cout << mps->board[i][j][0] <<"\t" ; 
      }
    }
    cout << endl;
  }
}

void sudoku_test1() {

  MnjSudoku s;
  //s.SetElement(1,1,1);
  //First Row
  s.SetElementFromIndex1(1, 1, 4);
  s.SetElementFromIndex1(1, 2, 6);
  s.SetElementFromIndex1(1, 4, 8);
  s.SetElementFromIndex1(1, 5, 9);
  s.SetElementFromIndex1(1, 6, 2);

  //2nd row
  s.SetElementFromIndex1(2, 1, 7);
  s.SetElementFromIndex1(2, 2, 3);
  s.SetElementFromIndex1(2, 4, 6);

  //3rd row
  s.SetElementFromIndex1(3, 3, 9);
  s.SetElementFromIndex1(3, 7, 1);
  s.SetElementFromIndex1(3, 8, 6);

  //4th row
  s.SetElementFromIndex1(4, 1, 1);
  s.SetElementFromIndex1(4, 2, 8);
  s.SetElementFromIndex1(4, 4, 5);  
  s.SetElementFromIndex1(4, 5, 7);
  s.SetElementFromIndex1(4, 6, 3);

  //5th row
  s.SetElementFromIndex1(5, 3, 3);
  s.SetElementFromIndex1(5, 4, 9);
  s.SetElementFromIndex1(5, 6, 4);
  s.SetElementFromIndex1(5, 7, 6);

  //6th row
  s.SetElementFromIndex1(6, 4, 2);
  s.SetElementFromIndex1(6, 5, 1);
  s.SetElementFromIndex1(6, 6, 6);
  s.SetElementFromIndex1(6, 8, 7);
  s.SetElementFromIndex1(6, 9, 3);

  //7th row
  s.SetElementFromIndex1(7, 2, 9);
  s.SetElementFromIndex1(7, 3, 2);
  s.SetElementFromIndex1(7, 7, 3);

  //8th Row
  s.SetElementFromIndex1(8, 6, 9);
  s.SetElementFromIndex1(8, 8, 8);
  s.SetElementFromIndex1(8, 9, 6);

  //9th Row
  s.SetElementFromIndex1(9, 4, 3);
  s.SetElementFromIndex1(9, 5, 6);
  s.SetElementFromIndex1(9, 6, 7);
  s.SetElementFromIndex1(9, 8, 2);
  s.SetElementFromIndex1(9, 9, 6);

  MnjSudoku::Debug d(&s);
  d.Print();
  s.Solve1();
  d.Print();

}







