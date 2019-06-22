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

/*
if (navigator.geolocation) {
    let location = new Geolocation();
    navigator.geolocation.getCurrentPosition(location.printLocation, location.printError);
    navigator.geolocation.watchPosition(location.printLocation);
} else {
    console.log("Geolocation not supported");
}
*/



