#ifndef _SAVELOAD_H
#define _SAVELOAD_H

struct date
{
	short	jour;
	short	mois;
	short	annee;
};
typedef struct date strdate;

struct compte
{
	char	*type;
	char 	libelle[50];
	float	valeur;
	strdate	date;
	float	solde;
};
typedef struct compte strcompte;

void AjouterMouvement (int mouv);
void SauvegarderFichier (strcompte comp);
int VerificationDate (strcompte newCompte);
float CalculSolde ();
void LectureFichier ();
void AfficherFichier (strcompte comp);

#endif // _SAVELOAD_H
