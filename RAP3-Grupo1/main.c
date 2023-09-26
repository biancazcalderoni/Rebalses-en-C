#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "RAL.h"
#include "RAC.h"
#include "RS.h"
/*
    GRUPO 1 - Santiago Politti Gil y Bianca Zoé Calderoni Alvarez

    En esta ocación estamos trabajando con RAL, RAC y RS. En todas las estructuras lo único que estamos analizando son
    los costos de las EVOCACIONES. Esto se debe a que tanto las ALTAS como las BAJAS tienen un costo constante.

    Desde el principio podemos ver que son estructuras especializadas en darse cuenta rápido si un elemento está o no
    presente en la estructura, pero la eficiencia de la misma se ve reducida mientras más elementos tengamos dentro de
    nuestra estructura.

    En cuanto a las EVOCACIONES EXITOSAS podemos deducir por el funcionamiento de las estructuras, que a medida que
    crece la cantidad de elementos que tenemos almacenados en nuestra estructura, más colisiones se producen y hacen que
    encontrar un elemento sea (o no) cada vez más costoso.

    Consideremos ahora las EVOCACIONES NO EXITOSAS, nos encontramos en la misma situación, a medida que crece la
    cantidad de elementos presentes en la estructura, las colisiones aumentan y los costos suben.

    Ahora veamos los costos luego de realizar la ejecución correspondiente al archivo de "Operaciones.txt"

        Resultados archivo de operaciones:
                        *******************************************************************
                        *                     Comparacion de Estructuras                  *
                        *******************************************************************
                        *   Costos                RAL       RAC        RS                 *
                        *   ------------------------------------------------------------- *
                        *   MAX. EVOC. EX.        2         2          2                  *
                        *   MED. EVOC. EX.        1.06      1.05       1.09               *
                        *   MAX. EVOC. NO EX.     4         4          1                  *
                        *   MED. EVOC. NO EX.     2.22      2.22       1.00               *
                        *                                                                 *
                        *******************************************************************

    Analizando un poco todo lo mencionado anteriormente junto con los costos a posteriori podemos ver lo siguiente:

    En este caso, pudimos analizar que por el cálculo del Hashing en este archivo particular, nunca se producuen más de 2
    colisiones, pero en el caso de encontrarnos con una carga de datos con más elementos y que produzca más colisiones,
    veríamos que el costo máximo en el RAL sería dar una vuelta completa consultando los M elementos. En el RAC podemos
    reducir las colisiones mediante el paso, haciendo que en una carga muy grande se produzca una diferencia notable con
    el RAL. Finalmente el RS solo va a colisionar cuando el Hashing lo determine y las listas nunca se cruzan como pasa
    en los otros rebalses, produciendo que en grandes cargas con elevada cantidad de colisiones, solo tenga que analizar
    todos los elementos que contengan el mismo Hashing hasta encontrarlo.

    Nosotros calculamos el espacio para cada estructura de más o menos 350 elementos para que sea eficiente, pero, ya que
    el lote de pruebas tiene hasta 60 artículos, las estructuras no tienen una diferencia tan notable en eficiencia.

    EVOCACIÓN EXITOSA: La diferencia entre las distintas estructuras se produce en el orden que se inserten los elementos
    y las distintas colisiones que estos pruduzcan. Como este lote tiene colisiones extremadamente reducidas, casi no
    podemos notar una diferencia entre las distintas estructuras. Sin embargo, el RAL, si al insertar elementos con
    distintos valores de hashing pero que las insersiones produzcan muchas colisiones, podríamos ver como los costos de
    una evocación exitosa aumentan en gran medida. En cambio, en el RAC, para el mismo caso de insersiones podríamos ver
    muchas menos colisiones debido a que las listas que empiezan en las posiciones determinadas por el hashing no
    recorren todos los elementos. Por último para el RS, dadas distintas insersiones, solo van a colisionar las que
    tengan exactamente el mismo valor del Hashing, y no elementos que deberían pertenecer a otras listas. Esto hace que
    las colisiones sean menores en casos de elevadas cantidades de elementos, y por ende, a la larga sea más conviniente
    para hacer localizaciones exitosas.

    EVOCACIÓN NO EXITOSA: La estructura más óptima en este caso siempre va a ser el RS, debido a que las colisiones
    siempre van a estar contenidas en la misma posición del arreglo, y no es necesario analizar elementos que no deberían
    ser analizados ya que su Hashing es distinto. En cambio, en el RAL, en un caso en el que hubiesen colisionados muchos
    elementos con distintos Hashing, la busqueda hubiese tenido que recorrer muchos más elementos hasta encontrar una
    celda virgen y ver que fracasa. Eventualmente si no encuentra una celda virgen, el costo se vuelve muy alto ya que
    debe consultar todos los elementos de la estructura. Por último, en el RAC, vemos que lo que pasa en la estructura
    cuando hay muchas colisiones, es muy similar a lo que pasa en el RAL, con la diferencia de que las colisiones se ven
    reducidas por el paso, ya que hace que las listas que empiezan en determinados elementos no colisionen tanto con
    otras listas.

    En conclusión: El RS es el más óptimo para casos en donde esperemos una carga muy grande con muchas colisiones, pero,
    en casos particulares como el del lote que estamos trabajando actualmente, no es tan notoria la diferencia entre las
    estructuras o bien, es mínima (debido a la baja cantidad de colisiones que genera este lote de Artículos). Por otro
    lado, el RS al ser desordenado nos proporciona su costo máximo solo cuando debemos buscar el último elemento en una
    de sus listas o, en el caso de la evocación no exitosa, tiene que recorrer toda la lista para saber que no se encuentra.


*/
void toMayus(char *idBuscado){
    int cantLetras;
    cantLetras = strlen(idBuscado);

    for(int i=0; i<cantLetras; i++){
        if(idBuscado[i] >= 'a' && idBuscado[i] <= 'z'){
            idBuscado[i] = idBuscado[i] - 32;
        }
    }
}


int main(){

        int typeEstructura = 0, decision = 0, codOperador=0, opciones = 0, cargadosRAL = 0, cargadosRAC = 0, cargadosRS = 0, rAlta = 0, rBaja = 0, rEvocar = 0, intBasura = 0;
        float floatBasura = 0;
        char codigoAux[9], tipoArtAux[21], marcaAux[31], descAux[101];
        Articulo aux, arregloRAL[MRAL], arregloRAC[MRAC];
        Lista arregloRS[MRS];
        inicializarRAL(arregloRAL, &cargadosRAL);
        inicializarRAC(arregloRAC, &cargadosRAC);
        inicializarRS(&arregloRS);

        //Le avisamos al usuario que puede salir en cualquier momento con 0
        printf("------------------------- ATENCION -------------------------\n"
               "En cualquier etapa del programa puede ingresar '0' para salir\n");
               system("pause");
               system("cls");

        do{
            do {
                printf("\n*****************************************************************************\n"
                       "*                               Opciones                                    *\n"
                       "*****************************************************************************\n"
                       "*                                                                           *\n"
                       "*   <0> Salir                                                               *\n"
                       "*   <1> Administrar Estructuras                                             *\n"
                       "*   <2> Comparar Estructuras                                                *\n"
                       "*                                                                           *\n"
                       "*****************************************************************************\n\n");
                scanf("%d", &opciones);
                getchar();
                system("cls");
            }while (opciones<0 || opciones >2);

            switch(opciones){
                case 0:{
                    break;
                }
                case 1:{
                     do{
                        do{
                            printf("\n*****************************************************************************\n"
                                   "*                      Con que estructura desea trabajar?                   *\n"
                                   "*****************************************************************************\n"
                                   "*                                                                           *\n"
                                   "*   <0> Salir                                                               *\n"
                                   "*   <1> Rebalse Abierto Lineal                                              *\n"
                                   "*   <2> Rebalse Abierto Cuadratico                                          *\n"
                                   "*   <3> Rebalse Separado                                                    *\n"
                                   "*                                                                           *\n"
                                   "*****************************************************************************\n\n");
                            scanf("%d", &typeEstructura);
                            getchar();
                            system("cls");
                        } while (typeEstructura<0 || typeEstructura>3);

                        switch(typeEstructura){
                             default:{
                                 do {
                                    do {
                                        if(typeEstructura == 1){
                                            printf("\n~~~~~~~~ Usted esta trabajando con la RAL ~~~~~~~~\n\n");
                                        } else if (typeEstructura == 2){
                                            printf("\n~~~~~~~~ Usted esta trabajando con la RAC ~~~~~~~~\n\n");
                                        } else if (typeEstructura == 3){
                                            printf("\n~~~~~~~~ Usted esta trabajando con la RS ~~~~~~~~\n\n");
                                        }
                                        printf("\n*************************************************************************\n"
                                               "*                           Que desea hacer?                            *\n"
                                               "*************************************************************************\n"
                                               "*                                                                       *\n"
                                               "*   <0> Salir                                                           *\n"
                                               "*   <1> Ingresar nuevo articulo                                         *\n"
                                               "*   <2> Eliminar articulo existente                                     *\n"
                                               "*   <3> Consultar un articulo                                           *\n"
                                               "*   <4> Mostrar estructura                                              *\n"
                                               "*   <5> Memorizacion previa                                             *\n"
                                               "*                                                                       *\n"
                                               "*************************************************************************\n\n");
                                        scanf("%d", &decision);
                                        getchar();
                                        system("cls");
                                    } while (decision<0 || decision>5);

                                    switch(decision){
                                        case 0:{
                                            break;
                                        }
                                        case 1:{
                                            //Pedir datos y meter en aux
                                            printf("\n ---------------------------------------------------------- \n");
                                            printf("Ingrese el codigo del articulo: \n");
                                            scanf("%[^\n]s", codigoAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(codigoAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }
                                            //Lo volvemos todo mayúsculas antes de darlo de alta
                                            toMayus(codigoAux);

                                            strcpy(aux.codigo,codigoAux);

                                            printf("Ingrese el tipo de articulo: \n");
                                            scanf("%[^\n]s", tipoArtAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(tipoArtAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.tipoArt,tipoArtAux);

                                            printf("Ingrese la marca: \n");
                                            scanf("%[^\n]s", marcaAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(marcaAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.marca,marcaAux);

                                            printf("Ingrese la descripcion del articulo: \n");
                                            scanf("%[^\n]s", descAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(descAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            strcpy(aux.desc,descAux);

                                            do{
                                                printf("Ingrese el precio del producto (No puede ser 0 ni menor): \n");
                                                scanf("%lf",&aux.precio);
                                            } while(aux.precio<0);

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (aux.precio == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            do{
                                                printf("Ingrese la cantidad de stock (No puede ser 0 ni menor) : \n");
                                                scanf("%d",&aux.cantidad);
                                            } while(aux.cantidad<0);

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (aux.cantidad == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }
                                            switch(typeEstructura){
                                                case 1:{
                                                    altaRAL(arregloRAL, &cargadosRAL, &rAlta, aux);
                                                    break;
                                                }
                                                case 2:{
                                                    altaRAC(arregloRAC, &cargadosRAC, &rAlta, aux);
                                                    break;
                                                }
                                                case 3:{
                                                    altaRS(&arregloRS, &rAlta, aux);
                                                    break;
                                                }
                                            }

                                            if(rAlta == 1){
                                                printf("\n El alta ha sido exitosa \n");
                                            } else if (rAlta == 0){
                                                printf("\n El alta ha fallado porque el elemento ya se encuenta en la estructura \n");
                                            } else if (rAlta == 2){
                                                printf("\n El alta ha fallado porque no hay espacio en la estructura \n");
                                            } else {
                                                printf("\n El alta ha fallado porque no hay espacio para este elemento en particular \n");
                                            }

                                            break;

                                        }
                                        case 2:{
                                            //Eliminar
                                            printf("\n ---------------------------------------------------------- \n");
                                            printf("Ingrese el codigo del articulo a eliminar: \n");
                                            scanf("%[^\n]s", codigoAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(codigoAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            //Lo hacemos mayúscula antes de copiar
                                            toMayus(codigoAux);

                                            strcpy(aux.codigo,codigoAux);
                                            //Pedimos solo el código pero lo metemos en un Artículo Aux

                                            switch(typeEstructura){
                                                case 1:{
                                                    bajaRAL(arregloRAL, &cargadosRAL, &rBaja, aux, 0);
                                                    break;
                                                }
                                                case 2:{
                                                    bajaRAC(arregloRAC, &cargadosRAC, &rBaja, aux, 0);
                                                    break;
                                                }
                                                case 3:{
                                                    bajaRS(&arregloRS, &rBaja, aux, 0);
                                                    break;
                                                }
                                            }

                                            if(rBaja == 1){
                                                printf("\n La baja ha sido exitosa \n");
                                            } else if (rBaja == 0){
                                                printf("\n La baja ha fallado \n");
                                            }

                                            break;

                                        }
                                        case 3:{
                                            //Consultar
                                            printf("\n ---------------------------------------------------------- \n");
                                            printf("Ingrese el codigo del articulo a consultar: \n");
                                            scanf("%[^\n]s", codigoAux);
                                            getchar();

                                            // Si el usuario ingresa 0 sale de la ejecución
                                            if (strcmp(codigoAux, "0") == 0){
                                                printf("Se ha cancelado el alta ya que ha escrito '0' \n");
                                                break;
                                            }

                                            //Lo hacemos mayúscula antes de consultar
                                            toMayus(codigoAux);

                                            switch(typeEstructura){
                                                case 1:{
                                                    aux = evocarRAL(arregloRAL, codigoAux, cargadosRAL, &rEvocar, 0, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura);
                                                    if(rEvocar == 1){
                                                        printf("Se econtro el articulo y es:\n");
                                                        printArt(aux);
                                                    } else {
                                                        printf("No se encontro el articulo\n");
                                                    }
                                                    break;
                                                }
                                                case 2:{
                                                    aux = evocarRAC(arregloRAC, codigoAux, cargadosRAC, &rEvocar, 0, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura);
                                                    if(rEvocar == 1){
                                                        printf("Se econtro el articulo y es:\n");
                                                        printArt(aux);
                                                    } else {
                                                        printf("No se encontro el articulo\n");
                                                    }
                                                    break;
                                                }
                                                case 3:{
                                                    aux = evocarRS(&arregloRS, &rEvocar, codigoAux, 0, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura, &intBasura);
                                                    if(rEvocar == 1){
                                                        printf("Se econtro el articulo y es:\n");
                                                        printArt(aux);
                                                    } else {
                                                        printf("No se encontro el articulo\n");
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                        case 4:{
                                            switch (typeEstructura){
                                                case 1:{

                                                    //MOSTRAR ESTRUCTURA RAL
                                                    if(cargadosRAL == 0){
                                                        printf("No se encuentran elementos cargados \n\n");
                                                    } else {
                                                        for(int i = 0; i < MRAL; i++){

                                                            if(i%15 == 0){
                                                               system("pause");
                                                            }

                                                            if(strcmpi(arregloRAL[i].codigo, "*") != 0 && strcmpi(arregloRAL[i].codigo, "+")){
                                                                printf("\n[%d] Articulo:", i);
                                                                printArt(arregloRAL[i]);
                                                                printf("\n");
                                                            } else {
                                                                if(strcmpi(arregloRAL[i].codigo, "*") == 0){
                                                                    printf("[%d] %s (Celda Virgen)\n", i , arregloRAL[i].codigo);
                                                                } else {
                                                                    printf("[%d] %s (Celda Libre)\n", i , arregloRAL[i].codigo);
                                                                }

                                                            }
                                                        }

                                                    }
                                                    break;
                                                }
                                                case 2:{

                                                    //MOSTRAR ESTRUCTURA RAC
                                                    if (cargadosRAC == 0){
                                                        printf("No se encuentran elementos cargados \n\n");
                                                    } else {
                                                        for(int i = 0; i < MRAC; i++){

                                                            if(i%15 == 0){
                                                               system("pause");
                                                            }

                                                            if(strcmpi(arregloRAC[i].codigo, "*") != 0 && strcmpi(arregloRAC[i].codigo, "+")){
                                                                printf("\n[%d] Articulo:", i);
                                                                printArt(arregloRAC[i]);
                                                                printf("\n");
                                                            } else {
                                                                if(strcmpi(arregloRAC[i].codigo, "*") == 0){
                                                                    printf("[%d] %s (Celda Virgen)\n", i , arregloRAC[i].codigo);
                                                                } else {
                                                                    printf("[%d] %s (Celda Libre)\n", i , arregloRAC[i].codigo);
                                                                }
                                                            }
                                                        }
                                                    }
                                                    break;

                                                }
                                                case 3: {

                                                    //MOSTRAR ESTRUCTURA RS

                                                    // ATENTOS A ESTO
                                                    // EL RS SE SUPONE QUE DEBE DECIR QUE NO TIENE ELEMENTOS EN UNA LISTA, ENTONCES SI EL ACC == NULL

                                                    mostrarRS(&arregloRS);
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                        case 5:{
                                            FILE *fp;
                                            Articulo art;
                                            if ((fp = fopen("Articulos.txt","r"))== NULL){
                                                printf("No se puedo abrir el archivo\n");
                                                return 0;
                                            }
                                            if (ferror(fp)!=0) printf("Ocurrio un error en la lectura\n");
                                            else {
                                                while(!(feof(fp))){
                                                    fgets(art.codigo,10,fp);
                                                    art.codigo[strlen(art.codigo)-1] = '\0';
                                                    fgets(art.tipoArt,21,fp);
                                                    art.tipoArt[strlen(art.tipoArt)-1] = '\0';
                                                    fgets(art.marca,31,fp);
                                                    art.marca[strlen(art.marca)-1] = '\0';
                                                    fgets(art.desc,101,fp);
                                                    art.desc[strlen(art.desc)-1] = '\0';
                                                    fscanf(fp,"%lf",&art.precio);
                                                    fgetc(fp);
                                                    fscanf(fp,"%d",&art.cantidad);
                                                    fgetc(fp);

                                                    toMayus(art.codigo);

                                                    switch (typeEstructura){
                                                        case 1:{
                                                            altaRAL(arregloRAL, &cargadosRAL, &rAlta, art);
                                                            break;
                                                        }
                                                        case 2:{
                                                            altaRAC(arregloRAC, &cargadosRAC, &rAlta, art);
                                                            break;
                                                        }
                                                        case 3:{
                                                            altaRS(&arregloRS, &rAlta, art);
                                                            break;
                                                        }
                                                    }
                                                }

                                                printf("Se cargaron correctamente todos los articulos \n\n");
                                            fclose(fp);
                                            }
                                            break;
                                        }
                                    }
                                 } while (decision != 0);
                                 break;
                            }
                            case 0:{
                                break;
                            }
                        }
                     } while (typeEstructura != 0);
                     break;
                }
                case 2:{

                // LIMPIAR ESTRUCTURAS
                inicializarRAL(arregloRAL, &cargadosRAL);
                inicializarRAC(arregloRAC, &cargadosRAC);
                inicializarRS(&arregloRS);

                //costos EvocarRAL Exito
                float costoMedioEvoExitoRAL=0;
                int costoMaxEvoExitoRAL=0, sumCostosEvoExitoRAL=0, cantExitosEvoRAL=0;

                //costos EvocarRAL Fracaso
                float costoMedioEvoFracasoRAL=0;
                int costoMaxEvoFracasoRAL=0, sumCostosEvoFracasoRAL=0, cantFracasosEvoRAL=0;

                //costos EvocarRAC Exito
                float costoMedioEvoExitoRAC=0;
                int costoMaxEvoExitoRAC=0, sumCostosEvoExitoRAC=0, cantExitosEvoRAC=0;

                //costos EvocarRAC Fracaso
                float costoMedioEvoFracasoRAC=0;
                int costoMaxEvoFracasoRAC=0, sumCostosEvoFracasoRAC=0, cantFracasosEvoRAC=0;

                //costos EvocarRS Exito
                float costoMedioEvoExitoRS=0;
                int costoMaxEvoExitoRS=0, sumCostosEvoExitoRS=0, cantExitosEvoRS=0;

                //costos EvocarRS Fracaso
                float costoMedioEvoFracasoRS=0;
                int costoMaxEvoFracasoRS=0, sumCostosEvoFracasoRS=0, cantFracasosEvoRS=0;


                                FILE *fp;
                                Articulo art;
                                if ((fp = fopen("Operaciones.txt","r"))== NULL){
                                    printf("No se puedo abrir el archivo\n");
                                    return 0;
                                }

                                if (ferror(fp)!=0) printf("Ocurrio un error en la lectura\n");
                                    else {
                                        while(!(feof(fp))){
                                            fscanf(fp, "%d", &codOperador);
                                            fgetc(fp);
                                            fscanf(fp, "%[^\n]", &art.codigo);
                                            fgetc(fp);

                                            toMayus(art.codigo);

                                            if(codOperador == 1 || codOperador == 2){
                                                fgets(art.tipoArt,21,fp);
                                                art.tipoArt[strlen(art.tipoArt)-1] = '\0';
                                                fgets(art.marca,31,fp);
                                                art.marca[strlen(art.marca)-1] = '\0';
                                                fgets(art.desc,101,fp);
                                                art.desc[strlen(art.desc)-1] = '\0';
                                                fscanf(fp,"%lf",&art.precio);
                                                fgetc(fp);
                                                fscanf(fp,"%d",&art.cantidad);
                                                fgetc(fp);

                                                if(codOperador == 1){
                                                    altaRAL(arregloRAL, &cargadosRAL, &rAlta, art);
                                                    altaRAC(arregloRAC, &cargadosRAC, &rAlta, art);
                                                    altaRS(&arregloRS, &rAlta, art);

                                                } else if (codOperador == 2){
                                                    bajaRAL(arregloRAL, &cargadosRAL, &rBaja, art, 1);
                                                    bajaRAC(arregloRAC, &cargadosRAC, &rBaja, art, 1);
                                                    bajaRS(&arregloRS, &rBaja, art, 1);
                                                }

                                            }else if (codOperador == 3){
                                                evocarRAL(arregloRAL, art.codigo, cargadosRAL, &rEvocar, 1, &costoMaxEvoExitoRAL, &sumCostosEvoExitoRAL, &cantExitosEvoRAL, &costoMaxEvoFracasoRAL, &sumCostosEvoFracasoRAL, &cantFracasosEvoRAL);
                                                evocarRAC(arregloRAC, art.codigo, cargadosRAC, &rEvocar, 1, &costoMaxEvoExitoRAC, &sumCostosEvoExitoRAC, &cantExitosEvoRAC, &costoMaxEvoFracasoRAC, &sumCostosEvoFracasoRAC, &cantFracasosEvoRAC);
                                                evocarRS(&arregloRS, &rEvocar, art.codigo, 1, &costoMaxEvoExitoRS, &sumCostosEvoExitoRS, &cantExitosEvoRS, &costoMaxEvoFracasoRS, &sumCostosEvoFracasoRS, &cantFracasosEvoRS);
                                            } else {
                                                printf("Error, el codigo de operacion no fue reconocido\n");
                                            }

                                            codOperador = 0;

                                        }

                                        printf("Se cargaron correctamente todos los articulos \n\n");
                                    fclose(fp);
                                    }

                                    //COSTO MEDIO DE EVOCAR EXITO

                                    costoMedioEvoExitoRAL = sumCostosEvoExitoRAL *1.0 / cantExitosEvoRAL;
                                    costoMedioEvoExitoRAC = sumCostosEvoExitoRAC *1.0 / cantExitosEvoRAC;
                                    costoMedioEvoExitoRS = sumCostosEvoExitoRS *1.0 / cantExitosEvoRS;

                                    //COSTO MEDIO DE EVOCAR FRACASO

                                    costoMedioEvoFracasoRAL = sumCostosEvoFracasoRAL *1.0 / cantFracasosEvoRAL;
                                    costoMedioEvoFracasoRAC = sumCostosEvoFracasoRAC *1.0 / cantFracasosEvoRAC;
                                    costoMedioEvoFracasoRS = sumCostosEvoFracasoRS *1.0 / cantFracasosEvoRS;

                            printf("\n*******************************************************************\n"
                                   "*                     Comparacion de Estructuras                  *\n"
                                   "*******************************************************************\n"
                                   "*   Costos                RAL       RAC        RS                 *\n"
                                   "*   ------------------------------------------------------------- *\n");
                            printf("*   MAX. EVOC. EX.        %d         %d          %d                  *\n", costoMaxEvoExitoRAL, costoMaxEvoExitoRAC, costoMaxEvoExitoRS);
                            printf("*   MED. EVOC. EX.        %.2f      %.2f       %.2f               *\n", costoMedioEvoExitoRAL, costoMedioEvoExitoRAC, costoMedioEvoExitoRS);
                            printf("*   MAX. EVOC. NO EX.     %d         %d          %d                  *\n", costoMaxEvoFracasoRAL, costoMaxEvoFracasoRAC, costoMaxEvoFracasoRS);
                            printf("*   MED. EVOC. NO EX.     %.2f      %.2f       %.2f               *\n", costoMedioEvoFracasoRAL, costoMedioEvoFracasoRAC, costoMedioEvoFracasoRS);
                            printf("*                                                                 *\n"
                                   "*******************************************************************\n\n");
                    break;
                }
                break;
            }
        } while (opciones != 0);

        printf("\n      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                 "      |                                                   |\n"
                 "      |    Muchas gracias por utilizar nuestro programa   |\n"
                 "      |                                                   |\n"
                 "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return 0;
}
