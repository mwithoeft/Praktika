/*DEMO-OBJEKTE*/
var testprojekt1 = new Project();
testprojekt1.id = 1;
testprojekt1.kurzbeschreibung = "Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren.";
testprojekt1.langbeschreibung = "Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren. Weiterhin können Projekte bewertet und Verbesserungsvorschläge eingereicht werden. Dieses Projekt entwickelt sich stetig weiter, sodass immer wieder neue Features hinzukommen. Das StudBoard richtet sich ausschließlich an Studierende, damit sie ihr bestmögliches Potenzial entfalten können.";
testprojekt1.projektleiter = "Florian Fehring";
testprojekt1.startzeitpunkt = "02/04/2019";
testprojekt1.endzeitpunkt = "06/07/2019";
testprojekt1.ziele.push("Studierende motivieren ihre Projekte zu veröffentlichen");
testprojekt1.ziele.push("Das größte an Potential aus jedem Entwickler herausholen");
testprojekt1.bild = "includes/Projektlogo.png";
testprojekt1.titel = "StudBoard";

var testprojekt2 = new Project();
testprojekt2.id = 2;
testprojekt2.kurzbeschreibung = "Beim Projekt der Geodatenverarbeitung geht es darum aus Punktwolken in Kombination mit Grundplänen von Häusern eine dreidimensionale Figur des Hauses zu schaffen.";
testprojekt2.langbeschreibung = "Beim Projekt der Geodatenverarbeitung geht es darum aus Punktwolken in Kombination mit Grundplänen von Häusern eine dreidimensionale Figur des Hauses zu schaffen. Aus diesen Informationen werden für jedes Haus bzw. Grundstück Dateien erzeugt, die die Informationen beinhalten. Mit diesen Informationen kann hinterher weiter gearbeitet werden. Es wird außerdem angestrebt, dass diese Funktion Bestandteil eines größeren Programms wird.";
testprojekt2.projektleiter = "Justin Drögemeier";
testprojekt2.startzeitpunkt = "02/04/2019";
testprojekt2.endzeitpunkt = "03/07/2019";
testprojekt2.ziele.push("Daten anschaulich darstellen und zur Verfügung stellen");
testprojekt2.ziele.push("Das größte an Potential aus jedem Entwickler herausholen");
testprojekt2.bild = "includes/Projektlogo.png";
testprojekt2.titel = "Geodatenverarbeitung";

var testprojects = [testprojekt1, testprojekt2];
var testusers = [];
var testcomments = [];


class Storage {
    
    constructor() {
        this.parser = new JSONApi();
        this.init();
    }

    init() {
        if (typeof (Storage) !== "undefined") {
            let visits = localStorage.getItem("visits");
            if (visits) { // Test if visits is not undefined
                let visitsNo = parseInt(visits); // parse because storage is string only
                visitsNo++;
                localStorage.setItem("visits", visitsNo);
                
                if (visitsNo > 5) { // Wenn mehr als 5 Besuche auf dem 'Konto' stehen, soll der Speicher aktualisiert werden
                    localStorage.clear();
                    localStorage.setItem("visits", 1);
                    this.writeUser(testusers);
                    this.writeProject(testprojects);
                    this.writeComment(testcomments);
                } else {
                    this.readUser();
                    this.readProject();
                    this.readComment();
                }
            } else {
                localStorage.setItem("visits", 1);
                this.writeUser(testusers);
                this.writeProject(testprojects);
                this.writeComment(testcomments);
            }
            console.log("This is your " + localStorage.getItem("visits") + " visit");
        } else {
            console.log("Sorry! No Web Storage support..");
        }
    }

    readUser() {
        console.log("\n Ausgabe der User");
        let items = {...localStorage};
        for (let item in items) {
            let user = this.parser.jsonToUser(items[item]);
            if (user.benutzername) {
                console.log(user);
            }
        }
    }

    readProject() {
        console.log("\n Ausgabe der Projekte");
        let items = {...localStorage};
        for (let item in items) {
            let project = this.parser.jsonToProject(items[item]);
            if (project.projektleiter) {
                console.log(project);
            }
        }
    }

    readComment() {
        console.log("\n Ausgabe der Kommentare");
        let items = {...localStorage};
        for (let item in items) {
            let comment = this.parser.jsonToProject(items[item]);
            if (comment.kommentar) {
                console.log(comment);
            }
        }
    }

    writeUser(users) {
        for (let y = 0; y < users.length; y++) {
            localStorage.setItem("user" + y, this.parser.userToJson(users[y]));
        }
    }
    writeProject(projects) {
        for (let y = 0; y < projects.length; y++) {
            localStorage.setItem("project" + y, this.parser.projectToJson(projects[y]));
        }
    }
    writeComment(comments) {
        for (let y = 0; y < comments.length; y++) {
            localStorage.setItem("comment" + y, this.parser.commentToJson(comments[y]));
        }
    }


}

window.onload = function () {
    let storage = new Storage();
}