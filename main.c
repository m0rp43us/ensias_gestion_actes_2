

#include "gestion_personne.h"
#include "gestion_enfants.h"
#include "gestion_deces.h"
#include "gestion_fichiers.h"
#include "menu.h"



int main()
{
	listePersonne listeP = NULL , p = NULL;
	int id, idP, idPere, idMere, idConj, NbrPers, i, j, testDate, testAge, nbrePersonne=0, choixSearch, choixIdent, a, idM, continu, choixMenuP, choixMenu=1;
	char nom[CMAX], prenom[CMAX], sexe, login[MAX],password[MAX], choixContinu, loginNom[20], choixSupp;
	date dateNaissance;
	
	
	

/*  CHARGER LES DONNEES  */


listeP = charger(&nbrePersonne);

	
/*  MENU  */


pageAcceuil();


/* AUTHENTIFICATION */


do{
      
    menuAuthentification();
    
    printf("\n\n\n\t -- Faites votre choix : ");
    fflush(stdin);
    scanf("%d",&choixIdent);
      
}while(choixIdent != 1 && choixIdent != 2);  


    
switch(choixIdent)
{
	
case 1: 
		     
    do 
    {
        system("cls");

        printf("\n\n\t\t\t    authentification\n\n");
        printf("\t\t--------------------------------------\n");
        printf("\n\t\t| Login : "); fflush(stdin); scanf("%s",&login);
        printf("\n\n\t\t| Mot de Passe : ");
              
        //Cacher le mot de passe:
         
        i=0;
        
		 //La saisie du mot de passe:      
        do{ 
             //On récupére chaque élément saisie:  	   
            password[i] = getch();
              	   
            if(password[i] == 0x08) // Code hexa. de backspace
            {
                system("cls");
                printf("\n\n\t\t\t    authentification\n\n");
                printf("\t\t--------------------------------------\n");
                printf("\n\t\t| Login : %s\n",login);
                printf("\n\n\t\t| Mot de Passe : ");
                        
                //On affiche les elements déjà saisies
				//sans l'element i-1 qui doit être supprimé 
				
                for( j=0 ; j<=i-2 ; j++ )
                   printf("*");
                                          
                if(i == 0 || i == 1) i = 0;
                else i = i-1;
                        
                j = i;
              	   	  
			}
			else
            {
				 //On affiche étoile tant qu'on a pas encore taper <entrer>
				if( password[i] != 0x0D )   printf("*"); 
				
				 //On récupére l'élément courant afin de tester s'il s'agit de <l'entrer> ou pas: 
                j = i;
                
                 //On passe à l'élément suivant:
		     	i++;
			}
              	
		}while(password[j] != 0x0D); //Code Hexa. de <entrer>, s'il s'agit de l'entrer on quitte.
			  
		password[j] = '\0';
              
               
        //Vérifier login et le mot de passe:
        if( ! authentifier( login,password,loginNom) )
        {
        	printf("\n\n\n\n\t\t  -Mot de passe ou login incorrect-  ");
        	getch();
        	continu = 0;
        }
        else continu = 1;

    }while(!continu );

           
    do{ 

        //L'espace administration:
    
        system("cls");
        menuAdmin();
        fflush(stdin);
        scanf("%d",&choixMenuP);

        switch(choixMenuP)
        {
        case 1: 
                //Gestion des personnes

                do
				{
                    menuGestionPersonnes();
					printf("\t -- Faites votre choix : ");
					fflush(stdin);
                    scanf("%d",&choixMenu);
                    fflush(stdin);
			         switch(choixMenu)
			         {
					    case 1 :
                                    system("cls");
                                    printf("\n\n - - - - - - - -  - - - - - ajouter des personnes - - - - - - - - - -  - - - - \n\n");
                                    
                                  	printf("\n - Combien de personne voulez vous saisir : ");
	                                scanf("%d",&NbrPers);
	                                
									if( NbrPers > 0 )
									{
									    printf("\n\n- - - - - - - - - - - - - la saisie des donnees - - - - - - - - - - - - - - - \n\n");
                                    }

	                                for(i = 0 ; i < NbrPers ; i++)
	                                {

                                       printf("  - prenom : ");fflush(stdin);gets(prenom);fflush(stdin);

                                       printf("\n  - sexe : ");fflush(stdin);scanf("%c",&sexe);fflush(stdin);


                                         //Vérification de l'identifiant du Père :
		                                 // - Si le père n'existe pas.
		                                 // - Si le père n'est pas un homme.
		                                 
		                                printf("\n  - identifiant du pere : ");
                                        do{

		                                	scanf("%d",&idPere);
		                                	
		                                	p = chercherPersonneById(listeP,idPere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		printf("\n  - cet identifiant n'existe pas -");
												printf(" identifiant du pere : ");

											}
											else
											{
												if( idPere%10 != 1 )
												{
		                                		    printf("\n  - Id invalid -");
												    printf(" ID DU PERE : ");	
												}
											}
					                  	 
                                        }while( !p || ( idPere%10 != 1 )  );



                                         //Vérification de l'identifiant de la mere :
	                             	     // - Si la mere n'existe pas.
	                              	     // - Si la mere n'est pas une femme.
	                              	     
	                              	    printf("\n  - ID DE LA MERE : ");
                                        do{

											scanf("%d",&idMere);
											
											p = chercherPersonneById(listeP,idMere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		printf("\n  - Id n'existe pas -");
												printf(" ID DE LA MERE : ");

											}
											else
											{
												if( idMere%10 != 2 )
												{
		                                		    printf("\n  - Id invalid -");
												    printf(" ID DE LA MERE : ");	
												}
											}

                                        }while( !p || ( idMere == idPere ) || ( idMere%10 != 2 ) );



                                         //On vérifier la date de naissance
                                        do{

	                                        printf("\n  - DATE DE NAISSANCE : ");
	                                        scanf("%d/%d/%d",&dateNaissance.jour,&dateNaissance.mois,&dateNaissance.annee);

                                             // Si la date est invalid 
                                            testDate = verifierDate(dateNaissance);     
											 
											 // Si l'age du fils est plus grand que celui du pere         
			                                testAge = verifierAge(listeP,dateNaissance,idPere);     

                                        }while( testDate == 0 || testAge==0 );
	                                   printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");


                                      /* insertion */
                                     listeP = addNewPersonne(listeP,&nbrePersonne,prenom,dateNaissance,sexe,idPere,idMere);

                                   }

                                    getch();
                                    break;
                                    

                        case 2 :
                                    system("cls");
                                    printf("\n\n - - - - - - - - - - - - - - - -  MODIFICATION  - - - - - - - - - - - - - - - - \n\n");
                                    printf("\n\n - Saisissez l'identifiant du personne a modifier : ");

                                    scanf("%d",&idM);

                                    modifierPrenomPersonne(listeP,idM);
                                    
                                    
                                    getch();
                                    break;

					    case 3 :
                                    system("cls");
                                    
                                    printf("\n\n - - - - - - - - - - - - - - - - -  AFFICHAGE  - - - - - - - - - - - - - - - - - \n\n");
                                    
                                    afficherListePersonne(listeP);
                                    
                                    
                                    getch();
                                    break;
                                    
                                    
                        case 4 :  
                                     do{
                        	
                        	            do{
                                             system("cls");
                                             printf("\n\n - - - - - - - - - - -  Rrecherche par nom/prenom/identifiant  - - - - - - - - - - - - \n\n");
                                    
                                    

                                             printf("\n\t\t [1].Recherche par l'Identifiant  \n");
                                             printf("\n\t\t [2].Recherche par Nom  \n");
                                             printf("\n\t\t [3].Recherche par Prenom  \n");
                                             printf("\n\t\t [4].Revenir au menu precedent \n\n");

                                             printf("\n\t - Faites votre choix : ");
                                             scanf("%d",&choixSearch);

                                          }while( choixSearch != 1 && choixSearch != 2 && choixSearch != 3 && choixSearch != 4 );

                                          chercherPersonne(listeP,choixSearch);
                                      
                                       }while( choixSearch != 4 );
                                      
                                      
                                       
                                       break;
                                    
                                    
					    case 5 :
                                    system("cls");
                                    
                                    printf("\n\n - - - - - - -   retourner le nom de la mere/pere   - - - - - - - \n\n");
                                    
                                    printf("\n\n - Saisissez l'identifiant d'une personne : ");
                                    scanf("%d",&id);
                                    
                                    nomPereMere( listeP, id );
                                    
                                    getch();
                                    break;
                                    
                        case 6 :
                                    system("cls");

                                    printf("\n\n - - - - - - - - - - - -   afficher l age d'une personne  - - - - - - - - - - - \n\n");
                                    
                                    printf("\n\n - Saisissez l'identifiant d'une personne : ");
                                    scanf("%d",&id);
                                    
                                    p = chercherPersonneById( listeP, id );
                                    
                                    if( !p ) printf("\n\n - La personne de l'id %d n'existe pas ! \n\n ",id);
                                    else
                                      printf("\n\n - %s %s , qui a comme identifiant %d, a %d ans \n\n",p->data->nom,p->data->prenom,p->data->id,agePersonne(p));

                                    getch();
                                    break;
                                    
					    case 7 :
                                    
                                    do
									{
									  
									    do
										{
											system("cls");
                                    
                                            printf("\n\n- - - - - - - - - - - - --  trier la liste des personnes - - - - - - - - - - - - \n\n");
											

                                            printf("\n\t\t [1].Trier par l'identifiant  \n");
                                            printf("\n\t\t [2].Trier par Nom  \n");
                                            printf("\n\t\t [3].Revenir au menu precedent \n\n");

                                            printf("\n - Faites votre choix : ");
                                            scanf("%d",&choixSearch);

                                        }while( choixSearch != 1 && choixSearch != 2 && choixSearch != 3 );

                                        listeP = trierListe(listeP,choixSearch);
									
								   }while( choixSearch != 3 );
									
									
                                    
                                    
                                    break;
                                    
                        case 8 :
                                    system("cls");
                                    
                                    printf("\n\n - - - -  - - - - - - - - -   imprimer acte de naissance   - - - - - - - - - - - - \n\n");
                                    
                                    
				                    
				                    printf("\n - Saisissez l'identifiant d'une personne : ");
                                    do{
									
	                                      scanf("%d",&id);
	                                      
	                                      p = chercherPersonneById(listeP,id);
	                                      
	                                      if(!p) printf("\n - Saisissez un autre : ");
	                                      
	                                  }while( !p );
				                    
				                    printPersonne(listeP,id);
				                    
				                    

				                    getch();                                    
                                    break;
                                    
                        case 9 :
                        	       //Revenir au menu principal
                        	
                        	        break;
                        	        
						case 10 :    
						
						            //Quitter
     	     
                                    sauvegarder( listeP,nbrePersonne);
   		                            exit(0);
						        
                                    break;
                                    
                                    
                                    
						default:
                                printf("\n\n\t/!\\ Votre choix est invalid /!\\\n\n");
                                getch();


		            }
		            

                    

              }while( choixMenu != 9  );

		            
		            
              break;




	    case 2:
	 	
	 	       //Gestion des enfants
		       do{
                     system("cls");
                     printf("\n - - - - - - - - - - gestion des enfants - - - - - - - - - - - \n\n\n");
                     printf("\t\t [1] . Afficher les enfants d'une personne \n\n");
                     printf("\t\t [2] . Ajouter les enfants d'une personne\n\n");
                     printf("\t\t [3] . Revenir au menu principal.\n\n");
                     printf("\t\t [4] . Quitter.\n\n\n");
					 printf("\t -- Faites votre choix : ");
                     scanf("%d",&choixMenu);



			         switch(choixMenu)
			         {
					    case 1 :
                                    system("cls");
                                    printf("\n\n - - - - - - - - - - - - - - afficher les enfants - - - - - - - - - - - - - - - \n\n");
                                  	printf("\n - Saisissez l'identifiant d'une personne : ");
	                                scanf("%d",&id);
	                                
	                                afficherEnfants(listeP,id);
	                                
                                    getch();
                                    break;
                                    


					    case 2 :
                                    system("cls");
                                    printf("\n\n - - - - - - - - - - - - - - ajouter des enfants - - - - - - - - - - - - - - - \n\n");
                                  	printf("\n - Combien d'enfants voulez vous saisir : ");
	                                scanf("%d",&NbrPers);

	                                printf("\n\n - - - - - - - - - - - - -  saisie des donnees - - - - - - - - - - - - \n\n");

	                                for(i = 0 ; i < NbrPers ; i++)
	                                {
                                       printf("  - PRENOM : ");fflush(stdin);gets(prenom);fflush(stdin);

                                       printf("  - SEXE : ");fflush(stdin);scanf("%c",&sexe);fflush(stdin);


                                         //Vérification de l'identifiant du Pere :
		                                 // - Si le pere n'existe pas.
		                                 // - Si le pere n'est pas un homme.
                                         
                                        printf("\n  - ID DU PERE : ");
                                        do{

		                                	scanf("%d",&idPere);
		                                	
		                                	p = chercherPersonneById(listeP,idPere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		printf("\n  - Id n'existe pas -");
												printf(" ID DU PERE : ");

											}
											else
											{
												if( idPere%10 != 1 )
												{
		                                		    printf("\n  - Id invalid -");
												    printf(" ID DU PERE : ");	
												}
											}
					                  	 
                                        }while( !p || ( idPere%10 != 1 )  );



                                         //Vérification de l'identifiant de la mere :
	                             	     // - Si la mere n'existe pas.
	                              	     // - Si la mere n'est pas une femme.
	                              	     
	                              	    printf("\n  - ID DE LA MERE : ");
                                        do{

											scanf("%d",&idMere);
											
											p = chercherPersonneById(listeP,idMere);
		                                	
		                                	if( !p ) 
		                                	{
		                                		printf("\n  - l'identifiant n'existe pas -");
												printf(" identifiant de la mere : ");

											}
											else
											{
												if( idMere%10 != 2 )
												{
		                                		    printf("\n  - identifiant invalid -");
												    printf(" identifiant de la mere : ");	
												}
											}

                                        }while( !p || ( idMere == idPere ) || ( idMere%10 != 2 ) );
 
                                        


                                      //On vérifier la date de naissance
                                      do{

	                                         printf("  - date de naissance : ");
	                                         scanf("%d/%d/%d",&dateNaissance.jour,&dateNaissance.mois,&dateNaissance.annee);

                                             testDate = verifierDate(dateNaissance);               /* Si la date est invalid */
			                                 testAge = verifierAge(listeP,dateNaissance,idPere);     /* Si l'age de fils est plus grand que celui du pere */

                                        }while( testDate == 0 || testAge==0 );



                                     listeP = addNewPersonne(listeP,&nbrePersonne,prenom,dateNaissance,sexe,idPere,idMere);    /* insertion */

                                   }

                                    getch();
                                    break;

                                    
                        case 3 : 
                                    //Revenir au menu principal
                                    break;
                        	
						case 4 :            
                                    //Quitter
     	     
                                    sauvegarder( listeP,nbrePersonne);
   		                            exit(0);
						        
                                    break;

						default:
                                printf("\n\n\t\t/!\\ Votre choix est invalid /!\\\n\n");
                                getch();


		            }

              

              }while( choixMenu != 3 );



              break;
			 
	    case 3:
	   	        //Gestion du deces
	 	
	 	
	 	
	 	        do{
                     system("cls");
                     printf("\n - - - - - - - - - - gestion des deces - - - - - - - - - - - \n\n\n");
                     printf("\t\t [1] . Declaration de deces \n\n");
                     printf("\t\t [2] . Imprimer l'acte de deces \n\n");
                     printf("\t\t [3] . Revenir au menu principal.\n\n");
                     printf("\t\t [4] . Quitter.\n\n\n");
                     
					 printf("\t -- Faites votre choix : ");
                     scanf("%d",&choixMenu);


			         switch(choixMenu)
			         {
			
					    case 1 :
                                    system("cls");
                                    printf("\n\n - - - - - - -  - - - - declaration des deces - - - - - - - -  - - - - \n\n");
                                    
                                    
                                    printf("\n - Saisissez l'identifiant de personne : ");
                                    do{
									
	                                    scanf("%d",&id);
	                                      
	                                    p = chercherPersonneById(listeP,id);
	                                      
	                                    if( !p ) 
		                                {
		                                	printf("\n  - Id n'existe pas -");
											printf(" Saisissez un autre : ");

										}
	                                      
	                                  }while( !p );
	                                
	                               
	                                p->data->deces = 1;
	                                
	                                printf("\n\n- Votre declaration a etait bien effectuer.\n\n");
	                                
                                    getch();
                                    break;
                                    
                        case 2 :
                                    system("cls");
                                    printf("\n\n - - - -  - - - - - - - - -   imprimer acte de deces   - - - - - - - - - - - - \n\n");
                                    printf("\n - Saisissez l'identifiant de personne : ");
                                    do{
									
	                                    scanf("%d",&id);
	                                      
	                                    p = chercherPersonneById(listeP,id);
	                                      
	                                    if( !p ) 
		                                {
		                                	printf("\n  - Id n'existe pas -");
											printf(" Saisissez un autre : ");

										}
	                                      
	                                  }while( !p );
	                                  
	                                  
	                               
	                                if( !p->data->deces ) printf("\n\n- Impossible de delivrer cet acte, cette personne est encore vivante !\n\n");
									  else
									  {
									  	acteDeces(listeP,p);
									  }
				                    
				                    
				                    
				                    getch();
                                    break;
                                    
                        case 3 :
                        	        //Revenir au menu principal
                        	        
                        	        break;
                        	        
						case 4 :    
						            //Quitter
     	     
                                    sauvegarder( listeP,nbrePersonne);
   		                            exit(0);
						        
                                    break;          
                                    

						default:
                                printf("\n\n\t/!\\ Votre choix est invalid /!\\\n\n");
                                getch();


		            }




              }while( choixMenu != 3 );



              break;
	     
		            

		       
        case 5:
     	       //Quitter
     	     
               sauvegarder( listeP,nbrePersonne);
   		       exit(0);
     
		       
        default :
                printf("\n\n\t\t/!\\ Votre choix est invalid /!\\\n\n");
                getch();

       }



    }while( choixMenuP != 5 );

    break;

case 2 :		
		//Quitter
        sauvegarder( listeP,nbrePersonne);
   		exit(0);
   		     
   		     
default:
        printf("\n\n\t/!\\ votre choix est valide /!\\\n\n");
        getch();		     
	
	
		
}
   sauvegarder( listeP,nbrePersonne);
    getch();
}
