#include "fir.h"
#include "fichiers.h"
#include <math.h>

absorp firTest(char* filename){
	absorp	myAbsorpE;// Entrée du filtre
    absorp myAbsorpS;// Sortie du filtre
	absorp tableau[51] = {0}; // Initialise un tableau pour stocker ACR & ACIR
	int fileState = 0;
	FILE* pFichier2 = initFichier(filename); // Ouvre le fichier

	while (fileState != EOF){// On continue tant que l'on est pas à la fin du fichier
        myAbsorpE = lireFichier(pFichier2, &fileState);// Parcours du fichier ligne par ligne en les stockants
            if (fileState != EOF){ //Pour ne pas avoir une ligne de plus à la fin du fichier
			myAbsorpS = FIR(myAbsorpE,tableau);// Stockage et filtrage des valeurs
			//printf("ligne %d : %.0f,%.0f,%.0f,%.0f \n", compteur, myAbsorpS.acr, myAbsorpS.dcr, myAbsorpS.acir, myAbsorpS.dcir);
		    }	
	}

	finFichier(pFichier2);// Fermeture du fichier à la fin de la lecture
	//printf("ligne %d : %.0f,%.0f,%.0f,%.0f \n", compteur, myAbsorpS.acr, myAbsorpS.dcr, myAbsorpS.acir, myAbsorpS.dcir);
	// Affichage des dernières valeurs
	return myAbsorpS; // On retourne les valeurs ayant subis le filtre FIR
}

absorp FIR(absorp myAbs, absorp *tableau){
	float y_acr = 0, y_acir = 0, FIR_TAPS[51]={1.4774946e-019,1.6465231e-004,3.8503956e-004,7.0848037e-004,1.1840522e-003,1.8598621e-003,2.7802151e-003,3.9828263e-003,5.4962252e-003,7.3374938e-003,9.5104679e-003,1.2004510e-002,1.4793934e-002,1.7838135e-002,2.1082435e-002,2.4459630e-002,2.7892178e-002,3.1294938e-002,3.4578348e-002,3.7651889e-002,4.0427695e-002,4.2824111e-002,4.4769071e-002,4.6203098e-002,4.7081811e-002,4.7377805e-002,4.7081811e-002,4.6203098e-002,4.4769071e-002,4.2824111e-002,4.0427695e-002,3.7651889e-002,3.4578348e-002,3.1294938e-002,2.7892178e-002,2.4459630e-002,2.1082435e-002,1.7838135e-002,1.4793934e-002,1.2004510e-002,9.5104679e-003,7.3374938e-003,5.4962252e-003,3.9828263e-003,2.7802151e-003,1.8598621e-003,1.1840522e-003,7.0848037e-004,3.8503956e-004,1.6465231e-004,1.4774946e-019};
	// Initialisation en flottant des coeffs et des valeurs de sorties du filtre
	// Initialisation des entiers
	int k = 0,l = 0;

	// Boucle for pour décaller les valeurs dans le tableau
	for (k = 50; k > 0; k--){
			tableau[k] = tableau[k-1]; // Permet de faire le décallage de gauche à droite et en supprimant l'ancienne valeur (buffer circulaire)
	}
	tableau[0]= myAbs; // Nouvelle valeur qu'on met au début du tableau

	// Boucle for pour faire la relation du filtre FIR
	for (l = 0; l <= 50; l++){
		y_acr += FIR_TAPS[l]*tableau[50-l].acr; //Sortie du filtre pour les ACR
		y_acir += FIR_TAPS[l]*tableau[50-l].acir; //Sortie du filtre pour les ACIR
	}

	myAbs.acr = y_acr;// On renvoie les valeurs dans la struct
	myAbs.acir = y_acir;// Seulement les ACR & ACIR (les DC sont inchangées)
	return myAbs;//On retourne les valeur filtrée
}

