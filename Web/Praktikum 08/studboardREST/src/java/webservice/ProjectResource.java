package webservice;

import java.io.IOException;
import java.io.Serializable;
import java.net.URI;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.xml.bind.JAXBException;
import org.codehaus.jackson.map.AnnotationIntrospector;
import org.codehaus.jackson.map.ObjectMapper;
import org.codehaus.jackson.xc.JaxbAnnotationIntrospector;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

@Path("project")
public class ProjectResource implements Serializable{
    
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response getProject(@QueryParam("id") Long id) throws JAXBException, IOException {
        Project test = new Project("Das hier ist eine Kurzbeschreibung zum Testen", "Das ist eine Langbeschreibung zum Testen", new String[]{"Ziel1, Ziel2"}, "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png", "TestTitel", "2019-05-18", "2019-06-30", "Testleiter");
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
        Project test1 = new Project("Das hier ist eine Kurzbeschreibung zum Testen1", "Das ist eine Langbeschreibung zum Testen1", new String[]{"Ziel1, Ziel2"}, "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png", "TestTitel1", "2019-04-18", "2019-07-30", "Testleiter1");
        Project test2 = new Project("Das hier ist eine Kurzbeschreibung zum Testen2", "Das ist eine Langbeschreibung zum Testen2", new String[]{"Ziel1, Ziel2"}, "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png", "TestTitel2", "2019-03-18", "2019-08-30", "Testleiter2");


        JSONObject obj = new JSONObject();
        JSONArray list = new JSONArray();

        JSONObject project1JSON = new JSONObject();
        project1JSON.put("id", test1.getID());
        project1JSON.put("titel", test1.getTitel());
        project1JSON.put("kurzbeschreibung", test1.getKurzbeschreibung());

        JSONObject project2JSON = new JSONObject();
        project2JSON.put("id", test2.getID());
        project2JSON.put("titel", test2.getTitel());
        project2JSON.put("kurzbeschreibung", test2.getKurzbeschreibung());

        list.add(project1JSON);
        list.add(project2JSON);

        obj.put("allProjects", list);

        Response.ResponseBuilder rb = Response.ok(obj.toJSONString());
        URI locLink1 = URI.create("/project/?id=" + test1.getID());
        URI locLink2 = URI.create("/project/?id=" + test2.getID());
        rb.link(locLink1, "show");
        rb.link(locLink2, "show");
        return rb.build();

    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response create(String project) {
        System.out.println(project);
        Response.ResponseBuilder rb = Response.ok(project);

        URI locLink = URI.create("project/getMore");
        rb.link(locLink, "Liste");
        return rb.build();
    }
    
}
