/*DEMO-OBJEKTE*/
var testprojekt1 = new Project();
testprojekt1.id = 0;
testprojekt1.kurzbeschreibung = "Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren.";
testprojekt1.langbeschreibung = "<h1>Allgemeines</h1>Beim StudBoard Projekt geht es um eine Website, die von Studierenden für Studierende erstellt worden ist, um ihre Projekte zu präsentieren. <h1>Weiteres</h1>Weiterhin können Projekte bewertet und Verbesserungsvorschläge eingereicht werden. Dieses Projekt entwickelt sich stetig weiter, sodass immer wieder neue Features hinzukommen. Das StudBoard richtet sich ausschließlich an Studierende, damit sie ihr bestmögliches Potenzial entfalten können.";
testprojekt1.projektleiter = "Florian Fehring";
testprojekt1.startzeitpunkt = "2019/03/02";
testprojekt1.endzeitpunkt = "2019/07/05";
testprojekt1.ziele.push("Studierende motivieren ihre Projekte zu veröffentlichen");
testprojekt1.ziele.push("Das größte an Potential aus jedem Entwickler herausholen");
testprojekt1.bild = "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png";
testprojekt1.titel = "StudBoard";

var testprojekt2 = new Project();
testprojekt2.id = 1;
testprojekt2.kurzbeschreibung = "Beim Projekt der Geodatenverarbeitung geht es darum aus Punktwolken in Kombination mit Grundplänen von Häusern eine dreidimensionale Figur des Hauses zu schaffen.";
testprojekt2.langbeschreibung = "<h1>Allgemeines</h1>Beim Projekt der Geodatenverarbeitung geht es darum aus Punktwolken in Kombination mit Grundplänen von Häusern eine dreidimensionale Figur des Hauses zu schaffen. <h2>Nützliches</h2>Aus diesen Informationen werden für jedes Haus bzw. Grundstück Dateien erzeugt, die die Informationen beinhalten. <h1>Weiteres</h1>Mit diesen Informationen kann hinterher weiter gearbeitet werden. Es wird außerdem angestrebt, dass diese Funktion Bestandteil eines größeren Programms wird.";
testprojekt2.projektleiter = "Justin Drögemeier";
testprojekt2.startzeitpunkt = "2019/04/07";
testprojekt2.endzeitpunkt = "2019/07/03";
testprojekt2.ziele.push("Daten anschaulich darstellen und zur Verfügung stellen");
testprojekt2.ziele.push("Das größte an Potential aus jedem Entwickler herausholen");
testprojekt2.bild = "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png";
testprojekt2.titel = "Geodatenverarbeitung";

var testprojekt3 = new Project();
testprojekt3.id = 2;
testprojekt3.kurzbeschreibung = "Test";
testprojekt3.langbeschreibung = "Test";
testprojekt3.projektleiter = "Justin Drögemeier";
testprojekt3.startzeitpunkt = "2019/03/31";
testprojekt3.endzeitpunkt = "2019/04/03";
testprojekt3.ziele.push("Test");
testprojekt3.ziele.push("Test");
testprojekt3.bild = "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png";
testprojekt3.titel = "Test";

class Storage {
    
    constructor() {
        this.parser = new JSONApi();
        this.init();
    }

    init() {
        if (typeof (Storage) === "undefined") {
            console.log("Sorry! No Web Storage support..");
        }
    }

    readUser() {
        let items = {...localStorage};
        let fetched = [];
        for (let item in items) {
            let user = this.parser.jsonToUser(items[item]);
            if (user.benutzername) {
                fetched.push(user);
            }
        }
        return fetched;
    }

    readProject() {
        let items = {...localStorage};
        let fetched = [];
        for (let item in items) {
            let project = this.parser.jsonToProject(items[item]);
            if (project.projektleiter) {
                fetched.push(project);
            }
        }
        return fetched;
    }

    readComment() {
        let items = {...localStorage};
        let fetched = [];
        for (let item in items) {
            let comment = this.parser.jsonToProject(items[item]);
            if (comment.kommentar) {
                fetched.push(comment);
            }
        }
        return fetched;
    }
    readRating() {
        let items = {...localStorage};
        let fetched = [];
        for (let item in items) {
            let rating = this.parser.jsonToRating(items[item]);
            if (rating.bewertung) {
                fetched.push(rating);
            }
        }
        return fetched;
    }

    writeUser(user) {
        let fetched = this.readUser();
        for (let y = 0; y <= fetched.length; y++) {
            if (y == fetched.length) {
                localStorage.setItem("user" + y, this.parser.userToJson(user));
            } else {
                localStorage.setItem("user" + y, this.parser.userToJson([y]));
            }
        }
    }
    writeProject(project) {
        let fetched = this.readProject();
        for (let y = 0; y <= fetched.length; y++) {
            if (y == fetched.length) {
                localStorage.setItem("project" + y, this.parser.projectToJson(project));
            }  else {
                localStorage.setItem("project" + y, this.parser.projectToJson(fetched[y]));
            }
        }
    }
    writeComment(comment) {
        let fetched = this.readComment();
        for (let y = 0; y <= fetched.length; y++) {
            if (y == fetched.length) {
                localStorage.setItem("comment" + y, this.parser.commentToJson(comment));
            } else {
                localStorage.setItem("comment" + y, this.parser.commentToJson(fetched[y]));
            }
        }
    }
    writeRating(rating) {
        let fetched = this.readRating();
        for (let y = 0; y <= fetched.length; y++) {
            if (y == fetched.length) {
                localStorage.setItem("rating" + y, this.parser.ratingToJson(rating));
            } else {
                localStorage.setItem("rating" + y, this.parser.ratingToJson(fetched[y]));
            }
        }
    }


}