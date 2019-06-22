package com.mycompany.studboardrest;

import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.PreDestroy;
import javax.annotation.Resource;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.HeuristicMixedException;
import javax.transaction.HeuristicRollbackException;
import javax.transaction.NotSupportedException;
import javax.transaction.RollbackException;
import javax.transaction.SystemException;
import javax.transaction.UserTransaction;

public class ProjectDao {

    @PersistenceContext(unitName = "studboardPU")
    private EntityManager em;
    
    @Resource
    private UserTransaction utx;


    public void create(Project project) {
        try {
            this.utx.begin();
        } catch (NotSupportedException | SystemException ex) {
            Logger.getLogger(ProjectDao.class.getName()).log(Level.SEVERE, null, ex);
        }
        em.persist(project);
        
        try {
            this.utx.commit();
        } catch (RollbackException | HeuristicMixedException | HeuristicRollbackException | SecurityException | IllegalStateException | SystemException ex) {
            Logger.getLogger(ProjectDao.class.getName()).log(Level.SEVERE, null, ex);
        }  
    }

    public List<Project> findAll() {
        return em.createNamedQuery("Project.findAll", Project.class).getResultList();
    }

    public List<Project> findByProjectId(long id) {
        return em.createNamedQuery("Project.findById", Project.class).getResultList();
    }

    
    @PreDestroy
    public void destruct() {
        em.close();
    }

}
