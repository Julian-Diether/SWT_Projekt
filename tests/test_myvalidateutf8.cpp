
#include "catch2/catch_amalgamated.hpp"
#include <string>
#include <algorithm>
#include "../main.cpp"
#include "../fileops.cpp"
//#include "../menu.cpp"


TEST_CASE("ValidInput", "[myvalidateutf8]") {
    std::string userinput = "2020, Ja, Nein, 1.2,3-4_5, Test!, t e s t b a n d, Songname";
    std::string correctoutput = "2020, Ja, Nein, 1.2,3-4_5, Test!, t e s t b a n d, Songname";
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput", "[myvalidateutf8]") {
    std::string userinput = "Test\xF0\x90song\x80\x80Song";//ungueltige/nicht utf-8 konforme zeichen
    std::string correctoutput = "Test??song??song"; //???? ?? ? ?  ---  hier mir den sonderzeichen
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput2", "[myvalidateutf8]") {
    std::string userinput = "Kuenstler [1], Album {feat. Ed Sheeran}";
    std::string correctoutput = "Kuenstler ?1? a ?Ed Sheeran?";
    std::string actualoutput = myvalidateutf8(userinput);
    REQUIRE(actualoutput == correctoutput);
}


