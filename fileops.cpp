//brauchen wir hier wohl auch:
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <cstdlib>
#include <string> //??!?
#include <string.h>
#include <cstring>//fuer strchr in mycheckifopen()
#include <cstdio>//fuer das loeschen von dateien
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

//deklarierung/inkludierung globaler variablen
extern std::string mypath;
//deklarierung eigener variablen
std::string filename = "";
nlohmann::json currentplaylist;
char answer[50];
bool repeat=true;
bool repeat2=true;
/*const char* mynein = "nein";
const char* myja = "ja"; brauchen wir zum glueck doch nicht*/

//deklarierung GLOBALER funktionen
void main_menu();
//void turn_off();  // turn_off(); anstatt exit(0); funktioniert in komplexen schleifen nicht, exit(0); scheint einfacher

void myinitialize();
void myopenfile();
void myprintfile();
/*
void mycreatefile();
*/
void myexit(char myinput[50]);
void mywaitenter();
void mycheckifopen(char myinput2[50]);
void mydashedline();


void myinitialize() {
    //char answer[50];
    //bool repeat = true;
    
    while (repeat) {
        //answer="";    nein, das waere viel zu einfach!!
        std::memset(answer, 0, sizeof(answer));
        // else if fuer nein und else danach mit "befehl nicht verstanden, playlist initialisieren (ja/nein)" einfuegen???
        cout << "Moechten sie eine Musik-Playlist initialisieren? (Ja/Nein): ";
        cin >> answer; //if (strcasecmp(answer, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
        //      alte version^^ jetzt mit myexit();
        myexit(answer);
        
        //cout << answer << endl; //testtest
        
        if (strcasecmp(answer, "ja") == 0) {//if (answer == "ja") {
            repeat = false;
            //bibliothek initialisieren
            myopenfile();
            //cout << "\nGeben sie den Namen der zu initialisierenden Playlist ein:\n" << endl; // sprache zu kompliziert fuer den benutzer??
            //cout << "answer=ja" << endl; //testtest
            
        } if (strcasecmp(answer, "nein") == 0) {
            repeat = false;   
            //cout << "answer=nein" << endl; //testtesttest

            //bibliothek NICHT initialisieren
            //hier soll es normal mit dem musikplayer weitergehen
            main_menu();
        } /*else {  //nichts es geht von selbst weiter  }*/
    }
}

void myopenfile() {
    //bool repeat = true;
    //bool repeat2= true;//hier brauchen wir tatsaechlich eine weitere repeat, da die beiden vernestet sind! wir machen sie global
    std::string filename2 = "";
    std::string tempfilename;
    //const char* myjson = ".json";//gibt es keinen besseren weg?

    mydashedline();
    //while schleife, bis die datei gueltig geoeffnet wurde
    repeat=true;
    while (repeat) {
        cout << "Geben sie den Namen der zu oeffnenden Playlist ein: "; // spezifizieren, dass nur name der playlist und nicht .json eingegeben werden soll???
        cin >> tempfilename; //char answer2=filename.c_str();//if (strcasecmp(answer2, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
        //WARUM IST ALLES SO UNNOETIG KOMPLKIZIERT?!?!?!?!?!? funktionier doch einfach
        char tempfilenamechar[tempfilename.size() + 1];//wer kommt auf so etwas?
        std::copy(tempfilename.begin(), tempfilename.end(), tempfilenamechar);
        tempfilenamechar[tempfilename.size()] = '\0';
        myexit(tempfilenamechar);//string wird hier ueber 5000 hochkomplexe schritte in einen char umgewandelt damit wir schauen koennen ob beenden geschrieben wurde

        //FAZIT: es ist (warum aucgh immer) SEHR schwierig leere oder nur aus leerzeichen bestehende inputs zu filtern
        //todo fuer
        //cout << "11";
        ///////if(tempfilename!="") {//nur wenn der dateiname nicht leer ist geht alles weiter!!
        //if (!tempfilename.empty()) {
        //das war eine fehlerquelle, die das programm komplett angehalten und unbenutzbar gemacht hat!
        //cout <<"222";
        //schauen ob datei schon offen ist!
        //if(filename==tempfilename) {
        //    cout << "Die Playlist: >" << filename << "< ist bereits geoeffnet!"<< endl;
        //    main_menu();
        //}
        mycheckifopen(tempfilenamechar);
        //alles gut?!   filename wird uebergeben und es geht
        filename = tempfilename;
        tempfilename = "";

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
            
            mydashedline();
            //cout << "\t----------------------------------" << endl;


        } catch (const std::exception& e) {
            repeat = true;
            cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << endl << e.what() << endl;
            mydashedline();
            //cout << "\t----------------------------------" << endl;
            //hier gab es einen fehler beim einlesen? der datei. zum bsp war sie leer ->siehe test2.json
            //("wenden sie sich mit folgender fehlermeldung an den support")?
        }

        //datei ist geoeffnet und kann hier direkt ausgegeben werden
        if(!repeat) {
        //char answer3[50];
        std::memset(answer, 0, sizeof(answer));
            repeat2=true;
            while (repeat2) {
            cout << "Soll die Playlist direkt angezeigt werden? (Ja/Nein): ";
            cin >> answer;//if (strcasecmp(answer3, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
            myexit(answer);//wurde "beenden" eingegeben?
    
                if (strcasecmp(answer, "ja") == 0) {//if (answer == "ja") {
                    repeat2 = false;
                    myprintfile();
                } if (strcasecmp(answer, "nein") == 0) {
                    repeat2 = false;   
                    main_menu();//zurueck zum hauptmenue
                }
            }
        }
        //////}
        //} else {
        //    cout << "fehler";
        //}
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
        mydashedline();
        //cout << "\t----------------------------------" << endl;
        mywaitenter();
        main_menu();
    }

    mydashedline();
    //cout << "\t----------------------------------" << endl;
    cout << "\tDie Datei " << filename << " wird ausgegeben." << endl;//WARUM FUNKTIONIERT DAS NICHT???
    cout << "     Titel     |   Interpret   |     Album     |  Erscheinungsjahr  |   Laenge   |   Genre   |   Jugendfrei"/*Explizit?*/"   |" << endl;

    //cout <<currentplaylist["data"][0]["title"] <<currentplaylist["data"][0]["artist"] <<currentplaylist["data"][0]["album"] <<currentplaylist["data"][0]["date"] <<currentplaylist["data"][0]["length"] <<currentplaylist["data"][0]["genre"] <<currentplaylist["data"][0]["explicit"] <<endl;

    for(int i=0; i<(currentplaylist.size()+1); i++) {
        cout <<
        currentplaylist["data"][i]["title"] << " | " <<
        currentplaylist["data"][i]["artist"] << " | " <<
        currentplaylist["data"][i]["album"] << " | " <<
        currentplaylist["data"][i]["date"] << " |    " <<
        currentplaylist["data"][i]["length"] << " |    " <<
        currentplaylist["data"][i]["genre"] << " |    ";// <<
        if(currentplaylist["data"][i]["explicit"]==true) {
            cout << "Nein";
        } else {
            cout <<"Ja";
        }//currentplaylist["data"][i]["explicit"]
        cout << "  | " << endl;
    }

    //cout << ">mit Enter zurueck zum Hauptmenue...";
    //std::string temp;
    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //cin.get();
    mywaitenter();

    main_menu();
}

void mycreatefile() {
    //bool repeat3=true;
    //bool repeat6=true;
    //char answer3[50];
    char filenamecreatefile[50];
    //char answer3temp[50];
    //char answer6[50];
    int length=0;
    
    //soll eine json datei mit bielibigem namen erstellen

    //while true schleife die einen gueltigen dateinamen(nur buchstaben, vllt zahlen wenn moeglich) abfragt
    //name darf noch nicht vergeben sein!! fehlermeldung die dem nutzer dies mitteilt
    //NEIN!!nutzer soll dann NEIN!!zurueck zum hauptmenue.NEIN!! ihm hier mitteilen, dassNEIN!! er dort songs NEIN!!hinzufuegen kann
    //JA!vllt fragen wir ihn hier, ob er direkt in den 'editor' will???JA!
    //cout << "createfile--------" << endl;
    
    mydashedline();
    //std::memset(filenamecreatefile, 0, sizeof(filenamecreatefile));
    cout << "Name der neuen Playlist eingeben: ";
    cin >> filenamecreatefile;//if (strcasecmp(answer3, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
    myexit(filenamecreatefile);
    //vllt schauen ob playlist gerade schon offen ist?DONE
    //cout << "davor: " << filenamecreatefile << endl;
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
    myexit(filenamecreatefile);//schwachsinn

    //for (size_t i = 0; i < answer3str.length(); ++i) {
    //    filenamecreatefile[i] = answer3str[i];
    //}
    //----------------------------------------------------^^^absolutes chaos!! muss spaeter alles aufgeraeumt werden!!!!!
    //cout << "danach:" << filenamecreatefile << endl;

    mycheckifopen(filenamecreatefile);
    //if(answer3==filename || answer3==) {
    //    cout << "Die Playlist: >" << answer3 << "< ist bereits geoeffnet!"<< endl;
    //    cout << "Bearbeiten/Loeschen und weitere Funktionen ueber das Hauptmenue." << endl;
    //    mywaitenter();
    //    main_menu();
    //}

    repeat=true;
    //hier sicherstellen, dass nur integer eingegeben werden, auf beenden pruefen vllt nicht moeglich
    while (repeat) {
        cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
        if (cin >> length) {//integer wurde eingegeben
        //cout <<"111";//test
            if(length>0) {repeat=false;}//integer ist größer als 0 -- also passt alles!!
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
    repeat=true;
    while (repeat) {
        std::memset(answer, 0, sizeof(answer));
        cout << length << " Songs werden zu " << filenamecreatefile << " hinzugefuegt. Fortfahren? (Ja/Nein):";//fragen, ob er fortfahren will?
        cin >> answer;
        myexit(answer);//wurde "beenden" eingegeben?
        if (strcasecmp(answer, "ja") == 0) {
            repeat = false;
        } if (strcasecmp(answer, "nein") == 0) {
            repeat = false;
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

    //bool repeat4=true;
    //bool repeat5=true;
    //char answer4[25];
    int tempyear=0;

    mydashedline();
    cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << endl;

    //brauchen wir diesen zwischenschritt ueberhaupt oder koennen wir die daten direkt an writefile uebergeben??
    //fuer jetzt behalten wir ihn, da wir probleme mit dem schreiben in die datei haben!! vllt spaeter entfernen? stichwort 'optimisation'
    std::memset(answer, 0, sizeof(answer));
    for(int i=0; i<length; i++) {
        //cout << "\t----------------------------------" << endl;
        mydashedline();
        cout << "Informationen fuer Song [" << i+1 << "] eingeben:" << endl;
        cout << "Songname: "; cin >> title[i];
        cout << "Interpret: "; cin >> artist[i];
        cout << "Album: "; cin >> album[i];
        repeat=true;
        while (repeat) {cout << "Erscheinungsjahr: ";
            if (cin >> tempyear) {//integer wurde eingegeben
                if(tempyear>0) {repeat=false;year[i]=tempyear;}//success!
            } else {
                std::cin.clear();//input wird geloescht
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //^^input wird ignoriert. warum schon wieder so kompliziert??!? / und ist er nicht eigentlich schon geloescht??
                cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << endl;}
        }
        cout << "Laenge [xx:xx]: "; cin >> duration[i];
        cout << "Musikrichtung: "; cin >> genre[i];
        repeat=true;
        while (repeat) {cout << "Jugendfrei (Ja/Nein): "; cin >> answer;
            //myexit(answer4);//brauchen wir das? ich lasse es drin bis wir die bestaetigung am anfang haben?!
            if (strcasecmp(answer, "ja") == 0) {repeat=false;badwords[i]=false;}
            if (strcasecmp(answer, "nein") == 0) {repeat=false;badwords[i]=true;}
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

    //for (int i2 = 0; i2<length; i2++) {
    //    for (int i = 0; i<5; i++) {
    //        cout << "duration["<<i2<<"]["<<i<<"]:  ";
    //        cout << duration[i2][i]<< endl;
    //    }
    //}//testen ob es geklappt hat!   /eigentlich klappt es immer, der fehler muss irgendwo anders liegen!

    mydashedline();
    cout << "Daten werden in Datei geschrieben" << endl;
    //try {
    nlohmann::json writefile = {//reihenfolge scheint irrelevant zu sein, da die eintraege alphabetisch? sortiert werden.
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

    //cout << "test1";
    for(int i=0; i<length; i++) {
        writefile["data"][i]["title"] = title[i];
        writefile["data"][i]["artist"] = artist[i];
        writefile["data"][i]["album"] = album[i];
        writefile["data"][i]["date"] = year[i];
        writefile["data"][i]["length"] = duration[i];
        writefile["data"][i]["genre"] = genre[i];
        writefile["data"][i]["explicit"] = badwords[i];
    }

    //}
    //catch(const std::exception& e) {
    //    mydashedline();
    //    cout << "Fehler beim schreiben in die Datei: " << e.what() << endl;
    //}


    
    //char answer8[50];
    //bool repeat7=true;
    //bool repeat8=true;
    std::memset(answer, 0, sizeof(answer));
    repeat=true;
    while(repeat) {//      ------das sollte jetzt alles abgeichert sein, aber wie testet man so etwas?? wie kann ich ein fole.is_open()==false erzwingen??
        //daten werden in die datei file2 geschrieben
        std::ofstream file2(mypath + filenamecreatefile);
        //cout << "test2: " << mypath+filenamecreatefile<<endl;

        if (!file2.is_open()) {
            cout << "Datei konnte nicht geoeffnet werden, um Datenn zu speichern! Fehlercode: 04" << endl;
            //main_menu();//vorerst zurueck zum mainmenu. speater muss hier eine loesung gefunden werden.
            //zum beispiel erneute abfrage nach dateinamen und versuch die bereits eingelesenen daten dotz zu speichern.
            //"wollen sie das speichern erneut versuchen? (ja/nein)"
            
        repeat2=true;
        while(repeat2) {
            cout << "Erneut mit anderem Dateinamen versuchen? (Ja/Nein): ";
            cin >> answer;
            myexit(answer);

            if (strcasecmp(answer, "ja") == 0) {//er will es nochmal versuchen. viel glueck!
                repeat2=false;
                std::string tempanswer;
                cout << "Geben sie einen alternativen Dateinamen ein:";
                cin >> tempanswer;
                //myexit(tempanswer.c_str());   geht nicht aber egal, da wir davor schon nach return zum mainmenu fragen
                if (tempanswer.find(".json") != std::string::npos) {
                    //cout << "test1 test1";
                    //.json ist schon angefuegt! hier passiert alles
                } else {
                    tempanswer = tempanswer + ".json";// an dateiname wird dateiendung .json angefuegt
                }
            }
            if (strcasecmp(answer, "nein") == 0) {
                repeat2=false;
                main_menu();
            }
        }
        //dann zurueck in den loop und es klappt hoffentlich
        } else {
            repeat=false;
            file2 << writefile.dump(2);
            //cout << "test3";
            //feierabend! datei wird geschlossen
            file2.close();
            main_menu();
        }
    }


}

void mydeletefile() {
    std::memset(answer, 0, sizeof(answer));//answer zuruecksetzen, weil sonst random sonderzeichen auftauchen
    cout << "Name der zu loeschenden Playlist eingeben: ";
    cin >> answer;
    
    std::string filenamedeletefile(answer);
    //da wir hier dateien loeschen mussen wir sehr vorsichtig sein!! der benutzer koennte auf andere ordner zugreifen!!!
    if (filenamedeletefile.find("/") != std::string::npos || filenamedeletefile.find("\\") != std::string::npos) {//zwei backslashes wil backslash benutzt wird um spezielle charakter darzustellen! '//' ==> /
        cout << "Fehler! Nicht erlaubte Zeichen eingegeben. Fehlercode: 05"<<endl;
        mywaitenter();
        main_menu();
    }
    filenamedeletefile=mypath+filenamedeletefile;
    //cout << "test1231:" << filenamedeletefile;

    repeat=true;
    while(repeat) {
        cout << "Die Playlist " << filenamedeletefile << " wird geloescht! Fortfahren? (Ja/Nein): ";

        if (strcasecmp(answer, "ja") == 0) {
            repeat = false;
            
        } if (strcasecmp(answer, "nein") == 0) {
            repeat = false;
            main_menu();
        }
    }

    //hier wird geloescht
    const char* filenamedeletefilec;
    filenamedeletefilec=filenamedeletefile.c_str();
    cout <<"testtest: " << filenamedeletefilec << endl;//testtest

    if (std::remove(filenamedeletefilec) != 0) {
        cout << "Fehler! Die Datei konnte nicht geloescht werden. Fehlercode: 06" << endl;
        mywaitenter();
        main_menu
    } else {
        mydashedline();
        std::cout << "\tDie Datei wurde erfolgreich geloescht!" << std::endl;
        mywaitenter();
        main_menu();    
    }
}

void myexit(char myinput[50]) {
//funktion ueberprueft inputs auf "beenden" und beendet dann das programm.
    //cout << "asdasdasd" << endl;//test
    //cout << myinput << endl;
    if(strcasecmp(myinput, "beenden")==0) {//hier koennen sehr leicht andere woerter, wie "exit" oder "schliessen" ergaenzt werden
        cout << "" << endl;           //was machen wir bei der eingabe von titel, interpret, album, ...? was wenn dort "beenden" auftaucht?
        cout << "\tDer Musikplayer wurde vom Benutzer beendet." << endl;
        exit(0);
    }
}

void mywaitenter() {
    cout << ">mit Enter zurueck zum Hauptmenue...";
    std::string temp;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

void mycheckifopen(char myinput2[50]) {
    //std::string tempfilename = filename;    
    const char* tempfilename; tempfilename = filename.c_str();//AAAARRRGHHH

    char* dotPos = std::strrchr(tempfilename, '.');//wir finden die stelle, an der der punkt ist
    if (dotPos != nullptr) {//falls es diese gibt
        *dotPos = '\0';//und loecshen alles danach!
    }

    if(myinput2==filename || myinput2==tempfilename) {
        cout << "Die Playlist: >" << myinput2 << "< ist bereits geoeffnet!"<< endl;
        cout << "Bearbeiten/Loeschen und weitere Funktionen ueber das Hauptmenue." << endl;
        mywaitenter();
        main_menu();
    }
}

void mydashedline() {
        cout << "\t----------------------------------" << endl;
}


