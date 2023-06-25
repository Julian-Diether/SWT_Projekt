
//#include "catch2/catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "myvalidateutf8.h"
#include <fstream>
//#include "main.cpp"
#include "fileops.cpp"
#include "menu.cpp"


TEST_CASE("Input_validation testing") // input_validation(option_num,whichmenu)
{
    SECTION("Main menu Testing") // 6 Optionen - Menu 1
    {
        REQUIRE(input_validation(6,1) == 1);
        REQUIRE(input_validation(6,1) == 2);
        REQUIRE(input_validation(6,1) == 3);
        REQUIRE(input_validation(6,1) == 4);
        REQUIRE(input_validation(6,1) == 5);
        REQUIRE(input_validation(6,1) == 6);    
    }
    
    SECTION("Song Managment menu Testing") // 6 Optionen - Menu 1
    {
        REQUIRE(input_validation(6,2) == 1);
        REQUIRE(input_validation(6,2) == 2);
        REQUIRE(input_validation(6,2) == 3);
        REQUIRE(input_validation(6,2) == 4);
        REQUIRE(input_validation(6,2) == 5);
        REQUIRE(input_validation(6,2) == 6);
    }
    SECTION("Playlist Managment menu Testing") // 7 Optionen - Menu 1
    {
        REQUIRE(input_validation(7,3) == 1);
        REQUIRE(input_validation(7,3) == 2);
        REQUIRE(input_validation(7,3) == 3);
        REQUIRE(input_validation(7,3) == 4);
        REQUIRE(input_validation(7,3) == 5);
        REQUIRE(input_validation(7,3) == 6);
        REQUIRE(input_validation(7,3) == 7);
    }
}
