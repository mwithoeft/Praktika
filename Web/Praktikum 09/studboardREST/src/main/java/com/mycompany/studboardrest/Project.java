package com.mycompany.studboardrest;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement
@Entity(name="Project")
@Table(name = "project")
@NamedQueries({
    @NamedQuery(name="Project.findAll", query="SELECT a FROM Project a"),
    @NamedQuery(name="Project.findById", query="SELECT a FROM Project a WHERE a.id = :id")
})
public class Project extends Project_User {
    
    @Column(name="titel")
    private String titel;
    @Column(name="startzeitpunkt")
    private String startzeitpunkt;
    @Column(name="endzeitpunkt")
    private String endzeitpunkt;
    @Column(name="projektleiter")
    private String projektleiter;


    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "nutzerID")
    private Person person;

    public Project() {}
    

    public Project(String kurzbeschreibung, String langbeschreibung, String[] ziele, String bild, String titel, String startzeitpunkt, String endzeitpunkt, String projektleiter, Person person) {
        super(kurzbeschreibung, langbeschreibung, ziele, bild);
        
        this.titel = titel;
        this.startzeitpunkt = startzeitpunkt;
        this.endzeitpunkt = endzeitpunkt;
        this.projektleiter = projektleiter;
        this.person = person;
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

    public void setPerson(Person person) {
        this.person = person;
    }
    
    @Override
    public String toString(){
        String s;
        s = "ID: " + id + "\nKurzbeschreibung: " + kurzbeschreibung + "\nLangbeschreibung: " + langbeschreibung + "\nZiel 1: " + ziel1 + "\nZiel 2: " + ziel2;
        s += "\nTitel: " + titel + "\nStartzeitpunkt: " + startzeitpunkt + "\nEndzeitpunkt: " + endzeitpunkt + "\nProjektleiter: " + projektleiter;
        return s;
    }
    
    
}
