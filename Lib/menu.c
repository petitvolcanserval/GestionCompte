#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

void AfficherMenu ()
{
	if (!Afficher("\t ****************************** \n"))
	{
		perror (" Erreur d'affichage.");
		exit (EXIT_FAILURE);	
	}

	if (!Afficher ("\t **********   Menu   ********** \n\n"))
	{
		perror (" Erreur d'affichage.");
		exit (EXIT_FAILURE);	
	}

	if (!Afficher ("\t ****************************** \n"))
	{
		perror (" Erreur d'affichage.");
		exit (EXIT_FAILURE);	
	}

	if (!Afficher ("\t 1. \t Ajout au solde. \n"))
	{
		perror (" Erreur d'affichage.");
		exit (EXIT_FAILURE);	
	}

	if (!Afficher ("\t 2. \t Retrait. \n"))
	{
		perror (" Erreur d'affichage.");
		exit (EXIT_FAILURE);	
	}

	if (!Afficher ("\t 3. \t Afficher mouvements. \n"))
	{
		perror (" Erreur d'affichage.");
		exit (EXIT_FAILURE);	
	}

	if (!Afficher ("\t 0. \t Quitter. \n"))
	{
		perror (" Erreur d'affichage.");
		exit (EXIT_FAILURE);	
	}
}

void SwitchMenu (int choix)
{
	int ret, mouv;
	float solde;

	switch (choix)
	{
		case 1 :
			system ("clear");
			printf ("\t Encodage d'un ajout à votre compte. \n\n");
			mouv = 1;
			AjouterMouvement (mouv);
			break;

		case 2 : 
			system ("clear");
			printf ("\t Encodage d'un retrait à votre compte. \n\n");
			mouv = -1;
			AjouterMouvement (mouv);
			break;

		case 3 :
			printf ("\t Voici le contenu de vos mouvements. \n\n");
			LectureFichier ();
			break;
	}	
}
