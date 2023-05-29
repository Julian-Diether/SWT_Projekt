//Software Technik Projekt Gruppe1 -- Julian Diether, Lionel Felipe, Noah Traub, Frederik Kempke
#include "fileops.cpp"//
#include "menu.cpp"

//deklarierung globaler variablen
std::string mypath = "playlists/"; //PFAD ZUM PLAYLIST ORDNER! immer aktuell halten! ggfs. spaeter in einstellungen aenderbar

int main() {
    //welcome_msg(); //Greetings at the programm start
    myinitialize();//wenn ja wird datei initialisiert/wenn nein --> main_menu();
    return 0;
}

