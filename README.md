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
    -03 --> user will datei ausgenen waehrend keine geoeffnet ist
    -04 --> die datei die erstellt werden soll wurde nicht geoeffnet (!file2.is_open())

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


