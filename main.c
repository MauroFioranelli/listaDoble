#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 30
#define INICIAL 0

typedef struct fecha {
    int dia;
    int mes;
    int anio;
} tfecha;

typedef struct doble {
    int cod;
    char nyp[MAX];
    tfecha nacimiento;
    float horas;
    float pago_por_hora;
    struct doble *sig;
    struct doble *ant;
} tdoble;

typedef struct cabeza {
    tdoble *pri;
    tdoble *ult;
} tcab;

/// modificar , eliminar nodo , destruir

void inicializar_doble(tcab *cab);
void genera_mayuscula(char nombre[]);
void carga_datos(tdoble *nuevo);
tdoble *genera_nodo();
void genera_doble(tcab *cab);
float calcular_sueldo(float horas, float pago);
void mostrar_datos(tdoble *aux);
void imprime_doble(tcab cab);
void maximo_sueldo(tcab cab);
void minimo_sueldo(tcab cab);
void sueldo_promedio(tcab cab);
int buscar_empleado(tcab cab, int referencia);
void modificar_horas(tcab cab);
void eliminar_vendedor(tcab cab);

int main() {
    tcab cab;
    inicializar_doble(&cab);
    genera_doble(&cab);
    genera_doble(&cab);
    //genera_doble(&cab);
    //genera_doble(&cab);
    imprime_doble(cab);
    //maximo_sueldo(cab);
    //minimo_sueldo(cab);
    //sueldo_promedio(cab);
    //modificar_horas(cab);
    eliminar_vendedor(cab);           ///FALLA CUANDO NO LO ENCUENTRA
    imprime_doble(cab);
    return 0;
}

void inicializar_doble(tcab *cab) {
    cab->pri = NULL;
    cab->ult = NULL;
}

void genera_mayuscula(char nombre[]) {
    nombre[INICIAL] = toupper(nombre[INICIAL]);
    int i;
    for(i=0; i<strlen(nombre); i++) {
        if(nombre[i] == 32 && (nombre[i+1]>96 && nombre[i+1]<123)) {
            nombre[i+1] = toupper(nombre[i+1]);
        }
    }
}

void carga_datos(tdoble *nuevo) {
    printf("Ingrese codigo del vendedor: ");
    fflush(stdin);
    scanf("%d",&nuevo->cod);
    printf("Ingrese nombre y apellido del vendedor: ");
    fflush(stdin);
    gets(nuevo->nyp);
    genera_mayuscula(nuevo->nyp);
    printf("Ingrese dia mes anio de nacimiento (separados por espacios en comun): ");
    fflush(stdin);
    scanf("%d%d%d",&nuevo->nacimiento.dia,&nuevo->nacimiento.mes,&nuevo->nacimiento.anio);
    printf("Ingrese cantidad de horas trabajadas: ");
    fflush(stdin);
    scanf("%f",&nuevo->horas);
    printf("Ingrese pago por hora trabajada: ");
    fflush(stdin);
    scanf("%f",&nuevo->pago_por_hora);
}

tdoble *genera_nodo() {
    tdoble *nuevo = malloc(sizeof(tdoble));
    carga_datos(nuevo);
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    return nuevo;
}

void genera_doble(tcab *cab) {
    tdoble *nuevo;
    nuevo = genera_nodo();

    if(cab->pri == NULL) {
        cab->pri = nuevo;
        cab->ult = nuevo;
    } else if(nuevo->cod<cab->pri->cod) {
        nuevo->sig = cab->pri;
        nuevo->sig->ant = nuevo;
        cab->pri = nuevo;
    } else if(nuevo->cod > cab->ult->cod) {
        nuevo->ant = cab->ult;
        nuevo->ant->sig = nuevo;
        cab->ult = nuevo;
    } else {
        tdoble *aux = cab->pri->sig;
        while(nuevo->cod > aux->cod)
            aux = aux->sig;
        nuevo->sig = aux;
        nuevo->ant = aux->ant;
        aux->ant->sig = nuevo;
        aux->ant = nuevo;
    }
}

float calcular_sueldo(float horas, float pago) {
    float sueldo = horas * pago;
    return sueldo;
}

void mostrar_datos(tdoble *aux) {
    puts("----------------------------");
    printf("Codigo: %d",aux->cod);
    printf("\nNombre: %s",aux->nyp);
    printf("\nFecha de nacimiento: %d/%d/%d",aux->nacimiento.dia,aux->nacimiento.mes,aux->nacimiento.anio);
    printf("\nHoras trabajadas: %g",aux->horas);
    printf("\nMonto a pagar por hora: %g",aux->pago_por_hora);
    printf("\nSaldo a abonar: $%g",calcular_sueldo(aux->horas,aux->pago_por_hora));
    puts("\n----------------------------");
}

void imprime_doble(tcab cab) {
    tdoble *aux = cab.pri;
    if(aux == NULL) {
        puts("No hay trabajadores ingresados!!!");
        system("pause");
    } else {
        while(aux!=NULL) {
            mostrar_datos(aux);
            aux = aux->sig;
        }
    }
}

void maximo_sueldo(tcab cab) {
    if(cab.pri == NULL) {
        puts("No hay trabajadores ingresados!!!");
        system("pause");
    } else {
        tdoble *aux = cab.pri->sig, *maximo = cab.pri;
        float max = 0, sueldo = 0;
        while(aux!=NULL) {
            sueldo = calcular_sueldo(aux->horas,aux->pago_por_hora);
            if(sueldo  > max) {
                maximo = aux;
                max = sueldo;
            }
            sueldo = 0;
            aux = aux->sig;
        }
        printf("El Empleado con el sueldo maximo es : \n");
        mostrar_datos(maximo);
    }
}

void minimo_sueldo(tcab cab) {
    if(cab.pri == NULL) {
        puts("No hay trabajadores ingresados!!!");
        system("pause");
    } else {
        tdoble *aux = cab.pri->sig, *minimo = cab.pri;
        float sueldo, min = calcular_sueldo(cab.pri->horas,cab.pri->pago_por_hora);
        while(aux!=NULL) {
            sueldo = calcular_sueldo(aux->horas,aux->pago_por_hora);
            if(sueldo < min) {
                min = sueldo;
                minimo = aux;
            }
            sueldo = 0;
            aux = aux->sig;
        }
        printf("El Empleado con el sueldo menor es : \n");
        mostrar_datos(minimo);
    }
}

void sueldo_promedio(tcab cab) {
    float suma=0;
    int cont = 0;
    tdoble *aux = cab.pri;
    if(aux == NULL) {
        puts("No hay trabajadores ingresados!!!");
        system("pause");
    } else {
        while(aux!=NULL) {
            suma += calcular_sueldo(aux->horas,aux->pago_por_hora);
            cont++;
            aux = aux->sig;
        }
        printf("El promedio de sueldos de los %d empleado es: %g",cont,(suma/cont));

    }
}

int buscar_empleado(tcab cab, int referencia) {
    tdoble *aux = cab.pri;
    while((aux != NULL) && (aux->cod != referencia)) {
        aux = aux->sig;
    }
    if(aux == NULL)
        return 0;
    else
        return 1;
}

void modificar_horas(tcab cab) {
    if(cab.pri == NULL) {
        puts("No hay trabajadores ingresados!!!");
        system("pause");
    } else {
        int referencia;
        printf("Introduzca en codigo del vendedor a modificar cantidad de horas: ");
        fflush(stdin);
        scanf("%d",&referencia);

        if(buscar_empleado(cab,referencia)) {
            tdoble *aux = cab.pri;
            while(aux->cod != referencia)
                aux = aux->sig;
            printf("Vendedor encontrado: \n");
            mostrar_datos(aux);
            printf("Ingrese la nueva cantidad de horas trabajadas: ");
            fflush(stdin);
            scanf("%f",&aux->horas);
            puts("Modificacion realizada correctamente!!!");
            system("pause");
        } else {
            puts("Trabajador no encontrado!!!");
            system("pause");
        }
    }
}

void eliminar_vendedor(tcab cab) {
    tdoble *aux = cab.pri;
    if(aux == NULL) {
        puts("No hay trabajadores ingresados!!!");
        system("pause");
    } else {
        int ref;
        printf("Ingrese el codigo del vendedor a eliminar: ");
        fflush(stdin);
        scanf("%d",&ref);
        if(buscar_empleado(cab,ref)==1) {

            while(aux->cod != ref)
                aux = aux->sig;
            if(cab.pri == cab.ult){
                cab.pri = NULL;
                cab.ult = NULL;
            } else if(ref == cab.pri->cod) {
                cab.pri = aux->sig;
                cab.pri->ant = NULL;
            } else if(ref == cab.ult->cod) {
                cab.ult = aux->ant;
                cab.ult->sig = NULL;
            } else {
                aux->sig->ant = aux->ant;
                aux->ant->sig = aux->sig;
            }
            free(aux);
            puts("Vendedor eliminado correctamente!");
            system("pause");
        } else {
            puts("Trabajador no encontrado!!!");
            system("pause");
        }
    }
}

