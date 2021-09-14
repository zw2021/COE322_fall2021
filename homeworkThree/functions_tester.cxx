#include "functions.h"
#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"
TEST_CASE( "test the increment function" ) {
/* ... */
  for (int i = -100; i<+100; i++){
   INFO("testing input: " << i); //STRUCTURED LIKE A COUT STATEMENT
    if (i>=0)
	 REQUIRE( increment_positive_only( i ) == i+1 );
    else
	REQUIRE_THROWS(increment_positive_only(i) == i+1); 
}

}

