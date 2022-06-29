#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "affichage.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "integration.h"
#include "fichiers.h"
#include "define.h"

int main(){
    int fileState = 0, compt = 0;
    //On initialise toutes les données
    oxy myOxy={0};
    absorp	myAbsorpE={0};// Entré du filtre
    absorp	myAbsorpS={0};// Sortie du filtre
    absorp tableau[51]={0};//Tableau pour stocker les valeurs AC et DC
	parametre_iir ValeurPres;
    init_iir(&ValeurPres);// Initialise les paramètre pour le filtre iir
    parametre_mesure para_mesure;
    init_mesure(&para_mesure);// Initialise les paramètre pour la fonction mesure
    
    FILE* pFichierF = initFichier("record1.dat");//On ouvre le fichier de base non filtré

    // On continue tant que l'on est pas à la fin du fichier
    while (fileState != EOF){
            myAbsorpE=lireFichier(pFichierF, &fileState);// Parcours du fichier ligne par ligne en les stockants
            if (fileState != EOF){
                myAbsorpS=FIR(myAbsorpE,tableau);//On filtre les valeurs d'entrées par le FIR
                myAbsorpS=iir(myAbsorpS,&ValeurPres);//Ensuite, on passe les valeurs dans le filtres IIR
                myOxy=mesure(myAbsorpS,myOxy,&para_mesure);//Puis, on cherche à déterminer le taux de SpO2 et les BPM des valeurs filtrées
                affichage(myOxy);//Enfin, on remplace les valeurs de SpO2 et BPM dans Data.txt
                compt++;
                printf("ligne %d : BPM %d    SpO2 %d\n", compt, myOxy.pouls, myOxy.spo2);// Affiche dans la console les BPM et SpO2
            }
    }
    finFichier(pFichierF);//On ferme le fichier une fois terminé
}