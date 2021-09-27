

#include "gestion_personne.h"

#include "gestion_deces.h"




/*********************/
/* Déclarer un deces */
/*********************/


void acteDeces(listePersonne debut, listePersonne person)
{
	
     listePersonne pere = NULL;
     listePersonne mere = NULL;
     date dateActuelle = DateActuelles();
     

	  //Son pere:
	 pere = chercherPersonneById(debut, person->data->idPere);
	 
	  //Sa mere:
     mere = chercherPersonneById(debut, person->data->idMere);
	 
	 FILE *fiche;

     fiche = fopen("acteDeces.doc","wt");

     if(fiche == NULL) printf("erreur\n");
     else
     {

       fprintf(fiche,"\t\t\t\tEXTRAIT DE L'ACTE DE DECES\n\n\n\n");
       
       fprintf(fiche,"\t     Il appert des Registres de Deces que  %s  %s \n\n\t, ne le  %d / %d / %d ",person->data->nom,person->data->prenom,person->data->dateNaissance.jour,person->data->dateNaissance.mois,person->data->dateNaissance.annee);

	   if(person->data->idPere != -1)
	      fprintf(fiche," ,fil de  %s  %s \n\n\t et de  %s  %s ",pere->data->nom,pere->data->prenom,mere->data->nom,mere->data->prenom);
	   
          
        fprintf(fiche,", est decede.\n\n\n");  
          
        fprintf(fiche,"\n\n\n\n\t\t\t\t\t -DATE DE DELIVRANCE : %d / %d / %d \n\n",dateActuelle.jour,dateActuelle.mois,dateActuelle.annee);

          

       fclose(fiche);
       
       //Convertir l'acte en PDF:
       system("OfficeToPDF.exe acteDeces.doc actes/acteDeces.pdf ");
       system("del acteDeces.doc ");
       
       printf("\n\n - L'actes de deces est bien imprime, vous pouvez le recuperer.\n\n");


      }
   

}



void deces(listePersonne debut, int idCurr, int idP, int choix)
{
	listePersonne person = NULL;
	listePersonne pCurr = chercherPersonneById(debut, idCurr);
	
	switch(choix)
	{
		case 1 : //Acte de deces du père.
		      
		         //Le père n'est pas inscrit.
		        if( pCurr->data->idPere == -1 )
		        {
		        	color(7,0);
		        	printf("\n\n - Impossible de delivrer cet acte ! Le pere n'est pas inscrit. \n\n");
		        	color(15,0);
				}
				else
				{  
				     //L'identifiant saisie n'est pas valid.
					if( pCurr->data->idPere != idP )
					{
						color(7,0);
		        	    printf("\n\n - Impossible de delivrer cet acte ! L'Id est invalid. \n\n");
		        	    color(15,0);	
					}
					else
					{ 
						person = chercherPersonneById(debut,idP);
					   
					     //Le père est encore vivant.	
						if( person->data->deces == 0 )
						{
							color(7,0);
		        	        printf("\n\n - Impossible de delivrer cet acte ! votre pere est encore vivant. \n\n");
		        	        color(15,0);	
						}
						else
						
						    acteDeces(debut,person);
					}
				}
				
				getch();
				break;
				
				
				
		case 2 : //Acte de deces de la mère
		      
		        if( pCurr->data->idMere == -1 )
		        {
		        	color(7,0);
		        	printf("\n\n - Impossible de delivrer cet acte ! La mere n'est pas inscrite. \n\n");
		        	color(15,0);
				}
				else
				{
					if( pCurr->data->idMere != idP )
					{
						color(7,0);
		        	    printf("\n\n - Impossible de delivrer cet acte ! L'Id est invalid. \n\n");
		        	    color(15,0);	
					}
					else
					{
						person = chercherPersonneById(debut,idP);
					   
					     //La mère est encore vivante.	
						if( person->data->deces == 0 )
						{
							color(7,0);
		        	        printf("\n\n - Impossible de delivrer cet acte ! votre mere est encore vivante. \n\n");
		        	        color(15,0);	
						}
						else
						
						    acteDeces(debut,person);
					}
				}
				
				getch();
				break;		
				
				
				
		case 3 : //Acte de deces du conjoint
		      
		        if( pCurr->data->idConjoint == -1 )
		        {
		        	color(7,0);
		        	printf("\n\n - Impossible de delivrer cet acte ! vous n'etes pas encore marie. \n\n");
		        	color(15,0);
				}
				else
				{
					if( pCurr->data->idConjoint != idP )
					{
						color(7,0);
		        	    printf("\n\n - Impossible de delivrer cet acte ! L'Id est invalid. \n\n");
		        	    color(15,0);	
					}
					else
					{
						person = chercherPersonneById(debut,idP);
					   
					     //Le conjoint est encore vivant.	
						if( person->data->deces == 0 )
						{
							color(7,0);
		        	        printf("\n\n - Impossible de delivrer cet acte ! votre conjoint est encore vivant. \n\n");
		        	        color(15,0);	
						}
						else
						
						    acteDeces(debut,person);
					}
				}
				
				getch();
				break;		
			      
	}
	           
	
}

