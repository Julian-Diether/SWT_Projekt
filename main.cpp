//Software Technik Projekt Gruppe1
#include <stdio.h>

int main() {
    char myinput [15];
    printf("************************\n");
    printf("Willkommen zum Musikplayer!\n");
    printf("Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein):");
    scanf("%s", myinput);
    printf("%s", myinput); //testtest
    
    if(myinput=="Ja" || myinput=="ja" || myinput=="JA") {

    } else if(myinput=="Nein" || myinput=="nein" || myinput=="NEIN" {
        
    } else {
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
