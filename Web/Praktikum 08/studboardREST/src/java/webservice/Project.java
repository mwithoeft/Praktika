package webservice;
import java.util.Date;
import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement
public class Project extends Project_User {
    
    private String titel;
    private String startzeitpunkt;
    private String endzeitpunkt;
    private String projektleiter;
    
    public Project(String kurzbeschreibung, String langbeschreibung, String[] ziele, String bild, String titel, String startzeitpunkt, String endzeitpunkt, String projektleiter) {
        super(kurzbeschreibung, langbeschreibung, ziele, bild);
        
        this.titel = titel;
        this.startzeitpunkt = startzeitpunkt;
        this.endzeitpunkt = endzeitpunkt;
        this.projektleiter = projektleiter;
    }
    
    public String getTitel() {
        return this.titel;
    }
    public String getStartzeitpunkt() {
        return this.startzeitpunkt;
    }
    public String getEndzeitpunkt() {
        return this.endzeitpunkt;
    }
    public String getProjektleiter() {
        return this.projektleiter;
    }
    
    
    
    
}
