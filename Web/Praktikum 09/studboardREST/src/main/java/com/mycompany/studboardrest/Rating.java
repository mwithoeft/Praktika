package com.mycompany.studboardrest;
import java.io.Serializable;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

@Entity(name = "Rating")
@Table(name="rating")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name="Rating.findAll", query="SELECT a FROM Rating a"),
    @NamedQuery(name="Rating.findByProjectId", query="SELECT a FROM Rating a WHERE a.project.id = :projektID")
})
public class Rating implements Serializable {
    
    @Id
    @GeneratedValue
    private long id;
    @Column(name="bewertung")
    private int bewertung;
    
    @ManyToOne
    @JoinColumn(name ="projektID")
    private Project project;
    
    private static long idCounter = 0;

    public Rating() {
    }
    
    public Rating(Project project, int bewertung) {
        this.project = project;
        this.bewertung = bewertung;
        
        this.id = idCounter;
        idCounter++;
    }
    
    public long getID() {
        return this.id;
    }
    
    public Project getProjekt() {
        return this.project;
    }
    public int getBewertung() {
        return this.bewertung;
    }
    
    @Override
    public String toString() {
        String s;
        s = "ID: " + id + " ProjektID: " + project + " Bewertung: " + bewertung;
        return s;
    }
    
}
