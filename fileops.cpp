//brauchen wir hier wohl auch:
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <cstdlib>
#include <string> //??!?
#include <string.h>
#include <iostream> //brauchen wir das alles? macht es das programm zu langsam/grosss?
#include <fstream>//benutzen wir um dateien zu lesen/schreiben
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
extern std::string mypath;
std::string filename = "";
nlohmann::json currentplaylist;
/*const char* mynein = "nein";
const char* myja = "ja"; brauchen wir zum glueck doch nicht*/

//deklarierung GLOBALER funktionen
void main_menu();
//void turn_off();  // turn_off(); anstatt exit(0); funktioniert in komplexen schleifen nicht, exit(0); scheint einfacher

void myinitialize();
void myopenfile();
void myprintfile();
void mycreatefile();



void myinitialize() {
    char answer[50];
    bool repeat = true;
    
    while (repeat) {
        // else if fuer nein und else danach mit "befehl nicht verstanden, playlist initialisieren (ja/nein)" einfuegen???
        cout << "Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ";
        cin >> answer; if (strcasecmp(answer, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
        //cout << answer << endl; //testtest
        
        if (strcasecmp(answer, "ja") == 0) {//if (answer == "ja") {
            repeat = false;
            //bibliothek initialisieren
            myopenfile();
            //cout << "\nGeben sie den Namen der zu initialisierenden Playlist ein:\n" << endl; // sprache zu kompliziert fuer den benutzer??
            //cout << "answer=ja" << endl; //testtest
            
        } if (strcasecmp(answer, "nein") == 0) {
            repeat = false;   
            cout << "answer=nein" << endl; //testtesttest

            //bibliothek NICHT initialisieren
            //hier soll es normal mit dem musikplayer weitergehen
            main_menu();
        } /*else {  //nichts es geht von selbst weiter  }*/
    }
}


void myopenfile() {
    bool repeat = true;
    bool repeat2= true;
    std::string filename2 = "";
    //const char* myjson = ".json";//gibt es keinen besseren weg?

    //while schleife, bis die datei gueltig geoeffnet wurde
    while (repeat) {
        cout << "Geben sie den Namen der zu oeffnenden Playlist ein: "; // spezifizieren, dass nur name der playlist und nicht .json eingegeben werden soll???
        cin >> filename; const char* answer=filename.c_str(); if (strcasecmp(answer, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!

        if (filename.find(".json") != std::string::npos) {
            //cout << "test1 test1";
            //.json ist schon angefuegt! hier passiert alles
        } else {
            std::swap(filename, filename2);//filename2 = filename
            filename = filename2 + ".json";// an dateiname wird dateiendung .json angefuegt
            //cout << filename;//test
        }
        cout << "\tDie Datei " << filename << " wird geoeffnet." << endl;

        //stand jetzt haben wir einen vielleicht gueltigen dateiname. datei wird nun geoeffnet
        try {
            std::ifstream file(mypath + filename);
            //oeffnen der .json datei^^ (in einem sicheren umfeld --> kein absturz)
            if (!file.is_open()) {
                std::cerr << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            
            repeat = false; //erst nachden file.is_open = true ist. danach bei fehler wieder geaendert
            /*nlohmann::json jsonContent;
            file >> jsonContent;//datei wird ausgelesen und in program als 'file' gespeichert!*/
            
            //datei ist gueltig also kann sie als variable an andere funktionen uebergeben werden
            file >> currentplaylist;
            file.close();
            cout << "\t\tPlaylist wurde geoeffnet" << endl; //erst hier ist die datei erfolgreich geoeffnet!!
            //wie genau benenne ich die dateitypen?? mit namen oder dateitypen? muss ich das ganze in eine ober kategorie??
            //wie suche ich spaeter die einzelnen metadaten?? muss ich die werte fuer die liste 'sterilisieren' um probleme zu verhindern?

            //damit das programm weitergeht, gehen wir zurueck zum mainmenu oder lesen die datei direkt aus
            
            cout << "\t----------------------------------" << endl;


        } catch (const std::exception& e) {
            repeat = true;
            cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << endl << e.what() << endl;
            cout << "\t----------------------------------" << endl;
            //hier gab es einen fehler beim einlesen? der datei. zum bsp war sie leer ->siehe test2.json
            //("wenden sie sich mit folgender fehlermeldung an den support")?
        }


        if(!repeat) {
        char answer2[50];
        while (repeat2) {
        cout << "Soll die Playlist direkt angezeigt werden? (Ja/Nein): ";
        cin >> answer2; if (strcasecmp(answer, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
        
            if (strcasecmp(answer2, "ja") == 0) {//if (answer == "ja") {
                repeat2 = false;
                myprintfile();
            } if (strcasecmp(answer2, "nein") == 0) {
                repeat2 = false;   
                main_menu();//zurueck zum hauptmenue
            }
        }
        }
    }


    //wo speichere ich die dateien solange die playlist offen ist? habe ich die datei dauerhaft offen?
    //^^eigentlich brauche ich das ja nur beim erstellen/editieren oder loeschen
    //ist es schlecht, die datei offen zu lassen??  was wenn das programm abstuerzt? kann ich die datei davor noch schliesssen??
}

void myprintfile() {
    //diese funkton soll saemtliche inhalte der aktuellen playlist ausgeben!
    //fehlermeldung falls keine playlist geoffnet ist (z.b. wenn keine initialisiert wurde aber im hauptmenue direkt ausgabe gefordet wurde)
    if (filename=="") {
        cout << "Fehler! Momentan ist keine Datei geoeffnet. Fehlercode: 03" << endl;
        cout << "\t----------------------------------" << endl;
        cout << ">mit Enter zurueck zum Hauptmenue...";
        std::string temp;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        main_menu();
    }

    cout << "\t----------------------------------" << endl;
    cout << "\tDie Datei " << filename << " wird ausgegeben." << endl;//WARUM FUNKTIONIERT DAS NICHT???
    cout << "     Titel     |   Interpret   |     Album     |  Erscheinungsjahr  |   Laenge   |   Genre   |   Explizit?   |" << endl;

    //cout <<currentplaylist["data"][0]["title"] <<currentplaylist["data"][0]["artist"] <<currentplaylist["data"][0]["album"] <<currentplaylist["data"][0]["date"] <<currentplaylist["data"][0]["length"] <<currentplaylist["data"][0]["genre"] <<currentplaylist["data"][0]["explicit"] <<endl;

    for(int i=0; i<(currentplaylist.size()+1); i++) {
        cout <<
        currentplaylist["data"][i]["title"] << " | " <<
        currentplaylist["data"][i]["artist"] << " | " <<
        currentplaylist["data"][i]["album"] << " | " <<
        currentplaylist["data"][i]["date"] << " |    " <<
        currentplaylist["data"][i]["length"] << " |    " <<
        currentplaylist["data"][i]["genre"] << " |    " <<
        currentplaylist["data"][i]["explicit"] << " | " <<
        endl;
    }

    cout << ">mit Enter zurueck zum Hauptmenue...";
    std::string temp;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();

    main_menu();
}

void mycreatefile() {
    char answer3[50];
    int length=0;
    
    //soll eine json datei mit bielibigem namen erstellen

    //while true schleife die einen gueltigen dateinamen(nur buchstaben, vllt zahlen wenn moeglich) abfragt
    //name darf noch nicht vergeben sein!! fehlermeldung die dem nutzer dies mitteilt
    //NEIN!!nutzer soll dann NEIN!!zurueck zum hauptmenue.NEIN!! ihm hier mitteilen, dassNEIN!! er dort songs NEIN!!hinzufuegen kann
    //JA!vllt fragen wir ihn hier, ob er direkt in den 'editor' will???JA!
    cout << "createfile--------" << endl;


    cout << "Name der neuen Playlist eingeben: ";
    cin >> answer3; if (strcasecmp(answer3, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!

    cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
    cin >> length;

    cout << length;//testtestt
    //gameplan:
    //abfragen, wie viele eintraege in die json datei geschrieben werden sollen = i
    //i mal jedes parameter nacheinander abfragen und in jeweiligen arrays speichern

    
    char title[length][25];
    char artist[length][25];
    char album[length][25];
    int year[length][25];// int erscheinungsjahr
    char duration[length][25];
    char genre[length][25];
    bool badwords[length];//    true/false

    //brauchen wir diesen zwischenschritt ueberhaupt oder koennen wir die daten direkt an writefile uebergeben??
    for(int i=0; i<length; i++) {
        cout << "Informationen fuer Song [" << i *****************<< "] eingeben:" << endl;
        cout << "Songname: "; cin >> title[i];
        cout << "Interpret: "; cin >> title[i];
        cout << "Album: "; cin >> title[i];
        cout << "Erscheinungsjahr: "; cin >> title[i];
        cout << "Laenge: "; cin >> title[i];
        cout << "Musikrichtung: "; cin >> title[i];
        cout << "Jugendfrei (Ja/Nein): "; cin >> title[i];
    }
cout << "Daten werden in Datei geschrieben" << endl;
    nlohmann::json writefile;

    for(int i=0; i<length; i++) {
        writefile[i]["title"] = title[i];
        writefile[i]["artist"] = artist[i];
        writefile[i]["album"] = album[i];
        writefile[i]["date"] = year[i];
        writefile[i]["length"] = duration[i];
        writefile[i]["genre"] = genre[i];
        writefile[i]["explicit"] = badwords[i];
    }



    //daten werden in die datei answer3 geschrieben
    std::ofstream file2(mypath + answer3);
    file2 << writefile;

    //feierabend! datei wird geschlossen
    file2.close();
}


