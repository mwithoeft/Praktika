class Geolocation {
    constructor() { }

    printLocation(position) {
        console.log("Location");
        for (let i in position.coords) {
            console.log(i + " = " + position.coords[i]);
        }
    }
    printError() {
        console.log("Location konnte nicht abgerufen werden");
    }
}

window.addEventListener("load", function () {
    if (navigator.geolocation) {
        console.log("Test");
        let location = new Geolocation();
        navigator.geolocation.getCurrentPosition(location.printLocation, location.printError);
        navigator.geolocation.watchPosition(location.printLocation);
        console.log("Test2");
    } else {
        console.log("Geolocation not supported");
    }
});

