class JSONApi {
    userToJson(user) {
        let userStr = JSON.stringify(user);
        return userStr;
    }
    jsonToUser(userStr) {
        let user = JSON.parse(userStr);
        Object.setPrototypeOf(user, User.prototype);
        return user;
    }

    projectToJson(project) {
        let projectStr = JSON.stringify(project);
        return projectStr;
    }
    jsonToProject(projectStr) {
        let project = JSON.parse(projectStr);
        Object.setPrototypeOf(project, Project.prototype);
        return project;
    }
}