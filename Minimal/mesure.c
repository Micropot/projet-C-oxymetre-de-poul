#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mesure.h"
#include "fichiers.h"


oxy mesure(absorp myAbsorp, oxy myOxy, parametre_mesure* para_mesure){
	float PtP_acr_1_periode;//pic to pic acr sur la premiere periode 
	float PtP_acir_1_periode;//pic to pic acir sur la premiere periode 
	float PtP_acr_final;//pic to pic acr valeur final
	float PtP_acir_final;// pic to pic acir valeur final
	float RsIR, SpO2, Quotient;
	float a1 = 25, b1 = 110, a2 = 35.41, b2 = 120.394;
	int pouls_final;
	float Periode;
	int i;
	
	

	//CALCUL MAX ET MIN DE ACR ET ACIR
	if(myAbsorp.acr >= para_mesure->acr_max){//calcul du Acr max pour une periode
		para_mesure->acr_max = myAbsorp.acr;//changement de la valeur de acr_max dans la structure para_mesure
	}
	if(myAbsorp.acir>= para_mesure->acir_max){//calcul du acir max pour une periode
		para_mesure->acir_max = myAbsorp.acir;
	}
	if(myAbsorp.acr<= para_mesure->acr_min){//calcul du acr minimum pour une periode
		para_mesure->acr_min = myAbsorp.acr;
	}
	if(myAbsorp.acir<=para_mesure->acir_min){//calcul du acir minimum pour une periode
		para_mesure->acir_min = myAbsorp.acir;
	}
	
	//PREMIERE DEMI PERIODE ACR
	if(para_mesure->valeur_precedente_acr<0 && myAbsorp.acr>=0){//si il y a eu un changement de signe
		para_mesure->passage_par_0_acr =1;//on marque qu'il y a eu un passage a 0
		if((para_mesure->valeur_precedente_acr<0 && myAbsorp.acr>=0) && para_mesure->passage_par_0_acr==1){//on test si il y a eu un nouveau changement de signe 
			para_mesure->periode_complete_acr = 1;//on marque qu'on a fait une periode complete
		
		}
		
	}
	para_mesure->valeur_precedente_acr = myAbsorp.acr;//la valeur precedente prend alors la valeur du tableau d'entrée

	if(para_mesure->valeur_precedente_acr>0 && myAbsorp.acr<=0){//si il y a eu un changement de signe
		para_mesure->passage_par_0_acr =1;//on marque qu'il y a eu un passage a 0
		if((para_mesure->valeur_precedente_acr>0 && myAbsorp.acr<=0) && para_mesure->passage_par_0_acr==1){//on test si il y a eu un nouveau changement de signe 
			para_mesure->periode_complete_acr = 1;//on marque qu'on a fait une periode complete
		
		}
		
	}
	para_mesure->valeur_precedente_acr = myAbsorp.acr;//la valeur precedente prend alors la valeur du tableau d'entrée
	
	//PREMIERE PERIODE COMPLETE
	if(para_mesure->periode_complete_acr == 1 ){//on verifie que l'on  a fait une periode complete
		para_mesure->dcr = myAbsorp.dcr;//on recupere les valeurs de dcr et de dcir 
		para_mesure->dcir = myAbsorp.dcir;
	
		//CALCUL DE PTP_ACR FINAL
		PtP_acr_1_periode = para_mesure->acr_max - para_mesure->acr_min;//on determine la valeur PtP pour une periode 
		if(para_mesure->PtP_acr_precedent == 0){//si la valeur precedente de PtP est à 0 cela signifie que nous somme a la premiere periode
			PtP_acr_final = PtP_acr_1_periode;//la valeur final prendre alors la valeur de PtP 1er periode
		}
		else{
			PtP_acr_final = (PtP_acr_1_periode+para_mesure->PtP_acr_precedent)/2;//si on est pas sur la premiere periode, la valeur final PtP est egale a la moyenne de de la valeur precedente et de la premiere periode
			para_mesure->PtP_acr_precedent = PtP_acr_final; 
		}
		PtP_acr_final = para_mesure->acr_max;//permet d'incrémenter ptp acr final

		//CALCUL DE PTP_ACIR FINAL
		//meme raiosnnement pour acir
		PtP_acir_1_periode = para_mesure->acir_max - para_mesure->acir_min;
		if(para_mesure->PtP_acir_precedent == 0){
			PtP_acir_final = PtP_acir_1_periode;
		}
		else{
			PtP_acir_final = (PtP_acir_1_periode+para_mesure->PtP_acir_precedent)/2; 
			para_mesure->PtP_acir_precedent = PtP_acir_final;
		}
		PtP_acir_final = para_mesure->acir_max;

		//APPLICATION DE LA FORMULE
		RsIR = ((PtP_acr_final/myAbsorp.dcr)/(PtP_acir_final/myAbsorp.dcir));

		//CALCUL DU SPO2	
		Quotient = RsIR;
		if (0.4 <= Quotient && Quotient <= 1){// Si Quotient appartient entre 0.4 et 1
			SpO2=-a1*Quotient+b1;// Alors on applique la fonction pour cette partie de la courbe
		}						 // pour obtenir le taux de SpO2
		else if (1 < Quotient && Quotient <= 3.4){// Si Quotient appartient entre 3.4 et 1
			SpO2=-a2*Quotient+b2;// Alors on applique la nouvelle fonction pour cette courbe
		}						 // pour obtenir le taux de SpO2
		myOxy.spo2 = SpO2; //on met la valeur de SPO2 dans la structure myOxy


		//CALCUL DU POULS
		Periode = (float)para_mesure->periode;//on recupere le nombre de point par periode dans la variable Periode
			if(para_mesure->pouls_premiere_periode == 0){
				pouls_final = 60/(Periode*0.002);

			}
			else{
				Periode = (Periode + para_mesure->pouls_premiere_periode)/2;//on calcul la moyenne des points entre la periode actuelle et la periode precedente (0 si la periode actuelle est la premiere)
				pouls_final = 60/(Periode*0.002);//on calcul le pouls pour des points toutes les 2ms
			}
			

		
		para_mesure->pouls_premiere_periode = para_mesure->periode;//on met la valeur du nombre de point actuelle dans la valeur de poul premiere periode (qui correspond a la periode precedente)
		myOxy.pouls = pouls_final;//on stock la sortie du calcul dans la structure myOxy
		// printf("SPO2 : %d\n", myOxy.spo2);
		// printf("BPM = %d\n",myOxy.pouls);


		//mise a 0 de toutes les variables utilisé dans pour les calculs de une periode. Cela permet de reiterer les calculs periode par periode 
		para_mesure->periode = 0;
		para_mesure->periode_complete_acr = 0;
		para_mesure->acr_max = 0;
		para_mesure->acir_max = 0;
		para_mesure->acr_min = 0;
		para_mesure->acir_min = 0;
		para_mesure->dcr = 0;
		para_mesure->dcir = 0;
	}
	para_mesure->periode++;//on incremente le compteur qui donne le nombre de point par periode
	// printf("spo2 : %d\n",myOxy.spo2);
	// printf("BPM : %d\n\n",myOxy.pouls);
	return(myOxy);	
}



oxy mesureTest(char* filename){
	oxy myOxy;//on appelle la strucutre oxy
	absorp myAbsorpt;//on appelle la structure asorp
	parametre_mesure para_mesure;//on appelle la structure parametre_mesure
	init_mesure(&para_mesure);//on recolte les valeurs d'initialisation de la structure para_mesure
	int fileState = 0;
	FILE* pFichier = initFichier(filename);//permet d'ouvrir
	while(fileState!=EOF){
		myAbsorpt = lireFichier(pFichier, &fileState);
		if(fileState!=EOF){
			myOxy = mesure(myAbsorpt, myOxy, &para_mesure);
		}
	}
	return myOxy;
}

void init_mesure(parametre_mesure* para_mesure){//permet de remplire la strucutr qui remplis les parametre d'initialisation de la fonction
	para_mesure->acr_max = 1;
	para_mesure->acir_max = 1;
	para_mesure->acr_min = 0;
	para_mesure->acir_min = 0;
	para_mesure->PtP_acr_precedent = 0;
	para_mesure->PtP_acir_precedent = 0;
	para_mesure->dcr = 0;
	para_mesure->dcir = 0;
	para_mesure->periode = 0;
	para_mesure->passage_par_0_acr = 0;
	para_mesure->pouls_premiere_periode = 0;
	para_mesure->valeur_precedente_acr = 0;
	para_mesure->valeur_precedente_pouls = 0;
	para_mesure->periode_complete_acr = 0;
	para_mesure->periode_complete_acir = 0;
}
