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

public class PersonDao {

    @PersistenceContext(unitName = "studboardPU")
    private EntityManager em;
    
    @Resource
    private UserTransaction utx;


    public void create(Person person) {
        try {
            this.utx.begin();
        } catch (NotSupportedException | SystemException ex) {
            Logger.getLogger(PersonDao.class.getName()).log(Level.SEVERE, null, ex);
        }
        em.persist(person);
        
        try {
            this.utx.commit();
        } catch (RollbackException | HeuristicMixedException | HeuristicRollbackException | SecurityException | IllegalStateException | SystemException ex) {
            Logger.getLogger(PersonDao.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }

    public List<Person> findAll() {
        return em.createNamedQuery("Person.findAll", Person.class).getResultList();
    }

    public List<Person> findById(long id) {
        return em.createNamedQuery("Person.findById", Person.class).getResultList();
    }

    @PreDestroy
    public void destruct() {
        em.close();
    }

}