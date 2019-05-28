/* Holt die Artikel nur vom Server, wenn sie nicht schon im local storage sind */
var fetchArticles = function () {
    let storage = new Storage();
    if (localStorage.length === 0) {

        /* Hole Projekte */
        fetch('http://localhost:8080/studfileserver/data/projects.json').then(
                function (response) {
                    return response.json();
                }
        ).then(
                function (jsonData) {
                    for(project of jsonData.projects) {
                        storage.writeProject(project);
                    }
                }
        ).catch(function (err) {
            console.log("There has been an error!", err);
        });

        /* Hole User */
        fetch('http://localhost:8080/studfileserver/data/users.json').then(
                function (response) {
                    return response.json();
                }
        ).then(
                function (jsonData) {
                    for(user of jsonData.users) {
                        storage.writeUser(user);
                    }
                }
        ).catch(function (err) {
            console.log("There has been an error!", err);
        });

        /* Hole Ratings */
        fetch('http://localhost:8080/studfileserver/data/ratings.json').then(
                function (response) {
                    return response.json();
                }
        ).then(
                function (jsonData) {
                    for(rating of jsonData.ratings) {
                        storage.writeRating(rating);
                    }
                }
        ).catch(function (err) {
            console.log("There has been an error!", err);
        });

        /* Hole Kommentare */
        fetch('http://localhost:8080/studfileserver/data/comments.json').then(
                function (response) {
                    return response.json();
                }
        ).then(
                function (jsonData) {
                    for(comment of jsonData.comments) {
                        storage.writeComment(comment);
                    }
                    location.reload();
                }
        ).catch(function (err) {
            console.log("There has been an error!", err);
        });

    }
};

window.addEventListener("load", fetchArticles);