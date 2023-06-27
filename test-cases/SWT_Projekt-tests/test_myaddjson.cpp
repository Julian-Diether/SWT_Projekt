
//#include "catch2/catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "myvalidateutf8.h"
//#include "main.cpp"
#include "fileops.cpp"
#include "menu.cpp"


TEST_CASE("Name1") {
    std::string userinput = "test11";
    std::string correctoutput = "test11.json";
    std::string actualoutput = myaddjson(userinput, false);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("Name2") {
    std::string userinput = "testtesttest";
    std::string correctoutput = "testtesttest.json";
    std::string actualoutput = myaddjson(userinput, false);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("Name3") {
    std::string userinput = "ttt2";
    std::string correctoutput = "playlists/ttt2.json";
    std::string actualoutput = myaddjson(userinput, true);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("Name_w_path") {
    std::string userinput = "playlists/test35";
    std::string correctoutput = "playlists/test35.json";
    std::string actualoutput = myaddjson(userinput, true);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("Name_with_ending") {
    std::string userinput = "test36.json";
    std::string correctoutput = "playlists/test36.json";
    std::string actualoutput = myaddjson(userinput, true);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("Name_with_both") {
    std::string userinput = "playlists/test32.json";
    std::string correctoutput = "playlists/test32.json";
    std::string actualoutput = myaddjson(userinput, true);
    REQUIRE(actualoutput == correctoutput);
}
