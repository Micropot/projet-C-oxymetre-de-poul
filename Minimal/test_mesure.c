#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mesure.h"
#include "fichiers.h"
#include "define.h"

int main(){
    absorp	myAbsorp;
    oxy myOxy;
    mesureTest("record1_iir.dat");

    
    
}







/*oxy mesure(absorp myAbsorp, parametre_mesure* para_mesure, oxy myOxy){
	float Quotient;
	float Periode_pouls;
	myOxy.spo2 = Mesure_SpO2(Quotient);
	myOxy.pouls = Mesure_pouls(Periode_pouls);
	//on remet toutes les valeurs a 0 pour éviter les problémes lors de l'utilisation suivante de la fonction
	para_mesure->periode = 0;
	para_mesure->passage_par_0 = 0;
	para_mesure->acr_max = 0;
	para_mesure->acir_max = 0;
	para_mesure->acr_min = 0;
	para_mesure->acir_min = 0;
	
	para_mesure->periode++;//on incrémente la periode
	return(myOxy);


}*/