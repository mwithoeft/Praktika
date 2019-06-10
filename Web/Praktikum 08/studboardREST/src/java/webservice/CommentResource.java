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

@Path("comment")
public class CommentResource implements Serializable {
    
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response getComment(@QueryParam("id") Long id) throws JAXBException, IOException {
        Comment test = new Comment(id, "Ich fasse es nicht wie geil das ist", null);
        ObjectMapper mapper = new ObjectMapper();
        AnnotationIntrospector introspector = new JaxbAnnotationIntrospector();
        mapper.setAnnotationIntrospector(introspector);
        String result = mapper.writeValueAsString(test);
        Response.ResponseBuilder rb = Response.ok(result);

        URI locLink = URI.create("/comment/getMore?id=" + id);
        rb.link(locLink, "Comments");
        return rb.build();
    }
    
    @GET
    @Path("getMore")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getList(@QueryParam("id") Long id) {
        Comment test1 = new Comment(id, "Test Kommentar1 Klasse Dude", null);
        Comment test2 = new Comment(id, "Test Kommentar2 Super Klasse Dude", null);

        JSONObject obj = new JSONObject();
        JSONArray list = new JSONArray();

        JSONObject comment1JSON = new JSONObject();
        comment1JSON.put("id", test1.getID());
        comment1JSON.put("kommentar", test1.getKommentar());

        JSONObject comment2JSON = new JSONObject();
        comment2JSON.put("id", test2.getID());
        comment2JSON.put("kommentar", test2.getKommentar());

        list.add(comment1JSON);
        list.add(comment2JSON);

        obj.put("allComments", list);

        Response.ResponseBuilder rb = Response.ok(obj.toJSONString());
        URI locLink1 = URI.create("/comment/getMore/?id=" + test1.getID());
        URI locLink2 = URI.create("/comment/getMore/?id=" + test2.getID());
        rb.link(locLink1, "show");
        rb.link(locLink2, "show");
        return rb.build();
    }
    
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response create(String comment) {
        System.out.println(comment);

        Response.ResponseBuilder rb = Response.ok(comment);

        URI locLink = URI.create("comment/getMore");
        rb.link(locLink, "Liste");
        return rb.build();

    }
    
}
