package com.mycompany.studboardrest;

import java.io.IOException;
import java.io.Serializable;
import java.net.URI;
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

@Path("rating")
public class RatingResource implements Serializable {
    
    @Inject
    private RatingDao ratingDao;
    
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response getRating(@QueryParam("id") Long id) throws JAXBException, IOException {
        Rating test = new Rating(null, 2);
        ObjectMapper mapper = new ObjectMapper();
        AnnotationIntrospector introspector = new JaxbAnnotationIntrospector();
        mapper.setAnnotationIntrospector(introspector);
        String result = mapper.writeValueAsString(test);
        Response.ResponseBuilder rb = Response.ok(result);

        URI locLink = URI.create("/rating/getMore?id=" + id);
        rb.link(locLink, "Ratings");
        return rb.build();
    }
    
    @GET
    @Path("getMore")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getList(@QueryParam("id") Long id) {
        Rating test1 = new Rating(null, 4);
        Rating test2 = new Rating(null, 1);


        JSONObject obj = new JSONObject();
        JSONArray list = new JSONArray();

        JSONObject rating1JSON = new JSONObject();
        rating1JSON.put("id", test1.getID());
        rating1JSON.put("bewertung", test1.getBewertung());

        JSONObject rating2JSON = new JSONObject();
        rating2JSON.put("id", test2.getID());
        rating2JSON.put("bewertung", test2.getBewertung());

        list.add(rating1JSON);
        list.add(rating2JSON);

        obj.put("allRatings", list);

        Response.ResponseBuilder rb = Response.ok(obj.toJSONString());
        URI locLink1 = URI.create("/rating/getMore/?id=" + test1.getID());
        URI locLink2 = URI.create("/rating/getMore/?id=" + test2.getID());
        rb.link(locLink1, "show");
        rb.link(locLink2, "show");
        return rb.build();
    }
    
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response create(String rating) {
        ObjectMapper mapper = new ObjectMapper();
 
        try {
            JsonNode jsonNode = mapper.readTree(rating);
            int id = jsonNode.get("id").asInt();
            int bewertung = jsonNode.get("bewertung").asInt();
            ratingDao.create(new Rating(null, bewertung));
        } catch (IOException ex) {
            Logger.getLogger(CommentResource.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Response.ResponseBuilder rb = Response.ok(rating);

        URI locLink = URI.create("comment/getMore");
        rb.link(locLink, "Liste");
        return rb.build();

    }
    
}
