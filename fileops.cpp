//brauchen wir hier wohl auch:
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <cstdlib>
#include <string> //??!?
#include <string.h>
//#include <conio.h>//fuer getch() (get characters, die gerade eingetippt wurden)

#include <cstring>//fuer strchr in mycheckifopen()
#include <cctype> // damit wir in mysearchfile() std::tolower() benutzen koennen. natuerlich gibt es einen weg das super einfach zu machen, aber er koennte nicht versteckter sein!!
#include <cstdio>//fuer das loeschen von dateien
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

//deklarierung/inkludierung globaler variablen
extern std::string mypath;
//deklarierung eigener variablen
std::string filename = "";
std::string tempfilename;
nlohmann::json currentplaylist;
nlohmann::json searchplaylist;//lieber eine neue erstellen, da currentplaylist in mehreren funktionen benuzt wird und dort genutzt wird um daten zwischen funktionen zu uebertragen. koennte am ende gecheckt werden um zu optimisieren! todo?
//nlohmann::json editplaylist;

char answer[50];
bool repeat=true;
bool repeat2=true;
/*const char* mynein = "nein";
const char* myja = "ja"; brauchen wir zum glueck doch nicht*/

//deklarierung GLOBALER funktionen
void main_menu();
void song_management();
//void turn_off();  // turn_off(); anstatt exit(0); funktioniert in komplexen schleifen nicht, exit(0); scheint einfacher

void myinitialize();
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
            myopenfile(false);
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

void myopenfile(bool justprint2) {
    //bool repeat = true;
    //bool repeat2= true;//hier brauchen wir tatsaechlich eine weitere repeat, da die beiden vernestet sind! wir machen sie global
    std::string filename2 = "";
    //std::string tempfilename;
    //const char* myjson = ".json";//gibt es keinen besseren weg?

    mydashedline();
    //while schleife, bis die datei gueltig geoeffnet wurde
    repeat=true;
    while (repeat) {
        if(justprint2) {
            std::cout << "Geben sie den Namen der zu bearbeitenden Playlist ein: ";
        } else {
            std::cout << "Geben sie den Namen der zu oeffnenden Playlist ein: "; // spezifizieren, dass nur name der playlist und nicht .json eingegeben werden soll???
        }
        std::cin >> tempfilename; //char answer2=filename.c_str();//if (strcasecmp(answer2, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
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
        //mycheckifopen(tempfilename);
        //alles gut?!   filename wird uebergeben und es geht
        filename = tempfilename;
        //tempfilename = "";

        if (filename.find(".json") != std::string::npos) {
            //cout << "test1 test1";
            //.json ist schon angefuegt! hier passiert alles
        } else {
            std::swap(filename, filename2);//filename2 = filename
            filename = filename2 + ".json";// an dateiname wird dateiendung .json angefuegt
            //cout << filename;//test
        }
       std::cout << "\tDie Datei " << filename << " wird geoeffnet." << std::endl;

        //stand jetzt haben wir einen vielleicht gueltigen dateiname. datei wird nun geoeffnet
        try {
            std::ifstream file(mypath + filename);
            //oeffnen der .json datei^^ (in einem sicheren umfeld --> kein absturz)
            if (!file.is_open()) {
                std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            
            repeat = false; //erst nachden file.is_open = true ist. danach bei fehler wieder geaendert
            /*nlohmann::json jsonContent;
            file >> jsonContent;//datei wird ausgelesen und in program als 'file' gespeichert!*/
            
            //datei ist gueltig also kann sie als variable an andere funktionen uebergeben werden
            file >> currentplaylist;
            file.close();
            std::cout << "\t   Playlist erfolgreich geoeffnet" << std::endl; //erst hier ist die datei erfolgreich geoeffnet!!
            //std::cout << "CURRENTPLAYLIST.SIZE =" << currentplaylist["data"].size() << std::endl;
            //wie genau benenne ich die dateitypen?? mit namen oder dateitypen? muss ich das ganze in eine ober kategorie??
            //wie suche ich spaeter die einzelnen metadaten?? muss ich die werte fuer die liste 'sterilisieren' um probleme zu verhindern?

            //damit das programm weitergeht, gehen wir zurueck zum mainmenu oder lesen die datei direkt aus
            
            if(!justprint2) {
                mydashedline();
            }
            //cout << "\t----------------------------------" << endl;


        } catch (const std::exception& e) {
            repeat = true;
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << std::endl << e.what() << std::endl;
            mydashedline();
            //cout << "\t----------------------------------" << endl;
            //hier gab es einen fehler beim einlesen? der datei. zum bsp war sie leer ->siehe test2.json
            //("wenden sie sich mit folgender fehlermeldung an den support")?
        }

        //datei ist geoeffnet und kann hier direkt ausgegeben werden
        if(!repeat && !justprint2) {
        //char answer3[50];
        std::memset(answer, 0, sizeof(answer));
            repeat2=true;
            while (repeat2) {
            std::cout << "Soll die Playlist direkt angezeigt werden? (Ja/Nein): ";
            std::cin >> answer;//if (strcasecmp(answer3, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
            myexit(answer);//wurde "beenden" eingegeben?
    
                if (strcasecmp(answer, "ja") == 0) {//if (answer == "ja") {
                    repeat2 = false;
                    myprintfile(false);
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

void myprintfile(bool justprint) {
    //diese funkton soll saemtliche inhalte der aktuellen playlist ausgeben!
    //fehlermeldung falls keine playlist geoffnet ist (z.b. wenn keine initialisiert wurde aber im hauptmenue direkt ausgabe gefordet wurde)
    mydashedline();
    if (filename=="") {
        std::cout << "Fehler! Momentan ist keine Datei geoeffnet. Fehlercode: 03" << std::endl;
        mydashedline();
        //cout << "\t----------------------------------" << endl;
        mywaitenter();
        main_menu();
    }

    
    //cout << "\t----------------------------------" << endl;
    if(!justprint) {
        std::cout << "\tDie Datei " << filename << " wird ausgegeben." << std::endl;//WARUM FUNKTIONIERT DAS NICHT???
    }
    std::cout << " Nr. |     Titel     |   Interpret   |     Album     |  Erscheinungsjahr  |   Laenge   |   Genre   |   Jugendfrei"/*Explizit?*/"   |" << std::endl;

    //cout <<currentplaylist["data"][0]["title"] <<currentplaylist["data"][0]["artist"] <<currentplaylist["data"][0]["album"] <<currentplaylist["data"][0]["date"] <<currentplaylist["data"][0]["length"] <<currentplaylist["data"][0]["genre"] <<currentplaylist["data"][0]["explicit"] <<endl;

    for(int i=0; i<currentplaylist["data"].size(); i++) {
        std::cout <<
        "  " << (i+1) << " |  " <<
        currentplaylist["data"][i]["title"] << " | " <<
        currentplaylist["data"][i]["artist"] << " | " <<
        currentplaylist["data"][i]["album"] << " | " <<
        currentplaylist["data"][i]["date"] << " |    " <<
        currentplaylist["data"][i]["length"] << " |    " <<
        currentplaylist["data"][i]["genre"] << " |    ";// <<
        if(currentplaylist["data"][i]["explicit"]==true) {
            std::cout << "Nein";
        } else {
            std::cout <<"Ja";
        }//currentplaylist["data"][i]["explicit"]
        std::cout << "  | " << std::endl;
    }

    //cout << ">mit Enter zurueck zum Hauptmenue...";
    //std::string temp;
    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //cin.get();
    if(!justprint) {
        mywaitenter();
        main_menu();
    }
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
    std::cout << "Name der neuen Playlist eingeben: ";
    std::cin >> filenamecreatefile;//if (strcasecmp(answer3, "beenden") == 0) {exit(0);}//programm beenden! ------------ DAS HIER UEBERALL KOPIEREN WO TEXT EINGELESEN WIRD!!
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
        std::cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
        if (std::cin >> length) {//integer wurde eingegeben
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //^^input wird ignoriert. warum schon wieder so kompliziert??!?
            std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
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
        std::cout << length << " Songs werden zu >" << filenamecreatefile << "< hinzugefuegt. Fortfahren? (Ja/Nein):";//fragen, ob er fortfahren will?
        std::cin >> answer;
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
    std::cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << std::endl;

    //brauchen wir diesen zwischenschritt ueberhaupt oder koennen wir die daten direkt an writefile uebergeben??
    //fuer jetzt behalten wir ihn, da wir probleme mit dem schreiben in die datei haben!! vllt spaeter entfernen? stichwort 'optimisation'
    std::memset(answer, 0, sizeof(answer));
    for(int i=0; i<length; i++) {
        //cout << "\t----------------------------------" << endl;
        mydashedline();
        std::cout << "Informationen fuer Song [" << i+1 << "] eingeben:" << std::endl;
        std::cout << "Songname: "; std::cin >> title[i];
        std::cout << "Interpret: "; std::cin >> artist[i];
        std::cout << "Album: "; std::cin >> album[i];
        repeat=true;
        while (repeat) {std::cout << "Erscheinungsjahr: ";
            if (std::cin >> tempyear) {//integer wurde eingegeben
                if(tempyear>0) {repeat=false;year[i]=tempyear;}//success!
            } else {
                std::cin.clear();//input wird geloescht
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //^^input wird ignoriert. warum schon wieder so kompliziert??!? / und ist er nicht eigentlich schon geloescht??
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;}
        }
        std::cout << "Laenge [xx:xx]: "; std::cin >> duration[i];
        std::cout << "Musikrichtung: "; std::cin >> genre[i];
        repeat=true;
        while (repeat) {std::cout << "Jugendfrei (Ja/Nein): "; std::cin >> answer;
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
    std::cout << "Daten werden in Datei geschrieben" << std::endl;
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
            std::cout << "Datei konnte nicht geoeffnet werden, um Datenn zu speichern! Fehlercode: 04" << std::endl;
            //main_menu();//vorerst zurueck zum mainmenu. speater muss hier eine loesung gefunden werden.
            //zum beispiel erneute abfrage nach dateinamen und versuch die bereits eingelesenen daten dotz zu speichern.
            //"wollen sie das speichern erneut versuchen? (ja/nein)"
            
        repeat2=true;
        while(repeat2) {
            std::cout << "Erneut mit anderem Dateinamen versuchen? (Ja/Nein): ";
            std::cin >> answer;
            myexit(answer);

            if (strcasecmp(answer, "ja") == 0) {//er will es nochmal versuchen. viel glueck!
                repeat2=false;
                std::string tempanswer;
                std::cout << "Geben sie einen alternativen Dateinamen ein:";
                std::cin >> tempanswer;
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
    mydashedline();
    std::cout << "Name der zu loeschenden Playlist eingeben: ";
    std::cin >> answer;
    //hier nicht myexit(answer); - user soll eine playlist namens beenden loeschen duerfen. zurueck zum menue, dann beenden ist auch noch im naechsten schritt moeglich!

    std::string filenamedeletefile(answer);
    //da wir hier dateien loeschen mussen wir sehr vorsichtig sein!! der benutzer koennte auf andere ordner zugreifen!!!
    if (filenamedeletefile.find("/") != std::string::npos || filenamedeletefile.find("\\") != std::string::npos) {//zwei backslashes wil backslash benutzt wird um spezielle charakter darzustellen! '//' ==> /
        std::cout << "Fehler! Nicht erlaubte Zeichen eingegeben. Fehlercode: 05"<<std::endl;
        mywaitenter();
        main_menu();
    }

    //.json an datei anfuegen, falls noch nicht vorhanden
    if (filenamedeletefile.find(".json") != std::string::npos) {

    } else {
        filenamedeletefile = filenamedeletefile + ".json";
    }
    //pfad (playlists/) vor dateinamen anfuegen
    filenamedeletefile=mypath+filenamedeletefile;
    //cout << "test1231:" << filenamedeletefile;

    repeat=true;
    while(repeat) {
        std::cout << "Die Playlist >" << filenamedeletefile << "< wird geloescht! Fortfahren? (Ja/Nein): ";
        std::cin >> answer;
        myexit(answer);
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
    //cout <<"testtest: " << filenamedeletefilec << endl;//testtest

    if (std::remove(filenamedeletefilec) != 0) {
        std::cout << "Fehler! Die Datei konnte nicht geloescht werden. Fehlercode: 06" << std::endl;
        mywaitenter();
        main_menu();
    } else {
        mydashedline();
        std::cout << "\tDie Datei wurde erfolgreich geloescht!" << std::endl;
        mywaitenter();
        main_menu();    
    }
}

void mysearchfile() {
    //dateien in arrays einlesen, oder direkt aus den dateien?
    //wo lese ich die datei aus? erst hier und es koennten unerwartete fehler auftauchen, oder soll ich sie schon beim oeffnen auslesen???
    //wenn wir schon eine datei einlesen muessen, sollen wir dann nicht nach dateinamen fragen, wie bei den anderen funktionen? etwas sinnlos und nicht sehr bedienfreundlich, dann auf die aktuelle datei zu bestehen, nicht?
    //^^^^^so machen wir es!!
    std::memset(answer, 0, sizeof(answer));
    mydashedline();

    
    //gerade ist keine datei geoeffnet, was passiert hier aber, wenn eine ungueltige geoeffnet ist? nichts, da durch myopenfile() nur gueltige dateien geoeffnet werden koennen??
    //if (filename=="") {
    //    cout << "Fehler! Momentan ist keine Datei geoeffnet. Fehlercode: 03" << endl;
    //    mydashedline();
    //    mywaitenter();
    //    main_menu();
    //}
    std::string filenamesearchfile;


    repeat=true;//waere schon lustig wenn man das hier vergisst und dann an dem gesamten code zweifelt...
    while (repeat) {

        std::cout << "Name der zu durchsuchenden Playlist eingeben: ";
        std::cin >> answer;
        //hier myexit(answer); ???????

        std::string filenamesearchfile2(answer);
        filenamesearchfile = filenamesearchfile2;//komm schon c++, was fuer ein schwachsinn... nur dass die datei spaeter noch sichtbar ist
        //.json an datei anfuegen, falls noch nicht vorhanden
        if (filenamesearchfile.find(".json") != std::string::npos) {

        } else {
            filenamesearchfile = filenamesearchfile + ".json";
        }//pfad (playlists/) vor dateinamen anfuegen
        filenamesearchfile=mypath+filenamesearchfile;


        std::memset(answer, 0, sizeof(answer));
        repeat2=true;
        while(repeat2) {
            std::cout << "Die Datei >" << filenamesearchfile << "< wird durchsucht. Fortfahren? (ja/nein): ";
            std::cin >> answer;
            myexit(answer);
            if (strcasecmp(answer, "ja") == 0) {
                repeat2 = false;

            } if (strcasecmp(answer, "nein") == 0) {
                repeat2 = false;
                main_menu();
            }
        }
        //jetzt kann endlich durchsucht werden!!! NAJA, zuerst muss datei erfolgreich! geoeffnent werden!!

        //mycheckifopen(tempfilenamechar);brauchen wir hier nicht, weil die datei ja sowieso ausgelesen werden muss!
        std::cout << "Die Datei " << filenamesearchfile << " wird geoeffnet." << std::endl;
        //stand jetzt haben wir einen vielleicht gueltigen dateiname. datei wird nun geoeffnet
        try {
            std::ifstream file(filenamesearchfile);//koennte es hier probleme geben, wenn die datei auch file heisst? Nein, sie ist lokal zum try block, wie auch die andere.
            //oeffnen der .json datei^^ (in einem sicheren umfeld --> kein absturz)
            if (!file.is_open()) {
                std::cerr << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            repeat = false;

            file >> searchplaylist;//Datei wird eingelesen
            file.close();//Datei wird geschlossen
            std::cout << "\tDie Datei wurde geoeffnet" << std::endl; //erst hier ist die datei erfolgreich geoeffnet!!
            mydashedline();
        } catch (const std::exception& e) {
            repeat = true;//erneut versuchen, da fehler
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << std::endl << e.what() << std::endl;
            mydashedline();
            //hier gab es einen fehler beim einlesen? der datei. zum bsp war sie leer ->siehe test2.json
            //("wenden sie sich mit folgender fehlermeldung an den support")?
        }
    }

    //cout << "playlist zum test:" << searchplaylist << endl;

    //jetzt koennen wir endlich durchsuchen!
    repeat=true;
    bool firstrun=true;
    std::string searchstring;
    while (repeat) {
        
        if(!firstrun) {
            mydashedline();
            repeat2=true;
            while(repeat2) {
                std::cout << "Datei >" << filenamesearchfile << "< erneut durchsuchen? (ja/nein): ";
                std::cin >> answer;
                myexit(answer);
                if (strcasecmp(answer, "ja") == 0) {
                    repeat2 = false;

                } if (strcasecmp(answer, "nein") == 0) {
                    repeat2 = false;
                    main_menu();
                }
            }
        }
        firstrun=false;//nach dem ersten durchlauf wird jetzt grfragt, ob erneut durchsucht werden soll.

        //cout << "testendeschleife" << searchplaylist << endl;
        //while true schleife, um weitere suchen zu ermoeglichen! mit irgendeiner variable, damit beim ersten mal nicht gefragt wird ob man nochmal suchen will!
        std::cout << "Achtung! Keine Sonderzeichen! Ausnahme Doppelpunkt." << std::endl;
        //mydashedline();
        std::cout << "Geben sie einen Suchbegriff ein: ";
        std::cin >> answer;
        searchstring = std::string(answer);//searchstring = "\"" + std::string(answer) + "\"";
        std::memset(answer, 0, sizeof(answer));

        std::replace(searchstring.begin(), searchstring.end(), ':', '_');//nun kann nach der laenge gesucht werden!
        std::replace(searchstring.begin(), searchstring.end(), ' ', '_');//und nach alben/titeln, die mehrere woerter umfassen! /normalerweise wuerde das schiefgehen, weil mehrere schritte vorgesprungen wird. hier egal, da alle schritte gleich sind((ja/nein) abfrage)!
        //cout << "--------" << searchstring << endl;

        //cout << "test. laenge:" << searchplaylist.size() << endl;
        //cout << searchstring << " | " << searchplaylist["data"][0]["artist"] << endl;
        
        //for(int i=0; i<(searchplaylist.size()+1); i++) {
        //    //if(searchstring==searchplaylist["data"][i]["title"]) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    if(strcasecmp(searchstring, searchplaylist["data"][i]["title"])) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    else if(strcasecmp(searchstring, searchplaylist["data"][i]["artist"])) {cout<<"Gefunden! Suche entspricht dem Interpreten von Song Nr. "<<i+1<<endl;}
        //    else if(strcasecmp(searchstring, searchplaylist["data"][i]["album"])) {cout<<"Gefunden! Suche entspricht dem Album von Song Nr. "<<i+1<<endl;}
        //    else if(strcasecmp(searchstring, searchplaylist["data"][i]["date"])) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
        //    else if(strcasecmp(searchstring, searchplaylist["data"][i]["length"])) {cout<<"Gefunden! Suche entspricht der Laenge von Song Nr. "<<i+1<<endl;}
        //    else if(strcasecmp(searchstring, searchplaylist["data"][i]["genre"])) {cout<<"Gefunden! Suche entspricht dem Genre von Song Nr. "<<i+1<<endl;}
        //    //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
        //    else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden!" << endl;}
        //}//also muessen wir es doch auslesen??
        
        //for(int i=0; i<(searchplaylist.size()+1); i++) {
        //    if(searchstring==searchplaylist["data"][i]["title"]) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    else if(searchstring==searchplaylist["data"][i]["artist"]) {cout<<"Gefunden! Suche entspricht dem Interpreten von Song Nr. "<<i+1<<endl;}
        //    else if(searchstring==searchplaylist["data"][i]["album"]) {cout<<"Gefunden! Suche entspricht dem Album von Song Nr. "<<i+1<<endl;}
        //    //else if(searchstring==searchplaylist["data"][i]["date"]) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
        //    else if(searchstring==searchplaylist["data"][i]["length"]) {cout<<"Gefunden! Suche entspricht der Laenge von Song Nr. "<<i+1<<endl;}
        //    else if(searchstring==searchplaylist["data"][i]["genre"]) {cout<<"Gefunden! Suche entspricht dem Genre von Song Nr. "<<i+1<<endl;}
        //    //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
        //    else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden!" << endl;}
        //}

        //for(int i=0; i<(searchplaylist.size()+1); i++) {
        //    if(searchplaylist["data"][i]["title"].find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    else if(searchplaylist["data"][i]["artist"].find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Interpreten von Song Nr. "<<i+1<<endl;}
        //    else if(searchplaylist["data"][i]["album"].find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Album von Song Nr. "<<i+1<<endl;}
        //    else if(searchplaylist["data"][i]["date"].find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
        //    else if(searchplaylist["data"][i]["length"].find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht der Laenge von Song Nr. "<<i+1<<endl;}
        //    else if(searchplaylist["data"][i]["genre"].find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Genre von Song Nr. "<<i+1<<endl;}
        //    //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
        //    else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden!" << endl;}
        //}//ich fuerchte wir muessen es wirklich auslesen :(

        //for(int i=0; i<(searchplaylist.size()+1); i++) {
        //    std::string str1(searchplaylist["data"][i]["title"]);
        //    std::string str2(searchplaylist["data"][i]["artist"]);
        //    std::string str3(searchplaylist["data"][i]["album"]);
        //    //std::string str4(searchplaylist["data"][i]["date"]);
        //    std::string str5(searchplaylist["data"][i]["length"]);
        //    std::string str6(searchplaylist["data"][i]["genre"]);
        //    
        //    if(str1.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    else if(str2.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Interpreten von Song Nr. "<<i+1<<endl;}
        //    else if(str3.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Album von Song Nr. "<<i+1<<endl;}
        //    //else if(str4.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
        //    else if(str5.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht der Laenge von Song Nr. "<<i+1<<endl;}
        //    else if(str6.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Genre von Song Nr. "<<i+1<<endl;}
        //    //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
        //    else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << endl;}
        //}//ahhhhh
        
        //const char* searchchar;
        //searchchar = searchstring.c_str();
        //cout << searchstring << endl;

        //for(int i=0; i<(searchplaylist.size()+1); i++) {
        //    //std::string str1(searchplaylist["data"][i]["title"]);
        //    //std::string str2(searchplaylist["data"][i]["artist"]);
        //    //std::string str3(searchplaylist["data"][i]["album"]);
        //    //std::string str4(searchplaylist["data"][i]["date"]);
        //    //std::string str5(searchplaylist["data"][i]["length"]);
        //    //std::string str6(searchplaylist["data"][i]["genre"]);
        //    
        //    if(std::strchr(searchchar, searchplaylist["data"][i]["title"])!=nullptr) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    else if(std::strchr(searchchar, searchplaylist["data"][i]["artist"])!=nullptr) {cout<<"Gefunden! Suche entspricht dem Interpreten von Song Nr. "<<i+1<<endl;}
        //    else if(std::strchr(searchchar, searchplaylist["data"][i]["album"])!=nullptr) {cout<<"Gefunden! Suche entspricht dem Album von Song Nr. "<<i+1<<endl;}
        //    //else if(str4.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
        //    else if(std::strchr(searchchar, searchplaylist["data"][i]["length"])!=nullptr) {cout<<"Gefunden! Suche entspricht der Laenge von Song Nr. "<<i+1<<endl;}
        //    else if(std::strchr(searchchar, searchplaylist["data"][i]["genre"])!=nullptr) {cout<<"Gefunden! Suche entspricht dem Genre von Song Nr. "<<i+1<<endl;}
        //    //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
        //    else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << endl;}
        //}//ahhhhh2

        //for(int i=0; i<(searchplaylist.size()+1); i++) {
        //    char char1 = searchplaylist["data"][i]["title"].get<std::string>()[0];
        //    char char2 = searchplaylist["data"][i]["artist"].get<std::string>()[0];
        //    char char3 = searchplaylist["data"][i]["album"].get<std::string>()[0];
        //    //char char4 = searchplaylist["data"][i]["date"].get<std::string>()[0];
        //    char char5 = searchplaylist["data"][i]["length"].get<std::string>()[0];
        //    char char6 = searchplaylist["data"][i]["genre"].get<std::string>()[0];
        //    
        //    if(std::strchr(searchchar, char1)!=nullptr) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    else if(std::strchr(searchchar, char2)!=nullptr) {cout<<"Gefunden! Suche entspricht dem Interpreten von Song Nr. "<<i+1<<endl;}
        //    else if(std::strchr(searchchar, char3)!=nullptr) {cout<<"Gefunden! Suche entspricht dem Album von Song Nr. "<<i+1<<endl;}
        //    //else if(str4.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
        //    else if(std::strchr(searchchar, char5)!=nullptr) {cout<<"Gefunden! Suche entspricht der Laenge von Song Nr. "<<i+1<<endl;}
        //    else if(std::strchr(searchchar, char6)!=nullptr) {cout<<"Gefunden! Suche entspricht dem Genre von Song Nr. "<<i+1<<endl;}
        //    //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
        //    else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << endl;}
        //}//ahhhhh3? NEIN! es funktioniert!!!!
        //aber wir brauchen es non case-sensitive!!!!
        
        //const char* searchchar;
        //searchchar = searchstring.c_str();
        //cout << searchstring << endl;
        //cout << searchchar << endl;
        //char searchchar2 = *searchchar;
//
        //for(int i=0; i<(searchplaylist.size()+1); i++) {
        //    searchchar2 = std::tolower(searchchar2);
//
        //    char charplaylist1=searchplaylist["data"][i]["title"].get<std::string>()[0];
        //    char char1 = std::tolower(charplaylist1);
        //    char charplaylist2=searchplaylist["data"][i]["artist"].get<std::string>()[0];
        //    char char2 = std::tolower(charplaylist2) ;
        //    char charplaylist3=searchplaylist["data"][i]["album"].get<std::string>()[0];
        //    char char3 = std::tolower(charplaylist3);
        //    //char char4 = searchplaylist["data"][i]["date"].get<std::string>()[0];
        //    char charplaylist5=searchplaylist["data"][i]["length"].get<std::string>()[0];
        //    char char5 = std::tolower(charplaylist5) ;
        //    char charplaylist6=searchplaylist["data"][i]["genre"].get<std::string>()[0];
        //    char char6 = std::tolower(charplaylist6);
//
//
        //    //char char1 = std::tolower(searchplaylist["data"][i]["title"].get<std::string>()[0]);
        //    //char char2 = std::tolower(searchplaylist["data"][i]["artist"].get<std::string>()[0]);
        //    //char char3 = std::tolower(searchplaylist["data"][i]["album"].get<std::string>()[0]);
        //    ////char char4 = searchplaylist["data"][i]["date"].get<std::string>()[0];
        //    //char char5 = std::tolower(searchplaylist["data"][i]["length"].get<std::string>()[0]);
        //    //char char6 = std::tolower(searchplaylist["data"][i]["genre"].get<std::string>()[0]);
//
        //    //const char* char1Str = std::string(1, char1).c_str();
        //    //const char* char2Str = std::string(1, char2).c_str();
        //    //const char* char3Str = std::string(1, char3).c_str();
        //    ////const char* char4Str = std::string(1, char4).c_str();
        //    //const char* char5Str = std::string(1, char5).c_str();
        //    //const char* char6Str = std::string(1, char6).c_str();
        //    
        //    cout << searchchar2 << " | " << char1 << endl;
//
        //    if(searchchar2==char1) {cout<<"Gefunden! Suche entspricht dem Titel von Song Nr. "<<i+1<<endl;}
        //    else if(searchchar2==char2) {cout<<"Gefunden! Suche entspricht dem Interpreten von Song Nr. "<<i+1<<endl;}
        //    else if(searchchar2==char3) {cout<<"Gefunden! Suche entspricht dem Album von Song Nr. "<<i+1<<endl;}
        //    //else if(str4.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
        //    else if(searchchar2==char5) {cout<<"Gefunden! Suche entspricht der Laenge von Song Nr. "<<i+1<<endl;}
        //    else if(searchchar2==char6) {cout<<"Gefunden! Suche entspricht dem Genre von Song Nr. "<<i+1<<endl;}
        //    //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
        //    else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << endl;}
        //}//jetzt geht garnichts mehr


        const char* searchchar;
        searchchar = searchstring.c_str();
        //cout << searchstring << endl;
        //cout << searchstring << " | " << searchplaylist["data"][0]["artist"] << endl;
        std::cout << "\t\t*******" << std::endl;
        //hoffentlich letzter versuch. JAAAAA //playlist zum test ist in line 635 falls sie je wieder gebraucht wird
        for(int i=0; i<(searchplaylist.size()+1); i++) {
            std::transform(searchstring.begin(), searchstring.end(), searchstring.begin(), ::tolower);
            //anfuehrungszeichen aus searchstring entfernen --> line 665 commented

            std::string str1(searchplaylist["data"][i]["title"]);
            std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
            std::string str2(searchplaylist["data"][i]["artist"]);
            std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
            std::string str3(searchplaylist["data"][i]["album"]);
            std::transform(str3.begin(), str3.end(), str3.begin(), ::tolower);
            //char char4 = searchplaylist["data"][i]["date"].get<std::string>()[0];
            std::string str5(searchplaylist["data"][i]["length"]);
            std::transform(str5.begin(), str5.end(), str5.begin(), ::tolower);
            std::string str6(searchplaylist["data"][i]["genre"]);
            std::transform(str6.begin(), str6.end(), str6.begin(), ::tolower);
            
            //cout << str1 << " | " << searchstring << endl;//tettsetsetsetstetsettesttest

            bool unabletolocate=true;//auf die art koennen mehrere eintraege durchsucht werden. zum beispiel titel und album
            if(str1.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Titel von Song Nr. "<<i+1<<"! -- >"<<str1<<"<"<<std::endl; unabletolocate=false;}
            if(str2.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Interpreten von Song Nr. "<<i+1<<"! -- >"<<str2<<"<"<<std::endl; unabletolocate=false;}
            if(str3.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Album von Song Nr. "<<i+1<<"! -- >"<<str3<<"<"<<std::endl; unabletolocate=false;}
            //else if(str4.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
            if(str5.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht der Laenge von Song Nr. "<<i+1<<"! -- >"<<str5<<"<"<<std::endl; unabletolocate=false;}
            if(str6.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Genre von Song Nr. "<<i+1<<"! -- >"<<str6<<"<"<<std::endl; unabletolocate=false;}
            //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
            if(unabletolocate) {std::cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << std::endl;}

            //if(str1.find(searchchar) != std::string::npos) {cout<<"Suchbegriff entspricht dem Titel von Song Nr. "<<i+1<<"! >"<<str1<<"<"<<endl;}
            //else if(str2.find(searchchar) != std::string::npos) {cout<<"Suchbegriff entspricht dem Interpreten von Song Nr. "<<i+1<<"! >"<<str2<<"<"<<endl;}
            //else if(str3.find(searchchar) != std::string::npos) {cout<<"Suchbegriff entspricht dem Album von Song Nr. "<<i+1<<"! >"<<str3<<"<"<<endl;}
            ////else if(str4.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
            //else if(str5.find(searchchar) != std::string::npos) {cout<<"Suchbegriff entspricht der Laenge von Song Nr. "<<i+1<<"! >"<<str5<<"<"<<endl;}
            //else if(str6.find(searchchar) != std::string::npos) {cout<<"Suchbegriff entspricht dem Genre von Song Nr. "<<i+1<<"! >"<<str6<<"<"<<endl;}
            ////else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
            //else {cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << endl;}
        }//ahhhhh3? NEIN! es funktioniert!!!!??? JAAAAAAAAAAAAAA
        

    }

    //ganz am ende zurueck zum hauptmenue
    main_menu();
}

void myeditfile(int select) {
    //myprintfile direkt ausfuehren?
    //std::cout << "Hier koennen die Details von Songs bearbeitet werden." << std::endl;
    
    //numerierungen
    //z.b. daten des songs bearbeiten - 1 |  song loeschen - 2 | haupemenue - 3
    //fuer 1    Details editieren: titel - 1 | interpret - 2 | album - 3 | ...
    //^^^diese werden dann umbenannt?! es wird nach einer eingabe gefragt, die den aktuellen wert ersetzt
    
    //HIER GEHT DIE FUNKTION LOS
    std::string filenameeditfile;
    
    myopenfile(true);
    //std:cout << "CURRENTPLAYLIST.SIZE =" << currentplaylist["data"].size() << std::endl;
    
    //myprintfile(true);
    mydashedline();
    //std::cout << "testestetsetstestestetsetstetsetstestetst" << std::endl;
    /*
    repeat=true;
    while (repeat) {
        std::memset(answer, 0, sizeof(answer));
        std::cout << "Name der zu bearbeitenden Playlist eingeben: ";
        std::cin >> answer;
        
        std::string filenameeditfile2(answer);
        filenameeditfile = filenameeditfile2;
        //.json an datei anfuegen, falls noch nicht vorhanden
        if (filenameeditfile.find(".json") != std::string::npos) {

        } else {
            filenameeditfile = filenameeditfile + ".json";
        }//pfad (playlists/) vor dateinamen anfuegen
        filenameeditfile=mypath+filenameeditfile;


        //std::memset(answer, 0, sizeof(answer));
        //repeat2=true;
        //while(repeat2) {
        //    std::cout << "Die Datei >" << filenameeditfile << "< wird durchsucht. Fortfahren? (ja/nein): ";
        //    std::cin >> answer;
        //    myexit(answer);
        //    if (strcasecmp(answer, "ja") == 0) {
        //        repeat2 = false;
//
        //    } if (strcasecmp(answer, "nein") == 0) {
        //        repeat2 = false;
        //        main_menu();
        //    }
        //}

        std::cout << "Die Datei " << filenameeditfile << " wird geoeffnet." << std::endl;
        //stand jetzt haben wir einen vielleicht gueltigen dateiname. datei wird nun geoeffnet
        try {
            std::ifstream file(filenameeditfile);//koennte es hier probleme geben, wenn die datei auch file heisst? Nein, sie ist lokal zum try block, wie auch die andere.
            //oeffnen der .json datei^^ (in einem sicheren umfeld --> kein absturz)
            if (!file.is_open()) {
                std::cerr << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            repeat = false;

            file >> currentplaylist;//Datei wird eingelesen
            //file.close();//Datei wird  NEIN! wir brauchen die datei ja noch!
            std::cout << "\tDie Datei wurde geoeffnet" << std::endl; //erst hier ist die datei erfolgreich geoeffnet!!
            mydashedline();
        } catch (const std::exception& e) {
            repeat = true;//erneut versuchen, da fehler
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << std::endl << e.what() << std::endl;
            mydashedline();
            //hier gab es einen fehler beim einlesen? der datei. zum bsp war sie leer ->siehe test2.json
            //("wenden sie sich mit folgender fehlermeldung an den support")?
        }
    }
    */
    //std::cout << "TEST laeuft es noch?" << std::endl;

    int playlistsize = currentplaylist["data"].size();//playlistgroesse fuer song hinzufuegen
    if(select==2) {playlistsize-=1;}//                  -----------||----------   bearbeiten
    if(select==3) {playlistsize-=2;}//                  -----------||----------   loeschen
    
    std::cout << "playlistsize:" << playlistsize << std::endl;

    //brauchen wir nur bei >songs hinzufuegen. koennen wir das nicht auch direkt in die datei schreiben??
    //direkt in myopenfile() auslesen geht nicht, da wir hier ggfs. groesse der arrays erhoehen muessen!!!
    char title[playlistsize+1][25] = {};
    char artist[playlistsize+1][25] = {};
    char album[playlistsize+1][25] = {};
    int year[playlistsize+1];// int erscheinungsjahr
    char duration[playlistsize+1][5] = {};
    char genre[playlistsize+1][25] = {};
    bool badwords[playlistsize+1];//    true/false
    //std::cout <<"testtesttest" << std::endl;
    for (int f = 0; f<playlistsize; f++) {//ich versuche sicherzustellen, dass es keine probleme beim speichern gibt
        for (int f2 = 0; f2<5; f2++) {
            duration[f][f2]='\0';
        }
    }

    
    std::string temptitle;
    std::string tempartist;
    std::string tempalbum;
    std::string tempduration;
    std::string tempgenre;
    for(int i=0; i<(playlistsize); i++) {//+1); i++) {//playlistsize+1 ist groesse des arrays! Wir koennen aber nicht mit ihr auslesen, da das letzte element der song ist, der hier hinzugefuegt werden soll!!
        temptitle = currentplaylist["data"][i]["title"];
        std::strcpy(title[i], temptitle.c_str());
        //std::cout << "test1" << std::endl;
        tempartist = currentplaylist["data"][i]["artist"];
        std::strcpy(artist[i], tempartist.c_str());
        //std::cout << "test2" << std::endl;
        tempalbum = currentplaylist["data"][i]["album"];
        std::strcpy(album[i], tempalbum.c_str());
        //std::cout << "test3" << std::endl;
        tempduration = currentplaylist["data"][i]["length"];
        //std::cout << "test3.5" << std::endl;
        std::strcpy(duration[i], tempduration.c_str());
        //std::cout << "test4" << std::endl;
        tempgenre = currentplaylist["data"][i]["genre"];
        std::strcpy(genre[i], tempgenre.c_str());
        //std::cout << "test5" << std::endl;

        //for(int i2=0; i2<25; i2++) {
        //    title[i][i2]=temptitle[i2];
        //    artist[i][i2]=tempartist[i2];
        //    album[i][i2]=tempalbum[i2];
        //    duration[i][i2]=tempduration[i2];
        //    genre[i][i2]=tempgenre[i2];
        //}
    }
    //std::cout << "test2--test2" << std::endl;
    

    //----------------------------------------------------------------------------------------------------------------------
/*
    for (int e = 0; e < playlistsize; e++) {
    mydashedline();
    std::cout << "Output for i=" << e << std::endl;
    std::cout << "title[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << title[e][e2];
    }
    std::cout << std::endl;

    std::cout << "artist[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << artist[e][e2];
    }
    std::cout << std::endl;

    std::cout << "album[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << album[e][e2];
    }
    std::cout << std::endl;

    std::cout << "year[" << e << "]: " << year[e] << std::endl;

    std::cout << "duration[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << duration[e][e2];
    }
    std::cout << std::endl;

    std::cout << "genre[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << genre[e][e2];
    }
    std::cout << std::endl;

    std::cout << "badwords[" << e << "]: " << badwords[e] << std::endl;
}
*/
    //----------------------------------------------------------------------------------------------------------------------



    int songposition=0;
    if(select==2||select==3) {
        myprintfile(true);
        repeat=true;
        while(repeat) {
            //std::memset(answer, 0, sizeof(answer));
            if(select==2) {
                std::cout << "Welche Songnummer soll bearbeitet werden?: ";
            } else {
                std::cout << "welche Songnummer soll geloescht werden?: ";
            }
            if(std::cin >> songposition) {
                if(songposition>0) {//Zahlen positiv
                    //if(songposition<(currentplaylist.size()+1)) {//passt doch.
                    if(songposition<currentplaylist["data"].size()+1) {
                        repeat=false;
                        songposition-=1;//sehr wichtig, da die zahlen in c++ bei 0, nicht 1 beginnen!!!!!
                    } else {//Zahl groesser als anzahl der eintraege in der Playlist
                        std::cout << "\tEingegebene Zahl ist zu gross!" << std::endl;
                    }
                } else {//Zahlen negativ
                    std::cout << "\tNegative Zahlen sind nicht zulaessig!" << std::endl;
                }
            } else {
                std::cin.clear();//hier muss der input ignoriert werden, damit c++ nicht ausrastet (char assigned to int)
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\t Buchstaben/Sonderzeichen sind nicht zulaessig!" << std::endl;
            }
            
            //if(answer>0 && answer<(currentplaylist.size()+1)) {
            //repeat=false;
        }
        std::cout << "Songposition: " << songposition << std::endl;
        
/*
while (repeat) {
        std::cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
        if (std::cin >> length) {//integer wurde eingegeben
        //cout <<"111";//test
            if(length>0) {repeat=false;}//integer ist größer als 0 -- also passt alles!!
        } else {
            std::cin.clear();
            //^^input wird geloescht
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //^^input wird ignoriert. warum schon wieder so kompliziert??!?
            std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
        }
    }
*/

    }



    int tempyear=0;
    //int tempi=currentplaylist.size();//current playlist.size gibt groesse beginnend mit 0 aus. z.B. 5 elemente (0 bis 4) = 5. Wir sind also schon am schluss und brauchen keine weiteren schritte!!
    //int tempi=currentplaylist["data"].size();//^^falsch!
    int tempi =playlistsize;
    switch(select) {
        case 1:
        //song hinzufuegen
        //song wird einfach am ende angefuegt, muss nicht hochkomplex werden, wenn es auch einfach geht!!
        //mydashedline();
        std::cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << std::endl;


        std::memset(answer, 0, sizeof(answer));

        mydashedline();
        std::cout << "Informationen fuer neuen Song eingeben:" << std::endl;
        std::cout << "Songname: "; std::cin >> title[tempi];
        std::cout << "Interpret: "; std::cin >> artist[tempi];
        std::cout << "Album: "; std::cin >> album[tempi];
        repeat=true;
        while (repeat) {std::cout << "Erscheinungsjahr: ";
            if (std::cin >> tempyear) {//zahl eingegebe
                if(tempyear>0) {repeat=false;year[tempi]=tempyear;}//success!n
            } else {
                std::cin.clear();//input wird geloescht
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //input ignorieren, falls keine zahl
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;}
        }
        std::cout << "Laenge [xx:xx]: "; std::cin >> duration[tempi];
        std::cout << "Musikrichtung: "; std::cin >> genre[tempi];
        repeat=true;
        while (repeat) {std::cout << "Jugendfrei (Ja/Nein): "; std::cin >> answer;
            //myexit(answer4);//brauchen wir das? ich lasse es drin bis wir die bestaetigung am anfang haben?!
            if (strcasecmp(answer, "ja") == 0) {repeat=false;badwords[tempi]=false;}
            if (strcasecmp(answer, "nein") == 0) {repeat=false;badwords[tempi]=true;}
        }

            for (int i = 0; i<5; i++) {
                if (duration[tempi][i] == ':') {
                    duration[tempi][i] = '_'; // Replace colon with underscore
                }
            }
        
            mydashedline();
            //mydashedline();
            //for (int i = 0; i<5; i++) {
            //    cout << "duration["<<tempi<<"]["<<i<<"]:  ";
            //    cout << duration[tempi][i]<< endl;
            //}
            //mydashedline();


        break;
        case 2:
      //song bearbeiten
        
        break;
        case 3:
        //song loeschen
        //myprintfile(true);
        break;
        default:
        song_management();
        break;//???
    }//         ----------------------------    stimmt hier etwas nicht???  Ja. jetzt behoben

    if(select==2) {
        

        
        //songposition gibt position des songs (vgl. i) an
        mydashedline();
        std::cout << "---Daten von Song Nr. " << (songposition+1) << " aendern oder bestaetigen(Enter)---" << std::endl;//  +1 von computer zaehlen in menschen zaehlen!!
        //      Abfrage, ob fortgefahren werden soll???---
        std::string tempstr;
        char ch;
        bool abort=false;
        //repeat=true;
        
            std::cout << "Titel: " << title[songposition] << std::endl;
            std::cout << title[songposition];

            while(std::cin.get(ch)) { // schleife, bis
                if (ch == '\n') { // wenn enter taste
                    break;//schleife wird unterbrochen und momentaner string (ueberprueft) und dann eingelesen
                } else if (ch == '\033') { // besondere faelle, wie pfeiltasten
                    abort = true;
                } else if (abort) {
                    // pfeiltasten
                    abort = false;
                } else if (ch == '\b') { // zurzeck taste/backspace
                    if (!tempstr.empty()) {//wenn noch buchstaben vorhanden sind
                        tempstr.pop_back();//werden sie aus dem string
                        std::cout << "\b \b"; // und dann aus dem terminal geloescht
                    }
                } else {
                    tempstr += ch;
                    std::cout << ch;
                }
            }
        
        
        std::cout << std::endl;
        std::cout << "      test: " << title[songposition] << std::endl;
        std::strcpy(title[songposition], tempstr.c_str());
        std::cout << "      test: " << title[songposition] << std::endl;
    //fertig, pruefen, ob dateiname gueltig ist (keine leerzeichen, sonderzeichen)/oder diese direkt ersetzen, statt fehler zu werdfen!
        
    //------------------------------------------------------------------------------------------------------------------------------------    

        std::cout << "Interpret: " << artist[songposition] << std::endl;
        std::cout << artist[songposition];
        /*
        while ((ch = getch()) != '\r') { // enter beendet die schleife, und damit auch die eingabe!
            if (ch == '\b') { // zurueck taste/backspace
                if (!tempstr.empty()) {
                    std::cout << "\b \b"; // wenn eingabe noch nicht leer ist wird im terminal ein charakter geloescht
                    tempstr.pop_back(); //  -----------------------||---------------- string ein charakter geloescht
                }
            } else {
                std::cout << ch;
                tempstr += ch; // kein backspace --> eingabe. eingabe wird angefuegt/.
            }
        }
        std::cout << std::endl;
        std::cout << "      test: " << artist[songposition] << std::endl;
        std::strcpy(artist[songposition], tempstr.c_str());
        std::cout << "      test: " << artist[songposition] << std::endl;
    //fertig, pruefen, ob dateiname gueltig ist (keine leerzeichen, sonderzeichen)/oder diese direkt ersetzen, statt fehler zu werdfen!
        
    //------------------------------------------------------------------------------------------------------------------------------------    

        std::cout << "Album: " << album[songposition] << std::endl;
        std::cout << album[songposition];
        
        while ((ch = getch()) != '\r') { // enter beendet die schleife, und damit auch die eingabe!
            if (ch == '\b') { // zurueck taste/backspace
                if (!tempstr.empty()) {
                    std::cout << "\b \b"; // wenn eingabe noch nicht leer ist wird im terminal ein charakter geloescht
                    tempstr.pop_back(); //  -----------------------||---------------- string ein charakter geloescht
                }
            } else {
                std::cout << ch;
                tempstr += ch; // kein backspace --> eingabe. eingabe wird angefuegt/.
            }
        }
        std::cout << std::endl;
        std::cout << "      test: " << album[songposition] << std::endl;
        std::strcpy(album[songposition], tempstr.c_str());
        std::cout << "      test: " << album[songposition] << std::endl;
    //fertig, pruefen, ob dateiname gueltig ist (keine leerzeichen, sonderzeichen)/oder diese direkt ersetzen, statt fehler zu werdfen!
        
    //------------------------------------------------------------------------------------------------------------------------------------    

        std::cout << "Erscheinungsjahr: " << year[songposition] << std::endl;
        std::cout << year[songposition];
        
        while ((ch = getch()) != '\r') { // enter beendet die schleife, und damit auch die eingabe!
            if (ch == '\b') { // zurueck taste/backspace
                if (!tempstr.empty()) {
                    std::cout << "\b \b"; // wenn eingabe noch nicht leer ist wird im terminal ein charakter geloescht
                    tempstr.pop_back(); //  -----------------------||---------------- string ein charakter geloescht
                }
            } else {
                std::cout << ch;
                tempstr += ch; // kein backspace --> eingabe. eingabe wird angefuegt/.
            }
        }
        std::cout << std::endl;
        //std::strcpy(year[songposition], tempstr.c_str());
    //fertig, pruefen, ob dateiname gueltig ist (keine leerzeichen, sonderzeichen)/oder diese direkt ersetzen, statt fehler zu werdfen!


    //wie wandle ich den integer jetzt um? muss ich wieder eine schleife erstellen, bis ein gueltiget wert vorhanden ist? geht wahrscheinlich nicht anders

    //------------------------------------------------------------------------------------------------------------------------------------    

        std::cout << "Songlaenge: " << duration[songposition] << std::endl;
        std::cout << duration[songposition];

        while ((ch = getch()) != '\r') { // enter beendet die schleife, und damit auch die eingabe!
            if (ch == '\b') { // zurueck taste/backspace
                if (!tempstr.empty()) {
                    std::cout << "\b \b"; // wenn eingabe noch nicht leer ist wird im terminal ein charakter geloescht
                    tempstr.pop_back(); //  -----------------------||---------------- string ein charakter geloescht
                }
            } else {
                std::cout << ch;
                tempstr += ch; // kein backspace --> eingabe. eingabe wird angefuegt/.
            }
        }
        std::cout << std::endl;
        std::strcpy(duration[songposition], tempstr.c_str());
    //fertig, pruefen, ob dateiname gueltig ist (keine leerzeichen, sonderzeichen)/oder diese direkt ersetzen, statt fehler zu werdfen!
        
    //------------------------------------------------------------------------------------------------------------------------------------    


        std::cout << "Genre: " << genre[songposition] << std::endl;
        std::cout << genre[songposition];

        while ((ch = getch()) != '\r') { //enter beendet die schleife, und damit auch die eingabe!
            if (ch == '\b') { // zurueck taste/backspace
                if (!tempstr.empty()) {
                    std::cout << "\b \b"; // wenn eingabe noch nicht leer ist wird im terminal ein charakter geloescht
                    tempstr.pop_back(); //  -----------------------||---------------- string ein charakter geloescht
                }
            } else {
                std::cout << ch;
                tempstr += ch; // kein backspace --> eingabe. eingabe wird angefuegt/.
            }
        }
        std::cout << std::endl;
        std::strcpy(genre[songposition], tempstr.c_str());
    //fertig, pruefen, ob dateiname gueltig ist (keine leerzeichen, sonderzeichen)/oder diese direkt ersetzen, statt fehler zu werdfen!
        
    //------------------------------------------------------------------------------------------------------------------------------------    


        std::cout << "Jugendfrei: " << badwords[songposition] << std::endl;
        //std::cout << badwords[songposition];
        if(badwords[songposition]) {
            std::cout << "Nein";
        } else {
            std::cout << "Ja";
        }

        while ((ch = getch()) != '\r') { // enter beendet die schleife, und damit auch die eingabe!
            if (ch == '\b') { // zurueck taste/backspace
                if (!tempstr.empty()) {
                    std::cout << "\b \b"; // wenn eingabe noch nicht leer ist wird im terminal ein charakter geloescht
                    tempstr.pop_back(); //  -----------------------||---------------- string ein charakter geloescht
                }
            } else {
                std::cout << ch;
                tempstr += ch; // kein backspace --> eingabe. eingabe wird angefuegt/.
            }
        }
        std::cout << std::endl;
        //strcsecmp von eingang und "ja"/"nein", wieder mit schleife, bis ein gueltiger wert kommt.
        //std::strcpy(badwords[songposition], tempstr.c_str());
    //fertig, pruefen, ob dateiname gueltig ist (keine leerzeichen, sonderzeichen)/oder diese direkt ersetzen, statt fehler zu werdfen!
    */
    //------------------------------------------------------------------------------------------------------------------------------------    
    }//ende if(select==2)

    



/*
for (int e = 0; e < playlistsize+1; e++) {
    mydashedline();
    std::cout << "Output for i=" << e << std::endl;
    std::cout << "title[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        //std::cout << title[e][e2];
    }
    std::cout << std::endl;

    std::cout << "artist[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << artist[e][e2];
    }
    std::cout << std::endl;

    std::cout << "album[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << album[e][e2];
    }
    std::cout << std::endl;

    std::cout << "year[" << e << "]: " << year[e] << std::endl;

    std::cout << "duration[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << duration[e][e2];
    }
    std::cout << std::endl;

    std::cout << "genre[" << e << "]: ";
    for (int e2 = 0; e2 < 25; e2++) {
        std::cout << genre[e][e2];
    }
    std::cout << std::endl;

    std::cout << "badwords[" << e << "]: " << badwords[e] << std::endl;
}
*/



    //for(int e=0; e<currentplaylist.size(); e++) {
    //        mydashedline();
    //        std::cout << "Output fuer i=" << e << std::endl;
    //        std::cout << "title["<<e<<"]: " << for(int e2=0; e2<25; e2++) {title[e][e2]}<< std::endl;
    //        std::cout << "artist["<<e<<"]: " << for(int e2=0; e2<25; e2++) {artist[e][e2]}<< std::endl;
    //        std::cout << "album["<<e<<"]: " << for(int e2=0; e2<25; e2++) {album[e][e2]}<< std::endl;
    //        std::cout << "year["<<e<<"]: " <<year[e]<< std::endl;
    //        std::cout << "duration["<<e<<"]: " << for(int e2=0; e2<25; e2++) {duration[e][e2]} << std::endl;
    //        std::cout << "genre["<<e<<"]: " << for(int e2=0; e2<25; e2++) {genre[e][e2]}<< std::endl;
    //        std::cout << "badwords["<<e<<"]: " <<badwords[e]<< std::endl;
    //    }
    //}
    



    nlohmann::json writefile = {//reihenfolge egal??!
        {
            "data",
            {
                {
                    //{"title", ""},
                    //{"artist", ""},
                    //{"album", ""},
                    //{"date", nullptr},
                    //{"length", ""},
                    //{"genre", ""},
                    //{"explicit", ""}
                    {"album", ""},
                    {"artist", ""},
                    {"date", nullptr},
                    {"explicit", ""},
                    {"genre", ""},
                    {"length", ""},
                    {"title", ""}
                }
            }
        }
    };


    //int testint =0;
    //testint = currentplaylist["data"].size();//warum auch immer brauchen wir diesen tempraeren integer. geben wir das argument direkt an die schleife, wird sie endlos
    //testint+=1;
    //std::cout << (currentplaylist["data"].size()+1) << std::endl;
    //std::cout << title[1]<<title[2]<<title[3]<<title[4] << std::endl;
    std::cout << "Aenderungen werden in die Datei geschrieben" << std::endl;
    //try{
    for(int i=0; i<(playlistsize+1); i++) {//hier alerdings wollen wir bis currentplaylist.size()+1 gehen!!
        writefile["data"][i]["title"] = title[i];
        //std::cout << "asdasdasd" << std::endl;//testtestte
        writefile["data"][i]["artist"] = artist[i];
        writefile["data"][i]["album"] = album[i];
        writefile["data"][i]["date"] = year[i];
        writefile["data"][i]["length"] = duration[i];
        writefile["data"][i]["genre"] = genre[i];
        writefile["data"][i]["explicit"] = badwords[i];
    }

    //nicht nur werden die aenderungen in der datei gepeichert, sondern auch lokal im programm. so koennen sie direkt im menue durch myprintfile() ausgegeben werden!!
    currentplaylist = writefile;
    //}
    //catch(std::exception& e) {
    //    std::cout << "FEHLER BEIM SPEICHERN DER DATEI! FEHLER:" << std::endl << e.what() << std::endl;
    //}
    //std::cout << "\t-----zwischenschritt 1-----" << std::endl;




std::memset(answer, 0, sizeof(answer));
    repeat=true;
    while(repeat) {//      ------das sollte jetzt alles abgeichert sein, aber wie testet man so etwas?? wie kann ich ein fole.is_open()==false erzwingen??
        //daten werden in die datei file2 geschrieben
        //std::cout << filename << std::endl;
        std::ofstream file2(mypath + filename);
        //std::cout << "test2: " << mypath+filename<<std::endl;

        if (!file2.is_open()) {
            std::cout << "Datei konnte nicht geoeffnet werden, um Datenn zu speichern! Fehlercode: 04" << std::endl;
            //main_menu();//vorerst zurueck zum mainmenu. speater muss hier eine loesung gefunden werden.
            //zum beispiel erneute abfrage nach dateinamen und versuch die bereits eingelesenen daten dotz zu speichern.
            //"wollen sie das speichern erneut versuchen? (ja/nein)"
            
        repeat2=true;
        while(repeat2) {
            std::cout << "\tErneut versuchen? (Ja/Nein): ";
            std::cin >> answer;
            if (strcasecmp(answer, "ja") == 0) {//er will es nochmal versuchen. viel glueck!
                repeat2=false;
            }
            if (strcasecmp(answer, "nein") == 0) {
                repeat2=false;
                repeat=false;
                song_management();
            }
        }
        //dann zurueck in den loop und es klappt hoffentlich
        } else {
            repeat=false;
            file2 << writefile.dump(2);
            //cout << "test3";
            //feierabend! datei wird geschlossen
            file2.close();
            //main_menu();
            std::cout << "---Aenderungen erfolgreich gespeichert---" << std::endl;
        }
    }


    //erneut die playlist ausgeben und zum start zurueckkehren! ???
    mywaitenter();
    //am ende zurueck zum hauptmenue
    main_menu();
}

void myexit(char myinput[50]) {
//funktion ueberprueft inputs auf "beenden" und beendet dann das programm.
    //cout << "asdasdasd" << endl;//test
    //cout << myinput << endl;
    if(strcasecmp(myinput, "beenden")==0) {//hier koennen sehr leicht andere woerter, wie "exit" oder "schliessen" ergaenzt werden
        std::cout << "" << std::endl;           //was machen wir bei der eingabe von titel, interpret, album, ...? was wenn dort "beenden" auftaucht?
        std::cout << "\tDer Musikplayer wurde vom Benutzer beendet." << std::endl;
        exit(0);
    }
}

void mywaitenter() {
    std::cout << ">mit Enter zurueck zum Hauptmenue...";
    std::string temp;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void mycheckifopen(char myinput2[50]) {
    //std::string tempfilename = filename;    
    //const char* tempfilename; tempfilename = filename.c_str();//AAAARRRGHHH

    //char* dotPos = std::strrchr(tempfilename, '.');//wir finden die stelle, an der der punkt ist
    //if (dotPos != nullptr) {//falls es diese gibt
    //    *dotPos = '\0';//und loecshen alles danach!
    //}
    
    //initialisieren funktioniert nicht, da der filename ueberprueft wird waehrend der nutzer noch gar nicht gefragt wurde!!

    /*if(myinput2==filename || myinput2==tempfilename) {
        std::cout << "Die Playlist: >" << myinput2 << "< ist bereits geoeffnet!"<< std::endl;
        std::cout << "Bearbeiten/Loeschen und weitere Funktionen ueber das Hauptmenue." << std::endl;
        mywaitenter();
        main_menu();
    }*/
}

void mydashedline() {
        std::cout << "\t----------------------------------" << std::endl;
}


