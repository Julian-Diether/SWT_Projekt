//Software Technik Projekt Gruppe1 -- Julian Diether, Lionel Felipe, Noah Traub, Frederik Kempke
//inkludieren saemtlicher bibliotheken
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>//darstellung myprintfile()
#include <cctype> // std::tolower() in mysearchfile()
#include <cstdio>//dateien loeschen
#include <iostream>
#include <fstream>//dateien lesen/schreiben
#include <limits>
#include "nlohmann/json.hpp"

//inkludierung globaler variablen
extern std::string mypath;

//deklarierung eigener variablen
std::string filename = "";
std::string tempstring;
nlohmann::json currentplaylist;
nlohmann::json searchplaylist;
char answer[50];
char tempchar[50];
bool repeat=true;
bool repeat2=true;

//deklarierung GLOBALER funktionen
void welcome_msg();
void main_menu();
void song_management();

//eigene funktionen
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
bool myjanein(std::string message);


void myinitialize() {
    
    welcome_msg();

    if(myjanein("Moechten sie eine Musik-Playlist initialisieren?")) {
        myopenfile(false);
    } else {
        main_menu();
    }
}

void myopenfile(bool justprint2) {

    mydashedline();
    //while schleife, bis datei gueltig geoeffnet ist
    repeat=true;
    while (repeat) {
        if(justprint2) {
            std::cout << "Geben sie den Namen der zu bearbeitenden Playlist ein: ";
        } else {
            std::cout << "Geben sie den Namen der zu oeffnenden Playlist ein: ";
        }
        std::cin >> filename;
        std::copy(filename.begin(), filename.end(), tempchar);
        tempchar[filename.size()] = '\0';
        myexit(tempchar);

        if (filename.find(".json") != std::string::npos) {
            //.json ist schon angefuegt
        } else {
            //std::swap(filename, filename2);//filename2 = filename
            filename = filename + ".json";//.json wird angefuegt
        }
       std::cout << "\tDie Datei " << filename << " wird geoeffnet." << std::endl;

        //datei wird geoeffnet
        try {
            std::ifstream file(mypath + filename);
            //oeffnen in sicheren umfeld --> kein absturz
            if (!file.is_open()) {
                std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            
            repeat = false; //erst nachden file.is_open = true ist. danach bei fehler wieder geaendert
            file >> currentplaylist;
            file.close();
            std::cout << "\t   Playlist erfolgreich geoeffnet" << std::endl; //erst hier ist die datei erfolgreich geoeffnet!!
            
            if(!justprint2) {
                mydashedline();
            }
        }

        catch (const std::exception& e) {
            repeat = true;
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << std::endl << e.what() << std::endl;
            mydashedline();
            //hier gab es einen fehler beim einlesen? der datei. zum bsp war sie leer ->siehe test2.json
        }

        //datei ist geoeffnet, kann direkt ausgegeben werden
        if(!repeat && !justprint2) {
            if(myjanein("Soll die Playlist direkt angezeigt werden?")) {
                myprintfile(false);
            } else {
                main_menu();
            }
        }
    }
}

void myprintfile(bool justprint) {
    
    mydashedline();
    if (filename=="") {
        std::cout << "Fehler! Momentan ist keine Datei geoeffnet. Fehlercode: 03" << std::endl;
        mydashedline();
        mywaitenter();
        main_menu();
    }

    if(!justprint) {
        std::cout << "\tDie Datei " << filename << " wird ausgegeben." << std::endl;
    }

    std::cout << std::left << std::setw(6) <<" Nr." <<
    std::setw(28) << "Titel" <<
    std::setw(28) << "Interpret" <<
    std::setw(30) << "Album" <<
    std::setw(20) << "Erscheinungsjahr" <<
    std::setw(10) << "Laenge" <<
    std::setw(15) << "Genre" <<
    std::setw(10) << "Jugendfrei" << std::endl;

    for(nlohmann::json::size_type i = 0; i<currentplaylist["data"].size(); i++) {
        std::string title = currentplaylist["data"][i]["title"];
        std::string artist = currentplaylist["data"][i]["artist"];
        std::string album = currentplaylist["data"][i]["album"];
        int date = currentplaylist["data"][i]["date"];
        std::string length = currentplaylist["data"][i]["length"];
        std::string genre = currentplaylist["data"][i]["genre"];

        for(nlohmann::json::size_type i = 0; i<currentplaylist["data"].size(); i++) {
            std::replace(length.begin(), length.end(), '_', ':');
        }

        std::cout << " ";
        std::cout << std::left << std::setw(6) << std::setfill(' ') << (i + 1)
          << std::setw(28) << std::setfill(' ') << title
          << std::setw(28) << std::setfill(' ') << artist
          << std::setw(30) << std::setfill(' ') << album
          << std::setw(20) << std::setfill(' ') << date
          << std::setw(10) << std::setfill(' ') << length
          << std::setw(15) << genre;

        if(currentplaylist["data"][i]["explicit"]) {
            std::cout << std::setw(10) << "Nein" << std::endl;
        } else {
            std::cout << std::setw(10) << "Ja" << std::endl;
        }
    }

    //mehr als 6 entries in .json datei --> legende unten erneut anzeigen
    if(currentplaylist["data"].size()>6) {
        std::cout << std::left << std::setw(6) <<" Nr." <<
        std::setw(28) << "Titel" <<
        std::setw(28) << "Interpret" <<
        std::setw(30) << "Album" <<
        std::setw(20) << "Erscheinungsjahr" <<
        std::setw(10) << "Laenge" <<
        std::setw(15) << "Genre" <<
        std::setw(10) << "Jugendfrei" << std::endl;
    }

    if(!justprint) {
        mydashedline();
        mywaitenter();
        main_menu();
    }
}

void mycreatefile() {

    char filenamecreatefile[50];
    int length=0;
    int tempyear=0;

    
    mydashedline();
    std::cout << "Name der neuen Playlist eingeben: ";
    std::cin >> filenamecreatefile;
    myexit(filenamecreatefile);
    
    std::string answer3str(filenamecreatefile);
    std::string answer3str2;//gegen sonderzeichen
    if (!(answer3str.find(".json") != std::string::npos)) {
        answer3str2 = answer3str;
        answer3str = answer3str2 + ".json";//.json anfuegen
    }

    std::copy(answer3str.begin(), answer3str.end(), filenamecreatefile);
    filenamecreatefile[answer3str.size()] = '\0';
    myexit(filenamecreatefile);//schwachsinn
    mycheckifopen(filenamecreatefile);//?

    if (std::filesystem::exists( mypath + filenamecreatefile)) {
        mydashedline();
        std::cout << "Die Datei existiert bereits! Fehlercode: 07" << std::endl;
        mywaitenter();
        main_menu();
    }

    repeat=true;
    //sicherstellen, dass nur integer eingegeben werden
    while (repeat) {
        std::cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
        if (std::cin >> length) {//integer eingegeben
            if(length>0) {repeat=false;}//integer größer 0 --> passt!
        } else {
            std::cin.clear();
            //^^input wird geloescht
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //^^input ignorieren. warum so kompliziert??!?
            std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
        }
    }

    tempstring = std::to_string(length) + " Songs werden zu " + std::string(filenamecreatefile) + " hinzugefuegt. Fortfahren?";
    if(!myjanein(tempstring)) {
        main_menu();
    }


    //ISO C++ forbids variable length array
    std::string title[length];
    std::string artist[length];
    std::string album[length];
    int year[length];
    std::string duration[length];
    std::string genre[length];
    bool badwords[length];
    //char title[length][25];
    //char artist[length][25];
    //char album[length][25];
    //char duration[length][5];
    //char genre[length][25];
    

    for (int i2 = 0; i2<length; i2++) {//probleme beim speichern vermeiden
        for (int i = 0; i<5; i++) {
            duration[i2][i]='\0';
        }
    }

    for (int i2 = 0; i2<length; i2++) {//probleme beim speichern vermeiden
        for (int i = 0; i<5; i++) {
            std::cout << "duration[" << i2 << "][" << i << "]: " << duration[i2][i] << std::endl;
        }
    }


    //hier beggint das einlesen der neuen songs!
    mydashedline();
    std::cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << std::endl;

    //std::memset(answer, 0, sizeof(answer));
    for(int i=0; i<length; i++) {
        mydashedline();
        std::cout << "Informationen fuer Song [" << (i+1) << "] eingeben:" << std::endl;
        std::cout << "Songname: "; std::cin >> title[i];
        std::cout << "Interpret: "; std::cin >> artist[i];
        std::cout << "Album: "; std::cin >> album[i];
        repeat=true;
        tempyear=0;
        while (repeat) {std::cout << "Erscheinungsjahr: ";
            if (std::cin >> tempyear) {//integer eingegeben
                if(tempyear>0) {repeat=false;year[i]=tempyear;}//success!
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;}
        }
        std::cout << "Laenge [xx:xx]: "; std::cin >> duration[i];
        std::cout << "Musikrichtung: "; std::cin >> genre[i];

        if(myjanein("Jugendfrei")) {
            badwords[i]=false;
        } else {
            badwords[i]=true;
        }
    }

    //doppelpunkt bei duration ersetzen
    for (int i2 = 0; i2<length; i2++) {
        for (int i = 0; i<5; i++) {
            if (duration[i2][i] == ':') {
                duration[i2][i] = '_';
            }
        }
    }


    mydashedline();
    std::cout << "Daten werden in Datei geschrieben" << std::endl;
    nlohmann::json writefile = {//reihenfolge irrelevant
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
    //hier werden sie tatsaechlich in die lokale json variable geschrieben.
    for(int i=0; i<length; i++) {
        writefile["data"][i]["title"] = title[i];
        writefile["data"][i]["artist"] = artist[i];
        writefile["data"][i]["album"] = album[i];
        writefile["data"][i]["date"] = year[i];
        writefile["data"][i]["length"] = duration[i];
        writefile["data"][i]["genre"] = genre[i];
        writefile["data"][i]["explicit"] = badwords[i];
    }

    std::memset(answer, 0, sizeof(answer));
    repeat=true;
    while(repeat) {
        std::ofstream file2(mypath + filenamecreatefile);

        if (!file2.is_open()) {
            std::cout << "Datei konnte nicht geoeffnet werden, um Daten zu speichern! Fehlercode: 04" << std::endl;
            
            if(myjanein("Ernet mit anderem Dateinamen versuchen?")) {
                //all dass muss nochchmal durchgegeangen und getestet werden!! Nur wie???
            } else {
                main_menu();
            }
            /*
            repeat2=true;
            while(repeat2) {
                std::cout << "Erneut mit anderem Dateinamen versuchen? (Ja/Nein): ";
                std::cin >> answer;
                myexit(answer);

                if (strcasecmp(answer, "ja") == 0) {//er will erneut versuchen. viel glueck!
                    repeat2=false;
                    std::string tempanswer;
                    std::cout << "Geben sie einen alternativen Dateinamen ein:";
                    std::cin >> tempanswer;

                    if (!(tempanswer.find(".json") != std::string::npos)) {
                        tempanswer = tempanswer + ".json";
                    }
                }
                if (strcasecmp(answer, "nein") == 0) {
                    repeat2=false;
                    main_menu();
                }
            }*/
            //zurueck in den loop, hoffentlich klappt es
        } else {
            repeat=false;
            file2 << writefile.dump(2);//lokale json variable in externe datei
            //feierabend! datei schliessen
            file2.close();
            main_menu();
        }
    }
}

void mydeletefile() {

    std::memset(answer, 0, sizeof(answer));//random sonderzeichen vermeiden
    mydashedline();
    std::cout << "Name der zu loeschenden Playlist eingeben: ";
    std::cin >> answer;

    std::string filenamedeletefile(answer);
    //da wir hier dateien loeschen mussen wir sehr vorsichtig sein!! der benutzer koennte auf andere ordner zugreifen!!!
    if (filenamedeletefile.find("/") != std::string::npos || filenamedeletefile.find("\\") != std::string::npos) {//_ '//' ==> /
        std::cout << "Fehler! Nicht erlaubte Zeichen eingegeben. Fehlercode: 05"<<std::endl;
        mywaitenter();
        main_menu();
    }

    //.json an datei anfuegen, falls noch nicht vorhanden
    if (!(filenamedeletefile.find(".json") != std::string::npos)) {
        filenamedeletefile = filenamedeletefile + ".json";
    }
    //pfad (playlists/) vor dateinamen anfuegen
    filenamedeletefile=mypath+filenamedeletefile;

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

    
    std::copy(filenamedeletefile.begin(), filenamedeletefile.end(), tempchar);
    //hier wird geloescht
    if (std::remove(tempchar) != 0) {
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

    std::memset(answer, 0, sizeof(answer));
    mydashedline();
    std::string filenamesearchfile;

    repeat=true;
    while (repeat) {

        std::cout << "Name der zu durchsuchenden Playlist eingeben: ";
        std::cin >> filenamesearchfile;

        if (!(filenamesearchfile.find(".json") != std::string::npos)) {
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

        std::cout << "Die Datei " << filenamesearchfile << " wird geoeffnet." << std::endl;
        try {
            std::ifstream file(filenamesearchfile);
            if (!file.is_open()) {
                std::cerr << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            repeat = false;

            file >> searchplaylist;//Datei wird eingelesen
            file.close();//Datei wird geschlossen
            std::cout << "\tDie Datei wurde geoeffnet" << std::endl;
            mydashedline();
        } catch (const std::exception& e) {
            repeat = true;//erneut versuchen, da fehler
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << std::endl << e.what() << std::endl;
            mydashedline();
        }
    }

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

        std::cout << "Achtung! Keine Sonderzeichen! Ausnahme Doppelpunkt." << std::endl;
        std::cout << "Geben sie einen Suchbegriff ein: ";
        std::cin >> answer;
        searchstring = std::string(answer);
        std::memset(answer, 0, sizeof(answer));

        std::replace(searchstring.begin(), searchstring.end(), ':', '_');//nun kann nach der laenge gesucht werden!
        std::replace(searchstring.begin(), searchstring.end(), ' ', '_');//und nach alben/titeln, die mehrere woerter umfassen! /normalerweise wuerde das schiefgehen, weil mehrere schritte vorgesprungen wird. hier egal, da alle schritte gleich sind((ja/nein) abfrage)!

        const char* searchchar;
        searchchar = searchstring.c_str();
        //cout << searchstring << endl;
        //cout << searchstring << " | " << searchplaylist["data"][0]["artist"] << endl;
        std::cout << "\t\t*******" << std::endl;
        //hoffentlich letzter versuch. JAAAAA //playlist zum test ist in line 635 falls sie je wieder gebraucht wird
        //for(int i=0; i<(searchplaylist["data"].size()); i++) {
        for(nlohmann::json::size_type i = 0; i<searchplaylist["data"].size(); i++) {
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
            

            bool unabletolocate=true;//auf die art koennen mehrere eintraege durchsucht werden. zum beispiel titel und album
            if(str1.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Titel von Song Nr. "<<i+1<<"! -- >"<<str1<<"<"<<std::endl; unabletolocate=false;}
            if(str2.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Interpreten von Song Nr. "<<i+1<<"! -- >"<<str2<<"<"<<std::endl; unabletolocate=false;}
            if(str3.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Album von Song Nr. "<<i+1<<"! -- >"<<str3<<"<"<<std::endl; unabletolocate=false;}
            //else if(str4.find(searchstring) != std::string::npos) {cout<<"Gefunden! Suche entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<endl;}//muss das noch irgendwie abgesichert weerden? kann so ein int ueberhaupt verglichen werden???
            if(str5.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht der Laenge von Song Nr. "<<i+1<<"! -- >"<<str5<<"<"<<std::endl; unabletolocate=false;}
            if(str6.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Genre von Song Nr. "<<i+1<<"! -- >"<<str6<<"<"<<std::endl; unabletolocate=false;}
            //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
            if(unabletolocate) {std::cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << std::endl;}
        }
        

    }
    main_menu();
}

void myeditfile(int select) {
    
    std::string filenameeditfile;
    myopenfile(true);

    if(select==1) {//erhoehte lesbarkeit
        mydashedline();
    }
    
    int playlistsize = currentplaylist["data"].size();

    int playlistsize1;
    if(select==1) {playlistsize1=(playlistsize+1);}//hinzufuegen
    if(select==2) {playlistsize1=playlistsize;}//bearbeiten
    if(select==3) {playlistsize1=playlistsize;}//loeschen

    std::string title[playlistsize1];
    std::string artist[playlistsize1];
    std::string album[playlistsize1];
    int year[playlistsize1];
    std::string duration[playlistsize1];
    std::string genre[playlistsize1];
    bool badwords[playlistsize1];

    std::string temptitle;
    std::string tempartist;
    std::string tempalbum;
    std::string tempgenre;

    nlohmann::json writefile = {
        {
            "data",
            {
                {
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

    //einlesen der .json datei in lokale variablen
    for(int i=0; i<(playlistsize); i++) {//+1); i++) {//playlistsize+1 ist groesse des arrays! Wir koennen aber nicht mit ihr auslesen, da das letzte element der song ist, der hier hinzugefuegt werden soll!!
        title[i] = currentplaylist["data"][i]["title"];
        artist[i] = currentplaylist["data"][i]["artist"];
        album[i] = currentplaylist["data"][i]["album"];
        year[i] = currentplaylist["data"][i]["date"];
        duration[i] = currentplaylist["data"][i]["length"];
        genre[i] = currentplaylist["data"][i]["genre"];
        if(currentplaylist["data"][i]["explicit"]) {
            badwords[i]=true;
        } else {
            badwords[i]=false;
        }
    }

    //playlist ist eingelesen, jetzt kann hinzugefuegt/bearbeitet/geloescht werden!

    //songnummer wird erfragt
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
                    if(songposition < static_cast<int>(currentplaylist["data"].size()) + 1) {//if(songposition<currentplaylist["data"].size()+1) {
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
        }       
    }

    std::memset(answer, 0, sizeof(answer));

    //durchfuehren von hinzufuegen/bearbeiten/loeschen
    int tempyear=0;
    if(select==1) {
        playlistsize+=1;

    
    int tempi =(playlistsize-1);
    
        std::cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << std::endl;

        mydashedline();
        std::cout << "Informationen fuer neuen Song eingeben:" << std::endl;
        std::cout << "Songname: "; std::cin >> title[tempi];
        //std::cout << "test" << std::endl;
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
        std::memset(answer, 0, sizeof(answer));
        while (repeat) {std::cout << "Jugendfrei (Ja/Nein): "; std::cin >> answer;
            if (strcasecmp(answer, "ja") == 0) {repeat=false;badwords[tempi]=false;}
            if (strcasecmp(answer, "nein") == 0) {repeat=false;badwords[tempi]=true;}
        }

            for (int i = 0; i<5; i++) {
                if (duration[tempi][i] == ':') {
                    duration[tempi][i] = '_';
                }
            }
            mydashedline();
    }

    if(select==2) {
        
        //songposition gibt position des songs (vgl. i) an
        mydashedline();
        //std::cout << "---Daten von Song Nr. " << (songposition+1) << " aendern oder bestaetigen(Enter)---" << std::endl;//  +1 von computer zaehlen in menschen zaehlen!!
        //      Abfrage, ob fortgefahren werden soll???---
        std::string tempstr;

        std::cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << std::endl;
        std::cout << "**Eintrag aendern, oder mit der Enter Taste beibehalten**" << std::endl;

        for (int i = 0; i<5; i++) {
                if (duration[songposition][i] == '_') {
                    duration[songposition][i] = ':';//zum ausgeben des momentanwerts im terminal
                }
            }

        std::string tempanswer;
        mydashedline();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//um probleme bei der 1. eingabe zu vermeiden

        std::cout << "Songname: " << title[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            title[songposition] = tempanswer;
        }

        std::cout << "Interpret: " << artist[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            artist[songposition] = tempanswer;
        }

        std::cout << "Album: " << album[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            album[songposition] = tempanswer;
        }

        std::cout << "Erscheinungsjahr: " << year[songposition] << std::endl;;
        repeat=true;
        while (repeat) {
            std::cout << ">";
            std::getline(std::cin, tempanswer);
            if (tempanswer.empty()) {
                repeat=false;//enter
            } else {
            
                try //(tempyear= std::stoi(tempanswer)) {//std::cin >> tempyear) {//zahl eingegebe
                    {
                    tempyear= std::stoi(tempanswer);
                    if(tempyear>0) {//sicherstellen, dass zahl positiv ist! ggfs. andere plausibilitaets checks.
                        repeat=false;year[songposition]=tempyear;
                    }//success!n
                } catch(std::invalid_argument()) {//falls keine zahl eingegeben wurde 
                    std::cerr << "Fehler!" << std::endl;
                    std::cin.clear();//input wird geloescht
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    tempanswer="";
                    std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
                }
            }
        }

        std::cout << "Laenge [xx:xx]: " << duration[songposition] << std::endl << ">";// std::cin >> duration[songposition];
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            duration[songposition] = tempanswer;
        }

        std::cout << "Musikrichtung: " << genre[songposition] << std::endl << ">";// std::cin >> genre[songposition];
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            genre[songposition] = tempanswer;
        }

        repeat=true;
        if(badwords[songposition]) {std::cout << "Jugendfrei (Ja/Nein): " << "Nein" << std::endl;} else {std::cout << "Jugendfrei (Ja/Nein): " << "Ja" << std::endl;}
        while (repeat) {std::cout << ">";
            std::getline(std::cin, tempanswer);
            if(!tempanswer.empty()) {
                std::copy(tempanswer.begin(), tempanswer.end(), answer);
                if (strcasecmp(answer, "ja") == 0) {repeat=false;badwords[songposition]=false;}
                if (strcasecmp(answer, "nein") == 0) {repeat=false;badwords[songposition]=true;}
            } else {
                //enter wurde gedrueckt, also wird der input ignoriert und der alte wert beibehalten
                repeat=false;
            }
        }

        for (int i = 0; i<5; i++) {
            if (duration[songposition][i] == ':') {
                duration[songposition][i] = '_';
            }
        }//ist ja nicht schlimm, dass das auch durchlaeuft, wenn nichts geaendert wurde.

        mydashedline();
    }//ende if(select==2)

    if(select==3) {
        
        if(currentplaylist["data"].size()<2) {
            mydashedline();
            std::cout << "\tAchtung, die ausgewaehlte Playlist enthaelt nur einen Song" << std::endl;

            repeat=true;
            while(repeat) {
                std::cout << "Mit loeschen der gesamten Playlist fortfahren? (Ja/Nein): ";
                std::cin >> answer;
                    
                if (strcasecmp(answer, "ja") == 0) {
                    repeat = false;
                    mydeletefile();//hier ggfs. noch dateinamen an funktion uebergeben
                }
                if (strcasecmp(answer, "nein") == 0) {
                    repeat = false;
                    //zum song editor zurueckkehren
                    song_management();
                }
            }
        }
        
        repeat=true;
        while(repeat) {
            std::cout << "ACHTUNG! Soll song Nr. " << (songposition+1) << " wirklich geloscht werden? (Ja/Nein):";
            std::cin >> answer;
            myexit(answer);
            if (strcasecmp(answer, "ja") == 0) {
                repeat = false;
            }
            if (strcasecmp(answer, "nein") == 0) {
                repeat = false;
                song_management();
            }
        }
    }

    //geanderte datei fuer das speichern vorbereiten
    std::cout << "Aenderungen werden in die Datei geschrieben" << std::endl;
    for(int i=0; i<(playlistsize1); i++) {//hier alerdings wollen wir bis currentplaylist.size()+1 gehen!!
        writefile["data"][i]["title"] = title[i];
        writefile["data"][i]["artist"] = artist[i];
        writefile["data"][i]["album"] = album[i];
        writefile["data"][i]["date"] = year[i];
        writefile["data"][i]["genre"] = genre[i];
        writefile["data"][i]["explicit"] = badwords[i];
        writefile["data"][i]["length"] = duration[i];
    }

    if(select==3) {//ggfs. song loeschen
        writefile["data"].erase(writefile["data"].begin() + songposition);
    }

    //nicht nur werden die aenderungen in der datei gepeichert, sondern auch lokal im programm. so koennen sie direkt im mensaue durch myprintfile() ausgegeben und abgespielt werden!!
    currentplaylist = writefile;

    std::memset(answer, 0, sizeof(answer));
    repeat=true;
    while(repeat) {//      ------das sollte jetzt alles abgeichert sein, aber wie testet man so etwas?? wie kann ich ein fole.is_open()==false erzwingen??
        //daten werden in die datei file2 geschrieben
        std::ofstream file2(mypath + filename);

        if (!file2.is_open()) {
            std::cout << "Datei konnte nicht geoeffnet werden, um Datenn zu speichern! Fehlercode: 04" << std::endl;
            
            repeat2=true;
            while(repeat2) {
                std::cout << "\tErneut versuchen? (Ja/Nein): ";
                std::cin >> answer;
                if (strcasecmp(answer, "ja") == 0) {//er will es nochmal versuchen. viel glueck!
                    repeat2=false;
                    //hier muss die abfrage nach dem dateinamen ergaenzt werden??
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
            //feierabend! datei wird geschlossen
            file2.close();
            std::cout << "---Aenderungen erfolgreich gespeichert---" << std::endl;
        }
    }

    //irgendwie gab es durch das erlauben von enter beim bearbeiten probleme mit diesem schritt, desshalb die ausnahme regelung
    if(select==2) {
        std::cout << ">mit Enter zurueck zum Hauptmenue...";
        std::string temp;
        std::getline(std::cin, temp);
    } else {
        mywaitenter();
    }
    //am ende zurueck zum hauptmenue
    main_menu();
}

void myexit(char myinput[50]) {
    //funktion ueberprueft inputs auf "beenden" und beendet dann das programm
    if(strcasecmp(myinput, "beenden")==0) {//hier koennen sehr leicht andere woerter, wie "exit" oder "schliessen" ergaenzt werden
        std::cout << std::endl << "\tDer Musikplayer wurde vom Benutzer beendet." << std::endl;
        exit(0);
    }
}

void mywaitenter() {
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//damit nach dem bearbeiten eines songs nicht mehrmals enter gedrueckt werden muss?!
    std::cout << ">mit Enter zurueck zum Hauptmenue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();//wartet auf den user input
}

void mycheckifopen(char myinput2[50]) {
//---was machen wit jetzt mit diesem schritt?? das oeffnen einer bereits geoeffneten datei ist ja nicht schlimm
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

bool myjanein(std::string message) {
    //ersetzt die einzelnen abfragen um den code zu vereinfachen/fehler zu vermeiden
    bool repeatjn = true;
    char answerjn[50];
    std::memset(answerjn, 0, sizeof(answerjn));

    while (repeatjn) {
        std::cout << message << " (Ja/Nein): ";
        std::cin >> answerjn;
        myexit(answerjn);

        if (strcasecmp(answerjn, "ja") == 0) {
            repeatjn = false;
            return true;
        }
        if (strcasecmp(answerjn, "nein") == 0) {
            repeatjn = false;
            return false;
        }
    }
    //-------------------------!ACHTUNG!-------------------------
    //!!!!!Das folgende return statement wird NIEMALS erreicht!!!!!
    //Es dient jediglich dazu, die folgende Compiler Warnung zu vermeiden
    //>>warning: control reaches end of non-void function [-Wreturn-type]<<
    //die obige logik wird IMMER den jeweiligen true/false wert zurueckgeben...
    //...beziehungsweise das programm auf wunsch des benutzers schliesssen
    return false;
}

