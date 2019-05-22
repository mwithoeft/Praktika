let de = {
    start: "Startseite",
    list: "Liste der Projekte",
    create: "Projekt erstellen",
    short_description: "Kurzbeschreibung",
    long_description: "Langbeschreibung",
    to_project: "Zur Projektseite!",
    rating: "Bewertung",
    project_goals: "Projektziele",
    project_information: "Projektinformation",
    additional: "Zusätzliches"
};

let en = {
    start: "Home",
    list: "List of projects",
    create: "Create a project",
    short_description: "Short description",
    long_description: "Long description",
    to_project: "To project!",
    rating: "Rating",
    project_goals: "Project goals",
    project_information: "Project information",
    additional: "Additional"
};


window.addEventListener("load", function() {
    setLanguage();
});

function setLanguage() {
    let lang;
    if (navigator.language == 'de-DE') {
        lang = de;
    } else if (navigator.language == 'en' || navigator.language == 'en-US' || navigator.language == 'en-NZ') {
        lang = en;
    }

    [].forEach.call(document.getElementsByClassName("lang_list"), function (el) {
        el.innerText = lang.list;
    });
    
    [].forEach.call(document.getElementsByClassName("lang_create"), function (el) {
        el.innerText = lang.create;
    });

    [].forEach.call(document.getElementsByClassName("lang_to_project"), function (el) {
        el.innerText = lang.to_project;
    });

    if (document.getElementById("kurzbeschreibung")) {
        document.getElementById("kurzbeschreibung").firstElementChild.innerText = lang.short_description;
    }
    if (document.getElementById("langbeschreibung")) {
        document.getElementById("langbeschreibung").firstElementChild.innerText = lang.long_description;
    }
    if (document.getElementById("projektziele")) {
        document.getElementById("projektziele").firstElementChild.innerText = lang.project_goals;
    }
    if (document.getElementById("bewertung")) {
        document.getElementById("bewertung").firstElementChild.innerText = lang.rating;
    }
    if (document.getElementById("zusaetzliches")) {
        document.getElementById("zusaetzliches").firstElementChild.innerText = lang.additional;
    }

}