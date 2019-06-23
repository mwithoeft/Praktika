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


@XmlRootElement
@Entity(name="Comment")
@Table(name="comment")
@NamedQueries({
    @NamedQuery(name="Comment.findAll", query="SELECT a FROM Comment a"),
    @NamedQuery(name="Comment.findByProjectId", query="SELECT a FROM Comment a WHERE a.project.id = :projektID"),
    @NamedQuery(name="Comment.findByPersonId", query="SELECT a FROM Comment a WHERE a.person.id = :nutzerID")
})
public class Comment implements Serializable {
    @Id
    @GeneratedValue
    private long id;
    @Column(name="kommentar")
    private String kommentar;
    
    @ManyToOne
    @JoinColumn(name="nutzerID")
    private Person person;
    
    @ManyToOne
    @JoinColumn(name ="projektID")
    private Project project;

    public Comment() {
    }
    
    
    public Comment(Project project, String kommentar, Person person) {
        this.person = person;
        this.kommentar = kommentar;
        this.project = project;
    }
    
    public long getID() {
        return this.id;
    }
    public Project getProject() {
        return this.project;
    }
    public String getKommentar() {
        return this.kommentar;
    }
    public Person getNutzer() {
        return this.person;
    }
    
    @Override
    public String toString() {
        String s = "ID: " + id + " ProjektID: " + project + " Kommentar: " + kommentar + " NutzerID: " + person;
        return s;
    }
}
