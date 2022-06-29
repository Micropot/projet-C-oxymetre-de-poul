#include "define.h"
#include "fichiers.h"
#include "affichage.h"

int main(){
    oxy myOxy;
    myOxy.pouls = 84; //on définit les valeurs de la structure
    myOxy.spo2 = 20;

    affichage(myOxy);
}
