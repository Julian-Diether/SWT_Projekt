//Software Technik Projekt Gruppe1
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int main() {
    char answer;
    bool repeat = true;
    /*
    printf("************************\n");
    printf("Willkommen zum Musikplayer!\n");
    printf("Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ");*/
    /*scanf("%c", myinput);
    printf("%c", myinput); //testtest
    */




    while (repeat) {
        cout << "\nMoechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ";
        cin >> answer;

        if (answer == 'ja' || answer == 'Ja' || answer == 'JA') {
            repeat = false;
            cout << "\nGeben sie den Namen der zu initialisierenden Playlist ein:\n" << endl; // sprache zu kompliziert fuer den benutzer??
            //hier kommt der musikplayer
            cout << "answer=ja" << endl;
            
        }
        }if (answer == 'nein' || answer =='Nein' || answer == 'NEIN') {
            repeat = false;   
            cout << "answer=nein" << endl;
        } /*else {
            //nichts es geht von selbst weiter
        }*/

    /*
    if(myinput=='ja') {
        //bibliothek initialisieren
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
    }*/

    return 0;
}


/*/
bool myinitialize(char *pointerFile) {
    FILE *initFile;
    //Bibiliothek initialisieren und status(erfolg/fehler) zurueckgeben!
    //Eingang: Pointer auf Datei??
    initFile = fopen(pointerFile, "r");

}*/
