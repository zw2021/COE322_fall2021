/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2021 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** queens.cxx : solution to 8-queens problem
 ****
 ****************************************************************/

#include <iostream>
// using std::cin;
// using std::cout;
// using std::endl;
// #include <iomanip>
// using std::fixed;
// using std::setprecision;

#include <vector>
// using std::vector;
// #include <chrono>
// #include <optional>
//using std::optional;
using namespace std;

class board {
private:
  vector<vector<int>> grid;
public:
  board(int n) {
    //vector<vector<int>> grid(n, vector<int>(n,0));
    vector<int> zeros;
    for(int i = 0; i < n; i++) {
      zeros.push_back(0);
    }
    for(int i = 0; i < n; i++) {
      grid.push_back(zeros);
    }
    fill_grid();
  }
  int val(int row, int col) {
    return grid[row][col];
  }
  bool contains_queen(int row, int col) {
    if (row < 0 || col < 0 || col >= grid[row].size()) {
      //cout << "Error: contains_queen out of bounds. Row = " << row <<", Col = " << col << endl;
      return false;
    }
    if (grid[row][col] == 1) {
      return true;
    }
    return false;
  }
  void place_queen(int row, int col) {
    cout << "placing queen at " << row << ", " << col << endl;
    if (row > grid.size() || row < 0 || col > grid[row].size() || col < 0) {
      cout << "Error in place_queen, row or column exceeds bound. Row = " << row << ", Col = " << col << endl;
      return; 
    }
    grid[row][col] = 1;
  }
  void delete_queen(int row, int col) {
    if (contains_queen(row,col)) {
      cout << "deleting queen at " << row << ", " << col << endl;
      grid[row][col] = 0;
      return;
    }
    //cout << "Error: queen not found at Row = " << row << ", Col = " << col << endl;
    return;
  }
  void move_queen(int row1, int col1, int row2, int col2) {
    delete_queen(row1,col1);
    place_queen(row2,col2);
    return;
  }
  void fill_grid() {
    for (int r = 0; r < grid.size(); r++) {
      for (int c = 0; c < grid[r].size(); c++) {
        if (is_valid(r,c)) {
          place_queen(r,c);
          break;
        }
      }
      if (!row_contains_queen(r)) {
        while (r >= 0) {
          delete_queen(r,get_queen_col(r));
          r--;
          if (get_queen_col(r) < grid[r].size() - 1) {
            
            move_queen(r,get_queen_col(r),r,get_queen_col(r)+1);
            break;
          }
        }
        if (r < 0) {
          cout << "Error: Grid size not feasible." << endl;
          return;
        }
      }
    }
    return;
  }
  int get_queen_col(int row) {
    for (int c = 0; c < grid[row].size(); c++) {
      if (contains_queen(row,c)) return c;
    }
    cout << "Error: get_queen_col could not find a queen on row " << row << endl;
    return -1;
  }
  bool row_contains_queen(int row) {
    for (int c = 0; c < grid[row].size(); c++) {
      if (contains_queen(row,c)) return true;
    }
    return false;
  }


  bool is_valid(int row, int col) {
    //check columns and diags
    for (int r = row; r >= 0; r--) {
      if (contains_queen(r,col)) return false;
      if (contains_queen(r,col - row + r)) return false;
      if (contains_queen(r,col + row - r)) return false;
    }
    return true;
    //check diags
  }
    
  void print() {
    for(int i = 0; i < grid.size(); i++) {
      for(int j = 0; j < grid[i].size(); j++) {
        cout << grid[i][j] << " ";
      }
      cout << endl;
    }
    return;
  }
};

int main() {
  int n = 8;
  board queens(n);
  queens.print();
  //cout << queens.val(0,0);
  return 0;
}
// #ifndef NQUEENS
// #define NQUEENS 8
// #endif

// #define CATCH_CONFIG_MAIN
// #include "catch2/catch_all.hpp"

// TEST_CASE( "empty board" ) {
//   int n=10;
//   board empty(n);
//   REQUIRE( empty.next_row_to_be_filled()==0 );
// }

// TEST_CASE( "bounds test" ) {
//   int n=10;
//   board empty(n);
//   REQUIRE_THROWS( empty.place_next_queen_at_column(-1) );
//   REQUIRE_THROWS( empty.place_next_queen_at_column(n) );
//   REQUIRE_NOTHROW( empty.place_next_queen_at_column(0) );
//   REQUIRE( empty.next_row_to_be_filled()==1 );
// }

// TEST_CASE( "feasibility test" ) {
//   constexpr int n=10;
//   board empty(n);
//   REQUIRE( empty.feasible() );

//   board one = empty;
//   one.place_next_queen_at_column(0);
//   REQUIRE( one.next_row_to_be_filled()==1 );
//   REQUIRE( one.feasible() );
// }

// TEST_CASE( "collision test" ) {
//   constexpr int n=10;
//   board empty(n);
//   board one = empty;
//   one.place_next_queen_at_column(0);
//   board collide = one;
//   collide.place_next_queen_at_column(0);
//   REQUIRE( not collide.feasible() );
// }

// #if 0

// TEST_CASE( "final test" ) {
//   board five( {0,3,1,4,2} );
//   REQUIRE( five.feasible() );
//   REQUIRE( five.filled() );
// }

// TEST_CASE( "generate one and two" ) {
//   constexpr int n=10;
//   board empty(n);

//   // loop over all possibilities first queen
//   auto firstcol = GENERATE_COPY( range(1,n) );
//   board place_one = empty;
//   REQUIRE_NOTHROW( place_one.place_next_queen_at_column(firstcol) );
//   REQUIRE( place_one.feasible() );

//   // loop over all possbilities second queen
//   auto secondcol = GENERATE_COPY( range(1,n) );
//   board place_two = place_one;
//   REQUIRE_NOTHROW( place_two.place_next_queen_at_column(secondcol) );
//   if (secondcol<firstcol-1 or secondcol>firstcol+1) {
//     REQUIRE( place_two.feasible() );
//   } else {
//     REQUIRE( not place_two.feasible() );
//   }
// }

// TEST_CASE( "final step" ) {
//   // make board 4x4 with 3 rows filled
//   board almost( 4, {1,3,0} );
//   auto solution = almost.place_queens();
//   REQUIRE( solution.has_value() );
//   REQUIRE( solution->filled() );
// }

// TEST_CASE( "no 2x2 solutions" ) {
//   board two(2);
//   auto solution = two.place_queens();
//   REQUIRE( not solution.has_value() );
// }

// TEST_CASE( "no 3x3 solutions" ) {
//   board three(3);
//   auto solution = three.place_queens();
//   REQUIRE( not solution.has_value() );
// }

// TEST_CASE( "there are 4x4 solutions" ) {
//   board four(4);
//   auto solution = four.place_queens();
//   REQUIRE( solution.has_value() );
// }

// #endif
