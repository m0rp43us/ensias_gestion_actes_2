#include "gestion_personne.h"

/* Calcule Age */

int calculerAge(date date_naissance)
{
    int age;
	age = 2018 - date_naissance.annee;
    return age;
}

int genererId(char sexe,int* nbrePersonne)
{
	int idPersonne;
	
	(*nbrePersonne)++;                                      
															 
	if( sexe == 'M' ) idPersonne = (*nbrePersonne)*10 + 3;      
	else
	   idPersonne = (*nbrePersonne)*10 - 2;
	   
	return idPersonne;
}

int agePersonne(listePersonne p)
{
    return calculerAge(p->data->dateNaissance);

}

int verifierAge(listePersonne debut,date dateFils, int idPere)
{
 	int agePere,ageFils;

	 listePersonne pere= chercherPersonneById( debut, idPere);
	 
	  //Calculer l'âge du père:
     agePere=agePersonne(pere);
     
      //Calculer l'âge du fils:
     ageFils=calculerAge(dateFils);

      //Si l'âge est invalid, on retourne 0 sinon 1
     return (agePere>ageFils)?1:0;


}


/*************************************************************************/
/* Créer la structure dataPersonne qui contient les données du personne  */
/*************************************************************************/

ptrDataPersonne creerDataPersonne(int id,char* nom,char* prenom,date date_naissance,char sexe,int deces,int idPere,int idMere)
{
	 //La création de la structure DataPersonne:
	ptrDataPersonne donnee = NULL;
	donnee = Malloc(dataPersonne);
	
	 //Remplissage des champs de données:
	donnee->id = id;
	donnee->idPere = idPere;
	donnee->idMere = idMere;
	strcpy(donnee->nom,nom);
	strcpy(donnee->prenom,prenom);
	donnee->dateNaissance = date_naissance;
	donnee->sexe = sexe;
	donnee->deces = deces;
	
	 //Lors de la création, la personne n'est pas encore marier.
	donnee->idConjoint = -1;
	
	return donnee;
}



/********************************/
/* Créer la structure Personne  */
/********************************/

listePersonne creerPersonne(int id,char* nom,char* prenom,date date_naissance,char sexe,int idPere,int idMere)
{
	listePersonne listeP = NULL;
	
	listeP = Malloc(personne);
	
     /** Création de la structure donnee **/
	listeP->data = creerDataPersonne(id,nom,prenom,date_naissance,sexe,0,idPere,idMere);  
	
	listeP->fils = NULL;
	listeP->frere = NULL;
	listeP->suivant = NULL;
	
	return listeP;
}

listePersonne chercherPersonneById(listePersonne debut,int id)
{
   listePersonne p = debut;
   
   while( p != NULL && p->data->id != id)  p = p->suivant;

   return p ;
}

listePersonne addNewPersonne(listePersonne debut,int* nbrePersonne,char* prenom,date date_naissance,char sexe,int idPere,int idMere)
{
	  listePersonne p = debut;
	  listePersonne pere = NULL;
	  listePersonne mere = NULL;
	  listePersonne listeP = NULL;
	  int id;
	  
       /* Generer l'identifiant du personne à partir de son sexe et le nbr des personnes */
	  id = genererId( sexe,nbrePersonne);        
	  
       /* pointeur sur la mere */
	  mere = chercherPersonneById(debut,idMere);

       /* pointeur sur le pere */
      pere = chercherPersonneById(debut,idPere);
	  
       /* création de la structure personne */
	  listeP = creerPersonne(id,pere->data->nom,prenom,date_naissance,sexe,idPere,idMere);
	  
	  if(p == NULL)
		 // si la liste des personnes est vide
			 debut = listeP;
	   else
	   {
	  
             /* on cherche le dernier element de la liste */
	        while( p->suivant != NULL)  p = p->suivant;     
	  
	        p->suivant = listeP;


	        p = mere->fils;
	  
            /* si la mère n'avait aucun fils */
	       if(!p) mere->fils = listeP;
	       else{
                  /* On cherche le plus petit frere du fils ainé de la mère */
                  /* afin d'ajouter ce nouveau fils comme son frere.   */
			     while( p->frere != NULL) p = p->frere;
															    
			     p->frere = listeP;
              }

            /* Si le pere n'a pas de fils */
           if(! (pere->fils)) pere->fils = listeP;

	  }
          
	  return debut;
			  
}


/*************************/
/* Afficher une personne */
/*************************/

void afficherPersonne(listePersonne p)
{
	printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
	printf("- - code : ");printf(" %d \n\n",p->data->id);
	printf("- - nom : ");printf(" %s \n\n",p->data->nom);
	printf("- - prenom : ");printf(" %s \n\n",p->data->prenom);
	printf("- - date de naissance : ");
	printf(" %d / %d / %d \n\n",p->data->dateNaissance.jour,p->data->dateNaissance.mois,p->data->dateNaissance.annee);
	 
	if( p->data->sexe == 'M' )
	{
	    printf("- - sexe : ");printf(" Homme \n\n");
    }
	else{
            printf("- - sexe : ");printf(" Femme \n\n");
		}
          
    if( p->data->idConjoint == -1 )
	{
        printf("- - situation familiale : ");printf(" Celibataire \n\n");
    }
    else{
            printf("- - situation familiale : ");printf(" marie \n\n");
	    }      
          
	if( p->data->deces == 0 )
	{
	    printf("- - age : ");printf(" %d ans \n\n",agePersonne(p));
        printf("- - situation : ");
		
		if( p->data->sexe == 'M' )  printf(" vivant \n\n");	
		else
		    printf(" vivante \n\n");	
		
    }
    else{
            printf("- - situation : ");
			if( p->data->sexe == 'M' )  printf(" mort \n\n");	
		    else
			    printf(" morte \n\n");
	    }
     printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");

}



/* Afficher la liste */

void afficherListePersonne(listePersonne debut)
{
	 listePersonne p = debut;
	 while(p != NULL)
	 {
		   afficherPersonne(p);
		   getch();
		   p = p->suivant;
	 }
}

/* Supprimer une personne */


int supprimerPersonne(listePersonne debut,int id)
{
   listePersonne pers = chercherPersonneById(debut,id);
   
   if( pers != NULL ) {                                 /* La personne n'existe pas */
   	                     pers->data->deces = 1;
   	                     return 1;
		              }
   else return 0;

}

/* modifier prenom d'une personne */

void modifierPrenomPersonne(listePersonne debut,int id)
{
 	 char prenom[CMAX];
	 listePersonne p = chercherPersonneById(debut,id);   /* rechercher la personne */
	 if(p==NULL)  printf("\n - le personne n'existe pas \n\n");
	 else {
	          printf("\n -- Entrer le nouveau prenom : ");
	          
	          fflush(stdin);gets(prenom);fflush(stdin);
	 
	          strcpy(p->data->prenom,prenom);
          }
}

/* Chercher personne par le nom ou prenom ou bien id */

void chercherPersonne(listePersonne debut, int choix)
{
	 int id, iTrouve = 0; 
	 char nom[CMAX],prenom[CMAX];
	 listePersonne pers = NULL;
	 
	 switch(choix)
	 {
		 case 1 : //recherche par l'identifiant
		 
		          system("cls");
                  printf("\n\n - - - - - - - - - - - - recherche par l'id  - - - - - - - - - - - - \n\n");
				  printf("\n\n -- Saisissez un identifiant : ");
				  scanf("%d",&id);
				  
				   //On cherche la personne par son identifiant:
				  pers = chercherPersonneById(debut,id);
				  
				   //La personne n'existe pas:
				  if( !pers ) 
				  {
				  	printf("\n\n - La personne de l'id %d n'existe pas ! \n\n ",id);
				  }
				  else{
				  	     afficherPersonne(pers);
				      }
				  
				  
				  getch();
				  break;
				  

		 case 2 : //recherche par le nom
		 
		          system("cls");
                  printf("\n\n - - - - - - - - - - - - - -  recherche par nom   - - - - - - - - - - - - - - \n\n");
                  printf("\n\n -- donner le nom : ");
                  fflush(stdin);gets(nom);fflush(stdin);
                  
                   //Rendre le nom en majuscule:
                  uppercase(nom);
                  
                   //La recherche:
                  pers = debut;

                  while( pers != NULL )
				  {
				  	      //On affiche chaque personne trouvée:
						 if( strcmp(pers->data->nom,nom) == 0) 
						  {
						  	iTrouve = 1;
						  	afficherPersonne(pers);
						  	getch();
						  }
						 
						 pers = pers->suivant;
   		          }
   		          
   		          if( iTrouve == 0 ) printf("\n\n - Personne n'a %s comme nom ! \n\n ",nom);

                  getch();
				  break;


		 case 3 : //recherche par le prenom
		 
		          system("cls");
                  printf("\n\n - - - - - - - - - - - - - -  recherche par prenom - - - - - - - - - - - - -\n\n");
                  printf("\n\n -- Saisissez un Prenom : ");
                  fflush(stdin);gets(prenom);fflush(stdin);
                  
                   //Premiere lettre en majuscule:
                  premLettreMaj(prenom);

                   //La recherche:
                  pers = debut;

                  while( pers != NULL )
				  {
				  	     
				  	      //On affiche chaque personne trouvée:
						 if( strcmp(pers->data->prenom,prenom) == 0) 
						 {
						 	iTrouve = 1;
						 	afficherPersonne(pers);
						 	getch();
						 }

						 pers = pers->suivant;
   		          }
   		          
   		          if( iTrouve == 0 ) printf("\n\n - Personne n'a %s comme prenom ! \n\n ",prenom);
   		          
                  getch();
				  break;
				  
		case 4 :
                 //Revenir au menu precedent
                        	
                  break;
                        	         

     }
}

/* Imprimer acte de naissance d'une personne  */

void printPersonne(listePersonne debut,int id)
{
     listePersonne pers = NULL;
     listePersonne pere = NULL;
     listePersonne mere = NULL;

	  //La personne qui veut avoir son acte de naissance:
	 pers = chercherPersonneById(debut,id);

	  //Son pere:
	 pere = chercherPersonneById(debut, pers->data->idPere);
	 
	  //Sa mere:
     mere = chercherPersonneById(debut, pers->data->idMere);
	 
	 FILE *fiche;

     fiche = fopen("acteNaissance.doc","wt");

     if(fiche == NULL) printf("erreur\n");
     else
     {

       fprintf(fiche,"\t\t\t\textrait d'acte de naissance\n\n\n");
       fprintf(fiche,"\t -nom :                 %s \n\n",pers->data->nom);
       fprintf(fiche,"\t -prenom :              %s \n\n",pers->data->prenom);
     
       if(pers->data->sexe == 'M')
         fprintf(fiche,"\t -sexe:              Masculin \n\n");
       else
         fprintf(fiche,"\t -sexe :              Feminin \n\n");
       
       fprintf(fiche,"\t -date de naissance :   %d / %d / %d \n\n\n",pers->data->dateNaissance.jour,pers->data->dateNaissance.mois,pers->data->dateNaissance.annee);

	   if(pers->data->idPere != -1)
	      fprintf(fiche,"\t -nom de pere :      %s %s \n\n",pere->data->nom,pere->data->prenom);
	   else
          fprintf(fiche,"\t -nom de pere :      ( n'est pas inscrit ) \n\n");
          
	   if(pers->data->idMere != -1)
          fprintf(fiche,"\t -nom de mere :      %s %s \n\n",mere->data->nom,mere->data->prenom);
       else
          fprintf(fiche,"\t -nom de mere :      ( n'est pas inscrite ) \n\n");

       fclose(fiche);
       
        //Convertir l'acte en PDF:
       system("OfficeToPDF.exe acteNaissance.doc actes/acteNaissance.pdf ");
       system("del acteNaissance.doc ");
       
       printf("\n\n - L'actes de naissance est bien imprime\n\n");


      }

}

/* Retourner le nom de mere ou pere d’une personne */

void nomPereMere( listePersonne debut,int id )
{
   listePersonne p = NULL;
   listePersonne pere=NULL;
   listePersonne mere = NULL;
   
   p = chercherPersonneById( debut, id );
   
   if( p->data->idPere == -1 && p->data->idMere == -1 )
   {
	   printf("\n - Les parents de  %s %s  ne sont pas enregistres. ",p->data->nom ,p->data->prenom);
   }
   else
   {
       pere = chercherPersonneById( debut, p->data->idPere);
       mere = chercherPersonneById( debut, p->data->idMere);

       printf("\n - Le Pere de %s %s est %s %s \n",p->data->nom ,p->data->prenom,pere->data->nom,pere->data->prenom);

       printf("\n\n - La Mere de %s %s est %s %s \n",p->data->nom,p->data->prenom,mere->data->nom,mere->data->prenom);

   }
   
   

}

/* modifierFilsFrere d'une personnes */

listePersonne modifierFilsFrere(listePersonne debut, listePersonne pCurr, listePersonne succ )
{
    listePersonne p = debut;
     
    while( p != NULL )
    {
		if( p->fils == pCurr )   p->fils = succ;        /* On change le fils ou le frere de cette personne  */
		else 
		    if( p->fils == succ )   
	            p->fils = pCurr;
		 
		if( p->frere == pCurr ) p->frere = succ;
		 else 
		    if( p->frere == succ ) 
			    p->frere = pCurr;
		 
		 p = p->suivant;

    }
     
     return debut;
}

/* Trier la liste des personnes */

listePersonne trierListe(listePersonne debut, int choix)
{
    
	listePersonne p = debut, succ = debut, temp = NULL;
    
    int continu = 0;

    temp = Malloc(personne);
     
     // Si la liste est vide 
    if( debut == NULL )
		return debut ;

	switch(choix)
	{

	case 1:

            do 
			{                                       /* i eme iteration */
				continu = 0;
				p = debut;
				succ = p->suivant;
				
				while (succ != NULL  )
	           	{
	        		if( p->data->id < succ->data->id )               /* Si l'identifiant de personne current est inf.
					                                                    à celui de la personne suivante   */
	        		{
                           debut = modifierFilsFrere( debut,p,succ );

						   /* Temp <- p */
						   
						   temp->data = p->data;
						   
						   temp->frere = p->frere;
						   temp->fils = p->fils;
						   
						   /* p <- succ */
						   
						   p->data = succ->data;

						   p->frere = succ->frere;
						   p->fils = succ->fils;
						   						   
						   /* succ <- Temp */

                           succ->data = temp->data;
                           
						   succ->frere = temp->frere;
						   succ->fils = temp->fils;


			        		continu = 1;
	        		}
                        p = succ;
	                    succ = succ->suivant;
	           }


	     	  }while(continu == 1);
	     	  
	     	  printf("\n\n - Le tri est bien effectuee \n\n");
            getch();
            break;

    case 2:

            do {
                continu = 0;
				p = debut;
				succ = p->suivant;

				while (succ != NULL)
	           	{
                   if( strcmp(p->data->nom,succ->data->nom) < 0 )
	        		{
                             modifierFilsFrere( debut,p,succ );

						   /* Temp <- p */

						   temp->data = p->data;

						   temp->frere = p->frere;
						   temp->fils = p->fils;

						   /* p <- succ */

						   p->data = succ->data;

						   p->frere = succ->frere;
						   p->fils = succ->fils;


						   /* succ <- Temp */

						   succ->data = temp->data;

						   succ->frere = temp->frere;
						   succ->fils = temp->fils;


			        		continu = 1;
		 	        }
		 	        
		 	            p = succ;
	                    succ = succ->suivant;
	           }

	     	  }while(continu == 1);
	     	  
	     	  printf("\n\n - Le tri est bien effectuee \n\n");

            getch();
            break;
            
    case 3 :  
	         //Retourner au menu précédent:
			 break;    
            

    default :
                 printf("\n\n\t/!\\ Votre choix est invalid /!\\\n\n");

    }

    return debut;
}

/* Majuscule  */

void uppercase ( char *ch )
{
	
  while ( *ch != '\0' )
  {
    *ch = toupper ( *ch );
    ++ch;
  }
  
}

/* 1ere lettre en Majuscule  */

void premLettreMaj ( char *ch )
{
	
  *ch = toupper ( *ch );
  
}