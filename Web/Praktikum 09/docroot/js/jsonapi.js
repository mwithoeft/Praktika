class JSONApi {
    userToJson(user) {
        let userStr = JSON.stringify(user);
        return userStr;
    }
    jsonToUser(userStr) {
        let user;
        try {
            user = JSON.parse(userStr);
        } catch (e) {
            user = [];
        }
        Object.setPrototypeOf(user, User.prototype);
        return user;
    }

    projectToJson(project) {
        let projectStr = JSON.stringify(project);
        return projectStr;
    }
    jsonToProject(projectStr) {
        let project;
        try {
            project = JSON.parse(projectStr);
        } catch (e) {
            project = [];
        }
        Object.setPrototypeOf(project, Project.prototype);
        return project;
    }

    commentToJson(comment) {
        let commentStr = JSON.stringify(comment);
        return commentStr;
    }
    jsonToComment(commentStr) {
        let comment;
        try {
            comment = JSON.parse(commentStr);
        } catch (e) {
            comment = [];
        }
        Object.setPrototypeOf(comment, Comment.prototype);
        return comment;
    }

    ratingToJson(rating) {
        let ratingStr = JSON.stringify(rating);
        return ratingStr;
    }
    jsonToRating(ratingStr) {
        let rating;
        try {
            rating = JSON.parse(ratingStr);
        } catch (e) {
            rating = [];
        }
        Object.setPrototypeOf(rating, Rating.prototype);
        return rating;
    }

}