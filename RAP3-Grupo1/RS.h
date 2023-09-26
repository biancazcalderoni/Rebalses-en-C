#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "Articulo.h"

// OPERACIONES DE MANEJO DE LISTAS VINCULADAS
typedef struct{
    Articulo vipd;
    struct nodo *next;
} nodo;

typedef struct{
    nodo *pre;
    nodo *cur;
}no2;

typedef struct{
    nodo *acc;
} Lista;

void inicializarRS(Lista *rebalse){
    // uso menor a MRS en vez de menor igual mrs-1
    for (int i=0; i<MRS; i++){
         rebalse[i].acc= NULL;
    }
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

/*void copiar(Lista l, Articulo *aux){
    *aux = l.cur->vipd;
}*/

//reformular
/*
void vaciarLista(Lista *l){
    nodo *pre, *cur;
    cur = pre = l->acc;//reset(l);
    while (cur != NULL){
        if (cur->next != NULL){
            avanzar(l);//ponerlo
            free(pre);
        } else {
            free(cur);
        }
    }
    l->acc = NULL;
}*/

void vaciarRebalseSep(Lista *rebalse){
    nodo *pre, *cur;
    for (int i=0; i<MRS; i++){
        cur = pre = rebalse[i].acc;//reset(l);
        while (cur != NULL){
            if (cur->next != NULL){
                //avanzar(l);
                pre = cur;
                cur = cur->next;
                free(pre);
            } else {
                free(cur);
                cur = NULL;
            }
        }
        rebalse[i].acc = NULL;
    }
}

void mostrarRS(Lista *rebalse){
    nodo *cur, *pre;
    for (int i=0; i<MRS; i++){
        cur = pre = rebalse[i].acc;
        printf("\n Posicion [%d]\n",i);
        if(rebalse[i].acc != NULL){
            while (cur!=NULL){
                printArt(cur->vipd);
                pre = cur;
                cur = cur->next;
            }
        }else {
            printf("Sin elementos.\n");
        }
    }
}

no2 localizarRS(Lista *rebalse, char *idBuscado, int *pos, int *rLocalizar, int *cantConsultas){
    //Función strcmpi (No usamos strcmp porque es CaseSensitive)
    //0 si a = b
    //<0 si a < b
    //>0 si a > b
    no2 nodos;
    *pos = hashing(idBuscado, MRS);
    nodos.cur = nodos.pre = rebalse[*pos].acc;
    *rLocalizar = 0;

    if (rebalse[*pos].acc != NULL){
        //(*cantConsultas)++; //por haber consultado el acceso
        while ((nodos.cur != NULL) && strcmpi(((nodos.cur->vipd).codigo), idBuscado)!=0){
            nodos.pre = nodos.cur;
            nodos.cur = nodos.cur->next;
            (*cantConsultas)++;
        }

        if (nodos.cur == NULL){
            *rLocalizar = 0; // Localizar falla
        }else if(strcmpi((nodos.cur->vipd.codigo), idBuscado)==0) {
            (*cantConsultas)++;
            *rLocalizar = 1; //Localizar exitoso
            //printArt(cur->vipd);
            //printArt(pre->vipd);
        }
        return nodos;
    } else {
        (*cantConsultas)++; //por haber consultado el acceso
        *rLocalizar = 2; //No hay elementos en la lista
        return nodos;
    }

}
// revisar alta y tema de pre y cur
void altaRS(Lista *rebalse, int *rAlta, Articulo art){
    int rLocalizar = 0, intBasuraInt = 0, pos = 0;
    *rAlta = 0;

    localizarRS(rebalse, art.codigo, &pos, &rLocalizar, &intBasuraInt);

    if (rLocalizar == 1){
        *rAlta = 0; //Como se encontró el elemento entonces el alta falla
    } else {
        nodo *n = (nodo*)malloc(sizeof(nodo));
        if (n != NULL){
            n->vipd = art;
            n->next = rebalse[pos].acc;
            rebalse[pos].acc = n;
            *rAlta = 1; // exito en el alta

        } else {
            *rAlta = 2; //El alta falla porque no hay más espacio en la estructura
        }
    }
}

void bajaRS(Lista *rebalse, int *rBaja, Articulo art, int lecOp){
    int rLocalizar = 0, eleccion = 0, intBasuraInt = 0, pos = 0;
    nodo *temp;
    no2 nodos;
    *rBaja = 0;

    nodos = localizarRS(rebalse, art.codigo, &pos, &rLocalizar, &intBasuraInt);

    if(rLocalizar == 1){

        if(lecOp == 0){
            printf("El articulo que quiere borrar es: \n");
            printArt(nodos.cur->vipd);

            do{
                printf("\n\n Esta seguro que quiere borrarlo? \n"
                       "<1> -------- Si --------\n"
                       "<2> -------- No --------\n");
                scanf("%d", &eleccion);
                getchar();
            } while (eleccion < 1 || eleccion > 2);
        } else {
            if (nodos.cur->vipd.cantidad == art.cantidad && strcmpi(nodos.cur->vipd.desc,art.desc)==0 && strcmpi(nodos.cur->vipd.marca,art.marca)==0 && nodos.cur->vipd.precio==art.precio && strcmpi(nodos.cur->vipd.tipoArt,art.tipoArt)==0){
                eleccion = 1;
            }
        }

        if (eleccion == 1){
            if(rebalse[pos].acc->next==NULL){ //1ra, unica y ultima
                temp = nodos.cur;
                rebalse[pos].acc = NULL;
                free(temp);
                *rBaja = 1;

            } else if (nodos.cur == nodos.pre){ //eliminamos la 1ra, con siguiente
                temp = rebalse[pos].acc;
                rebalse[pos].acc = rebalse[pos].acc->next;
                free(temp);
                *rBaja = 1;
            } else {
                temp = nodos.cur;
                nodos.pre->next = nodos.cur->next;
                free(temp);
                *rBaja = 1;
            }
        }
    } else {
        *rBaja = 0; //Baja fallida
    }
}

Articulo evocarRS(Lista *rebalse, int *rEvocar, char *idBuscado, int lecOp, int *costoMaxExito, int *sumCostosExito, int *cantExitos, int *costoMaxFracaso, int *sumCostosFracaso, int *cantFracasos){
    int rLocalizar = 0, cantConsultas = 0, intBasuraInt= 0, pos = 0;
    *rEvocar = 0;
    Articulo basura;
    no2 nodos;

    nodos = localizarRS(rebalse, idBuscado, &pos, &rLocalizar, &cantConsultas);
    //printArt(pre.vipd);
    //printArt(cur.vipd);
    //printArt(rebalse[pos].acc->vipd);

    if (rLocalizar==1){
        //printArt(l->cur->vipd);
        if(lecOp == 1){
            *sumCostosExito += cantConsultas;
            (*cantExitos)++;
            if(*costoMaxExito < cantConsultas){
                *costoMaxExito = cantConsultas;
            }
        }
        *rEvocar = 1;
        return nodos.cur->vipd;
    } else {
        if(lecOp == 1){
            *sumCostosFracaso += cantConsultas;
            (*cantFracasos)++;
            if(*costoMaxFracaso < cantConsultas){
                *costoMaxFracaso = cantConsultas;
            }
        }
        *rEvocar = 0;
        return basura;
    }
}

#endif // RS_H_INCLUDED
