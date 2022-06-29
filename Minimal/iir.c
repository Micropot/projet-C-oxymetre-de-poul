#include "iir.h"
#include "fichiers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

absorp iir(absorp myAbsop, parametre_iir* ValeurPres){//fonction qui permet de traiter une ligne du programme en fonction de la valeur du tableau et de la valeur précédente sauvegardé dans la structure parametreiir
	float alpha = 0.992;
	ValeurPres->y_n_1_acr = myAbsop.acr - ValeurPres->x_n_1_acr+alpha*ValeurPres->y_n_1_acr;//change la valeur de la strcuture par la valeur sortant de la formule
	ValeurPres->y_n_1_acir = myAbsop.acir - ValeurPres->x_n_1_acir+alpha*ValeurPres->y_n_1_acir;
	ValeurPres->x_n_1_acr = myAbsop.acr;//lit la valeur dans le fichier fir
	ValeurPres->x_n_1_acir = myAbsop.acir;

	myAbsop.acr = ValeurPres->y_n_1_acr;
	myAbsop.acir = ValeurPres->y_n_1_acir;
    return (myAbsop);//retour de la nouvelle valeur d'absorp
	
}


absorp iirTest(char* filename){
	absorp	myAbsorp;//utilisation de la strucuture absorp avec la variable myAbsorp
	absorp myAbsorp_FIR;//utilisation de la strucuture aborp avec la variable myAbsorp_FIR
	parametre_iir ValeurPres;//utilisation de la strucuture parametre_irr avec la variable ValeurPres
	init_iir(&ValeurPres);//permet de récuperer les valeurs de la structure 
	int fileState = 0;
	FILE* pFichier_FIR = initFichier(filename);//permet d'ouvrir le fichier d'entree

	while(fileState !=EOF){//tant qu'on est pas a la fin du fichier 
		myAbsorp_FIR = lireFichier(pFichier_FIR, &fileState);//on lit les valeurs du fichier d'entrée
		if(fileState != EOF){//permet de ne pas aller trop loins dans le fichier 
			myAbsorp = iir(myAbsorp_FIR, &ValeurPres);//remplie la structure avec les valeurs sortant de la fonction fir
		}
		printf("%.0f,%.0f,%.0f,%.0f\n", myAbsorp.acr,myAbsorp.dcr,myAbsorp.acir,myAbsorp.dcir);//permet d'observer les résultats.
	}

	return(myAbsorp);

}

void init_iir(parametre_iir* valeur_precedente){//on créer une structure avec les valeur précedentes. on les initialise a 0 pour le départ
	valeur_precedente->x_n_1_acr = 0;
	valeur_precedente->y_n_1_acr = 0;
	valeur_precedente->x_n_1_acir = 0;
	valeur_precedente->y_n_1_acir = 0;

}

