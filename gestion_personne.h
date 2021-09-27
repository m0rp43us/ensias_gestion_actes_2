

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define CMAX 20

#define Malloc(type) (type*) malloc(1*sizeof(type))

/******************/
/* Structure Date */
/******************/

typedef struct _date
{
   int jour;
   int mois;
   int annee;

}date;



/***************************/
/* Structure Data Personne */
/***************************/


typedef struct _data
{
   int id;
   int idPere;
   int idMere;
   int idConjoint;
   char nom[CMAX];
   char prenom[CMAX];
   date dateNaissance;
   char sexe;
   int deces;
   
}dataPersonne;



typedef dataPersonne* ptrDataPersonne;



/**********************/
/* Structure Personne */
/**********************/


typedef struct _personne
{
   ptrDataPersonne data;
   
   struct _personne* frere;
   struct _personne* fils;
   struct _personne* suivant;

}personne;


typedef personne* listePersonne;

/******************/
/* Verifier l'âge */
/******************/

int verifierAge(listePersonne debut,date dateFils, int idPere);


/***************/
/* Calcule Age */
/***************/

int calculerAge(date date_naissance);



/************************/
/* Identifiant personne */
/************************/


int genererId(char sexe,int* nbrePersonne);



/****************/
/* Age personne */
/****************/

int agePersonne(listePersonne p);



/*************************************************************************/
/* Créer la structure dataPersonne qui contient les données du personne  */
/*************************************************************************/

ptrDataPersonne creerDataPersonne(int id,char* nom,char* prenom,date date_naissance,char sexe,int deces,int idPere,int idMere);



/********************************/
/* Créer la structure Personne  */
/********************************/

listePersonne creerPersonne(int id,char* nom,char* prenom,date date_naissance,char sexe,int idPere,int idMere);



/********************************/
/* Chercher une personne by id  */
/********************************/


listePersonne chercherPersonneById(listePersonne debut,int id);



/********************************/
/* Chercher une personne by id  */
/********************************/


void printPersonne(listePersonne debut,int id);



/********************************/
/* Chercher une personne by id  */
/********************************/


void modifierPrenomPersonne(listePersonne debut,int id);


/**************************************/
/* Ajouter une Personne dans la liste */
/**************************************/


listePersonne addNewPersonne(listePersonne debut,int* nbrePersonne,char* prenom,date date_naissance,char sexe,int idPere,int idMere);


/*************************/
/* Afficher une personne */
/*************************/

void afficherPersonne(listePersonne p);



/*********************/
/* Afficher la liste */
/*********************/

void afficherListePersonne(listePersonne debut);



/**************************/
/* Supprimer une personne */
/**************************/


int supprimerPersonne(listePersonne debut,int id);



/*****************************************************/
/* Chercher personne par le nom ou prenom ou bien id */
/*****************************************************/

void chercherPersonne(listePersonne debut, int choix);


/***************************************************/
/* Retourner le nom de mere ou pere d’une personne */
/***************************************************/

void nomPereMere( listePersonne debut,int id );



/*************************************/
/* modifierFilsFrere d'une personnes */
/*************************************/

listePersonne modifierFilsFrere(listePersonne debut, listePersonne pCurr, listePersonne succ );
listePersonne trierListe(listePersonne debut, int choix);

void uppercase ( char *ch );

void premLettreMaj ( char *ch );