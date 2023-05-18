//Software Technik Projekt Gruppe1
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <string> //??!?
#include <string.h>
#include <iostream> //brauchen wir das alles? macht es das programm zu langsam/grosss?
#include <fstream>
#include "nlohmann/json.hpp"//nlohmann json bibliothek
using json = nlohmann::json;
//cpp sachen??!
using namespace std;
using std::cout;
using std::cin;
using std::endl;
//initialisierung eigener funktionen
void myinitialize();
void myopenfile();
//deklarierung globaler variablen
const char* mynein = "nein";
const char* myja = "ja";


int main() {
    /*std::string answer{};
    std::string mynein = "nein";
    std::string myja = "ja";*/

    myinitialize();
    

    return 0;
}


void myinitialize() {
    char answer[20];
    bool repeat = true;
    
    while (repeat) {
        cout << "\nMoechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ";
        cin >> answer;
        //cout << answer << endl; //testtest
        
            if (strcasecmp(answer, myja) == 0) {//if (answer == "ja") {
            repeat = false;
            //bibliothek initialisieren
            myopenfile();
            //cout << "\nGeben sie den Namen der zu initialisierenden Playlist ein:\n" << endl; // sprache zu kompliziert fuer den benutzer??
            //cout << "answer=ja" << endl; //testtest
            
        } if (strcasecmp(answer, mynein) == 0) {
            repeat = false;   
            //bibliothek NICHT initialisieren
            //hier soll es normal mit dem musikplayer weitergehen

            cout << "answer=nein" << endl; //testtesttest
        } /*else {  //nichts es geht von selbst weiter  }*/
    }
}


void myopenfile() {
    cout << "\nGeben sie den Namen der zu oeffnenden Playlist ein:\n" << endl;
    std::ifstream file("testtesttest.json");
    //oeffnen derr .json datei^^
    if (!file.is_open()) {
        std::cerr << "Die .json Datei konnte nicht geoeffnet werden!" << std::endl;
    }

    nlohmann::json jsonContent;
    file >> jsonContent;
    //cout << "funktioniert das?";
    
    //jsonContent[0][]?
    //wie genau benenne ich die dateitypen?? mit namen oder dateitypen? muss ich das ganze in eine ober kategorie??
    //wie suche ich spaeter die einzelnen metadaten?? muss ich die werte fuer die liste 'sterilisieren' um probleme zu verhindern?

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

