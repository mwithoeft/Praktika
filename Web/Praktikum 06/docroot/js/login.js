window.addEventListener("load", function() {
    let session = sessionStorage.getItem('login');
    if (session) {
        createLogoutForm();
    } else {
        createLoginForm();
    }
});


function createSession() {
    sessionStorage.setItem('login', 'userid');
}
function removeSession() {
    sessionStorage.removeItem('login');
    window.location.href = "./index.html";
}

function createLoginForm() {

    let signIn = document.getElementById("signin");
    
    /* Heading */
    let heading = document.createElement("h1");
    heading.innerText = "Login-Formular";
    signIn.appendChild(heading);



    /* Form */
    let f = document.createElement("form");
    f.setAttribute('method',"post");
    f.setAttribute('action',"receive.html");
    f.setAttribute('onsubmit', "createSession()");
    signIn.appendChild(f);

    /* Unordered List */
    let ul = document.createElement("ul");
    f.appendChild(ul);

    /* List Element 1 */
    let li1 = document.createElement("li");
    ul.appendChild(li1);
    let label1 = document.createElement("label");
    li1.appendChild(label1);
    label1.setAttribute('for',"login");
    label1.innerText = "Benutzer";
    let text = document.createElement("input");
    li1.appendChild(text);
    text.setAttribute('id',"login");
    text.setAttribute('name',"login");
    text.setAttribute('type',"text");

    /* List Element 2 */
    let li2 = document.createElement("li");
    ul.appendChild(li2);
    let label2 = document.createElement("label");
    li2.appendChild(label2);
    label2.setAttribute('for',"password");
    label2.innerText = "Passwort";
    let passwort = document.createElement("input");
    li2.appendChild(passwort);
    passwort.setAttribute('id',"password");
    passwort.setAttribute('name',"password");
    passwort.setAttribute('type',"password");

    /* List Element 3 */
    let li3 = document.createElement("li");
    ul.appendChild(li3);
    li3.appendChild(document.createElement("br"));
    let submit = document.createElement("input");
    li3.appendChild(submit);
    submit.setAttribute('value',"Anmelden");
    submit.setAttribute('type',"submit");
    let registration = document.createElement("a");
    li3.appendChild(registration);
    registration.innerText = "Neu registrieren";
    registration.setAttribute('href',"new_registration.html");
}
function createLogoutForm() {

    let signIn = document.getElementById("signin");

    /* Heading */
    let heading = document.createElement("h1");
    heading.innerText = "Logout";
    signIn.appendChild(heading);

    var button = document.createElement("BUTTON");
    signIn.appendChild(button);
    button.innerText = "Ausloggen";
    button.setAttribute('onclick', "removeSession()");
    button.style.borderRadius = "5px";
    button.style.padding = "5px";
    button.style.margin = "5px";

}