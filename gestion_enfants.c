
#include "gestion_personne.h"

#include "gestion_enfants.h"




/**************************************/
/* Afficher les frères d'une personne */
/**************************************/

void afficherFrere(listePersonne r)
{
   if(r != NULL)
   {
   	     //Afficher les informations d'une personne donnée:
		afficherPersonne(r);
		
		 //ainsi que celles de son frére:
		afficherFrere(r->frere);
   }

}




/****************************************/
/* Afficher les enfants d'une personne  */
/****************************************/

void afficherEnfants(listePersonne debut,int id)
{
	  //Récupèrer l'adresse de la personne:
	 listePersonne pers = chercherPersonneById(debut,id);
	 
	  //Vérifier si cette personne existe ou pas:
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
			
			 //pers->fils représente le fils ainé
			 //les enfants de pers sont les fréres de pers->fils
	        afficherFrere(pers->fils);
		 }
     }
	   
}

