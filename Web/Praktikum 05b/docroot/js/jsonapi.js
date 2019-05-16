class JSONApi {
    userToJson(user) {
        let userStr = JSON.stringify(user);
        return userStr;
    }
    jsonToUser(userStr) {
        let user = JSON.parse(userStr);
        if (!user) {
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
        let project = JSON.parse(projectStr);
        if (!project) {
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
        let comment = JSON.parse(commentStr);
        if (!comment) {
            comment = [];
        }
        Object.setPrototypeOf(comment, Comment.prototype);
        return comment;
    }
}