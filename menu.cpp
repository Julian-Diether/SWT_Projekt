//Software Technik Projekt Gruppe1 -- Julian Diether, Lionel Felipe, Noah Traub, Frederik Kempke
#include <string>

//eigene variablen
int counter=0;
char mybeenden[50] = "beenden";

//eigene funktionen
void welcome_msg();
void main_menu();
int input_validation(int option_num, bool bmainmenu);

//fremde funktionen (fileops.cpp)
void myopenfile(bool justprint);
void myprintfile(bool justprint2);
void mycreatefile();
void mydeletefile();
void mysearchfile();
void myeditfile(int select);

void myexit(char myinput[50]);
void mywaitenter();
void mycheckifopen(char myinput2[50]);
void mydashedline();


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
    std::cout << "Aktuelle Playlist anzeigen  -  1" << std::endl;
    std::cout << "Gespeicherte Playlist oeffnen - 2" << std::endl;
    std::cout << "Eine neue Playlist erstellen  -  3" << std::endl;
    std::cout << "Gespeicherte Playlist loeschen - 4" << std::endl;
    std::cout << "Titel der Playlist verwalten  -  5" << std::endl;
    std::cout << "Gespeicherte playlist durchsuchen - 6" << std::endl;
    std::cout << "Den Musikplayer jetzt beenden  -  7" << std::endl;
    int selection {0}; //User input
    int option_num {7}; //Number of options in the displayed menu
    selection = input_validation(option_num, true);

    switch(selection)
    {
        case 1:
            myprintfile(false);
        break;
        case 2:
            myopenfile(false);
        break;
        case 3:
            mycreatefile();
        break;
        case 4:
            mydeletefile();
        break;
        case 5:
            song_management();

        break;
        case 6:
            mysearchfile();
        break;
        case 7:
            myexit("beenden");//nicht sehr elegant, egal
        break;
        default:
        main_menu();//sollte nie passieren
        break;
    }
}

void song_management()
{
    std::cout << "\n*********************\tSong Editor\t***********************" << std::endl;
    std::cout << "Neuen Song hinzufuegen - 1" << std::endl;
    std::cout << "Song bearbeiten - 2" << std::endl;
    std::cout << "Song loeschen - 3" << std::endl;
    std::cout << "Zurueck zum menue - 4" << std::endl;
    std::cout << "Musikplayer beenden - 5" << std::endl;
    int selection {0}; //User input
    int option_num {5}; //Number of options in the displayed menu
    selection = input_validation(option_num, false); 

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
            myexit("beenden");
        break;
        default:
            song_management();//sollte nie passieren
        break;
    }
}

int input_validation(int option_num, bool bmainmenu)
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
                inputerror=true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\tBuchstaben sind nicht zulaessig!" << std::endl;
                repeat=false;
            } else {repeat=false; inputerror=false;}//gueltiger input
        }

        if (selection <= 0 || selection > option_num || inputerror)
        {
            std::cout << "\tGeben sie eine gueltige Zahl ein!" << std::endl;
            
            counter++;
            if(counter>3) {//nach 4 fehlern mainmenu bzw. songmanagement erneut anzeigen
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

