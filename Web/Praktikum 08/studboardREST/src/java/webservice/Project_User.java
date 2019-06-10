package webservice;


public abstract class Project_User {
    
    private long id;
    private String kurzbeschreibung;
    private String langbeschreibung;
    private String[] ziele;
    private String bild;
    private static long idCounter = 0;
    
    public Project_User(String kurzbeschreibung, String langbeschreibung, String[] ziele, String bild) {
        this.id = idCounter;
        this.kurzbeschreibung = kurzbeschreibung;
        this.ziele = ziele;
        this.bild = bild;
        idCounter++;
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
        return this.ziele;
    }
    
    public String getBild() {
        return this.bild;
    }
    
}
