
//#include "catch2/catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "myvalidateutf8.h"
//#include "main.cpp"
#include "fileops.cpp"
#include "menu.cpp"


TEST_CASE("Test1") {
    nlohmann::json correctfile;
    std::string filepath = "playlists/test11.json";
    correctfile = nlohmann::json::parse(std::ifstream(filepath));
    nlohmann::json userinput = "test11";
    nlohmann::json actualfile = myreadfile(1, userinput);
    REQUIRE(actualfile == correctfile);
}

TEST_CASE("Test2") {
    nlohmann::json correctfile;
    std::string filepath = "playlists/test15.json";
    correctfile = nlohmann::json::parse(std::ifstream(filepath));
    nlohmann::json userinput = "test15";
    nlohmann::json actualfile = myreadfile(1, userinput);
    REQUIRE(actualfile == correctfile);
}

TEST_CASE("Test3") {
    nlohmann::json correctfile;
    std::string filepath = "playlists/ttt2.json";
    correctfile = nlohmann::json::parse(std::ifstream(filepath));
    nlohmann::json userinput = "ttt2.json";
    nlohmann::json actualfile = myreadfile(1, userinput);
    REQUIRE(actualfile == correctfile);
}

TEST_CASE("Test4") {
    nlohmann::json correctfile;
    std::string filepath = "playlists/testtesttest.json";
    correctfile = nlohmann::json::parse(std::ifstream(filepath));
    nlohmann::json userinput = "testtesttest.json";
    nlohmann::json actualfile = myreadfile(1, userinput);
    REQUIRE(actualfile == correctfile);
}
