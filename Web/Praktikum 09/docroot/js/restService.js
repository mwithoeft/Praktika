window.addEventListener("load", fetchAllProjects);
window.addEventListener("load", fetchAllUsers);
window.addEventListener("load", fetchCommentsById);
window.addEventListener("load", fetchRatingsById);
window.addEventListener("load", fetchProjectById);
window.addEventListener("load", fetchUserById);

function fetchAllProjects() {
    let storage = new Storage();
    if (localStorage.length === 0) {
        $.ajax({ 
            type: "GET",
            url: "http://localhost:8080/studboardREST/webresources/project/getMore",
            success: function(data, textStatus, request){
                let alleProjekte = data.allProjects;
                let found = false;
                console.log(alleProjekte);
                for (let i = 0; i<alleProjekte.length; i++) {
                    storage.writeProject(alleProjekte[i]);
                    found = true;
                }
                if (found) location.reload();
            },
            error: function(){
              console.log('Fehler');   
            }
        });
    }
}

function fetchAllUsers() {
    $.ajax({ 
        type: "GET",
        url: "http://localhost:8080/studboardREST/webresources/user/getMore",
        success: function(data, textStatus, request){
            let alleUser = data.allUsers;
            console.log(alleUser);
        },
        error: function(){
            console.log('Fehler');   
        }
    });
}

function fetchCommentsById() {
    $.ajax({ 
        type: "GET",
        url: "http://localhost:8080/studboardREST/webresources/comment/getMore?id=0",
        success: function(data, textStatus, request){
            let alleKommentare = data.allComments;
            console.log(alleKommentare);
        },
        error: function(){
            console.log('Fehler');      
        }
    });
}

function fetchRatingsById() {
    $.ajax({ 
        type: "GET",
        url: "http://localhost:8080/studboardREST/webresources/rating/getMore?id=0",
        success: function(data, textStatus, request){
            let alleRatings = data.allRatings;
            console.log(alleRatings);
        },
        error: function(){
            console.log('Fehler');        
        }
    });
}

function fetchProjectById() {
    $.ajax({ 
        type: "GET",
        url: "http://localhost:8080/studboardREST/webresources/project?id=0",
        success: function(data, textStatus, request){
            console.log(data);
        },
        error: function(){
          console.log('Fehler');   
        }
    });
}

function fetchUserById() {
    $.ajax({ 
        type: "GET",
        url: "http://localhost:8080/studboardREST/webresources/user?id=0",
        success: function(data, textStatus, request){
            console.log(data);
        },
        error: function(){
          console.log('Fehler');   
        }
    });
}
