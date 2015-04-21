//#include "fonctions.h"
#include "output.h"
#include "input.h"
#include "menu.h"
#include "saveload.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define         NBRDATE             10
#define         NBRANNEE            4
#define         NBRJOURMOIS         2
#define         MINANNEE            1600
#define         MAXANNEE            2100
#define         MINMOIS             1
#define         MAXMOIS             12

void LireDate (strdate	*date);

int main (int argc, char *argv[])
{
	short choix, repMenu;
	printf ("Salut Timon");
	choix = -1;
	repMenu = 0;	

	system ("clear");
	while (choix != 0)	
	{
		do
		{
			AfficherMenu ();
			printf ("\t Votre choix : ");
			choix = LireShort ();
		} while (choix < MIN_MENU || choix > MAX_MENU);
		SwitchMenu (choix);
	}
	return 0;
}

/*
    Input :
        strJoueur *Joueur : structure des joueurs.
        date : vecteur de chaine comprenant la date.
        NbrAnnee : Nombre de caractères pour une année.
        NbrJourMois : Nombre de caractères pour les jours et pour les mois.
        minmois : nombre minimum pour le mois.
        maxmois : nombre maximum pour le mois.
        minannee : nombre minimum pour l'année.
        maxannee : nombre maximim pour l'année.
    Process :
        Cette fonction va recepetionner les éléments d'une date, vérifier leur validité et la copier dans sa structure.
*/
void LireDate (strdate	*date)
{
	char c;
    short cpt, Jour, Mois, Annee, sMax_jour;

	/* Vérification du jour. */
	cpt = 0;
	Jour = 0;
	fflush(stdin);
	c = getchar ();
	while (cpt < NBRJOURMOIS && c != '/')
	{
		if (c >= '0' && c <= '9')
		{
			Jour = Jour * 10 + (c - 48);
			c = getchar ();
			cpt ++;
		}
		else
		{
			printf ("\t Veuillez verifier votre format (jj/mm/aaaa). \n");
			exit (EXIT_FAILURE);
		}
	}

	/* Vérification du mois. */
	cpt = 0;
	Mois = 0;
	c = getchar ();
	while (cpt < NBRJOURMOIS && c != '/')
	{
		if (c >= '0' && c <= '9')
		{
			Mois = Mois * 10 + (c - 48);
			c = getchar ();
			cpt ++;
		}
		else
		{
			printf ("\t Veuillez verifier votre format (jj/mm/aaaa). \n");
			exit (EXIT_FAILURE);
		}
	}

	/* Vérification de l'année. */
	cpt = 0;
	Annee = 0;
	c = getchar ();
	while (cpt < NBRANNEE && c != '\n')
	{
		if (c >= '0' && c <= '9')
		{
			Annee = Annee * 10 + (c - 48);
			c = getchar ();
			cpt ++;
		}
		else
		{
			printf ("\t Veuillez verifier votre format (jj/mm/aaaa). \n");
			exit (EXIT_FAILURE);
		}
	}

	/* Vérification de la validité de l'année et redemande en cas d'erreur */
	if (Annee < MINANNEE || Annee > MAXANNEE)
	{
		printf ("\t Annee non-valide. \n");
		exit (EXIT_FAILURE);
	}

	/* Vérification de la validité du mois et redemande en cas d'erreur */
	if (Mois < MINMOIS || Mois > MAXMOIS)
	{
		printf ("\t Mois non-valide. \n");
		exit (EXIT_FAILURE);
	}

	/* Vérification de la validité du jour et redemance en cas d'erreur */
	switch (Mois)
	{
		case 1 :
		case 3 :
		case 5 :
		case 7 :
		case 8 :
		case 10 :
		case 12 :
			sMax_jour = 31;
			break;
		case 4 :
		case 6 :
		case 9 :
		case 11 :
			sMax_jour = 30;
			break;
		case 2 :
			if (((Annee % 4 == 0) && (Annee % 100 != 0)) || (Annee % 400 == 0))
				sMax_jour = 29;
			else
				sMax_jour = 28;
			break;
	}
	if (Jour < 1 || Jour > sMax_jour)
	{
		printf ("\t Jour non-valide. \n");
		exit (EXIT_FAILURE);
	}

	(date->jour) = Jour;
	(date->mois) = Mois;
	(date->annee) = Annee;
}

