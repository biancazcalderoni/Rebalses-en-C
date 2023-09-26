#ifndef VINCULADAS_H_INCLUDED
#define VINCULADAS_H_INCLUDED

#include "Articulo.h"

// OPERACIONES DE MANEJO DE LISTAS
typedef struct{
    Articulo vipd;
    struct nodo *next;
} nodo;

typedef struct{
    nodo *acc;
    nodo *cur;
    nodo *pre;
    int cargados;
} Lista;

void inicializar(Lista *l){
    l->acc = l->cur = l->pre = NULL;
    (*l).cargados = 0;
}

int isEmpty(Lista l){
    // Vacia -> 1
    if (l.acc == NULL){
        return 1;

    } else {
    // Con elementos -> 0
        return 0;
    }
}

void reset(Lista *l){
    l->cur = l->pre = l->acc;
}

void avanzar(Lista *l){
    l->pre = l->cur;
    l->cur = l->cur->next;
}

int isOos(Lista l){
    if (l.cur == NULL) return 1;
    else return 0;
}

void copiar(Lista l, Articulo *aux){
    *aux = l.cur->vipd;
}

void vaciarLista(Lista *l){
    l->cur = l->pre = l->acc;//reset(l);
    while (l->cur != NULL){
        if (l->cur->next != NULL){
            avanzar(l);
            free(l->pre);
        } else {
            free(l->cur);
        }
    }
    l->acc = l->cur = l->pre = NULL;
    (*l).cargados = 0;
}

void localizarVin(Lista *l, char *idBuscado, int *rLocalizar, int typeEstructura, int *cantConsultas){
    //Función strcmpi (No usamos strcmp porque es CaseSensitive)
    //0 si a = b
    //<0 si a < b
    //>0 si a > b
    l->cur = l->pre = l->acc;//reset(l);
    *rLocalizar = 0;

    if (l->acc != NULL){
        //typeEstructura == 1 significa que está usando LVD
        while ((l->cur != NULL) && strcmpi(((l->cur->vipd).codigo), idBuscado)!=0){
            avanzar(l);
            /*
            l->pre = l->cur;
             l->cur = l->cur->next;*/
            (*cantConsultas)++;
        }

        if (l->cur == NULL){
            *rLocalizar = 0; // Localizar falla
        }else if(strcmpi((l->cur->vipd.codigo), idBuscado)==0) {
            (*cantConsultas)++;
            *rLocalizar = 1; //Localizar exitoso
        }

    } else {
        *rLocalizar = 2; //No hay elementos en la lista
    }

}

void altaVin(Lista *l, int *rAlta, int typeEstructura, Articulo art, int lecOp, float *costoMax, float *sumCostos, int *cantExitos){
    int rLocalizar = 0, intBasuraInt = 0;
    float sumAux = 0;
    *rAlta = 0;

    localizarVin(l, art.codigo, &rLocalizar, typeEstructura, &intBasuraInt);

    if (rLocalizar == 1){
        *rAlta = 0; //Como se encontró el elemento entonces el alta falla
    } else {
        nodo *n = (nodo*)malloc(sizeof(nodo));
        if (n != NULL){
            n->vipd = art;
            n->next = NULL;
            sumAux+=0.5;

            // como es desordenada simplemente damos de alta al final
            if ((l->acc == NULL)){
                l->acc = n;
                sumAux+=0.5;
                *rAlta = 1; // exito en el alta
                (*cantExitos)++;
                (*l).cargados++;
            } else {
                l->pre->next = n;
                //l->cur = n;
                *rAlta = 1; // exito en el alta
                (*cantExitos)++;
                (*l).cargados++;
                sumAux+=0.5;
            }
            if(lecOp == 1){
                *sumCostos += sumAux;
                if (sumAux > *costoMax){
                    *costoMax = sumAux;
                }
                //(*cantExitos)++;
            }
        } else {
            *rAlta = 2; //El alta falla porque no hay más espacio en la estructura
        }
    }
}

void bajaVin(Lista *l, int *rBaja, int typeEstructura, Articulo art, int lecOp, float *costoMax, float *sumCostos, int *cantExitos){
    int rLocalizar = 0, eleccion = 0, intBasuraInt = 0;
    float sumAux = 0;
    nodo *temp;
    *rBaja = 0;

    localizarVin(l, art.codigo, &rLocalizar, typeEstructura, &intBasuraInt);

    if(rLocalizar == 1){

        if(lecOp == 0){
            printf("El articulo que quiere borrar es: \n");
            printArt(l->cur->vipd);

            do{
                printf("\n\n Esta seguro que quiere borrarlo? \n"
                       "<1> -------- Si --------\n"
                       "<2> -------- No --------\n");
                scanf("%d", &eleccion);
                getchar();
            } while (eleccion < 1 || eleccion > 2);
        } else {
            if (l->cur->vipd.cantidad == art.cantidad && strcmpi(l->cur->vipd.desc,art.desc)==0 && strcmpi(l->cur->vipd.marca,art.marca)==0 && l->cur->vipd.precio==art.precio && strcmpi(l->cur->vipd.tipoArt,art.tipoArt)==0){
                eleccion = 1;
            }
        }

        if (eleccion == 1){
            if(l->acc->next==NULL){
                temp = l->cur;
                l->acc = NULL;
                (*l).cargados = 0;
                sumAux+= 0.5;
                free(temp);
                *rBaja = 1;
                (*cantExitos)++;

            } else if (l->cur == l->pre){ //eliminamos la 1ra y unica y ultima
                temp = l->acc;
                l->acc = l->acc->next;
                sumAux+= 0.5;
                free(temp);
                (l->cargados)--;
                *rBaja = 1;
                (*cantExitos)++;
            } else {
                temp = l->cur;
                l->pre->next = l->cur->next;
                sumAux+= 0.5;
                free(temp);
                (l->cargados)--;
                *rBaja = 1;
                (*cantExitos)++;
            }
            if(lecOp == 1){
                *sumCostos += sumAux;
                if(sumAux > *costoMax){
                    *costoMax = sumAux;
                }
            }
        }
    } else {
        *rBaja = 0; //Baja fallida
    }
}

Articulo evocarVin(Lista *l, int *rEvocar, int typeEstructura, char *idBuscado, int lecOp, int *costoMaxExito, int *sumCostosExito, int *cantExitos, int *costoMaxFracaso, int *sumCostosFracaso, int *cantFracasos){
    int rLocalizar = 0, cantConsultas = 0;
    *rEvocar = 0;
    Articulo basura;

    localizarVin(l, idBuscado, &rLocalizar, typeEstructura, &cantConsultas);

    if (rLocalizar==1){
        //printArt(l->cur->vipd);
        *rEvocar = 1;
        if(lecOp == 1){
            *sumCostosExito += cantConsultas;
            (*cantExitos)++;
            if(*costoMaxExito < cantConsultas){
                *costoMaxExito = cantConsultas;
            }
        }
        return l->cur->vipd;
    } else {
        *rEvocar = 0;
        if(lecOp == 1){
            *sumCostosFracaso += cantConsultas;
            (*cantFracasos)++;
            if(*costoMaxFracaso < cantConsultas){
                *costoMaxFracaso = cantConsultas;
            }
        }
        return basura;
    }
}

#endif // VINCULADAS_H_INCLUDED
