window.addEventListener("load", function () {
    recentProjects();
});

function recentProjects() {
    let storage = new Storage();

    let projects = storage.readProject();
    projects.sort(compare);

    let article = document.getElementById("recentProjects");
    let heading = document.createElement("h1");
    heading.innerText = "Neueste Projekte";
    article.appendChild(heading);
    let ul = document.createElement("ul");
    article.appendChild(ul);


    for (let i = 0; i < 3; i++) {
        if (i < projects.length) {
            let li = document.createElement("li");
            ul.append(li);
            let entry = document.createElement("a");
            entry.setAttribute("href","./project.html?id="+projects[i].id);
            entry.innerText = projects[i].titel;
            li.appendChild(entry);
        }
    }

}

function compare(a, b) {
    let d1 = new Date(a.startzeitpunkt);
    let d2 = new Date(b.startzeitpunkt);

    /* Neueste Projekte nach vorn */
    if (d1 < d2) {
        return 1;
    }
    if (d1 > d2) {
        return -1;
    }
    return 0;
}