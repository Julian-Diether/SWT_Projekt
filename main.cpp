//Software Technik Projekt Gruppe1
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <cstdlib>
#include <string> //??!?
#include <string.h>
#include <cstring>
#include <iostream> //brauchen wir das alles? macht es das programm zu langsam/grosss?
#include <fstream>
#include "nlohmann/json.hpp"//nlohmann json bibliothek
//inkludieren anderer programmteile!!
#include "fileops.cpp"//
#include "menu.cpp"
//json bibiliothek
using json = nlohmann::json;
//cpp sachen??!
using namespace std;
//using std::cout;
//using std::cin;
//using std::endl;
//initialisierung eigener funktionen
//void myinitialize();
//void myopenfile();brauchenwirnicht

//deklarierung globaler variablen
std::string mypath = "playlists/"; //PFAD ZUM PLAYLIST ORDNER! immer aktuell halten! ggfs. spaeter in einstellungen aenderbar

//----------------------
//wichtig damit programm jederzeit beendet werden kann! IMMER HINZUFUEGEN WENN ETWAS EINGELESEN WIRD!!!
//  wenn char eingelesen wird:
// cin >> answer; if (strcasecmp(answer, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
//  wenn str eingelesen wird:
//  cin >> filename; const char* answer=filename.c_str(); if (strcasecmp(answer, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!



int main() {
    /*std::string answer{};
    std::string mynein = "nein";
    std::string myja = "ja";    brauchen wir das noch? eigentlich nicht*/

    //begruesssungsnachricht mit wichtigsten infos zur bedienung einfuegen?!
    welcome_msg(); //Greetings at the programm start
    //main_menu();
    myinitialize();//wenn ja wird datei initialisiert/wenn nein --> main_menu();

    //myinitialize();
    //ggfs variable anlegen um zu wissen ob initialisiert wurde oder nicht und dann anderen programmablauf durchfuehren??

    //------------------------------------
    //HIER KOMMT DAS HAUPTPROGRAMM!!
    //vllt eine while schleife, solange {answer!="beenden"} ist?
    //dann je nach befehl einzelne funktionen wie myopenfile() ansteuern
    //status angeben, ob gerade eine playlist initialisiert/geoeffnet ist

    return 0;
}


    /*    printf("************************\n");
    printf("Willkommen zum Musikplayer!\n");
    printf("Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ");
    scanf("%c", myinput);
    printf("%c", myinput); //testtest
    
    
    //if (answer == 'ja' || answer == 'Ja' || answer == 'JA') {
    
    //}if (answer == 'nein' || answer =='Nein' || answer == 'NEIN') {


    if(myinput=='ja') {
        
        printf("\nGeben sie den Namen der zu initialisierenden Playlist ein:\n"); // sprache zu kompliziert fuer den benutzer??

    } else {
        printf("\nfehler");
    } 
    else if(myinput=="Nein" || myinput=="nein" || myinput=="NEIN") {
        //bibliothek NICHT initialisieren
        //hier soll es normal mit dem musikplayer weitergehen

        printf("test - fall: nein");
    } else {
        //falsche eingabe (nicht "ja" oder "nein") --> wiederholen
        printf("hdahsfhdfsdo\n");
        printf("Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein):");
        scanf("%s", myinput);
    }


bool myinitialize(char *pointerFile) {
    FILE *initFile;
    //Bibiliothek initialisieren und status(erfolg/fehler) zurueckgeben!
    //Eingang: Pointer auf Datei??
    initFile = fopen(pointerFile, "r");

}*/

