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
#include "libraries/utf8library/source/utf8.h"//erkennen und filtern von sonderzeichen
#include "libraries/nlohmann/json.hpp"//json manipulation


//inkludierung globaler variablen
std::string mypath;
std::string settingsdir = "settings.json";

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
bool tempbool;
int tempint;

//deklarierung GLOBALER funktionen
void welcome_msg();
void main_menu();
void song_management();

//eigene funktionen
void myinitialize();
void myopenfile(bool justprint);
void myprintfile(bool justopen);
void mycreatefile();
void mydeletefile();
void mysearchfile();
void myeditfile(int select);
void myrenamefile();
void myduplicatefile();
void mylistfiles();

void myexit(std::string inpute);
void mywaitenter();
void mydashedline();
bool myjanein(std::string messagejn);
std::string myaddjson(std::string filenameaj, bool addpath);
void mycheckname(const std::string filenamecn);
nlohmann::json myreadfile(int select2);
void mywritefile(std::string filenamewf, const nlohmann::json writefilewf, bool currentfilewf);
std::string myvalidateutf8(std::string str);
bool myvalidatesyntax(const nlohmann::json& playlistvs);

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
        if (std::filesystem::exists(settingsdir)) {
            std::ifstream tempfile(settingsdir);
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

    currentplaylist = myreadfile(1);
    
    if(!justopen) {
        if(myjanein("Soll die Playlist direkt angezeigt werden?")) {
            myprintfile(false);
        } else {
            main_menu();
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

    std::string filenamecreatefile;
    int length=0;
    int tempyear=0;
    int continuecounter2=0;
    
    mydashedline();
    repeat=true;
    while(repeat) {
        if(continuecounter2>2) {
            continuecounter2=0;
            if(!myjanein("\tFortfahren?")) {
                main_menu();
            }
        }
        std::cout << "Name der neuen Playlist eingeben: ";
        std::getline(std::cin, filenamecreatefile);
        mycheckname(filenamecreatefile);

        filenamecreatefile = myaddjson(filenamecreatefile, false);

        if (std::filesystem::exists(mypath + filenamecreatefile)) {
            continuecounter2++;
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
        catch(std::out_of_range&) {
            std::cout << "Eingegebene Zahl ist viel zu gross! Fehlercode: 12" << std::endl;
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

    //hier beggint das einlesen der neuen songs!
    mydashedline();
    std::cout << "---ACHTUNG!! Bitte keine Sonderzeichen eingeben---" << std::endl;

    //std::memset(answer, 0, sizeof(answer));
    for(int i=0; i<length; i++) {
        mydashedline();
        std::cout << "Informationen fuer Song [" << (i+1) << "/" << length << "] eingeben:" << std::endl;
        std::cout << "Songname: "; std::getline(std::cin, tempstring);title.push_back(myvalidateutf8(tempstring));
        std::cout << "Interpret: "; std::getline(std::cin, tempstring);artist.push_back(myvalidateutf8(tempstring));
        std::cout << "Album: "; std::getline(std::cin, tempstring);album.push_back(myvalidateutf8(tempstring));
        repeat=true;
        tempyear=0;
        while (repeat) {std::cout << "Erscheinungsjahr: ";
            std::getline(std::cin, tempstring);
            //tempstring = myvalidateutf8(tempstring);  // - no need since it has to be an integer any way!!
            try {
                tempyear = std::stoi(tempstring);
            }
            catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde 
                std::cin.clear();//input wird geloescht
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }
            catch(std::out_of_range&) {
                std::cout << "Eingegebene Zahl ist viel zu gross! Fehlercode: 12" << std::endl;
            }

            if(tempyear>0 && tempyear<2500) {
                repeat=false;year.push_back(tempyear);
            } else {//success!
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }
        }

        std::cout << "Laenge [xx:xx]: "; std::getline(std::cin, tempstring); duration.push_back(myvalidateutf8(tempstring));
        std::cout << "Musikrichtung: "; std::getline(std::cin, tempstring); genre.push_back(myvalidateutf8(tempstring));

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

    mywritefile(filenamecreatefile, writefile, false);
}

void mydeletefile() {

    std::string filenamedeletefile;
    std::memset(answer, 0, sizeof(answer));//random sonderzeichen vermeiden
    mydashedline();
    std::cout << "Name der zu loeschenden Playlist eingeben: ";
    std::getline(std::cin, tempstring);

    myexit(tempstring);
    mycheckname(tempstring);
    filenamedeletefile = myaddjson(tempstring, true);

    tempstring = "Playlist >" + filenamedeletefile + "< wird geloescht! Fortfahren?";
    if(!myjanein(tempstring)) {
        main_menu();
    }
    
    
    tempbool=false;
    if(filenamedeletefile==filename) {
        //aktuell geoeffnete playlist wird geloscht
        tempbool=true;
    }

    mydashedline();
    std::copy(filenamedeletefile.begin(), filenamedeletefile.end(), tempchar);
    //hier wird geloescht
    if (std::remove(tempchar) != 0) {
        std::cout << "Fehler! Die Datei konnte nicht geloescht werden. Fehlercode: 06" << std::endl;
    } else {
        std::cout << "\tDie Datei wurde erfolgreich geloescht!" << std::endl;
        if(tempbool) {
            filename = "";//sorgt fuer 'keine playlist geoeffnet' warnung
            currentplaylist.clear();//loescht playlist aus zwischenspeicher
        }
    }
    mywaitenter();
    main_menu(); 
}

void mysearchfile() {

    std::string filenamesearchfile;

    searchplaylist = myreadfile(2);
    tempstring = "Datei >" + tempstring3 + "< wird durchsucht. Fortfahren?";
    if(!myjanein(tempstring)) {
        main_menu();
    }

    //jetzt koennen wir endlich durchsuchen!
    
    std::memset(answer, 0, sizeof(answer));
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

        std::cout << "Achtung! Keine Sonderzeichen! Ausnahme Doppelpunkt." << std::endl;
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
    //myopenfile(true);
    currentplaylist = myreadfile(3);

    if(select==1) {//erhoehte lesbarkeit
        mydashedline();
    }
    //[-Wconversion]
    long long unsigned int playlistsize = currentplaylist["data"].size();
    long long unsigned int playlistsize1;

    if(select==1 || select==4) {playlistsize1=(playlistsize+1);}//hinzufuegen oder duplizieren
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

    //songnummer wird erfragt (ausser ein neuer song wird hinzugefuegt)
    int songposition=0;
    int continuecounter3=0;
    if(select==2||select==3||select==4) {
        
        myprintfile(true);
        repeat=true;
        while(repeat) {
            if(continuecounter3>3) {
                continuecounter3=0;
                if(!myjanein("\tFortfahren?")) {
                    main_menu();
                }
            }
            if(select==2) {
                std::cout << "Welche Songnummer soll bearbeitet werden?: ";
            } if(select==3) {

                if(currentplaylist["data"].size()<2) {//handelt die exception wenn nur ein song vorhanden ist
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
            } if (select==4) {
                std::cout << "welche Songnummer soll dupliziert werden?: ";
            }

            std::getline(std::cin, tempstring);//eingabe erfassen
            try {
                songposition = std::stoi(tempstring);
            }
            catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde 
                std::cin.clear();//input wird geloescht
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
                continuecounter3++;
            }
            catch(std::out_of_range&) {
                std::cout << "Eingegebene Zahl ist viel zu gross! Fehlercode: 12" << std::endl;
                continuecounter3++;
            }
            
            if(songposition>0) {//Zahlen positiv
                if(songposition < static_cast<int>(currentplaylist["data"].size()) + 1) {//if(songposition<currentplaylist["data"].size()+1) {
                    repeat=false;
                    songposition-=1;//sehr wichtig, da die zahlen in c++ bei 0, nicht 1 beginnen!!!!!
                } else {//Zahl groesser als anzahl der eintraege in der Playlist
                    std::cout << "\tEingegebene Zahl ist zu gross!" << std::endl;
                    continuecounter3++;
                }
            } else {//Zahlen negativ
                std::cout << "\tNegative Zahlen/Null sind nicht zulaessig!" << std::endl;
                continuecounter3++;
            }
        }
    }


    //durchfuehren von hinzufuegen/bearbeiten/loeschen
    int tempyear=0;
    if(select==1) {
        playlistsize+=1;
    
    long long unsigned int tempi =(playlistsize-1);
    
        std::cout << "\tACHTUNG!! keine Sonderzeichen eingeben" << std::endl;
        mydashedline();
        std::cout << "Informationen fuer neuen Song eingeben:" << std::endl;
        std::cout << "Songname: "; getline(std::cin, tempstring); title.push_back(myvalidateutf8(tempstring));
        //std::cout << "test" << std::endl;
        std::cout << "Interpret: "; getline(std::cin, tempstring); artist.push_back(myvalidateutf8(tempstring));
        std::cout << "Album: "; getline(std::cin, tempstring); album.push_back(myvalidateutf8(tempstring));
        repeat=true;
        while (repeat) {std::cout << "Erscheinungsjahr: ";
            std::getline(std::cin, tempstring);

            try {
                tempyear = std::stoi(tempstring);//integer eingegeben
            }
            catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde 
                std::cin.clear();//fehler flags werden resettet
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }
            catch(std::out_of_range&) {
                std::cout << "Eingegebene Zahl ist viel zu gross! Fehlercode: 12" << std::endl;
            }

            if(tempyear>0 && tempyear<2500) {
                repeat=false;year.push_back(tempyear);
            } else {//success!n
                std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
            }
        }
        std::cout << "Laenge [xx:xx]: "; getline(std::cin, tempstring);duration.push_back(myvalidateutf8(tempstring));
        std::cout << "Musikrichtung: "; getline(std::cin, tempstring);genre.push_back(myvalidateutf8(tempstring));

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

        std::cout << "Songname: " << title[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            //title.push_back(tempanswer);
            title[songposition] = myvalidateutf8(tempanswer);
        }

        std::cout << "Interpret: " << artist[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            //artist.push_back(tempanswer);
            artist[songposition] = myvalidateutf8(tempanswer);
        }

        std::cout << "Album: " << album[songposition] << std::endl << ">";
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            //album.push_back(tempanswer);
            album[songposition] = myvalidateutf8(tempanswer);
        }

        std::cout << "Erscheinungsjahr: " << year[songposition] << std::endl;
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
                    if(tempyear>0 && tempyear<2500) {//sicherstellen, dass zahl positiv ist! ggfs. andere plausibilitaets checks.
                        repeat=false;
                        //year.push_back(tempyear);
                        year[songposition] = tempyear;            
                    }//success!n
                } catch(std::invalid_argument&) {//falls keine zahl eingegeben wurde
                    std::cin.clear();//input wird geloescht
                    tempanswer="";
                    std::cout << "Fehlerhafte Eingabe! Bitte geben sie eine (positive) Zahl ein!" << std::endl;
                }
                catch(std::out_of_range&) {
                    std::cout << "Eingegebene Zahl ist viel zu gross! Fehlercode: 12" << std::endl;
                }
            }
        }

        std::cout << "Laenge [xx:xx]: " << duration[songposition] << std::endl << ">";// std::cin >> duration[songposition];
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            //duration.push_back(tempanswer);
            duration[songposition] = myvalidateutf8(tempanswer);
        }

        std::cout << "Musikrichtung: " << genre[songposition] << std::endl << ">";// std::cin >> genre[songposition];
        std::getline(std::cin, tempanswer);
        if (!tempanswer.empty()) {
            //genre.push_back(tempanswer);
            genre[songposition] = myvalidateutf8(tempanswer);
        }

        repeat=true;
        std::memset(answer, 0, sizeof(answer));
        if(badwords[songposition]) {std::cout << "Jugendfrei (Ja/Nein): " << "Nein" << std::endl;} else {std::cout << "Jugendfrei (Ja/Nein): " << "Ja" << std::endl;}
        while (repeat) {std::cout << "> (Ja/Nein): ";
            std::getline(std::cin, tempanswer);
            if(!tempanswer.empty()) {

                std::copy(tempanswer.begin(), tempanswer.end(), answer);
                if (strcasecmp(answer, "ja") == 0) {repeat=false;badwords[songposition] = false;}//badwords.push_back(false);}
                if (strcasecmp(answer, "nein") == 0) {repeat=false;badwords[songposition] = true;}//badwords.push_back(true);}
            } else {
                //enter wurde gedrueckt, also wird der input ignoriert und der alte wert beibehalten
                repeat=false;
            }
        }

        std::replace(genre[songposition].begin(), genre[songposition].end(), ':', '_');
        std::replace(title[songposition].begin(), title[songposition].end(), ' ', '_');
        std::replace(artist[songposition].begin(), artist[songposition].end(), ' ', '_');
        std::replace(album[songposition].begin(), album[songposition].end(), ' ', '_');
        std::replace(genre[songposition].begin(), genre[songposition].end(), ' ', '_');
        //ist ja nicht schlimm, dass das auch durchlaeuft, wenn nichts geaendert wurde.

        mydashedline();
    }//ende if(select==2)
        

    if(select==4) {

        playlistsize+=1;
        //long long unsigned int tempi =(playlistsize-1);

        title.push_back(title[songposition]);
        artist.push_back(artist[songposition]);
        album.push_back(album[songposition]);
        year.push_back(year[songposition]);
        genre.push_back(genre[songposition]);
        badwords.push_back(badwords[songposition]);
        duration.push_back(duration[songposition]);

        std::cout << "Song Nr. " << (songposition+1) << " wurde erfolgreich dupliziert!" << std::endl;
    }


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

    //song (ggfs.) loeschen
    if(select==3) {
        //macht es optimisierungstechnisch einen unterschied, dass hier datein eingelesen werden, die im fall 'nein' nicht gebraucht werden??
        tempstring = "ACHTUNG! Soll song Nr. " + std::to_string((songposition+1)) + " wirklich geloscht werden?";
        if(myjanein(tempstring)) {
            writefile["data"].erase(writefile["data"].begin() + songposition);
        } else {
            song_management();
        }
    }//ende song loeschen

    mywritefile(filename, writefile, true);
}

void myrenamefile() {
    //filename wird nichzt benutzt, da hier keine datei geoeffnet wird und es (z.B.) bei myprintfile() zu logischen fehlern kommen koennte
    std::string filenameold;
    std::string filenamenew;
    
    repeat=true;
    while (repeat) {
        //loop verlassen, wenn erfolgreich umbenannt oder aufgegeben
        mydashedline();
        std::cout << "Geben sie den Namen der umzubenennenden Playlist ein: ";
        std::getline(std::cin, filenameold);
        mycheckname(filenameold);
        tempstring2 = filenameold;
        filenameold = myaddjson(filenameold, true);

        if(std::filesystem::exists(filenameold)) {
            std::cout << "Neuen Namen fuer \'" << tempstring2 << "\' eingeben: ";
            std::getline(std::cin, filenamenew);
            mycheckname(filenamenew);
            tempstring3 = filenamenew;
            filenamenew = myaddjson(filenamenew, true);

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
                        std::cout << "Fehler! Datei konnte nicht umbenannt werden. Fehlercode: 08" << std::endl;
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
                    if(myjanein("Zurzeck zum Hauptmenue? \'Nein\' --> erneuter Versuch")) {
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

void myduplicatefile() {
    //filename wird nichzt benutzt, da hier keine datei geoeffnet wird und es (z.B.) bei myprintfile() zu logischen fehlern kommen koennte
    std::string filenameold;
    std::string filenamenew;
    
    repeat=true;
    while (repeat) {
        //loop verlassen, wenn erfolgreich umbenannt oder aufgegeben
        mydashedline();
        std::cout << "Geben sie den Namen der zu duplizierenden Playlist ein: ";
        std::getline(std::cin, filenameold);
        mycheckname(filenameold);
        tempstring2 = filenameold;
        filenameold = myaddjson(filenameold, true);

        if(std::filesystem::exists(filenameold)) {
            std::cout << " Namen fuer duplizierte Playlist eingeben: ";
            std::getline(std::cin, filenamenew);
            mycheckname(filenamenew);
            tempstring3 = filenamenew;
            filenamenew = myaddjson(filenamenew, true);

            if(!std::filesystem::exists(filenamenew)) {
                //hier passen beide Dateinamen, es kann also fortgefahren werden!!!
                tempstring = "\'" + tempstring2 + "\'" + " wird in " + "\'" + tempstring3 + "\'" + " dupliziert. Fortfahren?";
                if(myjanein(tempstring)) {

                    try {
                        std::filesystem::copy(filenameold, filenamenew);
                    }
                    catch (const std::filesystem::filesystem_error& e) {
                        std::cout << "Fehler! Datei konnte nicht dupliziert werden. Fehlercode: 14 - mehr Informationen: " << e.what() << std::endl;
                        if(myjanein("Zurzeck zum Hauptmenue? \'Nein\' --> erneuter Versuch")) {
                        repeat=false;
                    }
                    }

                    mydashedline();
                    std::cout << "\tDie Datei wurde erfolgreich dupliziert!" << std::endl;
                    repeat=false;
                    mywaitenter();
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

void myexit(std::string inpute) {
    //funktion ueberprueft inputs auf "beenden" und beendet dann das programm,
    char inputchar[50];
    std::memset(inputchar, 0, sizeof(inputchar));//char leeren
    std::copy(inpute.begin(), inpute.end(), inputchar);//inputstring in char schreiben
    if(strcasecmp(inputchar, "beenden")==0) {//hier koennen sehr leicht andere woerter, wie "exit" oder "schliessen" ergaenzt werden
        std::cout << std::endl << "\tDer Musikplayer wurde vom Benutzer beendet." << std::endl;
        exit(0);
    }
}

void mywaitenter() {
    std::cout << ">mit Enter zurueck zum Hauptmenue...";
    std::cin.get();//input (der automatisch bis enter geht) abwarten
}

void mydashedline() {
        std::cout << "\t----------------------------------" << std::endl;
}

bool myjanein(std::string messagejn) {
    //testtestsette
    //ersetzt die einzelnen abfragen um den code zu vereinfachen/fehler zu vermeiden
    bool repeatjn = true;
    char answerjn[100];
    std::string stringjn;

    while (repeatjn) {
        std::cout << messagejn << " (Ja/Nein): ";
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

std::string myaddjson(std::string filenameaj, bool addpath) {
    //std::cout << "testsetsttests111: " << filenameaj << std::endl;
    if (filenameaj.find(".json") != std::string::npos) {
    } else {
        filenameaj = filenameaj + ".json";//.json wird angefuegt
    }
    if(addpath) {
        if(filenameaj.find(mypath) != std::string::npos) { } else {
            filenameaj = mypath + filenameaj;
        }
    }
    //std::cout << "testsetsttests222: " << filenameaj << std::endl;
    return filenameaj;
}

void mycheckname(const std::string filenamecn) {

    if (filenamecn.find("/") != std::string::npos || filenamecn.find("\\") != std::string::npos || filenamecn.find("*") != std::string::npos
    || filenamecn.find("!") != std::string::npos || filenamecn.find("?") != std::string::npos || filenamecn.find("%") != std::string::npos
    || filenamecn.find("§") != std::string::npos || filenamecn.find("$") != std::string::npos || filenamecn.find("&") != std::string::npos
    || filenamecn.find(":") != std::string::npos || filenamecn.find("ß") != std::string::npos || filenamecn.find("@") != std::string::npos
    || filenamecn.find("ü") != std::string::npos || filenamecn.find("ö") != std::string::npos || filenamecn.find("ä") != std::string::npos
    || filenamecn.find("(") != std::string::npos || filenamecn.find(")") != std::string::npos || filenamecn.find("#") != std::string::npos
    || filenamecn.find("\"") != std::string::npos || filenamecn.find("\'") != std::string::npos || filenamecn.find("^") != std::string::npos
    || filenamecn.find("<") != std::string::npos || filenamecn.find(">") != std::string::npos || filenamecn.find("|") != std::string::npos
    || filenamecn.find(",") != std::string::npos || filenamecn.find(";") != std::string::npos || filenamecn.find("+") != std::string::npos
    || filenamecn.find("~") != std::string::npos || filenamecn.find("=") != std::string::npos || filenamecn.find("€") != std::string::npos) {//_ '\\' ==> '\'
        mydashedline();
        std::cout << "Fehler! Nicht erlaubte Zeichen eingegeben. Fehlercode: 05"<<std::endl;
        mywaitenter();
        main_menu();
    }//ggfs. durch andere zeichen ergaenzen, vllt. sogar invertieren!
    if (!(filenamecn.find(".json") != std::string::npos)) {
         if (filenamecn.find(".") != std::string::npos) {
            std::cout << "Fehler! Nicht erlaubte Zeichen eingegeben. Fehlercode: 05"<<std::endl;
            mywaitenter();
            main_menu();
         }
    }//punkt eingegeben, ohne dass '.json' vorkommt
}

nlohmann::json myreadfile(int select2) {
    //filename in globale variable z.B. filename 2 schreiben
    //erst dann in filename, wenn schreiben in datei abgeschlossen ist!!
    
    nlohmann::json playlistread = {
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
    std::string filenameread;
    std::string tempstringfr = "";
    bool repeatread = true;//damit andere loops nicht beeinflusst werden!!! koennte sonst KATASTROPHAL werden.
    bool makecurrentfile=false;//die datei die in myprintfile() angezeigt wird (aus der musik abgespielt werden soll)
    int continuecounter = 0;

    switch(select2) {
        case 1:
    //z.b. 1=search, 2=delete, 3=open, 4=edit, usw...
            tempstringfr="Name der zu oeffnenden Playlist eingeben: ";
            //userconfirm=false;//tempstring3="< wird " + tempstring3 + " geoeffnet. Fortfahren?";//Dateiname hier noch nicht verfuegbar
            makecurrentfile=true;
            //follow the pattern! dann auch unnnoetige abfragen spaeter in den einzelnen funktionen entfernen
        break;
        case 2:
            tempstringfr="Name der zu durchsuchenden Playlist eingeben: ";
        break;
        case 3:
            tempstringfr="Name der zu bearbeitenden Playlist eingeben: ";
            makecurrentfile=true;
        break;
        default:
            main_menu();//darf eigentlich nie passieren!!
        break;
    }


    mydashedline();
    while (repeatread) {
        if(continuecounter>2) {
            continuecounter=0;
            if(!myjanein("\t\tFortfahren?")) {
                main_menu();
            }
        }
        std::cout << tempstringfr;
        std::getline(std::cin, filenameread);
        mycheckname(filenameread);
        filenameread = myaddjson(filenameread, true);
        if(select2==2) {tempstring3=filenameread;}//So kann der Dateiname in der Abfrage fortzufahren verwendet werden!

        if(!std::filesystem::exists(filenameread)) {
            continuecounter++;// -- wir fragen doch schon nach fortfahren(ja/nein)
            std::cout << "Die Datei konnte nicht geoeffnet werden! Fehlercode: 10" << std::endl;
            //if(myjanein("Eingegebener Dateiname existiert nicht! Erneut versuchen?")) {
                std::cout << "\tEingegebener Dateiname existiert nicht!" << std::endl;
                //break the loop, damit direkt nach einem neuen Namen gefragt wird!
                continue;
            //} else {
            //    main_menu();
            //}
        }

        std::cout << "Datei >" << filenameread << "< wird geoeffnet." << std::endl;
        try {
            std::ifstream fileread(filenameread);
            if (!fileread.is_open()) {
                std::cout << "\nDie Datei konnte nicht geoeffnet werden! Fehlercode: 01" << std::endl;
            } //fehler, wenn datei nicht geoeffnet werden konnte
            repeatread = false;

            fileread >> playlistread;//Datei wird eingelesen
            fileread.close();//Datei wird geschlossen

            if(makecurrentfile){filename=filenameread;}//dateiname wird uebergeben, sobald Datei geoeffnet ist.
            std::cout << "     -Die Datei wurde geoeffnet" << std::endl;

            if(myvalidatesyntax(playlistread)) {
                std::cout << "     -Dateiformat ist gueltig" << std::endl;
            } else {
                continuecounter++;
                repeatread = true;
                playlistread.clear();
                //mywaitenter();
                //main_menu();
            }

            if(!repeatread) {
                return playlistread;
            }//oder wir verlassen hier den loop und gehen zum return am ende der funktion
            //  ^^^^der return wird ja nur gerufen, wenn die datei erfolgreich geoeffnen und
            //      ueberprueft wurde. ansonsten wird die funktion durch aufrufen der
            //      main_menu() bzw. myexit() verlassen und keine playlist muss returned werden
            //-----------------------------------------------------------------
            //was returnen wir, wenn es nicht klappt? leere playlist und das wird dann per if statement geprueft und eine eigene fehlermeldung ausgegeben?!
            //-----------------------------------------------------------------
            //-----------------------------------------------------------------
            mydashedline();
        }
        catch (const std::exception& error) {
            continuecounter++;
            repeatread = true;//erneut versuchen, da fehler
            std::cout << "\nDatei konnte nicht geoeffnet werden! Fehlercode: 02 - mehr informationen: " << std::endl << error.what() << std::endl;
            mydashedline();
        }
    }
    //WIE HANDELN WIR DAS??
    //^gar nicht, dieser Punkt wird nie erreicht, der return dient nur dazu, compiler warnungen loszuwerden!
    return playlistread;
}

void mywritefile(std::string filenamewf, const nlohmann::json writefilewf, bool filecanexist) {

    //---------------------------------------------------------------------
    //ueberpruefen ob dateiname bereits existiert!!!!!
    //  ^^siehe myrenamefile()
    bool repeatwf;
    mydashedline();
    
    if(!filecanexist && std::filesystem::exists(filenamewf)) {//Datei existiert bereits, darf es aber nicht (Neue Datei!!)
        //^^^^ist das nicht redundant, da der gleiche chefkc bereits in mycreatefile erfolgt und auch nur dort relevant ist???
        //if(std::filesystem::exists(filenamewf)) {
        if(myjanein("Erneut mit anderem Dateinamen versuchen?")) {
            //all dass muss nochchmal durchgegeangen und getestet werden!! Nur wie???
            std::cout << "\tNeuen Dateinamen eingeben: ";
            std::getline(std::cin, filenamewf);
            mycheckname(filenamewf);
        } else {
            main_menu();
        }
    }

    filenamewf = myaddjson(filenamewf, true);
    //fuehrt aufgrund der checks nicht zu fehlern. Hinzufuegen nur wenn noch nicht vorhanden!!

    repeatwf=true;
    while(repeatwf) {
        std::ofstream filewf(filenamewf);//hier unbedingt alles einheitlich machen mit add json

        if (!filewf.is_open()) {
            std::cout << "Datei konnte nicht geoeffnet werden, um Daten zu speichern! Fehlercode: 04" << std::endl;
            
            if(myjanein("Erneut mit anderem Dateinamen versuchen?")) {
                //all dass muss nochchmal durchgegeangen und getestet werden!! Nur wie???
                std::cout << "\tNeuen Dateinamen eingeben: ";
                std::getline(std::cin, filenamewf);
                mycheckname(filenamewf);
                //zurueck in den loop, hoffentlich klappt es
            } else {
                main_menu();
            }
        } else {
            repeatwf=false;
            filewf << writefilewf.dump(2);//lokale json variable in externe datei
            currentplaylist = writefilewf;//
            filename = filenamewf;
            
            filewf.close();//feierabend! datei schliessen
            std::cout << "--Daten erfolgreich in " << filenamewf << " gespeichert!--" << std::endl;
            mywaitenter();
            main_menu();
        }
    }
}

std::string myvalidateutf8(std::string str) {
    //https://github.com/nemtrif/utfcpp
    
    std::string temp;
    utf8::replace_invalid(str.begin(), str.end(), back_inserter(temp));

    std::replace(temp.begin(), temp.end(), '[', '?');
    std::replace(temp.begin(), temp.end(), ']', '?');
    std::replace(temp.begin(), temp.end(), '{', '?');
    std::replace(temp.begin(), temp.end(), '}', '?');
    return temp;
}   

bool myvalidatesyntax(const nlohmann::json& playlistvs) {
    
    bool validvs = true;
    long long unsigned int lengthvs = 0;// [-Wconversion]
    //std::string tempstringvs = "";
    std::string tempstring2vs = "";
    bool error1vs = false;//syntax falsch
    bool error2vs = false;//objekt fehlt
    std::vector<std::string> errmsgs1;
    std::vector<std::string> errmsgs2;

    if(!playlistvs.contains("data")) {
        validvs = false;
        mydashedline();
        std::cout << "Fehler! Datei Format ist inkorrekt. Fehlercode: 11" << std::endl;
        std::cout << "\tDas Objekt  \"data\" existiert nicht" << std::endl;
    } else {
        lengthvs = playlistvs["data"].size();//ist immer >0, da sonst

        for(long long unsigned i=0; i<lengthvs; i++) {

            //ueberpruefen der einzelnen merkmale fuer jeden song
            if(playlistvs["data"][i].contains("title")) {
                if (!(playlistvs["data"][i]["title"].type() == nlohmann::json::value_t::string)) {
                    error2vs = true;
                    tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Inkorrektes Attribut: Titel";
                    errmsgs2.push_back(tempstring2vs);
                }
            } else {
                error1vs = true;
                tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Fehlendes Attribut: Titel";
                errmsgs1.push_back(tempstring2vs);
            }


            if(playlistvs["data"][i].contains("album")) {
                if (!(playlistvs["data"][i]["album"].type() == nlohmann::json::value_t::string)) {
                    error2vs = true;
                    tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Inkorrektes Attribut: Album";
                    errmsgs2.push_back(tempstring2vs);
                }
            } else {
                error1vs = true;
                tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Fehlendes Attribut: Album";
                errmsgs1.push_back(tempstring2vs);
            }


            if(playlistvs["data"][i].contains("artist")) {
                if (!(playlistvs["data"][i]["artist"].type() == nlohmann::json::value_t::string)) {
                    error2vs = true;
                    tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Inkorrektes Attribut: Interpret";
                    errmsgs2.push_back(tempstring2vs);
                }
            } else {
                error1vs = true;
                tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Fehlendes Attribut: Interpret";
                errmsgs1.push_back(tempstring2vs);
            }


            if(playlistvs["data"][i].contains("date")) {
                if (!(playlistvs["data"][i]["date"].type() == nlohmann::json::value_t::number_unsigned)) {
                    error2vs = true;
                    tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Inkorrektes Attribut: Erscheinungsjahr";
                    errmsgs2.push_back(tempstring2vs);
                }
            } else {
                error1vs = true;
                tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Fehlendes Attribut: Erscheinungsjahr";
                errmsgs1.push_back(tempstring2vs);
            }


            if(playlistvs["data"][i].contains("length")) {
                if (!(playlistvs["data"][i]["length"].type() == nlohmann::json::value_t::string)) {
                    error2vs = true;
                    tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Inkorrektes Attribut: Laenge";
                    errmsgs2.push_back(tempstring2vs);
                }
            } else {
                error1vs = true;
                tempstring2vs = "Song Nr. " + std::to_string(i+1) + " - Fehlendes Attribut: Laenge";
                errmsgs1.push_back(tempstring2vs);
            }


            if(playlistvs["data"][i].contains("genre")) {
                if (!(playlistvs["data"][i]["genre"].type() == nlohmann::json::value_t::string)) {
                    error2vs = true;
                    tempstring2 = "Song Nr. " + std::to_string(i+1) + " - Inkorrektes Attribut: Genre";
                    errmsgs2.push_back(tempstring2);
                }
            } else {
                error1vs = true;
                tempstring2 = "Song Nr. " + std::to_string(i+1) + " - Fehlendes Attribut: Genre";
                errmsgs1.push_back(tempstring2);
            }


            if(playlistvs["data"][i].contains("explicit")) {
                if (!(playlistvs["data"][i]["explicit"].type() == nlohmann::json::value_t::boolean)) {
                    error2vs = true;
                    tempstring2 = "Song Nr. " + std::to_string(i+1) + " - Inkorrektes Attribut: Jugenfrei";
                    errmsgs2.push_back(tempstring2);
                }
            } else {
                error1vs = true;
                tempstring2 = "Song Nr. " + std::to_string(i+1) + " - Fehlendes Attribut: Jugendfrei";
                errmsgs1.push_back(tempstring2);
            }
            //mydashedline();
        /*}
        catch(const std::exception& errorvs) {//  der for loop bricht trotzdem nach erstem catch ab :(
            validvs = false;
            mydashedline();
            std::cout << "Fehler! Datei Format ist inkorrekt. Fehlercode: 11" << std::endl;
            std::cout << "Song Nr. " << (i+1) << " -  Inkorrektes Attribut: " << attributevs << std::endl;
            std::cerr << "mehr Informationen: " << errorvs.what() << std::endl;
            continue;
        }
        catch(...) {//const nlohmann::json::exception& error2vs) {
            validvs = false;
            mydashedline();
            std::cout << "Fehler! Datei Format ist inkorrekt. Fehlercode: 11" << std::endl;
            std::cout << "Song Nr. " << (i+1) << " -  Fehlendes Attribut: " << attributevs << std::endl;
            //std::cerr << "mehr Informationen: " << error2vs.what() << std::endl;
            continue;
        }*/
    
        }//end for loop
    }//end: data exists
/*
mydashedline();//////////////test
    if(error1vs) {//////////////test
        std::cout << "true" << std::endl;//////////////test
    } else {//////////////test
        std::cout << "false" << std::endl;//////////////test
    }//////////////test
    if(error2vs) {//////////////test
        std::cout << "true" << std::endl;//////////////test
    } else {//////////////test
        std::cout << "false" << std::endl;//////////////test
    }//////////////test
    std::cout << errmsgs1.size() << std::endl;//////////////test
    std::cout << errmsgs2.size() << std::endl;//////////////test
*/

    //Ausgeben der Fehlermeldungen, "data" existiert but einzelne elemente fehlen oder sind vom falschen typ!!!
    if(error1vs) {
        validvs = false;
        mydashedline();
        std::cout << "Fehler! Datei Format ist inkorrekt. Fehlercode: 11" << std::endl;
        for(const auto& errmsg : errmsgs1) {
            std::cout << errmsg << std::endl;
        }
    }

    if(error2vs) {
        validvs = false;
        if(error1vs) {mydashedline();} else
        {std::cout << "Fehler! Datei Format ist inkorrekt. Fehlercode: 11" << std::endl;}
        for(const auto& errmsg : errmsgs2) {
            std::cout << errmsg << std::endl;
        }
    }

    //tatsaechlicher return
    return validvs;    
}

