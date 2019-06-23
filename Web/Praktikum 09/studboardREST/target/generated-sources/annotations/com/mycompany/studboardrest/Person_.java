package com.mycompany.studboardrest;

import javax.annotation.Generated;
import javax.persistence.metamodel.ListAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Person.class)
public abstract class Person_ extends com.mycompany.studboardrest.Project_User_ {

	public static volatile SingularAttribute<Person, String> passwort;
	public static volatile ListAttribute<Person, Project> projects;
	public static volatile SingularAttribute<Person, String> benutzername;
	public static volatile SingularAttribute<Person, String> email;

}

