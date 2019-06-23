window.addEventListener("load", function() {
    showProject();
    
    /* Zeige Bearbeiten Button, wenn eingeloggt */
    let session = sessionStorage.getItem('login');
    if (session) {
        document.getElementById("button_edit").style.display = "inline";
    } else {
        document.getElementById("button_edit").style.display = "none";
    }
});


function showProject() {
    let pID = getUrlVars()["id"];
    let storage = new Storage();

    let projects = storage.readProject();
    let project;

    /* Suche im Speicher nach Projekt */
    for (let i = 0; i < projects.length; i++) {
        if (projects[i].id == pID) {
            project = projects[i];
        }
    }

    if (project){
        /* Header */
        let header = document.getElementById("project_header");
        let header_image = document.createElement("img");
        let header_h1 = document.createElement("h1");
        let header_a = document.createElement("a");
        header.appendChild(header_image);
        header.appendChild(header_h1);
        header.appendChild(header_a);
        header_image.classList.add("projectlogo");
        header_image.src = project.bild;
        header_image.alt = "Header";
        header_h1.innerText = project.titel;
        header_a.rel = "author";
        header_a.innerText = project.projektleiter;
        header_a.href = ""; // später Link zum Nutzeraccount

        /* Kurzbeschreibung */
        let short_description = document.getElementById("p_kurzbeschreibung");
        short_description.innerText = project.kurzbeschreibung;

        /* Kurzbeschreibung */
        let long_description = document.getElementById("p_langbeschreibung");
        long_description.innerHTML = project.langbeschreibung;

        /* Projektziele */
        let project_goals = document.getElementById("ol_projektziele");
        let goal1 = document.createElement("li");
        goal1.innerText = project.ziele[0];
        let goal2 = document.createElement("li");
        goal2.innerText = project.ziele[1];
        project_goals.appendChild(goal1);
        project_goals.appendChild(goal2);


        showComments();
        showRatings();
        modifyContentBoard();
    } else {
        console.error("Das Projekt konnte nicht gefunden werden!");
    }
}

function showComments() {
    let storage = new Storage();
    let pID = getUrlVars()["id"];
    let comments = storage.readComment();
    let c = document.getElementById("d_kommentare");
    c.innerHTML = "";
    let heading = document.createElement("h1");
    heading.innerText = "Kommentare";
    c.appendChild(heading);

    for (let i = 0; i < comments.length; i++){
        if(comments[i].id == pID){
            let p = document.createElement("p");
            p.innerText = "Kommentar:\n\n" + comments[i].kommentar;
            c.appendChild(p);
        }
    }
}

function showRatings() {
    let storage = new Storage();
    let pID = getUrlVars()["id"];
    let ratings = storage.readRating();

    let c = document.getElementById("d_bewertung");
    c.innerHTML = "";
    let heading = document.createElement("h1");
    heading.innerText = "Bewertung";
    c.appendChild(heading);

    let score = 0;
    let number = 0;

    for (let i=0; i<ratings.length; i++) {
        if(ratings[i].id == pID) {
            score += parseInt(ratings[i].bewertung);
            number++;
        }
    }
    let p = document.createElement("p");
    c.appendChild(p);
    if (number > 0) {
        let average = score / number;
        p.innerText = "Durchschnittliche Bewertung: " + average;
    } else {
        p.innerText = "Bisher wurde keine Bewertung abgegeben."
    }

}
function storeComment() {
    let storage = new Storage();
    let value = document.getElementById("kommentar").value;
    let pID = getUrlVars()["id"];
    let comment = new Comment(pID, value, null);
    storage.writeComment(comment);

    let sender = new Sender();
    let parser = new JSONApi();
    let response = sender.postInformation("http://localhost:8080/studfileserver/data/comments.json", parser.commentToJson(comment));
    console.log("Local Storage: " + response);

    response = sender.postInformation("http://localhost:8080/studboardREST/webresources/comment/", parser.commentToJson(comment));
    console.log("Rest: " + response);

    showComments();
}
function storeRating() {
    let storage = new Storage();
    let value = document.getElementById("review").value;
    let pID = getUrlVars()["id"];
    let rating = new Rating(pID, value);
    storage.writeRating(rating);

    let sender = new Sender();
    let parser = new JSONApi();
    let response = sender.postInformation("http://localhost:8080/studfileserver/data/ratings.json", parser.ratingToJson(rating));
    console.log(response);

    showRatings();
}



function getUrlVars() {
    let vars = {};
    window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) {
        vars[key] = value;
    });
    return vars;
}

function modifyContentBoard () {
    let p = document.querySelector("#p_langbeschreibung");
    let headlines = p.querySelectorAll("h1, h2");

    if (headlines.length > 0) {
        var headlineList = document.createElement("ul");
        headlineList.setAttribute("id", "headlineList");
        let list = document.getElementById("langbeschreibung_list");
        list.appendChild(headlineList);
    
        for (let i = 0; i < headlines.length; i++) {
            headlines[i].setAttribute("id", "headline_" + i);
    
            if (headlines[i].nodeName === "H1") {
                var li = document.createElement("li");
                let root = document.getElementById("headlineList");
                root.appendChild(li);
            } else if (headlines[i].nodeName === "H2" && headlines[i - 1].nodeName === "H1") {
                var ul = document.createElement("ul");
                li.appendChild(ul);
                var li = document.createElement("li");
                ul.appendChild(li);
            } else if (headlines[i].nodeName === "H2" && headlines[i - 1].nodeName === "H2") {
                var li = document.createElement("li");
                ul.appendChild(li);
            }
            var link = document.createElement("a");
            li.appendChild(link);
            link.setAttribute("href", ("#" + headlines[i].id));
            link.innerHTML = headlines[i].innerHTML;
        }   
    }



}