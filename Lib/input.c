#include "input.h"
#include <stdio.h>
#include <stdlib.h>

short LireShort()
{
    /*
        cFaux : booléens qui force à quitter ou à recommencer en fonction de
            la valeur du nombre.
        cChaine : caractère de la chaine du buffer.
        iNombre : nombre en int qui reçoit la chaine transformée et qui
            permet d'éviter d'avoir un dépassement de capacité dans le short.
        sNombre : nombre short qui sera renvoyé au main.
        sSigne : signe positif ou négatif du nombre short.
    */
	char cChaine;
	short sNombre, sSigne;
	int iNombre;

	iNombre = 0;
	fflush (stdin);

	cChaine = getchar ();
	if (cChaine == '-')
	{
		cChaine = getchar ();
		sSigne = -1;
	}

	else
		sSigne = 1;

	while (cChaine != '\n')
	{
		if (cChaine >= '0' && cChaine <= '9')
		{
			iNombre = iNombre * 10 + (cChaine - 48);
			cChaine = getchar ();
		}
		else
		{
			printf ("\t Les caracteres entres ne correspondent pas a un entier. \n");
			exit (EXIT_FAILURE);
			cChaine = getchar ();
		}
		if (iNombre < 32769)
		{
			if (iNombre == 32768 && sSigne == -1)
				sNombre = iNombre;
			else
			{
				if (iNombre < 32768)
					sNombre = iNombre;
				else
				{
					printf ("\t Le nombre entre est trop grand. \n");
					exit (EXIT_FAILURE);
				}
			}
		}
		else
		{
			printf ("\t Le nombre entre est trop grand. \n");
			exit (EXIT_FAILURE);
		}
	}
	sNombre /= sSigne;

	return sNombre;
}

float LireFloat()
{
	double dNombre;
	float fNombre, deci = 0;
	short nbrdeci = 1, fin = 1, sSigne;
	char cChar;
	
	do
	{
        dNombre = 0;
        fflush (stdin);
        if (fin == -1)
        {
            printf ("\t Veuillez recommencer : ");
            fin = 1;
        }
		
        cChar = getchar ();
        if (cChar == '-')
        {
            cChar = getchar ();
            sSigne = -1;
        }

        else
        {
            sSigne = 1;
        }	
		while (fin != -1 && cChar != '.')
		{
			if (cChar >= '0' && cChar <= '9')
			{
				dNombre = dNombre * 10 + (cChar - 48);
				cChar = getchar ();
			}
			else
				fin = -1;
		}
		if (cChar == '.')
		{
			cChar = getchar ();
			while (fin != -1 && cChar != '\n')
			{
				if (cChar >= '0' && cChar <= '9')
				{
					deci = deci * 10 + (cChar - 48);
					cChar = getchar ();
					nbrdeci *= 10;
				}
				else
					fin = -1;
			}
		}
		else
			fin = -1; 
        if (dNombre < 32769)
        {
            if (dNombre == 32768 && sSigne == -1)
                fNombre = dNombre;
            else
            {
                if (dNombre < 32768)
                    fNombre = dNombre;
                else
                {
                    printf ("\t Le nombre entre est trop grand. \n");
                    fin = -1;
                }
            }
        }
        else
        {
            printf ("\t Le nombre entre est trop grand. \n");
            fin = -1;
        }
	} while (fin == -1);
			deci /= nbrdeci;
		dNombre += deci;
		printf ("Avant de continuer dans le lire float : \n");
		printf (" deci : %f, nbrdeci %hd \n", deci, nbrdeci);
		printf (" fNombre = %f \n", dNombre);
    return fNombre;
}

/*
    Input :
        pVec : chaine * de caractères.
        maxcol : nombre max de caractères.
    Process :
        Cette fonction va initialiser à '\0' le vecteur.
*/
void InitialiserChaine (char *pVec, short maxcol)
{
    short i;
    char *pCopie;

    pCopie = pVec;
    for (i = 0; i < maxcol; i++, pCopie ++)
    {
        *pCopie = '\0';
    }
    pVec = pCopie;
}

void LireChaine (char *pc, short maxi)
{
	char c, *pCopie;
	short i = 0;

        pCopie = pc;

        fflush (stdin);
        c = getchar();
        while ((i < maxi) && (c != '\n'))
        {
            *pCopie = c;
            pCopie++;
            i++;
            c = getchar();
            if (c == '\n')
            {
                *pCopie = '\0';
                i = 0;
            }
        }
        if (i != 0)
        {
            printf ("\t Depassement de capacite !\n");
			exit (EXIT_FAILURE);
        }
    pc = pCopie;
}
