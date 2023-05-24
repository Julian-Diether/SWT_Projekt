
//inkludieren saemtlicher bibliotheken
#include <cstdlib>//warum auch immer benoetigt um programm zu beenden
#include <string> //string.h und stdio.h fehlen hier! scheint kein problem zu sein?!
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
//using std::cout; //('using namespace std;' fehlt auch)
//using std::cin;
//using std::endl;
using json = nlohmann::json;

//globale variablen
int counter=0; // wird benutzt um nach 10 fehleingaben das hauptmenue erneut anzuzeigen. verbessert sichtbarkeit (siehe input_validation)

//initialisierung eigener funktionen
void welcome_msg();
void run_last_library();
//void load_library();
void add_library();
void create_library();
void song_management();
//void turn_off();
void add_song();
void modify_song();
void search_song();
void delete_song();
//void return_main();
void main_menu();
int input_validation(int option_num, bool bmainmenu);

//initialisierung fremder funktionen (fileops.cpp)
//void myinitialize();//brauchen wir nicht da in main initialisiert wird!
void myopenfile(bool justprint2);
void myprintfile(bool justprint);
void mycreatefile();
void mydeletefile();
void mysearchfile();
void myeditfile(int select);


void myexit(char myinput[50]);//vsc hat sich beschwert (gelbe kringel linien), dass die definition zu mycheckifopen fehle, beeintraechtigt programm aber nicht
void mywaitenter();
void mycheckifopen(char myinput2[50]);//vsc hat sich beschwert (gelbe kringel linien), dass die definition zu mycheckifopen fehle, beeintraechtigt programm aber nicht
void mydashedline();


//Main menu functions
void welcome_msg()
{
    std::cout << "******************************************************************" << std::endl;
    std::cout << "\t\t Willkommen zum Musikplayer!" << std::endl;
    std::cout << "\t    - zum schliessen >beenden< eingeben -" << std::endl;
    std::cout << "******************************************************************" << std::endl;
}
void run_last_library()
{
    std::cout << "Run last lib selected" << std::endl;
    main_menu();
}
/*void load_library()
{
    cout << "Load lib selected" << endl;
    main_menu();
}*/
void add_library()
{
    std::cout << "Add lib selected" << std::endl;
    main_menu();
}
void create_library()
{
    std::cout << "Create lib selected" << std::endl;
    main_menu();
}
/*void turn_off()
{
    cout << "Good Bye" << endl;
}*/
//Song functions
void add_song()
{
    std::cout << "Add song selected" << std::endl;
    song_management();
}
void modify_song()
{
    std::cout << "Mod song" << std::endl;
    song_management();
}
void search_song()
{
    std::cout << "Search song selected" << std::endl;
    song_management();
}
void delete_song()
{
    std::cout << "Delete song selected" << std::endl;
    song_management();
}
//void return_main()//redundant
//{
//    main_menu();
//}

//Options functions
void main_menu()
{
    /*cout << "\n***********************\tMain menu\t**************************" << endl;
    cout << "Load the last library to the playlist - 1" << endl;
    cout << "Load a new library to the playlist - 2" << endl;
    cout << "Add a library to the actual playlist - 3" << endl;
    cout << "Create a new library - 4" << endl;
    cout << "Manage songs - 5" << endl;
    cout << "Shut down app - 6" << endl;
    cout << "Enter an option number: ";
    cout << "\n***********************\tHauptmenue\t**************************" << endl;*/
    std::cout << "\n***********************  Hauptmenue  **************************" << std::endl;
    std::cout << "Aktuelle Playlist anzeigen  -  1" << std::endl;
    std::cout << "Gespeicherte Playlist oeffnen - 2" << std::endl;
    std::cout << "Eine neue Playlist erstellen  -  3" << std::endl;
    std::cout << "Gespeicherte Playlist loeschen - 4" << std::endl;
    std::cout << "Titel der Playlist verwalten  -  5" << std::endl;
    std::cout << "Gespeicherte playlist durchsuchen - 6" << std::endl;
    std::cout << "Den Musikplayer jetzt beenden  -  7" << std::endl;
    //cout << "--Geben sie die entsprechende Zahl ein: "; 
    int selection {0}; //User input
    int option_num {7}; //Number of options in the displayed menu
    selection = input_validation(option_num, true);
    //cout << selection << endl;//test

    switch(selection)
    {
        case 1:
            //run_last_library();
            myprintfile(false);
        break;
        case 2:
            //load_library();
            myopenfile(false);
        break;
        case 3:
            //add_library();
            mycreatefile();
        break;
        case 4:
            //                      playlist loeschen
            mydeletefile();
        break;
        case 5:
            //create_library();     titel verwalten
            song_management();

        break;
        case 6:
            //song_management();      playlist durchsuchen
            mysearchfile();
        break;
        case 7:
            //turn_off();
            exit(0);
        break;
        default:
        break;
    }
}
void song_management()
{
    std::cout << "\n*********************\tSong Editor\t***********************" << std::endl;
    std::cout << "Neuen Song hinzufuegen - 1" << std::endl;
    std::cout << "Song bearbeiten - 2" << std::endl;
    //std::cout << "Search a song - 3" << std::endl;//machen wir ueber das suchmenue (Nummer 6)
    std::cout << "Song loeschen - 3" << std::endl;
    std::cout << "Zurueck zum menue - 4" << std::endl;
    std::cout << "Musikplayer beenden - 5" << std::endl;
    //cout << "Enter an option number:";
    int selection {0}; //User input
    int option_num {5}; //Number of options in the displayed menu
    selection = input_validation(option_num, false); 

    switch(selection)
    {
        case 1:
            //add_song();
            myeditfile(1);
        break;
        case 2:
            //modify_song();
            myeditfile(2);
        break;
        case 3:
            //search_song();
            myeditfile(3);
        break;
        case 4:
            //delete_song();
            main_menu();
        break;
        case 5:
            //return_main();
            exit(0);
        break;
        default:
        break;//koennten wir die fehler nicht hier haendeln?
    }
}
//Extra functions
int input_validation(int option_num, bool bmainmenu)    //wenn input != int (buchstabe eingegeben) entstegt eine unendlich-schleife!!
{
    bool inputerror=false;
    bool repeat=true;
    int selection{0};
    do
    {
        repeat=true;
        while(repeat) {
            std::cout << "--Geben sie die entsprechende Zahl ein: "; 
            std::cin >> selection;
            if(std::cin.fail()) {//oder if(cin>>selection)???
                //cout << "FEHLERFEHLERFEHLERFEHLERFEHLER---------------" << endl;
                inputerror=true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\tBuchstaben sind nicht zulaessig!" << std::endl;
                //std::cout << "Geben sie eine gueltige Zahl ein: ";//user soll erneut eingeben, weil buchstabe eingegeben wurde
                repeat=false;
            } else {repeat=false;}
        }
        //cout << "testtesttest";
        if (selection <= 0 || selection > option_num || inputerror)
        {
            std::cout << "\tGeben sie eine gueltige Zahl ein!" << std::endl;;//user soll erneut eingegeben, weil ungueltige zahl eingegeben wurde
            
            counter++;
            if(counter>3) {//nach 4 fehlerhaften eingaben wird mainmenu bzw. songmanagement erneut angezeigt. fuer bessere lesbarkeit!
                counter=0;
                if(bmainmenu) {
                    main_menu();
                } else {
                    song_management();
                }
            }
        }
    }
    while (selection <= 0 || selection > option_num || inputerror);
    {
        return selection;
    }
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


