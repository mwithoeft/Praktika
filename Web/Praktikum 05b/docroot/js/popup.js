class Popup {

    constructor() { }

    openPopup(message, time) {
        let fenster1 = window.open("", "popup1", "width=200,height=100 left=200");
        fenster1.document.write(message);
        fenster1.focus();
        fenster1.setTimeout("close()", time);
    }




}

p = new Popup();
if (navigator.language == 'de-DE') {
    p.openPopup('Deutsch: Hallo!', 5000);
} else if (navigator.language == 'en' || navigator.language == 'en-US' || navigator.language == 'en-NZ') {
    p.openPopup('Englisch: Hello!', 5000);
}

