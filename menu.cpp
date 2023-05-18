
//inkludieren saemtlicher bibliotheken
#include <string> //string.h und stdio.h fehlen hier! scheint kein problem zu sein?!
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
using std::cout; //('using namespace std;' fehlt auch)
using std::cin;
using std::endl;
using json = nlohmann::json;

//initialisierung eigener funktionen
void welcome_msg();
void run_last_library();
void load_library();
void add_library();
void create_library();
void song_management();
void turn_off();
void add_song();
void modify_song();
void search_song();
void delete_song();
void return_main();
void main_menu();
int input_validation(int option_num);
//void myinitialize();
//void myopenfile();

//Main menu functions
void welcome_msg()
{
    cout << "******************************************************************" << endl;
    cout << "\t\tWillkommen zum Musikplayer!" << endl;
    cout << "******************************************************************" << endl;
}
void run_last_library()
{
    cout << "Run last lib selected" << endl;
    main_menu();
}
void load_library()
{
    cout << "Load lib selected" << endl;
    main_menu();
}
void add_library()
{
    cout << "Add lib selected" << endl;
    main_menu();
}
void create_library()
{
    cout << "Create lib selected" << endl;
    main_menu();
}
void turn_off()
{
    cout << "Good Bye" << endl;
}
//Song functions
void add_song()
{
    cout << "Add song selected" << endl;
    song_management();
}
void modify_song()
{
    cout << "Mod song" << endl;
    song_management();
}
void search_song()
{
    cout << "Search song selected" << endl;
    song_management();
}
void delete_song()
{
    cout << "Delete song selected" << endl;
    song_management();
}
void return_main()
{
    main_menu();
}

//Options functions
void main_menu()
{
    cout << "\n***********************\tMain menu\t**************************" << endl;
    cout << "Load the last library to the playlist - 1" << endl;
    cout << "Load a new library to the playlist - 2" << endl;
    cout << "Add a library to the actual playlist - 3" << endl;
    cout << "Create a new library - 4" << endl;
    cout << "Manage songs - 5" << endl;
    cout << "Shut down app - 6" << endl;
    cout << "Enter an option number: "; 
    int selection {0}; //User input
    int option_num {6}; //Number of options in the displayed menu
    selection = input_validation(option_num); 

    switch(selection)
    {
        case 1:
            run_last_library();
        break;
        case 2:
            load_library();
        break;
        case 3:
            add_library();
        break;
        case 4:
            create_library();
        break;
        case 5:
            song_management();
        break;
        case 6:
            turn_off();
        break;
        default:
        break;
    }
}
void song_management()
{
    cout << "\n*********************\tSong Manager\t***********************" << endl;
    cout << "Add new song - 1" << endl;
    cout << "Modify a song - 2" << endl;
    cout << "Search a song - 3" << endl;
    cout << "Delete a song - 4" << endl;
    cout << "Return to main menu - 5" << endl;
    cout << "Enter an option number:";
    int selection {0}; //User input
    int option_num {5}; //Number of options in the displayed menu
    selection = input_validation(option_num); 

    switch(selection)
    {
        case 1:
            add_song();
        break;
        case 2:
            modify_song();
        break;
        case 3:
            search_song();
        break;
        case 4:
            delete_song();
        break;
        case 5:
            return_main();
        break;
        default:
        break;
    }
}
//Extra functions
int input_validation(int option_num)
{
    int selection{0};
    do
    {
        cin >> selection;
        if (selection <= 0 || selection > option_num)
            cout << "Enter a valid option: ";
    }
    while (selection <= 0 || selection > option_num);
    return selection;
}

/*
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
        } //else {  //nichts es geht von selbst weiter  }
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

const char* mynein = "nein";
const char* myja = "ja";

int main() 
{
    char answer[20];
    //std::string answer{};
    bool repeat = true;
    const char* mynein = "nein";
    const char* myja = "ja";
    //std::string mynein = "nein";
    //std::string myja = "ja";

    welcome_msg(); //Greetings at the programm start
    main_menu();
    
    /*
    myinitialize();

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
    //    } else {  //nichts es geht von selbst weiter  }
    //}
    //

    return 0;
}



        printf("************************\n");
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

