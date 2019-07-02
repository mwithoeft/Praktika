window.addEventListener("load", function () {
    recentProjects();
});

function recentProjects() {
    let storage = new Storage();

    let projects = storage.readProject();
    projects.sort(compare);

    let article = $("#recentProjects").append('<h1>Neueste Projekte</h1>');
    let ul = $("<ul> </ul>");
    article.append(ul);


    for (let i = 0; i < 3; i++) {
        if (i < projects.length) {
            let li = $("<li> </li>");
            ul.append(li);
            let entry = $("<a> </a>");
            entry.attr("href","./project.html?id="+projects[i].id);
            entry.text(projects[i].titel);
            li.append(entry);
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