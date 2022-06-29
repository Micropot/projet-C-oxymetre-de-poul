#include "lecture.h"
#include "fichiers.h"
#include <string.h>

absorp lecture(FILE* file_pf, int* file_state){
	//On initalise nos variables nécéssaires
	int k = 0;
	char octet, trame[21] = {0};
	absorp myAbsorp;

	if (*file_state != EOF){// On regarde si le fichier n'est pas finit
		for (k = 0; k <= 20; k++){// On parcours toute la ligne
			octet = fgetc(file_pf);// On stock chaque char dans octet
			if (octet != EOF){// On regarde si 
				trame[k] = octet;// On stock les octets dans la trame
			}
			else{
				*file_state = EOF;
			}
		}
		/*printf("%d,%d,%d,%d \n", trame[0], trame[1], trame[2], trame[3]);
		printf("%d,%d,%d,%d \n", trame[5], trame[6], trame[7], trame[8]);
		printf("%d,%d,%d,%d \n", trame[10], trame[11], trame[12], trame[13]);
		printf("%d,%d,%d,%d \n", trame[15], trame[16], trame[17], trame[18]);
		*/
		// Conversion des octet de la trame et recentrage des valeurs que pour ACR & ACIR
		// -2048 pour le rencentrage car les valeurs sont comprises entre 0 et 4095
		myAbsorp.acr = (((trame[0]-48)*1000 + (trame[1]-48)*100 + (trame[2]-48)*10 + (trame[3]-48)) - 2048);
		myAbsorp.dcr = ((trame[5]-48)*1000 + (trame[6]-48)*100 + (trame[7]-48)*10 + (trame[8]-48));
		myAbsorp.acir = (((trame[10]-48)*1000 + (trame[11]-48)*100 + (trame[12]-48)*10 + (trame[13]-48)) - 2048);
		myAbsorp.dcir = ((trame[15]-48)*1000 + (trame[16]-48)*100 + (trame[17]-48)*10 + (trame[18]-48));
		//printf("%f,%f,%f,%f\n", myAbsorp.acr,myAbsorp.dcr,myAbsorp.acir,myAbsorp.dcir);
	}
	else{
		*file_state=EOF;
	}
	//printf("%f,%f,%f,%f\n", myAbsorp.acr,myAbsorp.dcr,myAbsorp.acir,myAbsorp.dcir);
	// Pour afficher les diférentes valeurs de AC et DC
	return myAbsorp; // return EOF flag
}
