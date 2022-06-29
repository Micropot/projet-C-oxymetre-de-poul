#include "lecture.h"
#include "fichiers.h"

int main(){
    int etat = 0;
    FILE* pFichier = initFichier("record1_bin.dat");
    lecture(pFichier,&etat);
}