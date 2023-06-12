//Software Technik Projekt Gruppe1 -- Julian Diether, Lionel Felipe, Noah Traub, Frederik Kempke
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>

//eigene variablen
int counter=0;
std::string mybeenden = "beenden";
std::string tempstringx;

//eigene funktionen
void welcome_msg();
void main_menu();
void song_management();
void playlist_management();
int input_validation(int option_num, int whichmenu);

//fremde funktionen (fileops.cpp)
void myopenfile(bool justprint);
void myprintfile(bool justprint2);
void mycreatefile();
void mydeletefile();
void mysearchfile();
void myrenamefile();
void mylistfiles();
void myeditfile(int select);
void myexit(std::string inputstring);

void welcome_msg()
{
    std::cout << "******************************************************************" << std::endl;
    std::cout << "\t\t Willkommen zum Musikplayer!" << std::endl;
    std::cout << "\t    - zum schliessen >beenden< eingeben -" << std::endl;
    std::cout << "******************************************************************" << std::endl;
}

void main_menu()
{
    std::cout << "\n***********************  Hauptmenue  **************************" << std::endl;
    std::cout << "Aktuelle Playlist anzeigen   -   1" << std::endl;
    std::cout << "Gespeicherte Playlist oeffnen - 2" << std::endl;
    std::cout << "Einzelne Playlists verwalten  -  3" << std::endl;
    std::cout << "Titel einer Playlist verwalten - 4" << std::endl;
    std::cout << "Eine playlist durchsuchen   -   5" << std::endl;
    std::cout << "Den Musikplayer jetzt beenden  -  6" << std::endl;
    int selection {0}; //User input
    int option_num {6}; //Number of options in the displayed menu
    selection = input_validation(option_num, 1);

    switch(selection)
    {
        case 1:
            myprintfile(false);
        break;
        case 2:
            myopenfile(false);
        break;
        case 3:
            playlist_management();
        break;
        case 4:
            song_management();
        break;
        case 5:
            mysearchfile();
        break;
        case 6:
            myexit(mybeenden);//nicht sehr elegant, egal
        break;
        default:
        main_menu();//sollte nie passieren!!
        break;
    }
}

void song_management()
{
    std::cout << "\n*********************\tSong Editor\t***********************" << std::endl;
    std::cout << "Song hinzufuegen  -  1" << std::endl;
    std::cout << "Song bearbeiten  -  2" << std::endl;
    std::cout << "Song loeschen   -   3" << std::endl;
    std::cout << "Zurueck zum menue  -  4" << std::endl;
    std::cout << "Musikplayer beenden  - 5" << std::endl;
    int selection {0}; //User input
    int option_num {5}; //Number of options in the displayed menu
    selection = input_validation(option_num, 2); 

    switch(selection)
    {
        case 1:
            myeditfile(1);
        break;
        case 2:
            myeditfile(2);
        break;
        case 3:
            myeditfile(3);
        break;
        case 4:
            main_menu();
        break;
        case 5:
            myexit(mybeenden);
        break;
        default:
            song_management();//sollte nie passieren
        break;
    }
}

void playlist_management()
{
    std::cout << "\n********************\tPlaylist Editor\t**********************" << std::endl;
    std::cout << "Neue Playlist erstellen - 1" << std::endl;
    std::cout << "Eine Playlist umbenennen - 2" << std::endl;
    std::cout << "Eine Playlist loeschen  -  3" << std::endl;
    std::cout << "Alle Playlists anzeigen - 4" << std::endl;
    std::cout << "Zurueck zum menue    -   5" << std::endl;
    std::cout << "Musikplayer beenden   -   6" << std::endl;
    int selection {0}; //User input
    int option_num {6}; //Number of options in the displayed menu
    selection = input_validation(option_num, 3);

    switch(selection)
    {
        case 1:
            mycreatefile();
        break;
        case 2:
            myrenamefile();
        break;
        case 3:
            mydeletefile();;
        break;
        case 4:
            mylistfiles();
        break;
        case 5:
            main_menu();
        break;
        case 6:
            myexit(mybeenden);
        break;
        default:
            song_management();//sollte nie passieren!
        break;
    }
}

int input_validation(int option_num, int whichmenu)
{
    bool inputerror=false;
    int selection{0};
    do
    {
        std::cout << "   --entsprechende Zahl--: ";
        std::getline(std::cin, tempstringx);

        try {
            selection = std::stoi(tempstringx);//integer eingegeben
            inputerror=false;
        }
        catch(const std::invalid_argument&) {//falls keine zahl eingegeben wurde
            inputerror=true;
            std::cin.clear();//die fehler flags werden geloescht!
            std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;

        }

        if (selection <= 0 || selection > option_num || inputerror)
        {
            std::cout << "\tGeben sie eine gueltige Zahl ein!" << std::endl;
            
            counter++;
            if(counter>2) {//nach 4 fehlern mainmenu bzw. song-/playlistmanagement erneut anzeigen
                counter=0;
                mydashedline();
                switch(whichmenu) {
                    case 1:
                        main_menu();
                    break;
                    case 2:
                        song_management();
                    break;
                    case 3:
                        playlist_management();
                    break;
                    default:
                        main_menu();
                    break;
                }
            }
        }
    }
    while (selection <= 0 || selection > option_num || inputerror);
    {
        return selection;
    }
}

