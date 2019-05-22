if (navigator.serviceWorker) {
    let serviceworker = navigator.serviceWorker.register('/service-worker.js');
    let succsessfullRegisterFunc = function (reg) {
        console.log("Erfolgreich registriert");
    };

    let errorRegisterFunc = function (err) {
        console.log("Fehler beim Registrieren: " + err);
    };

    serviceworker.then(succsessfullRegisterFunc, errorRegisterFunc);
} else {
    console.log("No ServiceWorker support");
}