#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
		float acr;  
		float dcr;  
		float acir;  
		float dcir;  
	} absorp;



typedef struct{
		int spo2;  
		int pouls; 
	} oxy;


typedef struct{
		float x_n_1_acr;
		float y_n_1_acr;
		float x_n_1_acir;
		float y_n_1_acir;
} parametre_iir;

typedef struct{
		float acr_max;
		float acr_min;
		float acir_max;
		float acir_min;
		float dcr;
		float dcir;
		int periode;
		int passage_par_0_acr;
		int passage_par_0_acir;
		float pouls_premiere_periode;
	
		float PtP_acr_precedent;
		float PtP_acir_precedent;
		float valeur_precedente_acr;
		float valeur_precedente_acir;
		float valeur_precedente_pouls;
		int periode_complete_acr;
		int periode_complete_acir;

} parametre_mesure;


#endif // DEFINE_H












