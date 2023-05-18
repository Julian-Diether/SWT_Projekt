//Software Technik Projekt Gruppe1
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <string> //??!?
#include <string.h>
#include <iostream> //brauchen wir das alles? macht es das programm zu langsam/grosss?
#include <fstream>
#include "nlohmann/json.hpp"//nlohmann json bibliothek
//inkludieren anderer programmteile!!
#include "fileops.cpp"//
//json bibiliothek
using json = nlohmann::json;
//cpp sachen??!
using namespace std;
using std::cout;
using std::cin;
using std::endl;
//initialisierung eigener funktionen
void myinitialize();
void myopenfile();



int main() {
    /*std::string answer{};
    std::string mynein = "nein";
    std::string myja = "ja";    brauchen wir das noch? eigentlich nicht*/

    //begruesssungsnachricht mit wichtigsten infos zur bedienung einfuegen?!

    myinitialize();
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
    /*scanf("%c", myinput);
    printf("%c", myinput); //testtest
    
    
    //if (answer == 'ja' || answer == 'Ja' || answer == 'JA') {
    
    //}if (answer == 'nein' || answer =='Nein' || answer == 'NEIN') {


    if(myinput=='ja') {
        
        printf("\nGeben sie den Namen der zu initialisierenden Playlist ein:\n"); // sprache zu kompliziert fuer den benutzer??

    } else {
        printf("\nfehler");
    } 
    /*else if(myinput=="Nein" || myinput=="nein" || myinput=="NEIN") {
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

