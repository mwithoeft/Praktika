function storeProject() {
    let storage = new Storage();

    let titel = document.getElementById("titel").value;
    let projektleiter = document.getElementById("projektleiter").value;
    let kurzbeschreibung = document.getElementById("text_kurzbeschreibung").value;
    let langbeschreibung = document.getElementById("text_langbeschreibung").value;
    let ziel1 = document.getElementById("projektziel1").value;
    let ziel2 = document.getElementById("projektziel2").value;
    let ziele = [ziel1, ziel2];
    let bild = "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png";
    let startzeitpunkt = document.getElementById("anfangsdatum").value;
    let endzeitpunkt = document.getElementById("enddatum").value;
    let id = storage.readProject().length;

    let p = new Project(id, kurzbeschreibung, langbeschreibung, ziele, bild, titel, startzeitpunkt, endzeitpunkt, projektleiter);
    storage.writeProject(p);

    let sender = new Sender();
    let parser = new JSONApi();
    let response = sender.postInformation("http://localhost:8080/studfileserver/data/projects.json", parser.projectToJson(p));
    console.log(response);

    window.location.replace("./project.html?id=" + id);
}