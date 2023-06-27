
//#include "catch2/catch_amalgamated.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "myvalidateutf8.h"
//#include "main.cpp"
#include "fileops.cpp"
#include "menu.cpp"


TEST_CASE("ValidInput") {
    nlohmann::json jsonfile;
    std::string jsonpath = "playlists/test11.json";
    jsonfile = nlohmann::json::parse(std::ifstream(jsonpath));
    bool correctoutput = true;
    bool actualoutput = myvalidatesyntax(jsonfile);
    REQUIRE(actualoutput == correctoutput);
}   

TEST_CASE("ValidInput2") {
    nlohmann::json jsonfile;
    std::string jsonpath = "playlists/testtesttest.json";
    jsonfile = nlohmann::json::parse(std::ifstream(jsonpath));
    bool correctoutput = true;
    bool actualoutput = myvalidatesyntax(jsonfile);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput") {
    nlohmann::json jsonfile;
    std::string jsonpath = "playlists/test35.json";
    jsonfile = nlohmann::json::parse(std::ifstream(jsonpath));
    bool correctoutput = false;
    bool actualoutput = myvalidatesyntax(jsonfile);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput2") {
    nlohmann::json jsonfile;
    std::string jsonpath = "playlists/test36.json";
    jsonfile = nlohmann::json::parse(std::ifstream(jsonpath));
    bool correctoutput = false;
    bool actualoutput = myvalidatesyntax(jsonfile);
    REQUIRE(actualoutput == correctoutput);
}

TEST_CASE("InvalidInput3") {
    nlohmann::json jsonfile;
    std::string jsonpath = "playlists/test32.json";
    jsonfile = nlohmann::json::parse(std::ifstream(jsonpath));
    bool correctoutput = false;
    bool actualoutput = myvalidatesyntax(jsonfile);
    REQUIRE(actualoutput == correctoutput);
}

