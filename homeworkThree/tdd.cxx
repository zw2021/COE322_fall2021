/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-2021 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** tdd.cxx : example of catch2 main
 ****
 ****************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

double f(int n) { return (.9)/((n*n)+1); }

#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"

TEST_CASE( "test that f always returns positive" ) {

  for (int n=0; n<1000; n++){
  // REQUIRE( f(n) < 1000) 
   INFO("function fails for " << n);
   REQUIRE( f(n)> 0. );  
}
}
