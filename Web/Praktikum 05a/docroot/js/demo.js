var parser = new JSONApi();

var projekt1 = new Project();
projekt1.id = 1;
projekt1.kurzbeschreibung = "Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren.";
projekt1.langbeschreibung = "Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren. Weiterhin können Projekte bewertet und Verbesserungsvorschläge eingereicht werden. Dieses Projekt entwickelt sich stetig weiter, sodass immer wieder neue Features hinzukommen. Das StudBoard richtet sich ausschließlich an Studierende, damit sie ihr bestmögliches Potenzial entfalten können.";
projekt1.projektleiter = "Florian Fehring";
projekt1.startzeitpunkt = "02/04/2019";
projekt1.endzeitpunkt = "06/07/2019";
projekt1.ziele.push("Studierende motivieren ihre Projekte zu veröffentlichen");
projekt1.ziele.push("Das größte an Potential aus jedem Entwickler herausholen");
projekt1.bild = "includes/Projektlogo.png";
projekt1.titel = "StudBoard";

var projekt2 = new Project();
projekt2.id = 2;
projekt2.kurzbeschreibung = "Beim Projekt der Geodatenverarbeitung geht es darum aus Punktwolken in Kombination mit Grundplänen von Häusern eine dreidimensionale Figur des Hauses zu schaffen.";
projekt2.langbeschreibung = "Beim Projekt der Geodatenverarbeitung geht es darum aus Punktwolken in Kombination mit Grundplänen von Häusern eine dreidimensionale Figur des Hauses zu schaffen. Aus diesen Informationen werden für jedes Haus bzw. Grundstück Dateien erzeugt, die die Informationen beinhalten. Mit diesen Informationen kann hinterher weiter gearbeitet werden. Es wird außerdem angestrebt, dass diese Funktion Bestandteil eines größeren Programms wird.";
projekt2.projektleiter = "Justin Drögemeier";
projekt2.startzeitpunkt = "02/04/2019";
projekt2.endzeitpunkt = "03/07/2019";
projekt2.ziele.push("Daten anschaulich darstellen und zur Verfügung stellen");
projekt2.ziele.push("Das größte an Potential aus jedem Entwickler herausholen");
projekt2.bild = "includes/Projektlogo.png";
projekt2.titel = "Geodatenverarbeitung";

var projekt3 = new Project();
projekt3.id = 3;
projekt3.kurzbeschreibung = "Mit RustUML lassen sich mit Hilfe einer bereits definierten Syntax UML-Diagramme beschreiben, die dann von dem entwickelten Programm visualisiert werden.";
projekt3.langbeschreibung = "RustUML ist ein Projekt von Valentin Hertel und Moritz Withöft, welches im Zuge einer Praktikumsaufgabe im Studium an der Fachhochschule Bielefeld entstanden ist. Mit RustUML lässt sich ein vorher überlegtes UML-Diagramm visualisieren. Dabei muss der Nutzer nicht selber an graphischen Oberflächen tätig werden, sondern kann seine Definition für ein UML-Diagramm per Text verarbeiten lassen.";
projekt3.projektleiter = "Moritz Withöft";
projekt3.startzeitpunkt = "01/08/2018";
projekt3.endzeitpunkt = "03/02/2019";
projekt3.ziele.push("Entwicklern ein einfaches Tool zur Visualisierung von UML-Diagrammen bereitstellen");
projekt3.ziele.push("Spaß am Erstellen von UML-Diagrammen wecken");
projekt3.bild = "includes/Projektlogo.png";
projekt3.titel = "RustUML";

var user1 = new User();
user1.id = 1;
user1.kurzbeschreibung = "Hallo, ich bin der Max. Ich entwickle gerne mit der Sprache Python und freue mich darauf, Euch meine Projekte zu zeigen."
user1.langbeschreibung = "Ich studiere seit dem Jahr 2017 an der FH-Bielefeld Campus Minden und habe bereits einige Kenntnisse gewinnen können. Besonders interssiere ich mich für objektorientierte Programmiersprachen, aber auch theoretische Informatik liegt mir sehr am Herzen. Aktuell schreibe ich einige neue Programme, also schaut doch mal bei meinen Projekten vorbei!"
user1.ziele.push("Meine Projekte anderen Nutzern zur Verfügung stellen");
user1.ziele.push("Meine Kenntnisse weiter ausbauen");
user1.bild = "includes/Projektlogo.png";
user1.benutzername = "informatik42";
user1.email = "informatik42@fh-bielefeld.de";
user1.passwort = "NutzerIstAusgedacht";

var jsonStr = "{\"id\":1,\"kurzbeschreibung\":\"Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren.\",\"langbeschreibung\":\"Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren. Weiterhin können Projekte bewertet und Verbesserungsvorschläge eingereicht werden. Dieses Projekt entwickelt sich stetig weiter, sodass immer wieder neue Features hinzukommen. Das StudBoard richtet sich ausschließlich an Studierende, damit sie ihr bestmögliches Potenzial entfalten können.\",\"ziele\":[\"Studierende motivieren ihre Projekte zu veröffentlichen\",\"Das größte an Potential aus jedem Entwickler herausholen\"],\"bild\":\"includes/Projektlogo.png\",\"titel\":\"StudBoard\",\"startzeitpunkt\":\"02/04/2019\",\"endzeitpunkt\":\"06/07/2019\",\"projektleiter\":\"Florian Fehring\"}";



window.onload = function () {
    let projekt1Str = parser.projectToJson(projekt1);
    console.log(projekt1Str);

    let projekt2Str = parser.projectToJson(projekt2);
    console.log(projekt2Str);

    let projekt3Str = parser.projectToJson(projekt3);
    console.log(projekt3Str);

    let user1Str = parser.userToJson(user1);
    console.log(user1Str);

    console.log(projekt1);
    console.log(parser.jsonToProject(jsonStr));

    for (let i in de) {
        console.log(i + " = " + de[i]);
    }
    for (let i in en) {
        console.log(i + " = " + en[i]);
    }
};