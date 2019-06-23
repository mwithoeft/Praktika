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

public class CommentDao {

    @PersistenceContext(unitName = "studboardPU")
    private EntityManager em;
    
    @Resource
    private UserTransaction utx;


    public void create(Comment comment) {
        try {
            this.utx.begin();
        } catch (NotSupportedException | SystemException ex) {
            Logger.getLogger(CommentDao.class.getName()).log(Level.SEVERE, null, ex);
        }
        em.persist(comment);
        
        try {
            this.utx.commit();
        } catch (RollbackException | HeuristicMixedException | HeuristicRollbackException | SecurityException | IllegalStateException | SystemException ex) {
            Logger.getLogger(CommentDao.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }

    public List<Comment> findAll() {
        return em.createNamedQuery("Comment.findAll", Comment.class).getResultList();
    }

    public List<Comment> findByProjectId(long projektID) {
        return em.createNamedQuery("Comment.findByProjectId", Comment.class).getResultList();
    }

    public List<Comment> findByPersonId(long nutzerID) {
        return em.createNamedQuery("Comment.findByPersonId", Comment.class).getResultList();
    }
    
    @PreDestroy
    public void destruct() {
        em.close();
    }

}
