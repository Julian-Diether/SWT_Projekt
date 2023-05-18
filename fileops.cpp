//brauchen wir hier wohl auch:
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <string> //??!?
#include <string.h>
#include <iostream> //brauchen wir das alles? macht es das programm zu langsam/grosss?
#include <fstream>
#include "nlohmann/json.hpp"//nlohmann json bibliothek
//inkludieren anderer programmteile!!
//json bibiliothek
using json = nlohmann::json;
//cpp sachen??!
using namespace std;
using std::cout;
using std::cin;
using std::endl;

//deklarierung globaler variablen
/*const char* mynein = "nein";
const char* myja = "ja"; brauchen wir zum glueck doch nicht*/

void myinitialize();
void myopenfile();


void myinitialize() {
    char answer[20];
    bool repeat = true;
    
    while (repeat) {
        // else if fuer nein und else danach mit "befehl nicht verstanden, playlist initialisieren (ja/nein)" einfuegen???
        cout << "Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ";
        cin >> answer;
        //cout << answer << endl; //testtest
        
            if (strcasecmp(answer, "ja") == 0) {//if (answer == "ja") {
            repeat = false;
            //bibliothek initialisieren
            myopenfile();
            //cout << "\nGeben sie den Namen der zu initialisierenden Playlist ein:\n" << endl; // sprache zu kompliziert fuer den benutzer??
            //cout << "answer=ja" << endl; //testtest
            
        } if (strcasecmp(answer, "nein") == 0) {
            repeat = false;   
            //bibliothek NICHT initialisieren
            //hier soll es normal mit dem musikplayer weitergehen

            cout << "answer=nein" << endl; //testtesttest
        } /*else {  //nichts es geht von selbst weiter  }*/
    }
}


void myopenfile() {
    bool repeat = true;
    std::string filename = "";
    std::string filename2 = "";
    //const char* myjson = ".json";//gibt es keinen besseren weg?

    //while schleife, bis die datei gueltig geoeffnet wurde
    while (repeat) {
        cout << "Geben sie den Namen der zu oeffnenden Playlist ein:"; // spezifizieren, dass nur name der playlist und nicht .json eingegeben werden soll???
        cin >> filename;

        if (filename.find(".json") != std::string::npos) {

            cout << "test1 test1";
            //hier passiert alles?!

        } else {
            std::swap(filename, filename2);//filename2 = filename
            std::string filename = filename2 + ".json";// an dateiname wird dateiendung angefuegt
            cout << filename;//test
        }

        cout << filename << endl;//test
        //stand jetzt haben wir einen vielleicht gueltigen dateiname. datei wird nun geoeffnet
        try {
            std::ifstream file(filename);
            //oeffnen der .json datei^^ (in einem sicheren umfeld --> kein absturz)
            if (!file.is_open()) {
                std::cerr << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte??
            
            repeat = false; //erst nachden file.is_open = true ist. danach bei fehler wieder geaendert
            nlohmann::json jsonContent;
            file >> jsonContent;
            //cout << "funktioniert das?";

            //hier ueberpruefen ob die datei leer ist oder inkorrekt geoeffnet wurde!! absturz des programmes verhindern und den nutzer erneut versuchen lassen

            //jsonContent[0][]?
            //wie genau benenne ich die dateitypen?? mit namen oder dateitypen? muss ich das ganze in eine ober kategorie??
            //wie suche ich spaeter die einzelnen metadaten?? muss ich die werte fuer die liste 'sterilisieren' um probleme zu verhindern?

        //falls ein fehler auftritt gibt wird hier die meldung abgegeben
        } catch (const std::exception& e) {
            repeat = true;
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen:" << e.what() << std::endl;
            //hier gab es einen fehler beim einlesen? der datei. "wenden sie sich mit folgender fehlermeldung an den support"
        }
    }


    //wo speichere ich die dateien solange die playlist offen ist? habe ich die datei dauerhaft offen?
    //^^eigentlich brauche ich das ja nur beim erstellen/editieren oder loeschen
    //ist es schlecht, die datei offen zu lassen??  was wenn das programm abstuerzt? kann ich die datei davor noch schliesssen??
}

