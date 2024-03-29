//Software Technik Projekt
Gruppe1 -- Julian Diether, Lionel Felipe, Noah Traub, Frederik Kempke



## Fehlercodes

***Fehlercodes***

    -01 --> fehler bei oeffnen der datei, datei existiert vermutlich nicht

    -02 --> fehler beim oeffnen der datei, sie existiert ist aber z.B. leer

    -03 --> user will datei ausgeben oder durchsuchen waehrend keine geoeffnet ist

    -04 --> die datei die erstellt werden soll wurde nicht geoeffnet (!file2.is_open())

    -05 --> user versuchte beim eingeben des zu loeschenden dateinamen / oder \ zu benutzen

    -06 --> fehler beim loeschen der datei (std::remove(filenamedeletefile) != 0) z.B. falscher Name, Datei existiert nicht, ...

    -07 --> fehler, datei existiert bereits (in mycreatefile())

    -08 --> fehler beim umbenennen der datei (if (std::rename(filenameold.c_str(), filename.c_str()) != 0)) , namen bereits geprueft

    -09 --> der auszulesende ordner existiert nicht. Eigentlich nur moeglich, wenn in settings.json ein nicht vorhandener pfad liegt!

    -10 --> der Dateiname der zu oeffnenden Datei existiert nicht (in myreadfile())
    
    -11 --> das Format der eingelesenen Datei passt nicht zu dem vorgegebenen. (in myvalidatesyntax())

    -12 --> einegebene zahl ist viel zu gross terminate: 'std::out_of_range' (stoi)

    -14 --> die datei konnte nicht dupliziert werden terminate: 'std::filesystem::filesystem_error' (std::filesystem::copy())


## Erklaerung saemtlicher Funktionen

**main.cpp**
<pre>
int main() {
    //ruft die myinitialize() funktion auf
}
</pre>

**fileops.cpp**
<pre>
void myinitialize() {
    //fragt den Nutzer ob zu Start des Programms eine Playlist geoeffnet werden soll
}

void myopenfile(bool justprint) {
    //fragt den Nutzer nach
}

void myprintfile(bool justopen) {
    //gibt die aktuell geoeffnet/intialisierte Datei aus (sofern vorhanden)
}

void mycreatefile() {
    //erstellt eine neue playlist mit beliebige vielen songs
}

void mydeletefile() {
    //loescht eine beliebige playlist
}

void mysearchfile() {
    //durchsucht saemtliche merkmale einer playlist auf ein beliebiges stichwort
}

void myeditfile(int select) {
    //erlaubt das hinzufuegen/bearbeiten/loeschen eines songs in einer playlist
}

void myrenamefile() {
    //benennt eine playlist in einen beliebigen namen um
}

void myduplicatefile() {
    //dupliziert ein playlist in eine neue mit beliebigem namen
}

void mylistfiles() {
    //gibt alle playlists und die anzahl deren songs im aktuellen verzeichnis aus
}

void myexit(std::string inpute) {
    //Hilfsfunktion, die Benutzereingaben auf 'beenden' ueberpruefen und ggfs. das programm schliessen
}

void mywaitenter() {
    //Hilfsfunktion, die wartet bis der Benutzer die Enter-Taste drueckt. Zum Beispiel um eine Fehler-/Statusmeldung zu lesen
}

void mydashedline() {
    //Hilfsfunktion, die eine gestrichelte linie ausgibt um die ubersicht zu steigern
}

bool myjanein(std::string messagejn) {
    //Hilfsfunktion, die eine Frage stellt und die Benutzereingabe auf 'ja' oder 'nein' ueberprueft
}

std::string myaddjson(std::string filenameaj, bool addpath) {
    //Hilfsfunktion, die die Dateiendung '.json', sowie den aktuellen Pfad an den Dateinamen anfuegen (falls noch nicht vorhanden)
}

void mycheckname(std::string filenamecn) {
    //Hilfsfunktion, die den eingegebenen Dateinamen auf unerlaubte Sonderzeichen ueberprueft
}

nlohmann::json myreadfile(int select2) {
    //Funktion die das tatsaechliche auslesen aud Dateien uebernimmt und absichert
}

void mywritefile(std::string filenameinwf, nlohmann::json writefilewf, bool currentfilewf) {
    //Funktion die das tatsaechliche speichern in Dateien uebernimmt und absichert
}

std::string myvalidateutf8(std::string str) {
    //Funktion entfernt vom Benutzer eingegebene Sonderzeichen und Klammern, die in .json Dateien Fehler verursachen koennten
}
</pre>

**menu.cpp**
<pre>
void welcome_msg() {
    //Gibt eine Willkommensnachricht zu Beginn des Programms aus
}

void main_menu() {
    //Zeigt dem Benutzer das Hauptmenue und moegliche auswahlen an
}

void song_management() {
    //Zeigt dem Benutzer den Song-Editor und dessen funktionen an
}

void playlist_management() {
    //Zeigt dem Benutzer den Playlist-Editor und dessen funktionen an
}

int input_validation(int option_num, int whichmenu) {
    //Ueberprueft dass nur die zu den erlaubten auswahlen gehoerenden zahlen eingegben wurden
}
</pre>

**test1.cpp**
<pre>
//Diente dazu diverse funktionen waehrend der entwicklung und dem troubleshooting gezielt und ohne groeßeren aufwand zu testen
</pre>


## Changelogs und ToDo liste

---
**17.05.**
<pre>
-Story-Boards und workflow in Jira anlegen
    -Zeitplan festlegen
-anlegen des Git-Hub repository
    verknuepfen mit online verzeichnis
    diverse tests mit git und den vsc plugins
    hinzufuegen anderer teilnehmer
    
-erste Test in cpp
    eingaben auslesen(nicht case-sensitiv), verschiedene programmebenen erstellen
</pre>
---
**18.05.**
<pre>
json datei layout:
songtitel, kuenstler, album, jahr, laenge des titels?, genre, explicit(y/n)?

-Kommentare ergaenzt!!
    alle wichtigen aufgaben und plaene jetzt im code (hoffentlich) an passender stelle aufgefuehrt!

-viele kleine und groeßere optimisationen im code
-aufteilung der dateioperationen in eine eigene datei fuer einfacheres zusammenarbeiten

-zusammenfuehrung mit felipes menue-datei

-hinzufuegen der 'beenden' funktion zu jedem zeitpunkt!
    (fuer spaeter: kann das eleganter geloest werden??)

-fertigstellung der funktion um dateien zu oeffnen
    seperater pfad, der in main veraenderbar ist
    mehr informationen fuer den benutzer

-teilweise uebersetzung von menu.cpp auf deustsch und zusammenfuehrung mit main.cpp und fileops.cpp

DONEtodo:inputs in menu.cpp gegebenenfalls als char speichern um probleme bei eingabe von buchstaben zu vermeiden!

DONEtodo:option hinzufuegen um die aktuell geoeffnete playlist umzubenennen?

-Im hauptmenue, sowie song-management menue werden die Befehle nach 6 ungueltigen versuchen nun wiederholt um die bedienfaehigkeit zu vermeiden

-das oeffnen und auslesen funktioniert nun!!
    dateien koennen direkt nach dem oeffnen ausgelesen werden
    dateien sind leichter lesbar, dank warten auf enter druck vor rueckkehr zum haupemenue
    vereinfachung der oeffnen funktion
</pre>
---
**19.05**
<pre>
-Fehlercodes hinzugefuegt!

-git ignore hinzugefuegt

DONEtodo: input laenge eingeben, bei datei erstellen auf integer ueberpruefen. sonst fehlermeldung und wiederholung. Kein Absturz!!

-myexit() / mywaitenter() / mycheckifopen() funktionen hinzugefuegt
    code vereinfacht und verschiedene fehler behoben

todo: beim oeffnen/ausgeben/erstellen von dateien leere eingaben NICHT zulassen!

todo: beim einlesen der dateien sonderzeichen herausfiltern! vllt noch einen hinweis anfuegen, dass diese nicht zulaessig sind!!

-mydashedline() hinzugefuegt und eingesetzt um die lesbarkeit im ganzen programm zu erhoehen

-mycreatefile stark ueberarbeitet und viele fehlerquellen beseitigt
    einlesen von erscheinungsjahr, musikdauer und jugendfrei berichtigt
    bessere uebersichtbarkeit durch mydashedline 

DONEtodo: inputs in mycreatefile(): beim auslesen schon leerzeichen und sonderzeichen durch z.B. unterstriche ersetzen!!
</pre>
---
**20.05.**
<pre>
-funktionierendes dateien erstellen

-datei erstellen deutlich besser abgesichert

todo: die diversen checks und failsafes irgendwie ueberpruefen
</pre>
---
**21.05.**
<pre>
DONEtodo: beim auslesen der datei, alles schoen untereinander schreiben um lesbarkeit zu erhoehen!!

-funktion vom loeschen von dateien hinzugefuegt und abgesichert

DONEtodo:: ueberpruefen ob wir die ganzen bibliotheken brauchen oder funktionen auch in anderen gefunden werden koennen, um das programm einfacher/schneller/kleiner zu machen!!

DONEtodo: ueberlegen ob sinnvoll, wenn ja ggfs eigene funktion fuer die ganzen (ja/nein) abfragen erstellen.

DONEtodo: ich glaube mycheckifopen funktioniert im momment nicht. wahrscheinlich, weil es die .json endung enthaelt waehrend der user nur den namen der datei eingeben kann. 
    -variable erstellen, die reinen dateinamen enthaelt, falls .json schon dabei ist ihn wieder herausfiltert.

DONEtodo: input bei searchfile auf leerzeichen absichern! leerzeichen-->underscore! auch bei createfile und spaeter dort wo songs erstellt/umbenannt, etc werden

-mysearchfile erstellt, ausgiebig getestet und abgesichert.
    -noetige anpassung von menu.cpp

!Fehler: Problem mit mycreatefile(). Datei mit 2 Songs erstellt, beim einlesen der laenge des 1. songs
    in terminal eingegeben: 04:25
    im code angekommen: 04_2505_54
    -fuer song 2 war das kein problem!!
    in terminal eingegeben: 05:54
    im code angekommen: 05_54
    datei: test10.json  immernoch unter playlist/ gespeichert!
</pre>
---
**23.05.**
<pre>
-jedes cin, cout und endl mit std:: erhaenzt um moegliche fehler zu vermeiden.

-absicherung des Hauptmenue, damit buchstaben nicht mehr zu fehlern fuehren

DONEtodo: herausfinden, ob es zu problemen kommen kann, dass currentplaylist waehrend nutzung des programms offen bleibt (kein file.close();)
^^NEIN! currentplaylist ist jediglich eine lokale nlohman::json. die datei selbst (file) wird direkt wieder geschlossen!

DONEtodo: mycheckifopen() reparieren, oder wenn nicht hilfreich/benoetigt abschaffen.

DONEtodo: herausfinden, ob beim loeschen von songs irgendwie der ganze eintrag der json datei geloscht werden kann!!
    -ansonsten gibt es danach einen leeren eintrag und playlist.size() ist nicht mehr aussagekraeftig.

DONEtodo: herausfinden, ob in dem funktiontsteil in mycreatefile(), der das leerzeichen ersetzt auch unterstriche verwendet wereden!!
    -falls ja: nach anderen zeichen suchen, da doppelpunkte auch durch unterstriche ersetzt werden!!
    -IST DAS UEBERHAUPT EIN PROBLEM??? oder werden die inputs nicht seperat zugewiesen?? vielleicht braucht man es doch nicht...

DONEtodo: bei eingabe des jahres (in mycreatefile() und myeditfile()) negative zahlen nicht zulassen?
    ggfs. inputs<1500 und >2100  auch nicht zulassen?

DONE:todo: mysearchfile() jetzt aufh mit myopenfile(false) programmieren!
    -sollte das programm deutlich vereinfachen!

-myeditfile() groessten teils fertig gestellt

-menu.cpp gegen falsche inputs abgesichert
</pre>
---
**24.05.**
<pre>
-myeditfile() hinzufuegen komplett, bearbeiten teilweise.

DONEtodo: finden, wo beim einlesen aus der .json datei fehler entstehen!! vor allem bei songlaenge und erscheinungsjahr extrem haeufig/auffaellig/stoerend/destruktiv! unbeding finden

-check, ob datei die erstellt werden soll, bereits existiert. wenn ja fehlercode07!

todo: spacing/padding bei myprintfile() abhaengig von groesse des groessten jeweiligen elements in der playlist machen (sofern das keine informatik masterarbeit wird)

-myprintfile() ueberarbeitet, dass die ausgaben jetzt sehr viel uebersichtlicher sind
    -ausgaben sind jetzt immer (ausser eine element ist ungewoehnlich gross) buendig untereinander geschrieben

-in myprintfile() eine zweite legende unten hinzugefuegt, wenn mehr als 6 songs in einer playlist sind.

-fehlermeldung hinzugefuegt, falls der user versucht einen song aus einer playlist zu loeschen, die nur einen song enthaelt.
    -es kann beim oeffnen leerer, dateien zu fehlern kommen. alle elemente auf null zu setzen waere eine option
    -user kann anschliessen direkt in das mydeletefile(); menue

DONEtodo: special case, dass der nutzer direkt die datei loeschen kann (siehe oben)?? sinvoll?
</pre>
---
**27.05.**
<pre>
-chars in myeditfile() durch strings ersetzt und viele fehler, vor allem bei grossen eingaben vermieden

DONEtodo: mycreatefile() und ggfs. myopenfile()/myprintfile() auch durch strings ersetzen --> deutlich vereinfachter code, weniger stellen a denen durch conversions fehler auftreten koennten

-myeditfile() delete funktioniert jetzt

DONEtodo: einlesen von currentplaylist in die temporaeren variablen, mit catch block absichern.
    -ueberdenken, ob wir die ueberhaupt brauchen und code/commentare vereinfachen

-bugfix: richtige eingaben im haupt-/song- menue wurden ignoriert bis das menue erneut angezeigt wurde, wenn eine falsche eingabe auftrat

-song in playlist bearbeiten hinzugefuegt

-etliche debugging ausgaben entfernt

-viele warnings behoben

-bearbeiten von Dateien hinzugefuegt
</pre>
---
**29.05.**
<pre>
DONEtodo: song bearbeiten, erscheinungsjahr != int absichern!!
</pre>
---
**30.05.**
<pre>
DONEtodo: durchsuchen von erscheinungsdatum hinzufuegen, dazu muss der input zu einem string konvertiert werden. aber wann???
    ist es nicht einfacher, das erscheinungsjahr zu konvertieren? wahrscheinlich schon. doer wo die datei eingelesen wird!

DONEtodo: beim ausgeben de suchergebnisse auch unterstriche in doppelpunkte umwandeln

DONEtodo: leerzeichen bei der eingabe von daten zum erstellen einer playlist (oder?) hinzufuegen eines songs, muss eine loesung gefunden werden!
</pre>
---
**31.05.**
<pre>
-einige warnungen mit vergleich unzulaessiger dateitypen behoben!
    jetzt gibt es nur noch 14(2*7) Warnungen fuer variable Dateilaengen

DONEtodo: Warnungen fuer variable Dateilaengen durch dynamische speicher allokierung beheben!
    sofern es sich ueberhaupt lohnt

todo: code auf anderen betriebssystemen testen
</pre>
---
**05.06.**
<pre>
-addition der myjanein() funktion um häufige abfragen zentral zu regeln, fehler zu vermeiden und den gesamten code etwas zu vereinfachen/entschleiern

-diverse probleme beim einlesen der song eigenschaften (beim erstellen einer playlist) behoben

DONEtodo: herausfinden, was beim erstellen einer datei mit existierendem namen passiert

DONEtodo: diverse fehler zu:
    terminate called after throwing an instance of 'nlohmann::json_abi_v3_11_2::detail::type_error'
      what():  [json.exception.type_error.316] invalid UTF-8 byte at index 4: 0x07
beheben!
    am besten mittels try&catch block absichern und zum hauptmenue zurueckkehren(?).

todo:repeat bei if (!file2.is_open()) (in mycreatefile()) irgendwie provozieren (vielleicht per deub)

-saemtliche char arrays bei mycreatefile() durch strings ersetzt, um diverse probleme zu vermeiden, einheit zu schaffen und benutzung der daten zu vereinfachen
</pre>
---
**06.06.**
<pre>
-vereinfachung saemtlicher funktionen und arbeitsschritte

todo: eingabe von duration auf buchstaben ueberpruefen und fehler ausgeben! (wo?: createfile & editfile(edit song & add song))
^^^^^hier eine while(repeat) schleife, die den repeat auf true setzt und erneut fragt, wenn buchstaben vorhanden sind!!
-jetzt kann auch nach erscheinungsjahr gesucht werden

todo: 575 myjanein - repeat dort auf null setzen?

verschiedene ausgaben wurden benutzerorientierter gestaltet
    -songdauer wird jetzt immer mit doppelpunkt ausgegeben, selbst bei suchergebnissen
    -titel ------||----------       leerzeichen     ------------||---------------
    -album, kuenstler, genre, ^^^
</pre>
---
**07.06.**
<pre>
ganz am ende von mysearchfile(); wurde main_menu(); entfernt.
    eigentlich doch egal, da dieser code nie erreicht wird, sonder stattdessen mit 'nein' oder 'beenden' die schleife schon vorher endet

DONEtodo: sicherheitsabfrage beim suchen auf dort verlegen, wo die datei schon geoffnet wurde(dass man nicht den dateinamen eingeben muss und bestaetigen muss, nur damit ein fehler erscheint)

-myrenamefile() erstellt

-hauptmenue komplett ueberarbeitet und sehr stark vereinfacht!!

DONEtodo: wohin soll fortfahren(ja/nein) zurueckfuehren??? immer main_menu(), oder ggfs. song/playlist_managemment()?

DONEtodo: sonderzeichen!!, aber erst mal punkte im dateiname erkennen

-das tatsaechliche schreiben in eine Datei noch irgendwie absichern??
    am besten in eine zusaetzliche funktion schreoben

-gerade erstellte datei ist jetzt auch die aktuell geoeffnete datei und kann direkt ausgegeben/verwendet werden

DONETODO: currentplaylist immer erst dort zuweisen, wo auch die datei gespeichert wird!!!

DONEtodo: tempstring2&tempstring3 auch enderswo benutzen, damit z.B. myaddjson() vereinfacht werden kann!!
</pre>
---
**08.06.**
<pre>
DONEtodo: settings.xml datei, um z.B. myinitialize() zu umgehen!

DONEtodo: mycreatefile() erneuter versuch(ja/nein) abfrage anstatt direkt ins hauptmenue zu gehen

todo: sind arrays bei mycreatefile nicht zu groß????

-settings.json hinzugefuegt und komplett abgesichert

NOTE: pfad in settings.json muss mit einem / enden. Ohne das / koennten zwar ordner aber keine KEINE DATEIEN geoeffnet werden!

-ausgeben aller playlists mylistfiles() hinzugefuegt

DONEtodo: dynamisch allokierter speicher jetzt auch fuer die diversen variablen, die die playlist auslesen
    ODER!!: alles ueber objekte(structs) machen, anstatt arrays. <-- das klingt nach einem guten plan!!
    ODER!!!!!!!: direkt in, aus der datei lesen
        ^^nicht ueberall moeglich, da es sonst ein albtraum waere alle user inputs abzusichern

-diverse kleinere aenderungen, zum beispiel im menue
</pre>
---
**10.06.**
<pre>
todo: fehlermeldung wenn leerzeichen beim dateinamen eingegeben wrden. zum beispiel bei mycreatefile() - !!!
^^Das machen wir ueber mycheckname(), dafür muss aber mit getline ausgelesen werden!!!! --> myreadfile() !

DONEtodo: in mycreatefile() den fehler if(!file2.is_open()) korrekt absichern!!
    provozieren zum beispiel mit gezielt falschem dateinamen dort wo die datei feoeffnet wird
    ^^circa zeile 380

-mit den folgendem debugging flags gibt es nur noch eine fehlermeldung fuer die ungenutze variable in mycheckifopen()
    -W -Wall -Wpedantic -Wextra -Wconversion -Wformat -Wuninitialized -Wshadow -Wunused-variable

DONEtodo: was ist der plan mit mycheckifopen()? ergibt das irgendeinen sinn?
    mach es optimierungs technisch sinn eine bereits geoeffnete date nicht erneut zu oeffnen
    passiert irgendwo etwas schlimmes wenn eine bereits geoeffnete datei erneut geoeffnet wird?? eigentlich ja nicht

DONEtodo: ggfs. myopenfile() auch anderswo benutzen, um dateien zu oeffnen.

DONEtodo: unebdingt ueberlegen ob das generelle oeffnen und auslesen von dateien in eine zentrale funktion gelegt werrden kann
    auch das schreiben in dateien koennte so durchgefuehrt werden!!

todo: herausfinden, wann diverse switch() >default< getriggert werden, und das ganze, am besten mit eigenem fehlercode, absichern!!!

DONEtodo: alle std::cin durch std::getline() ersetzen, um anfaelligkeit gegen leerzeichen zu beheben
^^dann kann ich auch die ganzen std::cin.ignore() entfernen

todo:: ggfs. fehler wenn bei den verschiedenen integer abfragen kommas bzw. punkte eingegeben werden

-std::cin komplett durch std::getline() ersetzt um viele fehler zum beispiel mit leerzeichen oder ueberbleibenden wertden zu beheben!!

DONEtodo: alle "integer-only" abfragen ueberpruefen

DONEtodo: myexit() ueberall ueberpruefen!!!!

-myexit() jetzt als string, anstatt char gestaltet um unnoetige umwandlungen ausserhalb zu vermeiden
</pre>
---
**12.06.**
<pre>
-absicherung bei der eingabe saemtlicher dateinamen: nach 3 fehlerhaften eingaben wird gefrag, ob zum hauptmenue zurueckgekehrt werden soll. vor allem in leeren verzeichnissen koennte es sonst zu endlos schleifen kommen.
    jetzt noch die frage: wie kann man den nutzer darauf hinweisen??!?

DONEtodo: muss die json datei on myreadfile auch mit dem fuer unsere playlists typischen syntax deklariert werden??
    damit koennten wir 'falsche' dateien schon frueher erkennen und zentral behandeln

-logischer fehler in mysearchfile behoben, der 'verbotene' zeichen hinzufuegte, bevor nach diesen gesucht und fehler gemeldet wurde!
</pre>
---
**13.06.**
<pre>
-beim loeschen der aktuellen playlist wird diese jetzt auch lokal geloscht

-mycheckifopen() geloescht

-diverse kommentare entfernt

todo: pfad (z.B. 'playlists/') nur hinzufuegen, wenn noch nicht hinzugefuegt!!!

-mywritefile() hinzugefuegt und implementiert

-myaddjson addiert den pfad jetzt nur, wenn er noch nicht hinzugefuegt wurde!!

-mehr uebersichtlichkeit unv verstaendlichkeit durch andere variablennamen

-bugfix myexit(), mywritefile(), ...

-myaddjson: aenderungen beim hinzufuegen des pfads erfolgreich getestet!!!

-entfernen saemtlicher auskommentierter code stellen

-vollendung von mywritefile()

-besseres handling zu oeffnen einer datei die nicht existiert

-trim whitespace (leerzeichen entfernen)
</pre>
---
**14.06.**
<pre>
DONEtodo: bedingung - erscheinungsjahr darf nicht groesser als 2500 sein um sehr grosse zahlen zu vermeiden!
    ^^datei erstellen, song bearbeiten, song hinzufuegen

-myvalidateutf8() um alle user inputs, die spaeter in .json dateien geschrieben werden in utf-8 konforme strings umzuwandeln!!
    mit klammern ergaenzt und komplett abgesichert

-abfrage, ob nach 3 fehlversuchen fortgefahren wereden soll jetzt auch beim eingeben eines dateinamen zu erstellen der datei!

-absturz bei eingabe zu grosser zahlen behoben, an folgenden stellen(eigentlich allen) behoben
    --erscheinungsjahr datei erstellen-
    --erscheinungsjahr song bearbeiten-
    --erscheinungsjahr song hinzufuegen-
    --selektion im hauptmenue-
    --anzahl an songs datei erstellen-
    --(bei durchsuchen nicht benoetigt)
    --welcher song bearbeitet werden soll-
    --welcher song geloescht werden soll-

DONEtodo:uerberpruefen ob myvalidate ueberall angewendet wird
</pre>
---
**15.06.**
<pre>
-logik fehler beim aufrufen von mywritefile() in myeditfile() behoben!

-in myeditfile() beim abfragen welcher song bearbeitet/geloescht/dupliziert werden soll eine "Fortfahren?" abfrage nach 3 fehlversuchen ergaentz

-in myeditfile() funktionalitaet zum duplizieren von songs hinzugefuegt,und abgesichert
    song menue dementsprechend angepasst

-logik fehler beim validieren des erscheinungsjahr beim hinzufuegen eines songs zur playlist behoben

-kleinere fehler beim duplizieren eines songs behoben

-validierung des syntax hinzugefuegt. falsch formatierte dateien werden jetzt nicht geoeffnet und eine Fehlermeldung wird ausgegeben

todo: saemtliche zahlen-eingaben mit kommazahlen ueberpruefen!! Auch z.B. wieviele Songs hinzugefuegt werden sollen!!!!!!!

-alter validierungscode und ungenutzte bibliothek entfernt

-saemtliche logik fehler beim ueberpruefen des syntaxes einer playlist behoben myvalidatesyntax() in myreadfile()

todo: position von return playlistread; in myreadfile() ueberdenken!! siehe kommentar vor dem jetzigen return!!!!!

-diverse variablen in myreadfile() und myvalidatesyntax() ersetzt um probleme zu vermeiden

-endlos-schleife beim oeffnen einer datei mit falschem syntax behoben

todo: verify boolean funktion die dann auch beim syntax aufgerufen wird!!!

-myvalidatesyntax() sehr stark vereinfacht!

-myduplicatefile() ergaenzt

-unbenutzte variable in myrenamefile() geloescht

DONEtodo: bei mydeletefile() sicherstellen, dass die playlist existiert bevor sie geloescht werden kann !!
    vergleichbar mit myrenamefile() myduplicatefile()




</pre>

