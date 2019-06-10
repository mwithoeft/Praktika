package webservice;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
public class Rating {
    
    private long id;
    private int bewertung;
    
    public Rating(long id, int bewertung) {
        this.id = id;
        this.bewertung = bewertung;
    }
    
    public long getID() {
        return this.id;
    }
    public int getBewertung() {
        return this.bewertung;
    }
    
}
