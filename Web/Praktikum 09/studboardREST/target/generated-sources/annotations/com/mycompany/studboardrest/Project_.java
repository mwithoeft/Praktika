package com.mycompany.studboardrest;

import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Project.class)
public abstract class Project_ extends com.mycompany.studboardrest.Project_User_ {

	public static volatile SingularAttribute<Project, String> endzeitpunkt;
	public static volatile SingularAttribute<Project, String> titel;
	public static volatile SingularAttribute<Project, Person> person;
	public static volatile SingularAttribute<Project, String> startzeitpunkt;
	public static volatile SingularAttribute<Project, String> projektleiter;

}

