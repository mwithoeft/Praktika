package com.mycompany.studboardrest;

import java.io.Serializable;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Inheritance;
import javax.persistence.InheritanceType;

@Entity
@Inheritance(strategy=InheritanceType.TABLE_PER_CLASS)
public abstract class Project_User implements Serializable {
    
    @Id
    @GeneratedValue
    protected long id;
    
    @Column(name="kurzbeschreibung")
    protected String kurzbeschreibung;
    
    @Column(name="langbeschreibung")
    protected String langbeschreibung;
    
    @Column(name="ziel1")
    protected String ziel1;
    
    @Column(name="ziel2")
    protected String ziel2;
    
    @Column(name="bild")
    protected String bild;

    public Project_User() {
    }
    
    
    public Project_User(String kurzbeschreibung, String langbeschreibung, String[] ziele, String bild) {
        this.kurzbeschreibung = kurzbeschreibung;
        this.langbeschreibung = langbeschreibung;
        this.ziel1 = ziele[0];
        this.ziel2 = ziele[1];
        this.bild = bild;
        
    }
    
    
    public long getID(){
        return this.id;
    }
    
    public String getKurzbeschreibung(){
        return this.kurzbeschreibung;
    }
    
    public String getLangbeschreibung(){
        return this.langbeschreibung;
    }
    
    public String[] getZiele(){
        String[] s = {ziel1, ziel2};
        return s;
    }
    
    public String getBild() {
        return this.bild;
    }
    
}
