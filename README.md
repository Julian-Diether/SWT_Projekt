SoftwareTechnik Projekt

**17.05.**
-Story-Boards und workflow in Jira anlegen
    -Zeitplan festlegen
-anlegen des Git-Hub repository
    verknuepfen mit online verzeichnis
    diverse tests mit git und den vsc plugins
    hinzufuegen anderer teilnehmer
    
-erste Test in cpp
    eingaben auslesen(nicht case-sensitiv), verschiedene programmebenen erstellen

**18.05.**
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

todo:inputs in menu.cpp gegebenenfalls als char speichern um probleme bei eingabe von buchstaben zu vermeiden!

todo:option hinzufuegen um die aktuell geoeffnete playlist umzubenennen?

-Im hauptmenue, sowie song-management menue werden die Befehle nach 6 ungueltigen versuchen nun wiederholt um die bedienfaehigkeit zu vermeiden

-das oeffnen und auslesen funktioniert nun!!
    dateien koennen direkt nach dem oeffnen ausgelesen werden
    dateien sind leichter lesbar, dank warten auf enter druck vor rueckkehr zum haupemenue
    vereinfachung der oeffnen funktion

**19.05**

***Fehlercodes***
    -01 --> fehler bei oeffnen der datei, datei existiert vermutlich nicht
    -02 --> fehler beim oeffnen der datei, sie existiert ist aber z.B. leer
    -03 --> user will datei ausgeben oder durchsuchen waehrend keine geoeffnet ist
    -04 --> die datei die erstellt werden soll wurde nicht geoeffnet (!file2.is_open())
    -05 --> user versuchte beim eingeben des zu loeschenden dateinamen / oder \ zu benutzen
    -06 --> fehler beim loeschen der datei (std::remove(filenamedeletefile) != 0)

-git ignore hinzugefuegt

todo: input laenge eingeben, bei datei erstellen auf integer ueberpruefen. sonst fehlermeldung und wiederholung. Kein Absturz!!

-myexit() / mywaitenter() / mycheckifopen() funktionen hinzugefuegt
    code vereinfacht und verschiedene fehler behoben

todo: beim oeffnen/ausgeben/erstellen von dateien leere eingaben NICHT zulassen!

todo: beim einlesen der dateien sonderzeichen herausfiltern! vllt noch einen hinweis anfuegen, dass diese nicht zulaessig sind!!

-mydashedline() hinzugefuegt und eingesetzt um die lesbarkeit im ganzen programm zu erhoehen

-mycreatefile stark ueberarbeitet und viele fehlerquellen beseitigt
    einlesen von erscheinungsjahr, musikdauer und jugendfrei berichtigt
    bessere uebersichtbarkeit durch mydashedline 

todo: inputs in mycreatefile(): beim auslesen schon leerzeichen und sonderzeichen durch z.B. unterstriche ersetzen!!

**20.05.**
-funktionierendes dateien erstellen

-datei erstellen deutlich besser abgesichert

todo: die diversen checks und failsafes irgendwie ueberpruefen

**21.05.**
todo: beim auslesen der datei, alles schoen untereinander schreiben um lesbarkeit zu erhoehen!!

-funktion vom loeschen von dateien hinzugefuegt und abgesichert

todo:: ueberpruefen ob wir die ganzen bibliotheken brauchen oder funktionen auch in anderen gefunden werden koennen, um das programm einfacher/schneller/kleiner zu machen!!

todo: ueberlegen ob sinnvoll, wenn ja ggfs eigene funktion fuer die ganzen (ja/nein) abfragen erstellen.

todo: ich glaube mycheckifopen funktioniert im momment nicht. wahrscheinlich, weil es die .json endung enthaelt waehrend der user nur den namen der datei eingeben kann. 
    -variable erstellen, die reinen dateinamen enthaelt, falls .json schon dabei ist ihn wieder herausfiltert.

todo: input bei searchfile auf leerzeichen absichern! leerzeichen-->underscore! auch bei createfile und spaeter dort wo songs erstellt/umbenannt, etc werden

-mysearchfile erstellt, ausgiebig getestet und abgesichert.
    -noetige anpassung von menu.cpp

!Fehler: Problem mit mycreatefile(). Datei mit 2 Songs erstellt, beim einlesen der laenge des 1. songs
    in terminal eingegeben: 04:25
    im code angekommen: 04_2505_54
    -fuer song 2 war das kein problem!!
    in terminal eingegeben: 05:54
    im code angekommen: 05_54
    datei: test10.json  immernoch unter playlist/ gespeichert!

-jedes cin, cout und endl mit std:: erhaenzt um moegliche fehler zu vermeiden.

-absicherung des Hauptmenue, damit buchstaben nicht mehr zu fehlern fuehren

todo: herausfinden, ob es zu problemen kommen kann, dass currentplaylist waehrend nutzung des programms offen bleibt (kein file.close();)
^^NEIN! currentplaylist ist jediglich eine lokale nlohman::json. die datei selbst (file) wird direkt wieder geschlossen!

todo: mycheckifopen() reparieren, oder wenn nicht hilfreich/benoetigt abschaffen.

todo: herausfinden, ob beim loeschen von songs irgendwie der ganze eintrag der json datei geloscht werden kann!!
    -ansonsten gibt es danach einen leeren eintrag und playlist.size() ist nicht mehr aussagekraeftig.

todo: herausfinden, ob in dem funktiontsteil in mycreatefile(), der das leerzeichen ersetzt auch unterstriche verwendet wereden!!
    -falls ja: nach anderen zeichen suchen, da doppelpunkte auch durch unterstriche ersetzt werden!!
    -IST DAS UEBERHAUPT EIN PROBLEM??? oder werden die inputs nicht seperat zugewiesen?? vielleicht braucht man es doch nicht...

todo: bei eingabe des jahres (in mycreatefile() und myeditfile()) negative zahlen nicht zulassen?
    ggfs. inputs<1500 und >2100  auch nicht zulassen?

todo: mysearchfile() jetzt aufh mit myopenfile(false) programmieren!
    -sollte das programm deutlich vereinfachen!

-myeditfile() groessten teils fertig gestellt

-menu.cpp gegen falsche inputs abgesichert


