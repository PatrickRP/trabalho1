#include<stdio.h>
#include<string.h>

#include"kdTree.h"

int main(void){

    FILE* file = fopen("municipio.csv", "r");

    if(!file){
        fprintf(stderr, "Não foi possivel abrir o arquivo!\n");
        return 1;
    }

    while(!feof(file)){
        char codigo_ibge[8] = "";
        char nome[30] = "";
        float latitude = 0.0;
        float longitude = 0.0;
        int capital = 0;
        int codigo_uf = 0;
        int siafi_id = 0;
        int ddd = 0;
        char fuso_horario[30] = "";

        int nfields = fscanf(file, "%[^,],%[^,],%lf,%lf,%d,%d,%d,%d,%[^,],%[^\n]",
            codigo_ibge, nome, &latitude, &longitude, &capital, &codigo_uf, &siafi_id, &ddd, fuso_horario
        );

        if(nfields != 9)
            break;

        printf("%s, %s, %lf, %lf, %d, %d, %d, %d, %s", codigo_ibge, nome, latitude, longitude, capital, codigo_uf, siafi_id, ddd, fuso_horario);
    }
    fclose(file);
    return 0;
}