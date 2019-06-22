package com.mycompany.studboardrest;

import java.util.ArrayList;
import java.util.List;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
@Entity(name = "Person")
@Table(name = "person")
@NamedQueries({
    @NamedQuery(name="Person.findAll", query="SELECT a FROM Person a"),
    @NamedQuery(name="Person.findById", query="SELECT a FROM Person a WHERE a.id = :id")
})
public class Person extends Project_User {
    
    
    @Column(name="benutzername")
    private String benutzername;
    @Column(name="email")
    private String email;
    @Column(name="passwort")
    private String passwort;
    
    
    @OneToMany(
        mappedBy = "person",
        cascade = CascadeType.ALL,
        orphanRemoval = true
    )
    private List<Project> projects = new ArrayList<>();

    public Person() {
    }
    
    
    public Person(String kurzbeschreibung, String langbeschreibung, String[] ziele, String bild, String benutzername, String email, String passwort) {
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
    
    public void addProjekt(Project projekt) {
        projects.add(projekt);
        projekt.setPerson(this);
    }
 
    public void removeProjekt(Project projekt) {
        projects.remove(projekt);
        projekt.setPerson(null);
    }
    
    @Override
    public String toString(){
        String s;
        s = "ID: " + id + "\nKurzbeschreibung: " + kurzbeschreibung + "\nLangbeschreibung: " + langbeschreibung + "\nZiel 1: " + ziel1 + "\nZiel 2: " + ziel2;
        s+= "\nNutzername: " + benutzername + "\nE-Mail: " + email + "\nPasswort: " + passwort;
        return s;
    }
    
    
}
