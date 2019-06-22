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

public class RatingDao {

    @PersistenceContext(unitName = "studboardPU")
    private EntityManager em;
    
    @Resource
    private UserTransaction utx;


    public void create(Rating rating) {
        try {
            this.utx.begin();
        } catch (NotSupportedException | SystemException ex) {
            Logger.getLogger(RatingDao.class.getName()).log(Level.SEVERE, null, ex);
        }
        em.persist(rating);
        
        try {
            this.utx.commit();
        } catch (RollbackException | HeuristicMixedException | HeuristicRollbackException | SecurityException | IllegalStateException | SystemException ex) {
            Logger.getLogger(RatingDao.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }

    public List<Rating> findAll() {
        return em.createNamedQuery("Rating.findAll", Rating.class).getResultList();
    }

    public List<Rating> findByProjectId(long projektID) {
        return em.createNamedQuery("Rating.findByProjectId", Rating.class).getResultList();
    }
    
    @PreDestroy
    public void destruct() {
        em.close();
    }

}
