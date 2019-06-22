package com.mycompany.studboardrest;

import java.io.IOException;
import java.io.Serializable;
import java.net.URI;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.inject.Inject;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.xml.bind.JAXBException;
import org.codehaus.jackson.JsonNode;
import org.codehaus.jackson.map.AnnotationIntrospector;
import org.codehaus.jackson.map.ObjectMapper;
import org.codehaus.jackson.xc.JaxbAnnotationIntrospector;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

@Path("project")
public class ProjectResource implements Serializable{
    
    @Inject
    private ProjectDao projectDao;
    
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response getProject(@QueryParam("id") Long id) throws JAXBException, IOException {
        Project test = new Project("Das hier ist eine Kurzbeschreibung zum Testen", "Das ist eine Langbeschreibung zum Testen", new String[]{"Ziel1", "Ziel2"}, "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png", "TestTitel", "2019-05-18", "2019-06-30", "Testleiter", null);
        ObjectMapper mapper = new ObjectMapper();
        AnnotationIntrospector introspector = new JaxbAnnotationIntrospector();
        mapper.setAnnotationIntrospector(introspector);
        String result = mapper.writeValueAsString(test);
        Response.ResponseBuilder rb = Response.ok(result);
        URI locLink = URI.create("/projects/getMore?id=" + id);
        rb.link(locLink, "Projects");
        return rb.build();
    }
    
    
    @GET
    @Path("getMore")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getList() {
        JSONArray list = new JSONArray();

        List<Project> projects = projectDao.findAll();
        for(Project p : projects) {
            JSONObject project1JSON = new JSONObject();
            project1JSON.put("id", p.getID());
            project1JSON.put("titel", p.getTitel());
            project1JSON.put("kurzbeschreibung", p.getKurzbeschreibung());
            list.add(project1JSON);
        }
        JSONObject obj = new JSONObject();
        obj.put("allProjects", list);

        Response.ResponseBuilder rb = Response.ok(obj.toJSONString());
        return rb.build();

    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response create(String project) {
        ObjectMapper mapper = new ObjectMapper();
 
        try {
            JsonNode jsonNode = mapper.readTree(project);
            String titel = jsonNode.get("titel").asText();
            String projektleiter = jsonNode.get("projektleiter").asText();
            String kurzbeschreibung = jsonNode.get("kurzbeschreibung").asText();
            String langbeschreibung = jsonNode.get("langbeschreibung").asText();
            String endzeitpunkt = jsonNode.get("endzeitpunkt").asText();
            String bild = jsonNode.get("bild").asText();
            JsonNode ziele = jsonNode.get("ziele");
            String[] zielArray = mapper.readValue(ziele, String[].class);
            projectDao.create(new Project(kurzbeschreibung, langbeschreibung, zielArray, bild, titel, endzeitpunkt, endzeitpunkt, projektleiter, null));
        } catch (IOException ex) {
            Logger.getLogger(ProjectResource.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Response.ResponseBuilder rb = Response.ok(project);

        URI locLink = URI.create("comment/getMore");
        rb.link(locLink, "Liste");
        return rb.build();
    }
    
}
