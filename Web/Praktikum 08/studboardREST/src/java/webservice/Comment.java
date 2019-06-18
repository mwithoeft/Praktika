package webservice;

import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement
public class Comment {
    
    private long id;
    private String kommentar;
    private String nutzer;
    
    public Comment(long id, String kommentar, String nutzer) {
        this.id = id;
        this.kommentar = kommentar;
        this.nutzer = nutzer;
    }
    
    public long getID() {
        return this.id;
    }
    public String getKommentar() {
        return this.kommentar;
    }
    public String getNutzer() {
        return this.nutzer;
    }
    
    @Override
    public String toString() {
        String s = "ID: " + id + " Kommentar: " + kommentar + " Nutzer: " + nutzer;
        return s;
    }
}
