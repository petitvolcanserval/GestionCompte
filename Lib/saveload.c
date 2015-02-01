#include "saveload.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void AjouterMouvement (int mouv)
{
	strcompte compte;
	float centime;
	short ret;

	if (mouv == 1)
	{
		compte.type = "Ajout";
	}
	else
	{
		compte.type = "Retrait";
	}

	printf ("\t Libellé : ");
	LireChaine (compte.libelle, 50);

	printf ("\t Valeur (en euro) : ");
	if (mouv == 1)
	{
		compte.valeur = LireShort ();
		while (compte.valeur > 32766)
		{			
			if (compte.valeur > 32766)
			{
				printf ("Valeur trop grande. \n\tRecommencez : ");
				compte.valeur = LireShort ();
			}
		}

		printf ("\t Valeur (en centime) : ");
		centime = LireShort ();
		while (centime  < 0 || centime > 99)
		{
			if (centime < 0 || centime > 99)
			{
				printf ("Cette valeur n'est pas comprise pour les euros. \n\tRecommencez : ");
				centime = LireShort ();
			}
		} 
		centime /= 100;
		compte.valeur += centime;
	}
	else
	{
		do
		{
			compte.valeur = LireShort  ();
		} while (compte.valeur >= 500000);
		do
		{
			printf ("\t Valeur (en centime) : ");
			centime = LireShort ();
		} while (centime < 0 || centime > 99);
		centime /= 100;
		compte.valeur += centime;
		compte.valeur *= -1;
	}

	do
	{	
		ret = 1;
		if (!Afficher("\t Date : "))
		{
			perror (" Erreur lors de l'affichage. ");
		}
		LireDate (&compte.date);
		ret = VerificationDate (compte);
		if (ret == -1)
			printf ("\t La date du mouvement ne peut être inférieur au denier mouvement effectué sur ce compte. \n");	
	} while (ret == -1);
	compte.solde = compte.valeur + CalculSolde ();
	SauvegarderFichier (compte);
}

int VerificationDate (strcompte newCompte)
{
	short ret = 1;
	FILE *fp = NULL;	
	strcompte compte;
	
	fp = fopen ("data.dat", "a+b");
	if (fp == NULL)
	{
		perror (" Erreur de création du fichier data");
		fclose (fp);
	}
	fseek (fp, -sizeof(strcompte), SEEK_END);
	fread (&compte, sizeof(strcompte), 1, fp);
	if (newCompte.date.annee > compte.date.annee)
		ret = 1;
	if (newCompte.date.annee < compte.date.annee)
		ret = -1;
	if (newCompte.date.annee == compte.date.annee && newCompte.date.mois > compte.date.mois)
		ret = 1;
	if (newCompte.date.annee == compte.date.annee && newCompte.date.mois < compte.date.mois)
		ret = -1;
	if (newCompte.date.annee == compte.date.annee && newCompte.date.mois == compte.date.mois && newCompte.date.jour > compte.date.jour)
		ret = 1;
	if (newCompte.date.annee == compte.date.annee && newCompte.date.mois == compte.date.mois && newCompte.date.jour < compte.date.jour)
		ret = -1;
	if (newCompte.date.annee == compte.date.annee && newCompte.date.mois == compte.date.mois && newCompte.date.jour == compte.date.jour)
		ret = 1;

	fclose (fp);
	
	return ret;
}

void SauvegarderFichier (strcompte compte)
{
	FILE * fp = NULL;
	short choix;

	printf ("\n");
	printf ("\t Voici ce que vous venez d'encoder : \n\n");
	AfficherFichier (compte);
	printf ("\t 1. Pour enregistrer. \n");
	printf ("\t 2. Pour ne rien enregistrer. \n");
	printf ("\t Votre choix : ");
	choix = LireShort ();
	
	if (choix == 1)
	{
		fp = fopen ("data.dat", "a+b");
		if (fp == NULL)
		{
			perror (" Erreur de création du fichier data");
			fclose (fp);
		}
		fwrite (&compte, sizeof(strcompte), 1, fp);
		printf ("\t Le mouvement a bien été enregistré. \n\n");
		fclose (fp);
	}
	else
	{
		printf ("\t Aucune action n'a été enregistrée. \n\n");
	}	
}

float CalculSolde ()
{
	FILE * fp = NULL;
	strcompte compte;
	float solde;

	solde = 0;

	fp = fopen ("data.dat", "a+b");
	if (fp == NULL)
	{
		perror (" Erreur de création du fichier data");
		fclose (fp);
		exit (EXIT_FAILURE);
	}
	fread (&compte, sizeof(strcompte), 1, fp);
	
	while (!feof(fp))
	{
		solde += compte.valeur;
		fread (&compte, sizeof(strcompte), 1, fp);
	}
	fclose (fp);

	return solde;
}

void LectureFichier ()
{
	FILE * fp = NULL;
	strcompte compte;
	float solde;

	fp = fopen ("data.dat", "a+b");
	if (fp == NULL)
	{
		perror (" Erreur de création du fichier data");
		fclose (fp);
		exit (EXIT_FAILURE);
	}
	fread (&compte, sizeof(strcompte), 1, fp);
	
	while (!feof(fp))
	{
		AfficherFichier (compte);
		fread (&compte, sizeof(strcompte), 1, fp);
	}
	fclose (fp);
}

void AfficherFichier (strcompte compte)
{
	printf ("\t\t Mouvement : \n");
	printf ("\t Type : %s \n", compte.type);
	printf ("\t Libellé : %s \n", compte.libelle);
	printf ("\t Valeur : %.2f €\n", compte.valeur);
	printf ("\t Solde : %.2f €\n", compte.solde);
	printf ("\t Date : %hd/%hd/%hd \n\n", compte.date.jour, compte.date.mois, compte.date.annee);
}
