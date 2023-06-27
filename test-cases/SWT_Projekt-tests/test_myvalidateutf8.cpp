
//#include "catch2/catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "myvalidateutf8.h"
//#include "main.cpp"
#include "fileops.cpp"
#include "menu.cpp"


TEST_CASE("ValidInput") {
    std::string userinput = "2020, Ja, Nein, 1.2,3-4_5, Test!, t e s t b a n d, Songname";
    std::string correctoutput = "2020, Ja, Nein, 1.2,3-4_5, Test!, t e s t b a n d, Songname";
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("ValidInput2") {
    std::string userinput  = "album: testsongs_2030, artist: der_tester_und_band, date: 2030, explicit: true, genre: testsongs, length: 25_19, title: testsong_3";
    std::string correctoutput = "album: testsongs_2030, artist: der_tester_und_band, date: 2030, explicit: true, genre: testsongs, length: 25_19, title: testsong_3";
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput") {
    std::string userinput = "Test\xF0\x90song\x80\x80Song";//ungueltige/nicht utf-8 konforme zeichen
    std::string correctoutput = "Test┬┤ÔöÉ┬ósong┬┤ÔöÉ┬ó┬┤ÔöÉ┬óSong";
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput2") {
    std::string userinput = "Kuenstler [1], Album {feat. Ed Sheeran}";
    std::string correctoutput = "Kuenstler ?1?, Album ?feat. Ed Sheeran?";
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput3") {
    std::string userinput = "Genre:;$% *+~ - ??{[]}?";
    std::string correctoutput = "Genre:;$% *+~ - ???????";
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}
