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
#include <filesystem>//pruefen ob dateien existieren
#include <limits>//warnungsfreihe vergleiche
#include <stdexcept>//um z.B. std::invalid_argument zu catchen
#include <vector>//dynamische speicher allokation
#include "nlohmann/json.hpp"//json manipulagion

//inkludierung globaler variablen
std::string mypath;
std::string settingspath = "settings.json";

//deklarierung eigener variablen
std::string filename = "";
std::string tempstring;
std::string tempstring2;
std::string tempstring3;
nlohmann::json currentplaylist;
nlohmann::json searchplaylist;
char answer[100];
char tempchar[100];

bool repeat=true;
//bool repeat2=true;
bool tempbool;
int tempint;

//deklarierung GLOBALER funktionen
void welcome_msg();
void main_menu();
void song_management();
/**/
//eigene funktionen
void myinitialize();
void myopenfile(bool justprint);
void myprintfile(bool justopen);
void mycreatefile();
void mydeletefile();
void mysearchfile();
void myeditfile(int select);
void myrenamefile();
void mylistfiles();

void myexit(std::string inputstring);
void mywaitenter();
void mycheckifopen(char myinput2[50]);
void mydashedline();
bool myjanein(std::string message);
std::string myaddjson(std::string filenamein, bool addpath);
void mycheckname(std::string filenamein2);
nlohmann::json myreadfile(int select2);

void myinitialize() {

    //fallback settings:
    bool skipini=false;
    mypath = "playlists/";

    nlohmann::json settings = {
        {
            "skipini", false,
            "mypath", ""
        }
    };

    try {
        if (std::filesystem::exists(settingspath)) {
            std::ifstream tempfile(settingspath);
            if(tempfile.is_open()) {
                tempfile >> settings;
                tempfile.close();
                mypath = settings["mypath"];
                skipini = settings["skipini"];
            } else {//not open
                //fallback settings
            }
        } else {//not existing
            //fallback settings
        }
    }//end try
    catch(const std::exception& e) {
        //fallback settings / keine fehlermeldung
    }

    if(skipini) {
        main_menu();
    }

    welcome_msg();
    if(myjanein("Moechten sie eine Musik-Playlist initialisieren?")) {
        myopenfile(false);
    } else {
        main_menu();
    }
}

void myopenfile(bool justopen) {

    //mydashedline();
    currentplaylist = myreadfile(1);
    
    if(!justopen) {
        if(myjanein("Soll die Playlist direkt angezeigt werden?")) {
            myprintfile(false);
        } else {
            main_menu();
        }
    }

/*
    //while schleife, bis datei gueltig geoeffnet ist
    repeat=true;
    while (repeat) {
        if(justopen) {
            std::cout << "Geben sie den Namen der zu bearbeitenden Playlist ein: ";
        } else {
            std::cout << "Geben sie den Namen der zu oeffnenden Playlist ein: ";
        }
        std::cin >> filename;
        std::copy(filename.begin(), filename.end(), tempchar);
        tempchar[filename.size()] = '\0';
        myexit(tempchar);
        mycheckname(filename);

        std::cout << "\tDie Datei " << filename << " wird geoeffnet." << std::endl;
        filename = myaddjson(filename, true);
        
        //datei wird geoeffnet
        try {
            std::ifstream file(filename);
            //oeffnen in sicheren umfeld --> kein absturz
            if (!file.is_open()) {
                std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            
            repeat = false; //erst nachden file.is_open = true ist. danach bei fehler wieder geaendert
            file >> currentplaylist;
            file.close();
            std::cout << "\t   Playlist erfolgreich geoeffnet" << std::endl; //erst hier ist die datei erfolgreich geoeffnet!!
            
            if(!justopen) {
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
        if(!repeat && !justopen) {
            if(myjanein("Soll die Playlist direkt angezeigt werden?")) {
                myprintfile(false);
            } else {
                main_menu();
            }
        }
    }*/

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

        std::replace(length.begin(), length.end(), '_', ':');
        std::replace(artist.begin(), artist.end(), '_', ' ');
        std::replace(album.begin(), album.end(), '_', ' ');
        std::replace(title.begin(), title.end(), '_', ' ');
        std::replace(genre.begin(), genre.end(), '_', ' ');

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

    //mehr als 5 entries in .json datei --> legende unten erneut anzeigen
    if(currentplaylist["data"].size()>5) {
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

    //char filenamecreatefile[50];
    std::string filenamecreatefile;
    int length=0;
    int tempyear=0;
    
    mydashedline();
    repeat=true;
    while(repeat) {
        std::cout << "Name der neuen Playlist eingeben: ";
        std::getline(std::cin, filenamecreatefile);
        mycheckname(filenamecreatefile);

        filenamecreatefile = myaddjson(filenamecreatefile, false);

        if (std::filesystem::exists(mypath + filenamecreatefile)) {
            mydashedline();
            std::cout << "Die Datei existiert bereits! Fehlercode: 07" << std::endl;
        } else {
            repeat=false;
        }
    }
    repeat=true;
    //sicherstellen, dass nur integer eingegeben werden
    while (repeat) {
        std::cout << "Wie viele Songs sollen hinzugefuegt werden?: ";
        std::getline(std::cin, tempstring);

        try {
            length = std::stoi(tempstring);//integer eingegeben
        }
        catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde 
            std::cin.clear();//input wird geloescht
            std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
        }
        if(length>0) {//sicherstellen, dass zahl positiv ist! ggfs. andere plausibilitaets checks.
            repeat=false;
        }//success!n
    }
    tempstring2="";
    tempstring3="wird";
    if(length>1) {tempstring2="s";tempstring3="werden";}
    tempstring = std::to_string(length) + " Song" + tempstring2 + " " + tempstring3 + " zu " + std::string(filenamecreatefile) + " hinzugefuegt. Fortfahren?";
    if(!myjanein(tempstring)) {
        main_menu();
    }

    //ISO C++ forbids variable length array - FIXED :)
    std::vector<std::string> title;
    std::vector<std::string> artist;
    std::vector<std::string> album;
    std::vector<int> year;
    std::vector<std::string> duration;
    std::vector<std::string> genre;
    std::vector<bool> badwords;
    
    //for (int i2 = 0; i2<length; i2++) {//probleme beim speichern vermeiden
    //    for (int i = 0; i<5; i++) {
    //        duration[i2][i]='\0';
    //    }
    //}

    //hier beggint das einlesen der neuen songs!
    mydashedline();
    std::cout << "ACHTUNG!! keine Sonderzeichen oder Leerzeichen eingeben" << std::endl;

    //std::memset(answer, 0, sizeof(answer));
    for(int i=0; i<length; i++) {
        mydashedline();
        std::cin.ignore();
        std::cout << "Informationen fuer Song [" << (i+1) << "/" << length << "] eingeben:" << std::endl;
        std::cout << "Songname: "; std::getline(std::cin, tempstring);title.push_back(tempstring);
        std::cout << "Interpret: "; std::getline(std::cin, tempstring);artist.push_back(tempstring);
        std::cout << "Album: "; std::getline(std::cin, tempstring);album.push_back(tempstring);
        repeat=true;
        tempyear=0;
        while (repeat) {std::cout << "Erscheinungsjahr: ";
            std::getline(std::cin, tempstring);
            try {
                tempyear = std::stoi(tempstring);
            }
            catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde 
                std::cin.clear();//input wird geloescht
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }

            if(tempyear>0) {
                repeat=false;year.push_back(tempyear);
            } else {//success!
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }
        }

        std::cin.ignore();
        std::cout << "Laenge [xx:xx]: "; std::getline(std::cin, tempstring); duration.push_back(tempstring);
        std::cout << "Musikrichtung: "; std::getline(std::cin, tempstring); genre.push_back(tempstring);

        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //std::cin.ignore();
        if(myjanein("Jugendfrei")) {
            badwords.push_back(false);
        } else {
            badwords.push_back(true);
        }
        
        std::replace(duration[i].begin(), duration[i].end(), ':', '_');
        std::replace(title[i].begin(), title[i].end(), ' ', '_');
        std::replace(artist[i].begin(), artist[i].end(), ' ', '_');
        std::replace(album[i].begin(), album[i].end(), ' ', '_');
        std::replace(genre[i].begin(), genre[i].end(), ' ', '_');
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
            
            if(myjanein("Erneut mit anderem Dateinamen versuchen?")) {
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
            currentplaylist = writefile;//hierdurch wird die gerade erstellte playlist jetzt auch
            filename = filenamecreatefile;//siehe obige zeile
            //feierabend! datei schliessen
            file2.close();
            std::cout << "Die Daten wurden erfolgreich gespeichert!" << std::endl;
            mywaitenter();
            main_menu();
        }
    }
}

void mydeletefile() {

    std::string filenamedeletefile;
    std::memset(answer, 0, sizeof(answer));//random sonderzeichen vermeiden
    mydashedline();
    std::cout << "Name der zu loeschenden Playlist eingeben: ";
    std::getline(std::cin, tempstring);

    myexit(tempstring);
    mycheckname(tempstring);
    filenamedeletefile = myaddjson(filenamedeletefile, true);

    tempstring = "Die Playlist >" + filenamedeletefile + "< wird geloescht! Fortfahren?";
    if(!myjanein(tempstring)) {
        main_menu();
    }
    
    mydashedline();
    std::copy(filenamedeletefile.begin(), filenamedeletefile.end(), tempchar);
    //hier wird geloescht
    if (std::remove(tempchar) != 0) {
        std::cout << "Fehler! Die Datei konnte nicht geloescht werden. Fehlercode: 06" << std::endl;
    } else {
        std::cout << "\tDie Datei wurde erfolgreich geloescht!" << std::endl;   
    }
    mywaitenter();
    main_menu(); 
}

void mysearchfile() {

    std::memset(answer, 0, sizeof(answer));
    mydashedline();
    std::string filenamesearchfile;

    repeat=true;
    while (repeat) {

        std::cout << "Name der zu durchsuchenden Playlist eingeben: ";
        std::getline(std::cin, filenamesearchfile);
        mycheckname(filenamesearchfile);
        tempstring = "Die Datei >" + filenamesearchfile + "< wird durchsucht. Fortfahren?";
        if(!myjanein(tempstring)) {
            main_menu();
        }
        filenamesearchfile = myaddjson(filenamesearchfile, true);//pfad (playlists/) vor dateinamen anfuegen
        //jetzt kann endlich durchsucht werden!!! NAJA, zuerst muss datei erfolgreich! geoeffnent werden!!

        std::cout << "Die Datei " << filenamesearchfile << " wird geoeffnet." << std::endl;
        try {
            std::ifstream file(filenamesearchfile);
            if (!file.is_open()) {
                std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
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
            if(!myjanein("\t Die Datei erneut durchsuchen?")) {
                main_menu();
            }
        }
        firstrun=false;//nach dem ersten durchlauf wird gefragt, ob erneut durchsucht werden soll.

        std::cout << "Achtung! Keine Sonderzeichen oder Leerzeichen! Ausnahme Doppelpunkt." << std::endl;
        std::cout << "Geben sie einen Suchbegriff ein: ";
        std::getline(std::cin, searchstring);
        //std::cin >> answer;
        //searchstring = std::string(answer);
        //std::memset(answer, 0, sizeof(answer));

        //std::replace(searchstring.begin(), searchstring.end(), ':', '_');//nun kann nach der laenge gesucht werden!
        std::replace(searchstring.begin(), searchstring.end(), '_', ' ');//und nach alben/titeln, die mehrere woerter umfassen! /normalerweise wuerde das schiefgehen, weil mehrere schritte vorgesprungen wird. hier egal, da alle schritte gleich sind((ja/nein) abfrage)!
        std::transform(searchstring.begin(), searchstring.end(), searchstring.begin(), ::tolower);
        const char* searchchar;
        searchchar = searchstring.c_str();
        std::cout << "\t\t*******" << std::endl;
        for(nlohmann::json::size_type i = 0; i<searchplaylist["data"].size(); i++) {

            std::string str1(searchplaylist["data"][i]["title"]);
            std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
            std::string str2(searchplaylist["data"][i]["artist"]);
            std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
            std::string str3(searchplaylist["data"][i]["album"]);
            std::transform(str3.begin(), str3.end(), str3.begin(), ::tolower);
            tempint = searchplaylist["data"][i]["date"];
            std::string str4(std::to_string(tempint));
            std::transform(str4.begin(), str4.end(), str4.begin(), ::tolower);
            std::string str5(searchplaylist["data"][i]["length"]);
            std::transform(str5.begin(), str5.end(), str5.begin(), ::tolower);
            std::string str6(searchplaylist["data"][i]["genre"]);
            std::transform(str6.begin(), str6.end(), str6.begin(), ::tolower);
            
            std::replace(str5.begin(), str5.end(), '_', ':');//duration
            std::replace(str1.begin(), str1.end(), '_', ' ');//title
            std::replace(str2.begin(), str2.end(), '_', ' ');//artist
            std::replace(str3.begin(), str3.end(), '_', ' ');//album
            std::replace(str6.begin(), str6.end(), '_', ' ');//genre

            bool unabletolocate=true;//auf die art koennen mehrere eintraege durchsucht werden. zum beispiel titel und album
            if(str1.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Titel von Song Nr. "<<i+1<<"! -- >"<<str1<<"<"<<std::endl; unabletolocate=false;}
            if(str2.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Interpreten von Song Nr. "<<i+1<<"! -- >"<<str2<<"<"<<std::endl; unabletolocate=false;}
            if(str3.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Album von Song Nr. "<<i+1<<"! -- >"<<str3<<"<"<<std::endl; unabletolocate=false;}
            if(str4.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Erscheinungsjahr von Song Nr. "<<i+1<<"! -- >"<<str4<<"<"<<std::endl; unabletolocate=false;}
            if(str5.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht der Laenge von Song Nr. "<<i+1<<"! -- >"<<str5<<"<"<<std::endl; unabletolocate=false;}
            if(str6.find(searchchar) != std::string::npos) {std::cout<<"Suchbegriff entspricht dem Genre von Song Nr. "<<i+1<<"! -- >"<<str6<<"<"<<std::endl; unabletolocate=false;}
            //else if(answer==searchplaylist["data"][i]["explicit"]) {cout<<"Gefunden! Suche entspricht dem ??? von Song Nr. "<<i+1<<endl;}//ergibt wenig sinn...
            if(unabletolocate) {std::cout << "Fuer Song Nr. " << i+1 << " wurde nichts gefunden." << std::endl;}
        }
    }
}

void myeditfile(int select) {
    
    std::string filenameeditfile;
    myopenfile(true);

    if(select==1) {//erhoehte lesbarkeit
        mydashedline();
    }
    //[-Wconversion]
    long long unsigned int playlistsize = currentplaylist["data"].size();
    long long unsigned int playlistsize1;

    if(select==1) {playlistsize1=(playlistsize+1);}//hinzufuegen
    if(select==2) {playlistsize1=playlistsize;}//bearbeiten
    if(select==3) {playlistsize1=playlistsize;}//loeschen

    //ISO C++ forbids variable length array - FIXED :)
    std::vector<std::string> title;
    std::vector<std::string> artist;
    std::vector<std::string> album;
    std::vector<int> year;
    std::vector<std::string> duration;
    std::vector<std::string> genre;
    std::vector<bool> badwords;

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
    for(long long unsigned int i=0; i<(playlistsize); i++) {//+1); i++) {//playlistsize+1 ist groesse des arrays! Wir koennen aber nicht mit ihr auslesen, da das letzte element der song ist, der hier hinzugefuegt werden soll!!
        title.push_back(currentplaylist["data"][i]["title"]);
        artist.push_back(currentplaylist["data"][i]["artist"]);
        album.push_back(currentplaylist["data"][i]["album"]);
        year.push_back(currentplaylist["data"][i]["date"]);
        duration.push_back(currentplaylist["data"][i]["length"]);
        genre.push_back(currentplaylist["data"][i]["genre"]);
        if(currentplaylist["data"][i]["explicit"]) {
            badwords.push_back(true);
        } else {
            badwords.push_back(false);
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
            } else {//song loeschen selektiert

                if(currentplaylist["data"].size()<2) {
                    mydashedline();
                    std::cout << "\tAchtung, die ausgewaehlte Playlist enthaelt nur einen Song" << std::endl;

                    if(myjanein("Mit loeschen der gesamten Playlist fortfahren?")) {
                        mydeletefile();
                    } else {
                        song_management();
                    }
                } else {
                        std::cout << "welche Songnummer soll geloescht werden?: ";
                }
            }

            std::getline(std::cin, tempstring);
            try {
                std::stoi(tempstring);
            }
            catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde 
                std::cin.clear();//input wird geloescht
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }
            
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
        }
    }

    std::memset(answer, 0, sizeof(answer));

    //durchfuehren von hinzufuegen/bearbeiten/loeschen
    int tempyear=0;
    if(select==1) {
        playlistsize+=1;

    
    long long unsigned int tempi =(playlistsize-1);
    
        std::cout << "\tACHTUNG!! keine Sonderzeichen eingeben" << std::endl;
        std::cin.ignore();
        mydashedline();
        std::cout << "Informationen fuer neuen Song eingeben:" << std::endl;
        std::cout << "Songname: "; getline(std::cin, tempstring); title.push_back(tempstring);
        //std::cout << "test" << std::endl;
        std::cout << "Interpret: "; getline(std::cin, tempstring); artist.push_back(tempstring);
        std::cout << "Album: "; getline(std::cin, tempstring); album.push_back(tempstring);
        repeat=true;
        while (repeat) {std::cout << "Erscheinungsjahr: ";
            std::getline(std::cin, tempstring);

            try {
                tempyear = std::stoi(tempstring);//integer eingegeben
            }
            catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde 
                std::cin.clear();//input wird geloescht
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }

            if(tempyear>0) {
                repeat=false;year.push_back(tempyear);
            } else {//success!n
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }
        }
        std::cin.ignore();
        std::cout << "Laenge [xx:xx]: "; getline(std::cin, tempstring);duration.push_back(tempstring);
        std::cout << "Musikrichtung: "; getline(std::cin, tempstring);genre.push_back(tempstring);

        if(myjanein("Jugendfrei")) {
            badwords.push_back(false);
        } else {
            badwords.push_back(true);
        }

        std::replace(duration[tempi].begin(), duration[tempi].end(), ':', '_');
        std::replace(title[tempi].begin(), title[tempi].end(), ' ', '_');
        std::replace(artist[tempi].begin(), artist[tempi].end(), ' ', '_');
        std::replace(album[tempi].begin(), album[tempi].end(), ' ', '_');
        std::replace(genre[tempi].begin(), genre[tempi].end(), ' ', '_');
        mydashedline();
    }

    if(select==2) {
        
        //songposition gibt position des songs (vgl. i) an
        mydashedline();
        //std::cout << "---Daten von Song Nr. " << (songposition+1) << " aendern oder bestaetigen(Enter)---" << std::endl;//  +1 von computer zaehlen in menschen zaehlen!!
        //      Abfrage, ob fortgefahren werden soll???---
        std::string tempstr;

        std::cout << "\tACHTUNG!! keine Sonderzeichen eingeben" << std::endl;
        std::cout << "**Eintrag aendern, oder mit der Enter Taste beibehalten**" << std::endl;

        std::replace(duration[songposition].begin(), duration[songposition].end(), '_', ':');
        std::replace(title[songposition].begin(), title[songposition].end(), '_', ' ');
        std::replace(artist[songposition].begin(), artist[songposition].end(), '_', ' ');
        std::replace(album[songposition].begin(), album[songposition].end(), '_', ' ');
        std::replace(genre[songposition].begin(), genre[songposition].end(), '_', ' ');

        std::string tempanswer;
        mydashedline();
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//um probleme bei der 1. eingabe zu vermeiden
        std::cin.ignore();  
        std::cout << "Songname: " << title[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            title.push_back(tempanswer);
        }

        std::cout << "Interpret: " << artist[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            artist.push_back(tempanswer);
        }

        std::cout << "Album: " << album[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            album.push_back(tempanswer);
        }

        std::cout << "Erscheinungsjahr: " << year[songposition] << std::endl;;
        repeat=true;
        while (repeat) {
            std::cout << ">";
            std::getline(std::cin, tempanswer);
            if (tempanswer.empty()) {
                repeat=false;//enter gedrueckt/soll beibehalten werden
            } else {
            
                try //(tempyear= std::stoi(tempanswer)) {//std::cin >> tempyear) {//zahl eingegebe
                    {
                    tempyear= std::stoi(tempanswer);
                    if(tempyear>0) {//sicherstellen, dass zahl positiv ist! ggfs. andere plausibilitaets checks.
                        repeat=false;
                        year.push_back(tempyear);
                    }//success!n
                } catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde
                    std::cin.clear();//input wird geloescht
                    tempanswer="";
                    std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
                }
            }
        }

        std::cout << "Laenge [xx:xx]: " << duration[songposition] << std::endl << ">";// std::cin >> duration[songposition];
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            duration.push_back(tempanswer);
        }

        std::cout << "Musikrichtung: " << genre[songposition] << std::endl << ">";// std::cin >> genre[songposition];
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            genre.push_back(tempanswer);
        }

        repeat=true;
        if(badwords[songposition]) {std::cout << "Jugendfrei (Ja/Nein): " << "Nein" << std::endl;} else {std::cout << "Jugendfrei (Ja/Nein): " << "Ja" << std::endl;}
        while (repeat) {std::cout << "> (Ja/Nein): ";
            std::getline(std::cin, tempanswer);
            if(!tempanswer.empty()) {

                std::copy(tempanswer.begin(), tempanswer.end(), answer);
                if (strcasecmp(answer, "ja") == 0) {repeat=false;badwords.push_back(false);}
                if (strcasecmp(answer, "nein") == 0) {repeat=false;badwords.push_back(true);}
            } else {
                //enter wurde gedrueckt, also wird der input ignoriert und der alte wert beibehalten
                repeat=false;
            }
        }

        std::replace(genre[songposition].begin(), genre[songposition].end(), ':', '_');
        //ist ja nicht schlimm, dass das auch durchlaeuft, wenn nichts geaendert wurde.

        mydashedline();
    }//ende if(select==2)
        

    //geanderte datei fuer das speichern vorbereiten
    std::cout << "Aenderungen werden in die Datei geschrieben" << std::endl;
    for(long long unsigned int i=0; i<(playlistsize1); i++) {//hier alerdings wollen wir bis currentplaylist.size()+1 gehen!!
        writefile["data"][i]["title"] = title[i];
        writefile["data"][i]["artist"] = artist[i];
        writefile["data"][i]["album"] = album[i];
        writefile["data"][i]["date"] = year[i];
        writefile["data"][i]["genre"] = genre[i];
        writefile["data"][i]["explicit"] = badwords[i];
        writefile["data"][i]["length"] = duration[i];
    }

    if(select==3) {
        //macht es optimisierungstechnisch einen unterschied, dass hier datein eingelesen werden, die im fall 'nein' nicht gebraucht werden??
        tempstring = "ACHTUNG! Soll song Nr. " + std::to_string((songposition+1)) + " wirklich geloscht werden?";
        if(myjanein(tempstring)) {
            writefile["data"].erase(writefile["data"].begin() + songposition);
        } else {
            song_management();
        }
    }

    //nicht nur werden die aenderungen in der datei gepeichert, sondern auch lokal im programm. so koennen sie direkt im mensaue durch myprintfile() ausgegeben und abgespielt werden!!
    currentplaylist = writefile;

    std::memset(answer, 0, sizeof(answer));
    repeat=true;
    while(repeat) {//      ------das sollte jetzt alles abgeichert sein, aber wie testet man so etwas?? wie kann ich ein fole.is_open()==false erzwingen??
        //daten werden in die datei file2 geschrieben
        std::ofstream file2(filename);
        if (!file2.is_open()) {
            std::cout << "Datei konnte nicht geoeffnet werden, um Daten zu speichern! Fehlercode: 04" << std::endl;

            if(myjanein("\tErneut versuchen?")) {
                    //hier muss die abfrage nach dem dateinamen ergaenzt werden??
                    std::cout << "Geben sie den Dateinamen ein: ";
                    std::getline(std::cin, filename);
                    filename = myaddjson(filename, true);
            } else {
                    repeat=false;
                    song_management();
            }

            /*
            repeat2=true;
            while(repeat2) {
                std::cout << "\tErneut versuchen? (Ja/Nein): ";
                std::cin >> answer;
                if (strcasecmp(answer, "ja") == 0) {//er will es nochmal versuchen. viel glueck!
                    repeat2=false;
                    //hier muss die abfrage nach dem dateinamen ergaenzt werden??
                    std::cout << "Geben sie den Dateinamen ein: ";
                    std::cin >> filename;
                    filename = myaddjson(filename, true);
                }
                if (strcasecmp(answer, "nein") == 0) {
                    repeat2=false;
                    repeat=false;
                    song_management();
                }
            }
            */

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

void myrenamefile() {
    //filename wird nichzt benutzt, da hier keine datei geoeffnet wird und es (z.B.) bei myprintfile() zu logischen fehlern kommen koennte
    std::string filenameold;
    std::string filenamenew;
    nlohmann::json renameplaylist;
    
    repeat=true;
    while (repeat) {
        //loop verlassen, wenn erfolgreich umbenannt oder aufgegeben
        mydashedline();
        std::cout << "Geben sie den Namen der umzubenennenden Playlist ein: ";
        std::getline(std::cin, filenameold);
        tempstring2 = filenameold;
        filenameold = myaddjson(filenameold, true);
        mycheckname(filenameold);

        if(std::filesystem::exists(filenameold)) {
            std::cout << "Neuen Namen fuer \'" << tempstring2 << "\' eingeben: ";
            std::getline(std::cin, filenamenew);
            tempstring3 = filenamenew;
            filenamenew = myaddjson(filenamenew, true);
            mycheckname(filenamenew);

            if(!std::filesystem::exists(filenamenew)) {
                //hier passen beide Dateinamen, es kann also fortgefahren werden!!!
                tempstring = "\'" + tempstring2 + "\'" + " wird in " + "\'" + tempstring3 + "\'" + " umbenannt. Fortfahren?";
                if(myjanein(tempstring)) {
                    const char* temp11;
                    const char* temp12;
                    temp11=filenamenew.c_str();
                    temp12=filenameold.c_str();

                    if (std::rename(temp12, temp11) != 0) {
                    //if (std::rename(filenamenew.c_str(), filenamenew.c_str()) != 0) {
                        std::cout << "Fehler! Die Datei konnte nicht umbenannt werden. Fehlercode: 08" << std::endl;
                        if(!myjanein("\t Umbenennen erneut versuchen?")) {
                            repeat=false;
                        }
                    } else {
                        mydashedline();
                        std::cout << "\tDie Datei wurde erfolgreich umbenannt!" << std::endl;
                        repeat=false;
                        mywaitenter();
                    }
                } else {
                    if(myjanein("Zurzeck zum Hauptmenue? Sonst erneuter Versuch.")) {
                        repeat=false;
                    }
                }
            } else {
                if(!myjanein("Eingegebener Dateiname existiert bereits! Erneut versuchen?")) {
                    repeat=false;
                }
            }
        } else {
            if(!myjanein("Eingegebener Dateiname existiert nicht! Erneut versuchen?")) {
                repeat=false;
            }
        }
    }
    main_menu();
}

void mylistfiles() {

    mydashedline();
    std::vector<std::string> myfilenames;// Array vom Typ std::string mit dynamischer laenge!
    std::vector<std::string> mynumberofsongs;
    nlohmann::json tempplaylist;
    
    if (std::filesystem::exists(mypath) && std::filesystem::is_directory(mypath)) {//verzeichnis existiert && ist valide/gueltig
        for (const auto& myfile : std::filesystem::directory_iterator(mypath)) {//es wird ueber alle dateien iteriert
            if (std::filesystem::is_regular_file(myfile)) {//Einzelne datei existiert(ist gueltiger dateityp)

                std::string filepath = myfile.path().string();//Pfad der Datei (die existiert) --> path2
                std::string extension = myfile.path().extension().string();//Dateiendung auslesen
                
                if (extension == ".json") {//es werden NUR .json Dateien eingelesen
                    myfilenames.push_back(myfile.path().filename().string());//Dateinamen dynamisch allokierten array zwischenspeichern
                }
            }
        }

        tempbool = false;
        std::cout << "     In dem Verzeichnis >" << mypath << "< wurden " << myfilenames.size() << " Playlists gefunden!" << std::endl;
        for (std::vector<std::string>::size_type i=0; i<myfilenames.size(); i++) {
            //Auslesen der Anzahl an Songs!
            try {
                //std::cout << myaddjson(myfilenames[i], true);
                std::ifstream file(myaddjson(myfilenames[i], true));//haette filepath auch zu einem vector<string> machen koennen!
            if (!file.is_open()) {
                tempbool=true;
                mynumberofsongs.push_back("-Fehler-");
            }
            //Datei ist offen und wird eingelesen
            file >> tempplaylist;
            file.close();
            mynumberofsongs.push_back(std::to_string(tempplaylist["data"].size()));
            }
            catch (const std::exception& e) {
                if(!tempbool) {
                    mynumberofsongs.push_back("-Fehler-");
                }
            }

            tempstring = "  Playlist[" + std::to_string(i+1) + "/" + std::to_string(myfilenames.size()) + "]:";
            std::cout << std::left << std::setfill(' ') << std::setw(22) << tempstring
            << std::setw(22) << myfilenames[i]
            << std::setw(7) << "-"
            << std::setw(19) << "Anzahl an Songs: "
            << std::setw(5) << mynumberofsongs[i] << std::endl;

            //std::cout << "  Playlist [" << (i+1) << "/" << myfilenames.size() << "]:   " << myfilenames[i] << "  -  Anzahl an Songs: "<< mynumberofsongs[i] << std::endl;
            //gegebenenfalls noch die Playlistlaenge angeben. Muss die Datei dafuer geoeffnet werden?? Ja .. schwierig
            //naja wir koennten alles mit eine try/catch block absichern und wenn eine datei nicht geoeffnet werden kann...
            //...wird eben '---' oder 'Fehler!' anstatt der laenge angezeigt, waere ja kein sehr grosses problem fuer den user.
        }
        //(sobald die funktion verlassen wird werden die arrays automatisch geloescht und ihre speicher wieder befreit)
    } else {
        //sollte eigentlich nicht passieren
        std::cout << "Fehler! Der spetifizierte Pfad existiert nicht. Fehlercode: 09" << std::endl;
        std::cout << "\t---Der spezifizierte Pfad lautet: >" << mypath << "<.---" << std::endl;
    }
    mywaitenter();
    main_menu();
}

void myexit(std::string inputstring) {
    //funktion ueberprueft inputs auf "beenden" und beendet dann das programm,
    char inputchar[50];
    std::memset(inputchar, 0, sizeof(inputchar));//char leeren
    std::copy(inputstring.begin(), inputstring.end(), inputchar);//inputstring in char schreiben
    if(strcasecmp(inputchar, "beenden")==0) {//hier koennen sehr leicht andere woerter, wie "exit" oder "schliessen" ergaenzt werden
        std::cout << std::endl << "\tDer Musikplayer wurde vom Benutzer beendet." << std::endl;
        exit(0);
    }
}

void mywaitenter() {
    std::cout << ">mit Enter zurueck zum Hauptmenue...";
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Enter ignorieren
    std::cin.get();//std::cin.clear();
    //while(std::cin.get() != '\n') {
    //    std::cin.clear();//Input Buffer KOMPLETT loeschen
    //}
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
    //testtestsette
    //ersetzt die einzelnen abfragen um den code zu vereinfachen/fehler zu vermeiden
    bool repeatjn = true;
    char answerjn[100];    
    std::string stringjn;

    //std::cin.ignore();
    while (repeatjn) {
        std::cout << message << " (Ja/Nein): ";
        std::getline(std::cin, stringjn);//jetzt immun gegen leerzeichen!
        myexit(stringjn);

        std::memset(answerjn, 0, sizeof(answerjn));//char leeren
        std::copy(stringjn.begin(), stringjn.end(), answerjn);//in char wandeln
        
        if (strcasecmp(answerjn, "ja") == 0) {
            repeatjn = false;
            return true;
        }
        if (strcasecmp(answerjn, "nein") == 0) {
            repeatjn = false;
            return false;
        }
    }
    //------------------------!!!ACHTUNG!!!------------------------
    //!!!!!Das folgende return statement wird NIEMALS erreicht!!!!!
    //Es dient jediglich dazu, die folgende Compiler Warnung zu vermeiden
    //>>warning: control reaches end of non-void function [-Wreturn-type]<<
    //die obige logik wird IMMER den jeweiligen true/false wert zurueckgeben...
    //...beziehungsweise das programm auf wunsch des benutzers schliesssen
    return false;
}

std::string myaddjson(std::string filenamein, bool addpath) {
    if (filenamein.find(".json") != std::string::npos) {
    } else {
        filenamein = filenamein + ".json";//.json wird angefuegt
    }
    if(addpath) {
        filenamein = mypath + filenamein;
    }
    return filenamein;
}

void mycheckname(std::string filenamein2) {
    if (filenamein2.find("/") != std::string::npos || filenamein2.find("\\") != std::string::npos || filenamein2.find("*") != std::string::npos
    || filenamein2.find("!") != std::string::npos || filenamein2.find("?") != std::string::npos || filenamein2.find("%") != std::string::npos
    || filenamein2.find("§") != std::string::npos || filenamein2.find("$") != std::string::npos || filenamein2.find("&") != std::string::npos
    || filenamein2.find(":") != std::string::npos || filenamein2.find("ß") != std::string::npos || filenamein2.find("@") != std::string::npos
    || filenamein2.find("ü") != std::string::npos || filenamein2.find("ö") != std::string::npos || filenamein2.find("ä") != std::string::npos
    || filenamein2.find("(") != std::string::npos || filenamein2.find(")") != std::string::npos || filenamein2.find("#") != std::string::npos
    || filenamein2.find("\"") != std::string::npos || filenamein2.find("\'") != std::string::npos || filenamein2.find("^") != std::string::npos
    || filenamein2.find("<") != std::string::npos || filenamein2.find(">") != std::string::npos || filenamein2.find("|") != std::string::npos
    || filenamein2.find(",") != std::string::npos || filenamein2.find(";") != std::string::npos || filenamein2.find("+") != std::string::npos
    || filenamein2.find("~") != std::string::npos || filenamein2.find("=") != std::string::npos || filenamein2.find("€") != std::string::npos) {//_ '\\' ==> '\'
        std::cout << "Fehler! Nicht erlaubte Zeichen eingegeben. Fehlercode: 05"<<std::endl;
        mywaitenter();
        main_menu();
    }//ggfs. durch andere zeichen ergaenzen, vllt. sogar invertieren!
    if (!(filenamein2.find(".json") != std::string::npos)) {
         if (filenamein2.find(".") != std::string::npos) {
            std::cout << "Fehler! Nicht erlaubte Zeichen eingegeben. Fehlercode: 05"<<std::endl;
            mywaitenter();
            main_menu();
         }
    }//punkt eingegeben, ohne dass '.json' vorkommt
}

nlohmann::json myreadfile(int select2) {
    //filename in globale variable z.B. filename 2 schreiben
    //erst dann in filename wenn schreiben in datei abgeschlossen ist!!

    
    nlohmann::json playlistread;
    std::string filenameread;
    bool repeatread = true;//damit andere loops nicht beeinflusst werden!!! koennte sonst KATASTROPHAL werden.
    bool userconfirm;

    switch(select2) {
        case 1:
    //z.b. 1=search, 2=delete, 3=open, 4=edit, usw...
            tempstring2="Name der zu oeffnenden Playlist eingeben: ";
            userconfirm=false;//tempstring3="< wird " + tempstring3 + " geoeffnet. Fortfahren?";//Dateiname hier noch nicht verfuegbar
            //follow the pattern! dann auch unnnoetige abfragen spaeter in den einzelnen funktionen entfernen
        break;
        case 2:
            tempstring2="Name der zu durchsuchenden Playlist eingeben: ";
            tempstring3="< wird " + tempstring3 + " durchsucht. Fortfahren?";
            userconfirm=true;
        break;
        case 3:

        break;
        case 4:

        break;
        default:
            main_menu();//darf eigentlich nie passieren!!
        break;
    }

    mydashedline();
    while (repeatread) {
        std::cout << tempstring2;
        std::getline(std::cin, filenameread);
        std::cout << "read out>" << filenameread << "< asdasd " << std::endl;
        mycheckname(filenameread);
        tempstring = "Die Datei >" + filenameread/*Dateiname*/ + tempstring3;//wird geoeffnet/durchsucht
        if(userconfirm) {//Fortfahren(Ja/Nein) Abfrage kann hier uebersprungen werden!!!
            if(!myjanein(tempstring)) {
                main_menu();
            }
        }
        filenameread = myaddjson(filenameread, true);
        std::cout << "Die Datei " << filenameread << " wird geoeffnet." << std::endl;

        try {
            std::ifstream fileread(filenameread);
            if (!fileread.is_open()) {
                std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            repeatread = false;

            fileread >> playlistread;//Datei wird eingelesen
            fileread.close();//Datei wird geschlossen
            filename=filenameread;//dateiname wird uebergeben, sobald Datei geoeffnet ist!!
            std::cout << "\tDie Datei wurde geoeffnet" << std::endl;
            return playlistread;
            //-----------------------------------------------------------------
            //was returnen wir, wenn es nicht klappt? leere playlist und das wird dann per if statement geprueft und eine eigene fehlermeldung ausgegeben?!
            //-----------------------------------------------------------------
            //-----------------------------------------------------------------

            mydashedline();
        } catch (const std::exception& error) {
            repeatread = true;//erneut versuchen, da fehler
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 02 mehr informationen: " << std::endl << error.what() << std::endl;
            mydashedline();
        }
    }

    //DAMIT MEIN PROGRAMM WIEDER FUNKTINOIERT - AHHHH!!
    return playlistread;

}

