#include "gestion_personne.h"

#include "gestion_fichiers.h"

/* Sauvegarder les donn�es */

void sauvegarder(listePersonne debut, int nbrPersonne)
{
    listePersonne p = NULL;
    int x = -1;
	 //Ouverture en �criture du fichier listePersonne qui contient les donnees de chaque personne:
    FILE* filePersonne = fopen("listePersonne.dta","wb");
	 //Ouverture en �criture du fichier relation qui contient les identifiants des personnes qui sont en relation :
    FILE* fileRelation = fopen("relation.dta","wb");

	 //V�rifier si l'ouverture des fichiers est possible :
    if( filePersonne == NULL || fileRelation == NULL )
    {
        printf("\n\n /!\\ Impossible d'ouvrir le fichier /!\\\n ");
        getch(); 
		//On quitte le programme :
        exit(0);
    }
     //Sauvegarder le nombre de personnes :
    fwrite( &nbrPersonne,sizeof(int),1,filePersonne);                 
    /* Sauvegarder la liste des personnes */
    p = debut;
     //On parcours la liste des personnes pour sauvegarder
	 //les donnees dans le fichier listePersonne.dta et les identifiant des fils et fr�res dans le fichier relation.dta :
    while(p != NULL)
	{
		 //Sauvegarder dans le fichier listePersonne.dta :
        fwrite(p->data,sizeof(dataPersonne),1,filePersonne);
         //Sauvegarder dans le fichier relation.dta :
        if(p->fils == NULL)
			 //Si la personne n'a aucun fils alors on enregistre -1 dans le fichier relation.dta
		    fwrite(&x,sizeof(int),1,fileRelation);
        else
             //Sinon on enregistre son identificateur
            fwrite(&(p->fils->data->id),sizeof(int),1,fileRelation);
        if(p->frere == NULL) 
             //Si la personne n'a aucun fr�re alors on enregistre -1 dans le fichier relation.dta		
		    fwrite(&x,sizeof(int),1,fileRelation);
        else
             //Si non on enregistre son identificateur
            fwrite(&(p->frere->data->id),sizeof(int),1,fileRelation);
		 //On passe au personne suivant pour l'enregistrer jusqu'a la fin
        p = p->suivant;
      }
      
      fclose(filePersonne);
      fclose(fileRelation);

}

/* Charger les donn�es */

listePersonne charger(int* nbrPersonne)
{
	int x;
    listePersonne p = NULL, q = NULL, listeP = NULL;
	ptrDataPersonne data = NULL;
     //Ouverture en lecture du fichier listePersonne qui contient les donn�es de chaque personne:
    FILE* filePersonne = fopen("listePersonne.dta","rb");
     //V�rifier Si l'ouverture du fichier est possible :
    if( filePersonne == NULL )
    {
        printf("\n\n /!\\ Impossible d'ouvrir le fichier /!\\\n ");
        getch();
         //On quitte le programme :
        exit(0);
    }
     //Charger le nombre de personnes
     //Si le fichier est vide, on a rien � r�cup�rer et le nombre de personnes �gale � 0
    if( fread(nbrPersonne,sizeof(int),1,filePersonne) != 0 )
    {
        //On charge la liste de personnes puisque le fichier n'est pas vide :
         //On cr�e un noeud personne :
        p = Malloc(personne);
	     //listeP repr�sente le d�but de la liste :
        listeP = p;
         //On cr�e un noeud data dans lequel on charge les donn�es
         //� partie du fichier listPersonne :
        p->data = Malloc(dataPersonne);
        p->suivant = NULL;
        fread(p->data,sizeof(dataPersonne),1,filePersonne);
	     //Si on a plus qu'une personne, on doit lier les noeuds :
	    if( *nbrPersonne > 1 ) 
	    {
          q = p;  //On garde le pointeur sur le noeud pr�c�dent:
          do{
              q->suivant = p;
              q = p;
	           //On cr�e un noeud Personne et Data pour charger d'autre donn�es d'un autre personne :
              p = Malloc(personne);
              p->data = Malloc(dataPersonne);
              p->suivant = NULL;
            }while(fread(p->data,sizeof(dataPersonne),1,filePersonne)!=0);
             //tant qu'on a encore des donn�es dans le fichier listePersonne, on va les charger.
        }
    }
    else 
         *nbrPersonne  = 0; //Le nombre de personnes �gale � 0
	 //Fermeture de fichier listePersonne 
	fclose(filePersonne); 
	 //Ouverture en lecture de fichier relation :
	FILE* fileRelation = fopen("relation.dta","rb"); 
	if( fileRelation == NULL )
    {
        printf("\n\n /!\\ Impossible d'ouvrir le fichier /!\\\n ");
        getch();
        exit(0);
    }
	 //On pointe sur le premier �l�ment de la liste r�cup�r�e d'apr�s le fichier listePersonne.dta :
	p = listeP;
	 //On parcours la liste tant qu'on est pas encore arriv� � la fin :
	while( p != NULL )
	{ 
	     //Charger l'identifiant d'un fils et le mettre dans la variable x :
		fread(&x,sizeof(int),1,fileRelation);
		 //La personne n'a pas de fils lorsque l'identifiant r�cup�r� �gale � -1
        if( x == -1 ) p->fils = NULL;
		else
		     //Sinon on appelle la fonction chercherPersonneById
		     //qui va retourner l'adresse du fils et le mettre dans le noeud convenable
		    p->fils = chercherPersonneById(listeP,x);
		 //Puis on charger l'identifiant d'un fr�re
    	fread(&x,sizeof(int),1,fileRelation);
         //La personne n'a pas de fr�re lorsque l'identifiant r�cup�r� �gale � -1
        if( x == -1 ) p->frere = NULL;
		else
		     //Si non on appelle la fonction chercherPersonneById
		     //qui va retourner l'adresse du fr�re et le mettre dans le noeud convenable
		    p->frere = chercherPersonneById(listeP,x);
		p = p->suivant;
    }
     //Fermeture du fichier
    fclose(fileRelation);
	 //On retourne le liste dans laquelle on a charger les donn�es du fichier
    return listeP;
}
/* V�rifier login et le mot de passe pour l'authentification  */
int authentifier(char* login, char* password,char* log)
{

	char loginF[20];
	char passwordF[10];
	 //Les variables qui vaut contenir le vrai login et le vrai mot de passe.

	FILE * fichier;
 
     //L'ouverture en lecture du fichier authentification.dta.  
	fichier = fopen("authentification.dta","rb");

	if(!fichier){
					printf(" -/!\\ ERREUR : Ouverture de fichier est impossible !");
					getch();
					exit(0);
                }
	fread(loginF,sizeof(loginF),1,fichier);
	fread(passwordF,sizeof(passwordF),1,fichier);
	strcpy(log,loginF);
	fclose(fichier);
    if( strcmp(login,loginF) == 0  &&  strcmp(password,passwordF) == 0 ) 
	    return 1;
    else
        return 0;}