
/*
//testen der createfile funktion, da das schreiben in dateien momentan nicht funktioniert
#include "fileops.cpp"//
#include "menu.cpp"

#include <stdio.h>
#include <cstdlib>
#include <string> //??!?
#include <string.h>
#include <cstring>//fuer strchr in mycheckifopen()
#include <iostream> //brauchen wir das alles? macht es das programm zu langsam/grosss?
#include <fstream>//benutzen wir um dateien zu lesen/schreiben
#include "nlohmann/json.hpp"//nlohmann json bibliothek
//inkludieren anderer programmteile!!
//json bibiliothek
using json = nlohmann::json;
//cpp sachen??!
using namespace std;
//using std::cout;
//using std::cin;
//using std::endl;

//deklarierung globaler variablen
//extern std::string mypath;
std::string mypath="playlists/";


//deklarierung GLOBALER funktionen
void main_menu();
//
//void myinitialize();
//void myopenfile();
//void myprintfile();
void myexit(char input[100]);
void mywaitenter();
void mycheckifopen(char input2[25]);
void mydashedline();


void mycreatefile();

int main() {
    //myopenfile();
    mycreatefile();
    cout<<"\tDAS PROGRAMM IST DURCHGELAUFEN!!!!!!!!!"<<endl;
    return 0;
}



void mycreatefile() {
    bool repeat3=true;
    bool repeat6=true;
    //char answer3[50];
    char filenamecreatefile[50];
    //char answer3temp[50];
    char answer6[50];
    int length=0;
    
    //soll eine json datei mit bielibigem namen erstellen

    //while true schleife die einen gueltigen dateinamen(nur buchstaben, vllt zahlen wenn moeglich) abfragt
    //name darf noch nicht vergeben sein!! fehlermeldung die dem nutzer dies mitteilt
    //NEIN!!nutzer soll dann NEIN!!zurueck zum hauptmenue.NEIN!! ihm hier mitteilen, dassNEIN!! er dort songs NEIN!!hinzufuegen kann
    //JA!vllt fragen wir ihn hier, ob er direkt in den 'editor' will???JA!
    //cout << "createfile--------" << endl;
    
    mydashedline();
    cout << "Name der neuen Playlist eingeben: ";
    cin >> filenamecreatefile;//if (strcasecmp(answer3, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
    myexit(filenamecreatefile);
    //vllt schauen ob playlist gerade schon offen ist?DONE
    cout << "davor: " << filenamecreatefile << endl;
    std::string answer3str(filenamecreatefile);
    std::string answer3str2;//sonst bekommen wir irgendwelche schwachsinnigen emojis uns sonderzeichen.
    if (answer3str.find(".json") != std::string::npos) {
        //cout << "test1 test1";
        //.json ist schon angefuegt! hier passiert alles
    } else {
        answer3str2 = answer3str;//WARUM MUSS ALLES SO KOMPLIZIERT SEIN???
        answer3str = answer3str2 + ".json";// an dateiname wird dateiendung .json angefuegt
        //cout << filename;//test
    }

    std::copy(answer3str.begin(), answer3str.end(), filenamecreatefile);
    filenamecreatefile[answer3str.size()] = '\0';
    myexit(filenamecreatefile);

    //for (size_t i = 0; i < answer3str.length(); ++i) {
    //    filenamecreatefile[i] = answer3str[i];
    //}
    //----------------------------------------------------^^^absolutes chaos!! muss spaeter alles aufgeraeumt werden!!!!!
    cout << "danach:" << filenamecreatefile << endl;

    mycheckifopen(filenamecreatefile);
    //if(answer3==filename || answer3==) {
    //    cout << "Die Playlist: >" << answer3 << "< ist bereits geoeffnet!"<< endl;
    //    cout << "Bearbeiten/Loeschen und weitere Funktionen ueber das Hauptmenue." << endl;
    //    mywaitenter();
    //    main_menu();
    //}

    repeat3=true;
    //hier sicherstellen, dass nur integer eingegeben werden, auf beenden pruefen vllt nicht moeglich
    while (repeat3) {
        cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
        if (cin >> length) {//integer wurde eingegeben
        //cout <<"111";//test
            if(length>0) {repeat3=false;}//integer ist größer als 0
        } else {
            //char tempchar[25];
            //cin >> tempchar;
            //cout << tempchar;
            //cout << "asdasd";
            //myexit(tempchar);
            //versuch2
            //char eskoenntesoeinfachsein[cin.size() + 1];//wer kommt auf so etwas?
            //std::copy(cin.begin(), cin.end(), eskoenntesoeinfachsein);
            //eskoenntesoeinfachsein[cin.size()] = '\0';
            //myexit(eskoenntesoeinfachsein);
            //------------------------------------
            //ich gebe auf. hier kann nicht beendet werden. wir fragen den benutzer einfach "continue (ja/nein)" bei naechster moeglichkeit!


            //if(length<=0) {cout << "Fehlerhafte Eingabe! Bitte geben sie eine gueltige Zahl ein: " << endl;}
            std::cin.clear();
            //^^input wird geloescht
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //^^input wird ignoriert. warum schon wieder so kompliziert??!?
            cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << endl;
        }
    }
    //cin >> length;
    //cout << length;//testtestt
    //gameplan:
    //abfragen, wie viele eintraege in die json datei geschrieben werden sollen = i
    //i mal jedes parameter nacheinander abfragen und in jeweiligen arrays speichern
    while (repeat6) {
        cout << length << " Songs werden zu " << filenamecreatefile << " hinzugefuegt. Fortfahren? (Ja/Nein):";//fragen, ob er fortfahren will?
        cin >> answer6;
        myexit(answer6);//wurde "beenden" eingegeben?
        if (strcasecmp(answer6, "ja") == 0) {
            repeat6 = false;
        } if (strcasecmp(answer6, "nein") == 0) {
            repeat6 = false;
            main_menu();
        }
    }

    char title[length][25];
    char artist[length][25];
    char album[length][25];
    int year[length];// int erscheinungsjahr
    char duration[length][5] = {};
    char genre[length][25];
    bool badwords[length];//    true/false

    for (int i2 = 0; i2<length; i2++) {//ich versuche sicherzustellen, dass es keine probleme beim speichern gibt
        for (int i = 0; i<5; i++) {
            duration[i2][i]='\0';
        }
    }

    bool repeat4=true;
    bool repeat5=true;
    char answer4[25];
    int tempyear=0;

    mydashedline();
    cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << endl;

    //brauchen wir diesen zwischenschritt ueberhaupt oder koennen wir die daten direkt an writefile uebergeben??
    //fuer jetzt behalten wir ihn, da wir probleme mit dem schreiben in die datei haben!! vllt spaeter entfernen? stichwort 'optimisation'
    for(int i=0; i<length; i++) {
        //cout << "\t----------------------------------" << endl;
        mydashedline();
        cout << "Informationen fuer Song [" << i+1 << "] eingeben:" << endl;
        cout << "Songname: "; cin >> title[i];
        cout << "Interpret: "; cin >> artist[i];
        cout << "Album: "; cin >> album[i];
        repeat5=true;
        while (repeat5) {cout << "Erscheinungsjahr: ";
            if (cin >> tempyear) {//integer wurde eingegeben
                if(tempyear>0) {repeat5=false;year[i]=tempyear;}//success!
            } else {
                std::cin.clear();//input wird geloescht
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //^^input wird ignoriert. warum schon wieder so kompliziert??!? / und ist er nicht eigentlich schon geloescht??
                cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << endl;}
        }
        cout << "Laenge [xx:xx]: "; cin >> duration[i];
        cout << "Musikrichtung: "; cin >> genre[i];
        repeat4=true;
        while (repeat4) {cout << "Jugendfrei (Ja/Nein): "; cin >> answer4;
            //myexit(answer4);//brauchen wir das? ich lasse es drin bis wir die bestaetigung am anfang haben?!
            if (strcasecmp(answer4, "ja") == 0) {repeat4=false;badwords[i]=false;}
            if (strcasecmp(answer4, "nein") == 0) {repeat4=false;badwords[i]=true;}
        }
    }

    //jetzt muessen wir den doppelpunkt bei duration ersetzen
    //ggfs sollten wir auch onch andere inputs ueberpruefen und sonderzeichen herausfiltern! --> aufgabe fuer spaeter!
    for (int i2 = 0; i2<length; i2++) {
        for (int i = 0; i<5; i++) {
            if (duration[i2][i] == ':') {
                duration[i2][i] = '_'; // Replace colon with underscore
            }
        }
    }


    for (int i2 = 0; i2<length; i2++) {
        for (int i = 0; i<5; i++) {
            cout << "duration["<<i2<<"]["<<i<<"]:  ";
            cout << duration[i2][i]<< endl;
        }
    }//testen ob es geklappt hat!   /eigentlich klappt es immer, der fehler muss irgendwo anders liegen!

    mydashedline();
    cout << "Daten werden in Datei geschrieben" << endl;
    nlohmann::json writefile = {
        {
            "data",
            {
                {
                    {"title", ""},
                    {"artist", ""},
                    {"album", ""},
                    {"date", nullptr},
                    {"length", ""},
                    {"genre", ""},
                    {"explicit", ""}
                }
            }
        }
    };

    cout << "test1";
    for(int i=0; i<length; i++) {
        writefile["data"][i]["title"] = title[i];
        writefile["data"][i]["artist"] = artist[i];
        writefile["data"][i]["album"] = album[i];
        writefile["data"][i]["date"] = year[i];
        writefile["data"][i]["length"] = duration[i];
        writefile["data"][i]["genre"] = genre[i];
        writefile["data"][i]["explicit"] = badwords[i];
    }


    
    //daten werden in die datei answer3 geschrieben
    std::ofstream file2(mypath + filenamecreatefile);
    cout << "test2: " << mypath+filenamecreatefile<<endl;

    /*if (!file2.is_open()) {
        cout << "Datei konnte nicht geoeffnet werden, um Dateien zu speichern! Fehlercode4" << endl;
        main_menu();//vorerst zurueck zum mainmenu. speater muss hier eine loesung gefunden werden.
        //zum beispiel erneute abfrage nach dateinamen und versuch die bereits eingelesenen daten dotz zu speichern.
        //"wollen sie das speichern erneut versuchen? (ja/nein)"
    }*/
/////////*
//    file2 << writefile.dump(2);
//    cout << "test3";
//    //feierabend! datei wird geschlossen
//    file2.close();
//}
//*/


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------



/*
void mycreatefile() {
    bool repeat3=true;
    bool repeat6=true;
    char answer3[50];
    int length=0;
    
    //soll eine json datei mit bielibigem namen erstellen

    //while true schleife die einen gueltigen dateinamen(nur buchstaben, vllt zahlen wenn moeglich) abfragt
    //name darf noch nicht vergeben sein!! fehlermeldung die dem nutzer dies mitteilt
    //NEIN!!nutzer soll dann NEIN!!zurueck zum hauptmenue.NEIN!! ihm hier mitteilen, dassNEIN!! er dort songs NEIN!!hinzufuegen kann
    //JA!vllt fragen wir ihn hier, ob er direkt in den 'editor' will???JA!
    //cout << "createfile--------" << endl;
    
    mydashedline();
    cout << "Name der neuen Playlist eingeben: ";
    cin >> answer3;//if (strcasecmp(answer3, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
    myexit(answer3);
    //vllt schauen ob playlist gerade schon offen ist?DONE
    mycheckifopen(answer3);
    //if(answer3==filename || answer3==) {
    //    cout << "Die Playlist: >" << answer3 << "< ist bereits geoeffnet!"<< endl;
    //    cout << "Bearbeiten/Loeschen und weitere Funktionen ueber das Hauptmenue." << endl;
    //    mywaitenter();
    //    main_menu();
    //}

    repeat3=true;
    //hier sicherstellen, dass nur integer eingegeben werden, auf beenden pruefen vllt nicht moeglich
    while (repeat3) {
        cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
        if (cin >> length) {//integer wurde eingegeben
        //cout <<"111";//test
            if(length>0) {repeat3=false;}//integer ist größer als 0
        } else {
            //char tempchar[25];
            //cin >> tempchar;
            //cout << tempchar;
            //cout << "asdasd";
            //myexit(tempchar);
            //versuch2
            //char eskoenntesoeinfachsein[cin.size() + 1];//wer kommt auf so etwas?
            //std::copy(cin.begin(), cin.end(), eskoenntesoeinfachsein);
            //eskoenntesoeinfachsein[cin.size()] = '\0';
            //myexit(eskoenntesoeinfachsein);
            //------------------------------------
            //ich gebe auf. hier kann nicht beendet werden. wir fragen den benutzer einfach "continue (ja/nein)" bei naechster moeglichkeit!


            //if(length<=0) {cout << "Fehlerhafte Eingabe! Bitte geben sie eine gueltige Zahl ein: " << endl;}
            std::cin.clear();
            //^^input wird geloescht
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //^^input wird ignoriert. warum schon wieder so kompliziert??!?
            cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << endl;
        }
    }
    //cin >> length;
    //cout << length;//testtestt
    //gameplan:
    //abfragen, wie viele eintraege in die json datei geschrieben werden sollen = i
    //i mal jedes parameter nacheinander abfragen und in jeweiligen arrays speichern
    while (repeat6) {
        cout << length << " Songs werden zu " << answer3 << " hinzugefuegt. Fortfahren? (Ja/Nein):";//fragen, ob er fortfahren will?
        cin >> answer3;
        myexit(answer3);//wurde "beenden" eingegeben?
        if (strcasecmp(answer3, "ja") == 0) {
            repeat6 = false;
        } if (strcasecmp(answer3, "nein") == 0) {
            repeat6 = false;
            main_menu();
        }
    }

    char title[length][25];
    char artist[length][25];
    char album[length][25];
    int year[length];// int erscheinungsjahr
    char duration[length][5] = {};
    char genre[length][25];
    bool badwords[length];//    true/false

    for (int i2 = 0; i2<length; i2++) {//ich versuche sicherzustellen, dass es keine probleme beim speichern gibt
        for (int i = 0; i<5; i++) {
            duration[i2][i]='\0';
        }
    }

    bool repeat4=true;
    bool repeat5=true;
    char answer4[25];
    int tempyear=0;

    mydashedline();
    cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << endl;

    //brauchen wir diesen zwischenschritt ueberhaupt oder koennen wir die daten direkt an writefile uebergeben??
    //fuer jetzt behalten wir ihn, da wir probleme mit dem schreiben in die datei haben!! vllt spaeter entfernen? stichwort 'optimisation'
    for(int i=0; i<length; i++) {
        //cout << "\t----------------------------------" << endl;
        mydashedline();
        cout << "Informationen fuer Song [" << i+1 << "] eingeben:" << endl;
        cout << "Songname: "; cin >> title[i];
        cout << "Interpret: "; cin >> artist[i];
        cout << "Album: "; cin >> album[i];
        repeat5=true;
        while (repeat5) {cout << "Erscheinungsjahr: ";
            if (cin >> tempyear) {//integer wurde eingegeben
                if(tempyear>0) {repeat5=false;year[i]=tempyear;}//success!
            } else {
                std::cin.clear();//input wird geloescht
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //^^input wird ignoriert. warum schon wieder so kompliziert??!? / und ist er nicht eigentlich schon geloescht??
                cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << endl;}
        }
        cout << "Laenge [xx:xx]: "; cin >> duration[i];
        cout << "Musikrichtung: "; cin >> genre[i];
        repeat4=true;
        while (repeat4) {cout << "Jugendfrei (Ja/Nein): "; cin >> answer4;
            //myexit(answer4);//brauchen wir das? ich lasse es drin bis wir die bestaetigung am anfang haben?!
            if (strcasecmp(answer4, "ja") == 0) {repeat4=false;badwords[i]=false;}
            if (strcasecmp(answer4, "nein") == 0) {repeat4=false;badwords[i]=true;}
        }
    }

    //jetzt muessen wir den doppelpunkt bei duration ersetzen
    //ggfs sollten wir auch onch andere inputs ueberpruefen und sonderzeichen herausfiltern! --> aufgabe fuer spaeter!
    for (int i2 = 0; i2<length; i2++) {
        for (int i = 0; i<5; i++) {
            if (duration[i2][i] == ':') {
                duration[i2][i] = '_'; // Replace colon with underscore
            }
        }
    }


    for (int i2 = 0; i2<length; i2++) {
        for (int i = 0; i<5; i++) {
            cout << "duration["<<i2<<"]["<<i<<"]:  ";
            cout << duration[i2][i]<< endl;
        }
    }//testen ob es geklappt hat!   /eigentlich klappt es immer, der fehler muss irgendwo anders liegen!

    mydashedline();
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
*/



