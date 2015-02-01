// Mes fichiers
#include "output.h"

// Les libraires
#include <stdio.h>

int Afficher (const char *message)
{
	int erreur;
	
	erreur = 0;

	erreur = printf ("%s", message);
	if (erreur < 0)
		return FALSE; // Erreur lors de la fonction printf.
	return TRUE; // Affichage correctement déroulé.
}
