class Sender {

    constructor() { }

    postInformation(url, data) {
        // Default options are marked with *
        return fetch(url, {
            body: JSON.stringify(data), // must match 'Content-Type' header
            cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
            credentials: 'same-origin', // include, *omit
            headers: {
                'user-agent': 'Mozilla/4.0 MDN Example',
                'content-type': 'application/json'
            },
            method: 'POST', // *GET, PUT, DELETE, etc.
            mode: 'cors', // no-cors, *same-origin
            redirect: 'follow', // *manual, error
            referrer: 'no-referrer' // *client
        }).then(response => response.json()); // parses response to JSON
    }

}