package webservice;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
public class User extends Project_User {
    
    private String benutzername;
    private String email;
    private String passwort;
    
    public User(String kurzbeschreibung, String langbeschreibung, String[] ziele, String bild, String benutzername, String email, String passwort) {
        super(kurzbeschreibung, langbeschreibung, ziele, bild);
        
        this.benutzername = benutzername;
        this.email = email;
        this.passwort = passwort;
    }
    
    public String getBenutzername() {
        return this.benutzername;
    }
    public String getEmail() {
        return this.email;
    }
    public String getPasswort() {
        return this.passwort;
    }
    
    
}
