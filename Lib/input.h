#ifndef _INPUT_H
#define _INPUT_H

#define         LG_DATE             10
#define         LG_ANNEE            4
#define         LG_JOURMOIS         2
#define         MINANNEE            1600
#define         MAXANNEE            2100
#define         MINMOIS             1
#define         MAXMOIS             12

short LireShort ();
float LireFloat();
void InitialiserChaine (char *, short);
void LireChaine (char *, short);

#endif // _INPUT_H
