//Software Technik Projekt Gruppe1
#include <stdio.h>
#include <string> //??!?
#include <string.h>
#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

int main() {
    char answer[20];
    //std::string answer{};
    bool repeat = true;
    const char* mynein = "nein";
    const char* myja = "ja";
    //std::string mynein = "nein";
    //std::string myja = "ja";


    while (repeat) {
        cout << "\nMoechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ";
        cin >> answer;
        //cout << answer << endl; //testtest
        
            if (strcasecmp(answer, myja) == 0) {//if (answer == "ja") {
            repeat = false;
            //bibliothek initialisieren
            cout << "\nGeben sie den Namen der zu initialisierenden Playlist ein:\n" << endl; // sprache zu kompliziert fuer den benutzer??
            
            cout << "answer=ja" << endl; //testtest
            
        } if (strcasecmp(answer, mynein) == 0) {
            repeat = false;   
            //bibliothek NICHT initialisieren
            //hier soll es normal mit dem musikplayer weitergehen

            cout << "answer=nein" << endl; //testtesttest
        } /*else {  //nichts es geht von selbst weiter  }*/
    }
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
