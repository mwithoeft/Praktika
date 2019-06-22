class Project_User {
    constructor(id, kurzbeschreibung, langbeschreibung, ziele=[], bild) {
        if (new.target === Project_User) {
            throw new TypeError("Abstrakte Klasse kann nicht direkt instanziiert werden");
        }
        this.id = id;
        this.kurzbeschreibung = kurzbeschreibung;
        this.langbeschreibung = langbeschreibung;
        this.ziele = ziele;
        this.bild = bild;
    }
}

class User extends Project_User {
    constructor(id, kurzbeschreibung, langbeschreibung, ziele=[], bild, benutzername, email, passwort) {
        super(id, kurzbeschreibung, langbeschreibung, ziele, bild);
        this.benutzername = benutzername;
        this.email = email;
        this.passwort = passwort;
    }
}

class Project extends Project_User {
    constructor(id, kurzbeschreibung, langbeschreibung, ziele=[], bild, titel, startzeitpunkt, endzeitpunkt, projektleiter) {
        super(id, kurzbeschreibung, langbeschreibung, ziele, bild);
        this.titel = titel;
        this.startzeitpunkt = startzeitpunkt;
        this.endzeitpunkt = endzeitpunkt;
        this.projektleiter = projektleiter;        
    }
}

class Comment {
    constructor(id, kommentar, nutzer) {
        this.id = id;
        this.kommentar = kommentar;
        this.nutzer = nutzer;
    }
}

class Rating {
    constructor(id, bewertung) {
        this.id = id;
        this.bewertung = bewertung;
    }
}