
#include "gestion_personne.h"

#include "gestion_enfants.h"




/**************************************/
/* Afficher les fr�res d'une personne */
/**************************************/

void afficherFrere(listePersonne r)
{
   if(r != NULL)
   {
   	     //Afficher les informations d'une personne donn�e:
		afficherPersonne(r);
		
		 //ainsi que celles de son fr�re:
		afficherFrere(r->frere);
   }

}




/****************************************/
/* Afficher les enfants d'une personne  */
/****************************************/

void afficherEnfants(listePersonne debut,int id)
{
	  //R�cup�rer l'adresse de la personne:
	 listePersonne pers = chercherPersonneById(debut,id);
	 
	  //V�rifier si cette personne existe ou pas:
	 if( pers == NULL ) 
	   printf("\n - ID n'existe pas. \n\n");
	 else
	 {
	 	  //Si cette personne n'a pas encore d'enfants:
     	 if( pers->fils == NULL ) 
		   printf("\n - %s %s n'a pas encore d'enfants.\n",pers->data->nom,pers->data->prenom);
	     else
		 { 
		     //Si la personne a au moins un enfant:
			printf("\n\n\t\t - - -  LES ENFANTS DE %s %s - - - \n\n",pers->data->nom,pers->data->prenom);
			
			 //pers->fils repr�sente le fils ain�
			 //les enfants de pers sont les fr�res de pers->fils
	        afficherFrere(pers->fils);
		 }
     }
	   
}

