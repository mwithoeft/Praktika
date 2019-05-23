window.addEventListener("load", function () {
    listProjects();
});

function listProjects() {
    let storage = new Storage();
    let projects = storage.readProject();
    let projectAmount = document.getElementById("amount").value;
    /* Clear these two */
    document.getElementsByClassName("overviewprojects")[0].innerHTML = "";
    document.getElementById("project_list").innerHTML = "";

    console.log(projectAmount);

    for (let i = 0; i < projectAmount; i++) {
        if (i < projects.length) {
            addSection(projects[i]);
        }
    }

}

function addSection(project) {
    let section = document.createElement("section");
    let header = document.createElement("header");
    let heading = document.createElement("h1");
    let p = document.createElement("p");
    let footer = document.createElement("footer");
    let a = document.createElement("a");

    section.setAttribute("id", project.id);
    heading.innerText = project.titel;
    p.classList.add("shortdescription");
    p.innerText = project.kurzbeschreibung;
    a.classList.add("lang_to_project");
    a.setAttribute("href","./project.html?id="+project.id);

    document.getElementsByClassName("overviewprojects")[0].appendChild(section);
    section.appendChild(header);
    header.appendChild(heading);
    section.appendChild(p);
    section.appendChild(footer);
    footer.appendChild(a);

    let content = document.getElementById("project_list");
    let li = document.createElement("li");
    let link = document.createElement("a");

    link.setAttribute("href", "#"+project.id);
    link.innerText = project.titel;
    content.appendChild(li);
    li.appendChild(link);


    setLanguage();
}