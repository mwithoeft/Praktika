// Called on install stage
self.addEventListener('install', function (event) {
    // Sicherstellen, dass zuerst alle Dateien im Cache landen
    event.waitUntil(
        caches.open('v1').then(function (cache) {
            console.log("Open Cache");
            return cache.addAll([
                '/index.html',
                '/disclosures.html',
                '/new_project.html',
                '/new_registration.html',
                '/non-warranty.html',
                '/overview.html',
                '/privacy_statement.html',
                '/project_geodatenverarbeitung.html',
                '/project_studboard.html',
                '/receive.html',

                '/includes/favicon.ico',
                '/includes/header320x34.png',
                '/includes/header640x67.png',
                '/includes/header1280x133.png',
                '/includes/header1920x200.png',
                '/includes/Projektlogo.png',
                '/includes/startseite.svg',
                '/includes/video.mp4',

                '/css/style.css',
                '/css/index.css',
                '/css/new_project.css',
                '/css/overview.css',
                '/css/project_page.css',

                '/serviceworker.js',
                '/service-worker.js',

                '/js/jsonapi.js',
                '/js/lang.js',
                '/js/projektverwaltung.js',
                '/js/location.js',
                '/js/localStorage.js',
                '/js/login.js',
            ]);

        })
    );
});

// Wird aufgerufen wenn Dateien angefragt werden
self.addEventListener('fetch', function (evt) {
    console.log("Hole " + evt.request.url);
    evt.respondWith(// Responde with erwartet eine asynchrone Funktion
        caches.match(evt.request).then(
            function (res) {
                console.log("Resource >" + res.url + "< aus dem Cache geholt");
                return res;
            }).catch(function (err) {
                console.log("Resource >" + evt.request.url + "< nicht im Cachegefunden");
                return fetch(evt.request);
            })
    );
});