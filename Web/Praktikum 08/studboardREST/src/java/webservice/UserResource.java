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

@Path("user")
public class UserResource implements Serializable{
    
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response getUser(@QueryParam("id") Long id) throws JAXBException, IOException {
        User test = new User("User Kurzbeschreibung", "User Langbeschreibung", new String[]{"Userziel1", "Userziel2"}, "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png", "TestNutzer", "testemail@test.de", "testpw");
        ObjectMapper mapper = new ObjectMapper();
        AnnotationIntrospector introspector = new JaxbAnnotationIntrospector();
        mapper.setAnnotationIntrospector(introspector);
        String result = mapper.writeValueAsString(test);
        Response.ResponseBuilder rb = Response.ok(result);
        URI locLink = URI.create("/user/getMore?id=" + id);
        rb.link(locLink, "Users");
        return rb.build();
    }
    
    @GET
    @Path("getMore")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getList() {
        User test1 = new User("User1 Kurzbeschreibung", "User1 Langbeschreibung", new String[]{"Userziel11", "Userziel12"}, "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png", "TestNutzer1", "testemail1@test.de", "testpw");
        User test2 = new User("User2 Kurzbeschreibung", "User2 Langbeschreibung", new String[]{"Userziel21", "Userziel22"}, "http://localhost:8080/studfileserver/projectlogos/Projektlogo.png", "TestNutzer2", "testemail2@test.de", "testpw");


        JSONObject obj = new JSONObject();
        JSONArray list = new JSONArray();

        JSONObject user1JSON = new JSONObject();
        user1JSON.put("id", test1.getID());
        user1JSON.put("benutzername", test1.getBenutzername());
        user1JSON.put("kurzbeschreibung", test1.getKurzbeschreibung());

        JSONObject user2JSON = new JSONObject();
        user2JSON.put("id", test2.getID());
        user2JSON.put("benutzername", test2.getBenutzername());
        user2JSON.put("kurzbeschreibung", test2.getKurzbeschreibung());

        list.add(user1JSON);
        list.add(user2JSON);

        obj.put("allUsers", list);

        Response.ResponseBuilder rb = Response.ok(obj.toJSONString());
        URI locLink1 = URI.create("/user/?id=" + test1.getID());
        URI locLink2 = URI.create("/user/?id=" + test2.getID());
        rb.link(locLink1, "show");
        rb.link(locLink2, "show");
        return rb.build();

    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response create(String user) {
        System.out.println(user);
        Response.ResponseBuilder rb = Response.ok(user);

        URI locLink = URI.create("user/getMore");
        rb.link(locLink, "Liste");
        return rb.build();
    }
    
}
