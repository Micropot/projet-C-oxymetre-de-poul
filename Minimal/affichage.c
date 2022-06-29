#include "affichage.h"
#include <unistd.h>

void affichage(oxy myOxy){
    if( access(".verrouData", F_OK ) != -1 ){// Test si .verrouData exite
        printf(".verrouData existe !\n"); // verrouData existe
    }
    else{// verrouData n'existe pas
        FILE *pFichier = fopen ("Data.txt", "w"); // Ouverture de Data.txt en écriture
        FILE *pVerrou = fopen (".verrouData", "w"); // Création du fichier .verrouData
        fprintf(pFichier,"%d",myOxy.spo2);// Ecriture des valeurs dans le fichier Data.txt
        fprintf(pFichier,"\n");
        fprintf(pFichier,"%d",myOxy.pouls);// Ecriture des valeurs dans le fichier Data.txt
        fclose(pFichier);// Fermeture de Data.txt
        fclose(pVerrou);// Fermeture de verrouData
        remove(".verrouData");// Supprime verrouData
    }
}