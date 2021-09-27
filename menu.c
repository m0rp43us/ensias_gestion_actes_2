
#include "gestion_personne.h"

#include "menu.h"
/* L'interface d'acceuil */

void pageAcceuil()
{
    
    printf("\n\n\t\tProjet de Gestion des Actes d'Etat Civil Numerises\n\n\n");
    printf("\t\t\tEncadre par Mr. A. El Hassouny ");
    printf("\t\tRealise par abderrafia Duik et wail Chalabi\n\n");
    printf("\n\n\n\n\n");
    printf(" \t \tENSIAS 2017-2018 \n \n");
    getch(); 
	
}

/* Le menu d'authentification  */
void menuAuthentification()
{
      system("cls");
      printf("\t\t\t [1] . Entrer\n\n");
      printf("\t\t\t [2] . 	Sortir\n\n\n");
	
}
/* Le menu */
void menuAdmin()
{
    printf("\n\n\t\t\t\tM E N U\n");
    printf("\t\t\t\t-------\n\n\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t|                                     |\n");
    printf("\t\t| [1] . Gestion des personnes         |\n\n");
    printf("\t\t| [2] . Gestion des enfants           |\n\n");
    printf("\t\t| [3] . Gestion des deces             |\n\n");
    printf("\t\t| [4] . Sortir                        |\n");
    printf("\t\t|                                     |\n");
    printf("\t\t--------------------------------------\n\n");
	
}
/* Le menu de gestion des personnes */
void menuGestionPersonnes()
{	
	system("cls");
                     printf("\n\n\n  - - - - - - - - -  gestion   de   personne - - - - - - - - \n\n\n");
                     printf("\t\t [1] . Ajouter une personne.\n\n");
                     printf("\t\t [2] . Modifier les enregistrements d'une personne.\n\n");
                     printf("\t\t [3] . Consulter la liste des personnes.\n\n");
                     printf("\t\t [4] . Chercher une personne par son CIN , nom ou prenom.\n\n");
                     printf("\t\t [5] . Retourner le nom des parents d'une personne.\n\n");
                     printf("\t\t [6] . Retourner son age.\n\n");
                     printf("\t\t [7] . Trie de la liste des personnes.\n\n");
                     printf("\t\t [8] . Impression d'acte de naissance.\n\n");
                     printf("\t\t [9] . Revenir au Menu.\n\n");
                     printf("\t\t[10] . Sortir	.\n\n\n");
	
}