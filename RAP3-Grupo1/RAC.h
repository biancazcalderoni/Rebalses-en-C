#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include "Articulo.h"

void inicializarRAC(Articulo *arreglo, int *cargados) {
    for(int i = 0; i < MRAC; i++){
        strcpy(arreglo[i].codigo, "*");
    }
    *cargados = 0;
}

void localizarRAC(Articulo *arreglo, char *idBuscado, int *pos, int *rLocalizar, int cargados, int *cantConsultas){
    *pos = hashing(idBuscado, MRAC);
    *rLocalizar = 0;
    int i = 0, marcAux = -1, contador = 0, k = 1;

    if(cargados > 0){
        i = *pos;
        while (contador < MRAC && strcmpi(arreglo[i].codigo, "*") != 0 && strcmpi(arreglo[i].codigo, idBuscado) != 0){
            if(marcAux == -1 && strcmpi(arreglo[i].codigo, "+") == 0){
                marcAux = i;
            }
            i = (i+k) % MRAC;
            k = k + 1;
            contador++;
            (*cantConsultas)++;
        }
        if(strcmpi(arreglo[i].codigo, idBuscado) != 0){
            if(strcmpi(arreglo[i].codigo, "*") == 0){
                if(marcAux != -1){
                    *pos = marcAux;
                } else {
                    *pos = i;
                }
                *rLocalizar = 0; //Localizar falla se puede dar alta
                if (contador < MRAC){
                    (*cantConsultas)++;
                }
            } else {
                if(marcAux != -1){
                    *pos = marcAux;
                    *rLocalizar = 0; //Localizar falla se puede dar alta
                } else {
                    *rLocalizar = 3; //Localizar falla no se puede dar el alta
                }
                if (contador < MRAC){
                    (*cantConsultas)++;
                }
            }
        } else {
            *pos = i;
            *rLocalizar = 1; //Localizar exito
            if (contador < MRAC){
                (*cantConsultas)++;
            }
        }

    } else {
        *rLocalizar = 2; //Localizar falla porque no hay elementos (se puede dar alta)
    }
}

void altaRAC(Articulo *arreglo, int *cargados, int *rAlta, Articulo aux){
    *rAlta = 0;
    int rLocalizar = 0, pos = 0, intBasura = 0;

    if (*cargados < MRAC){
        localizarRAC(arreglo, aux.codigo, &pos, &rLocalizar, *cargados, &intBasura);
        if(rLocalizar == 1){
            *rAlta = 0; //Como se encontró el elemento, el alta falla
        } else if (rLocalizar == 3) {
            *rAlta = 3; //Como no hay espacio para dar el alta, el alta falla
        }else{
            arreglo[pos] = aux;
            (*cargados)++;
            *rAlta = 1; //El alta es exitosa
        }
    } else {
        *rAlta = 2; //El alta falla porque no hay espacio en la estructura
    }
}

void bajaRAC(Articulo *arreglo, int *cargados, int *rBaja, Articulo aux, int lecOp){
    *rBaja = 0;
    int eleccion = 0, rLocalizar = 0, pos = 0, intBasura = 0;

    localizarRAC(arreglo, aux.codigo, &pos, &rLocalizar, *cargados, &intBasura);

    if(rLocalizar == 1){
        if(lecOp == 0){
            //ESTAMOS EN ADMINISTRACIÓN
            printf("El articulo que quiere borrar es: \n");
            printArt(arreglo[pos]);

            do{
                printf("\n\n Esta seguro que quiere borrarlo? \n"
                       "<1> -------- Si --------\n"
                       "<2> -------- No --------\n");
                scanf("%d", &eleccion);
                getchar();
            } while (eleccion < 1 || eleccion > 2);
        } else {
            //ESTAMOS EN OPERACIONES
            if(strcmpi(arreglo[pos].tipoArt, aux.tipoArt)==0 &&
               strcmpi(arreglo[pos].marca, aux.marca)==0 &&
               strcmpi(arreglo[pos].desc, aux.desc)==0 &&
               arreglo[pos].precio == aux.precio &&
               arreglo[pos].cantidad == aux.cantidad){

                eleccion = 1;
            }
        }
        if(eleccion == 1){
            strcpy(arreglo[pos].codigo, "+");
            (*cargados)--;
            *rBaja = 1; //Baja exitosa
        } else {
            *rBaja = 0; //Baja fallida
        }
    } else {
        *rBaja = 0; //Baja fallida
    }
}

Articulo evocarRAC(Articulo *arreglo, char *idBuscado, int cargados, int *rEvocar, int lecOp, int *costoMaxExito, int *sumCostosExito, int *cantExitos, int *costoMaxFracaso, int *sumCostosFracaso, int *cantFracasos){
    int rLocalizar = 0, pos = 0, cantConsultas = 0;
    Articulo aux;
    localizarRAC(arreglo, idBuscado, &pos, &rLocalizar, cargados, &cantConsultas);

    if (rLocalizar == 1){
        *rEvocar = 1;
        if(lecOp == 1){
            *sumCostosExito += cantConsultas;
            (*cantExitos)++;
            if(*costoMaxExito < cantConsultas){
                *costoMaxExito = cantConsultas;
            }
        }
        return arreglo[pos];
    } else {
        *rEvocar = 0;
        if(lecOp == 1){
            *sumCostosFracaso += cantConsultas;
            (*cantFracasos)++;
            if(*costoMaxFracaso < cantConsultas){
                *costoMaxFracaso = cantConsultas;
            }
        }
        return aux;
    }
}

#endif // RAC_H_INCLUDED
