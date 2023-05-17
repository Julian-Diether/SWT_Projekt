//Software Technik Projekt Gruppe1
#include <stdio.h>

int main() {
    char myinput [15];
    printf("************************\n");
    printf("Willkommen zum Musikplayer!\n");
    printf("Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ");
    scanf("%s", myinput);
    printf("%s", myinput); //testtest
    printf("\n");
    
    if(myinput=="Ja" || myinput=="ja" || myinput=="JA") {
        //bibliothek initialisieren
        printf("Geben sie den Namen der zu initialisierenden Playlist ein:\n"); // sprache zu kompliziert fuer den benutzer??

    } else if(myinput=="Nein" || myinput=="nein" || myinput=="NEIN") {
        //bibliothek NICHT initialisieren
        //hier soll es normal mit dem musikplayer weitergehen

        printf("test - fall: nein");
    } else {
        //falsche eingabe (nicht 'ja' oder 'nein') --> wiederholen
        printf("Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein):");
        scanf("%s", myinput);
    }



    return 0;
}

bool myinitialize(char *pointerFile) {
    FILE *initFile;
    //Bibiliothek initialisieren und status(erfolg/fehler) zurueckgeben!
    //Eingang: Pointer auf Datei??
    initFile = fopen(pointerFile, "r");

}
