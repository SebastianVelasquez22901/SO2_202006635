#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t lock;

typedef struct {
    char tipo;
    char* ruta;
} cargaDatosArgs;

#define MAX_ERRORES 100

typedef struct {
    char* erroresCargaUsuarios[MAX_ERRORES];
    int lineasCargaUsuarios[MAX_ERRORES];
    char* erroresCargaOperacionesMasivas[MAX_ERRORES];
    int lineasCargaOperacionesMasivas[MAX_ERRORES];
} Errores;



struct data_struct_u {
    int no_cuenta;
    char nombre[50];
    float saldo;
};

struct data_struct_o {
    int operacion;
    int no_cuenta1;
    int no_cuenta2;
    float monto;
};

struct data_struct_u usuarios[1000];
struct data_struct_o operaciones[1000];

int n = 0;
int o = 0;
struct data_struct_u* buscarCuenta(struct data_struct_u* arrayUsuarios, int n, int numeroCuenta) {
    for (int i = 0; i < n; i++) {
        if (arrayUsuarios[i].no_cuenta == numeroCuenta) {
            return &arrayUsuarios[i];
        }
    }
    return NULL;
}

void* cargaDatosUsuario(void* arg) 
{ 
    //wait
    cargaDatosArgs* args = (cargaDatosArgs*) arg;
    char tipo = args->tipo;
    char* ruta = args->ruta;
    pthread_mutex_lock(&lock);
    FILE *fp;
    fp = fopen(ruta, "r");

    if (tipo == 'c') {
        printf("Cargando cuentas...\n"); 

        char row[1000];
        char *token;

        fgets(row, 1000, fp);

        n = 0;

        while (feof(fp) != true)
        {
            fgets(row, 1000, fp);
            token = strtok(row, ",");
            usuarios[n].no_cuenta = atoi(token);

            token = strtok(NULL, ",");

            token = strtok(NULL, ",");

            n++;
        }
    } else if (tipo == 'n') {
        printf("Cargando nombres...\n");

        char row[1000];
        char *token;

        fgets(row, 1000, fp);

        n = 0;

        while (feof(fp) != true)
        {
            fgets(row, 1000, fp);
            token = strtok(row, ",");

            token = strtok(NULL, ",");
            sprintf(usuarios[n].nombre, "%s", token);

            token = strtok(NULL, ",");

            n++;
        } 
    } else if (tipo == 's') {
        printf("Cargando saldos...\n");

        char row[1000];
        char *token;

        fgets(row, 1000, fp);

        n = 0;

        while (feof(fp) != true)
        {
            fgets(row, 1000, fp);
            token = strtok(row, ",");
            
            token = strtok(NULL, ",");
            
            token = strtok(NULL, ",");
            usuarios[n].saldo = atof(token);

            n++;
        }
    }

    sleep(1); 
      
    pthread_mutex_unlock(&lock); 
}

void* cargaDatosOperaciones(void* arg) 
{ 
    //wait
    cargaDatosArgs* args = (cargaDatosArgs*) arg;
    char tipo = args->tipo;
    char* ruta = args->ruta;
    pthread_mutex_lock(&lock);
    FILE *fp;
    fp = fopen(ruta, "r");

    if (tipo == 'o') {
        printf("Cargando operaciones...\n"); 
        char row[1000];
        char *token;

        fgets(row, 1000, fp);

        o = 0;

        while (feof(fp) != true)
        {
            fgets(row, 1000, fp);

            token = strtok(row, ",");
            operaciones[o].operacion = atoi(token);

            token = strtok(NULL, ",");

            token = strtok(NULL, ",");

            token = strtok(NULL, ",");

            o++;
        }

    } else if (tipo == '1') {
        printf("Cargando cuentas...\n"); 

        char row[1000];
        char *token;

        fgets(row, 1000, fp);

        o = 0;

        while (feof(fp) != true)
        {
            fgets(row, 1000, fp);

            token = strtok(row, ",");

            token = strtok(NULL, ",");
            operaciones[o].no_cuenta1 = atoi(token);

            token = strtok(NULL, ",");

            token = strtok(NULL, ",");

            o++;
        } 
    }else if (tipo == '2') {
        printf("Cargando cuentas...\n");

        char row[1000];
        char *token;

        fgets(row, 1000, fp);

        o = 0;

        while (feof(fp) != true)
        {
            fgets(row, 1000, fp);

            token = strtok(row, ",");

            token = strtok(NULL, ",");
            

            token = strtok(NULL, ",");
            operaciones[o].no_cuenta2 = atoi(token);

            token = strtok(NULL, ",");

            o++;
        } 
    } else if (tipo == 'm') {
        printf("Cargando montos...\n");

        char row[1000];
        char *token;

        fgets(row, 1000, fp);

        o = 0;

        while (feof(fp) != true)
        {
            fgets(row, 1000, fp);

            token = strtok(row, ",");

            token = strtok(NULL, ",");
            

            token = strtok(NULL, ",");

            token = strtok(NULL, ",");
            operaciones[o].monto = atof(token);

            o++;
        } 
    } 
    sleep(1); 
      
    pthread_mutex_unlock(&lock); 
}

void reporteCuentas(){
    FILE *fp;

    // Abre el archivo en modo de escritura. Si el archivo no existe, se creará.
    // Si el archivo existe, su contenido se borrará antes de abrirlo.
    fp = fopen("usuarios.csv", "w");

    if (fp == NULL)
    {
        printf("Error al abrir el archivo!\n");
        return;
    }

    // Escribe la cabecera del CSV
    fprintf(fp, "NumeroC,Nombre,Saldo\n");

    // Itera sobre tus usuarios y escribe cada uno en el archivo
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d,%s,%f\n", usuarios[i].no_cuenta, usuarios[i].nombre, usuarios[i].saldo);
    }

    // Cierra el archivo
    fclose(fp);
    return;
}

void OperacionesCargadas() {
    for (int i = 0; i < o; i++) {
        int operacion = operaciones[i].operacion;
        int cuenta1O = operaciones[i].no_cuenta1;
        int cuenta2O = operaciones[i].no_cuenta2;
        float monto = operaciones[i].monto;

        if (operaciones[i].operacion == 1) {

            struct data_struct_u* cuenta = buscarCuenta(usuarios, n, cuenta1O);
            if (cuenta != NULL) {
                cuenta->saldo += monto;
            } else {
                printf("No se encontro la cuenta %d\n", cuenta1O);
            }
        
            
        } else if (operaciones[i].operacion == 2) {
            printf("Retiro\n");
            struct data_struct_u* cuenta = buscarCuenta(usuarios, n, cuenta1O);
            if (cuenta != NULL) {
                cuenta->saldo -= monto;
            } else {
                printf("No se encontro la cuenta %d\n", cuenta1O);
            }

        } else if (operaciones[i].operacion == 3) {
            printf("Transferencia\n");
            struct data_struct_u* cuenta1 = buscarCuenta(usuarios, n, cuenta1O);
            struct data_struct_u* cuenta2 = buscarCuenta(usuarios, n, cuenta2O);
            if (cuenta1 != NULL && cuenta2 != NULL) {
                if (cuenta1->saldo >= monto) {
                    cuenta1->saldo -= monto;
                    cuenta2->saldo += monto;
                } else {
                    printf("Saldo insuficiente en la cuenta %d\n", cuenta1->no_cuenta);
                }
            } else {
                printf("No se encontro alguna de las cuentas.\n");
            }
        }
        
    }
}

void verificarUsuarios() {
    Errores errores;
    int i, j;

    time_t t = time(NULL);
    struct tm* tm = localtime(&t);

    // Generar el nombre del archivo de log
    char nombreArchivo[64];
    strftime(nombreArchivo, sizeof(nombreArchivo), "carga_%Y_%m_%d-%H_%M_%S.log", tm);

    // Abrir el archivo de log
    FILE* logFile = fopen(nombreArchivo, "w");
    if (logFile == NULL) {
        printf("No se pudo abrir el archivo de log\n");
        return;
    }
    fprintf(logFile, "-------Carga de Usuarios-------\n");
    fprintf(logFile, "\nSe cargaron %d usuarios\n", n);

    for (i = 0; i < n; i++) {
        // Verificar si el número de cuenta es un número entero positivo
        if (usuarios[i].no_cuenta <= 0) {
            fprintf(logFile, "Línea %d: El número de cuenta no es un número entero positivo\n", i + 1);
        }

        // Verificar si el saldo es un número real positivo
        if (usuarios[i].saldo < 0) {
            fprintf(logFile, "Línea %d: El saldo no es un número real positivo\n", i + 1);
        }

        // Verificar números de cuenta duplicados
        for (j = i + 1; j < n; j++) {
            if (usuarios[i].no_cuenta == usuarios[j].no_cuenta) {
                fprintf(logFile, "Línea %d: Número de cuenta duplicado\n", i + 1);
            }
        }
    }

    // Cerrar el archivo de log
    fclose(logFile);
}

void verificarOperaciones() {
    int i, j;

    // Obtener la fecha y hora actuales
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);

    // Generar el nombre del archivo de log
    char nombreArchivo[64];
    strftime(nombreArchivo, sizeof(nombreArchivo), "operaciones_%Y_%m_%d-%H_%M_%S.log", tm);

    // Abrir el archivo de log
    FILE* logFile = fopen(nombreArchivo, "w");
    if (logFile == NULL) {
        printf("No se pudo abrir el archivo de log\n");
        return;
    }

    fprintf(logFile, "-------Reporte de Operaciones-------\n");

    for (i = 0; i < o; i++) {
        // Verificar si el número de cuenta existe
        struct data_struct_u* cuenta1 = buscarCuenta(usuarios, n, operaciones[i].no_cuenta1);
        struct data_struct_u* cuenta2 = buscarCuenta(usuarios, n, operaciones[i].no_cuenta2);
        if (cuenta1 == NULL) {
            fprintf(logFile, "Linea %d: El número de cuenta no existe\n", i + 1);
            continue;
        }
        if (cuenta2 == NULL) {
            fprintf(logFile, "Linea %d: El número de cuenta no existe\n", i + 1);
            continue;
        }

        // Verificar si el monto es un número positivo
        if (operaciones[i].monto < 0) {
            fprintf(logFile, "Linea %d: El monto no es un número positivo\n", i + 1);
            continue;
        }

        // Verificar si el identificador de la operación existe
        if (operaciones[i].operacion < 0 || operaciones[i].operacion > 3) {
            fprintf(logFile, "Linea %d: El identificador de la operación no existe\n", i + 1);
            continue;
        }

        // Verificar si la cuenta tiene saldo suficiente para la operación
        if (operaciones[i].operacion == 2 && cuenta1->saldo < operaciones[i].monto) {
            fprintf(logFile, "Operación %d: La cuenta no tiene saldo suficiente para la operación\n", i + 1);
        }
    }

    // Cerrar el archivo de log
    fclose(logFile);
}

void OperacionesI() {
    int opcion;
    do {
        printf("\nMenu:\n");
        printf("1. Deposito\n");
        printf("2. Retiro\n");
        printf("3. Transaccion\n");
        printf("4. Consultar cuenta\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        

        switch (opcion) {
            case 1:
                // Aquí va el código para realizar un depósito
                printf("Has seleccionado Deposito.\n");
                if (n == 0) {
                    printf("No hay cuentas cargadas.\n");
                } else {
                    int cuenta;
                    float monto;
                    printf("Ingrese el numero de cuenta: ");
                    scanf("%d", &cuenta);
                    printf("Ingrese el monto a depositar: ");
                    scanf("%f", &monto);
                    bool encontrado = false;
                    for (int i = 0; i < n; i++) {
                        if (usuarios[i].no_cuenta == cuenta) {
                            encontrado = true;
                            usuarios[i].saldo += monto;
                            printf("Deposito realizado con exito.\n");
                            reporteCuentas();
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("No se encontro la cuenta.\n");
                    }
                }
                break;
            case 2:
                // Aquí va el código para realizar un retiro
                printf("Has seleccionado Retiro.\n");
                if (n == 0) {
                    printf("No hay cuentas cargadas.\n");
                } else {
                    int cuenta;
                    float monto;
                    printf("Ingrese el numero de cuenta: ");
                    scanf("%d", &cuenta);
                    printf("Ingrese el monto a retirar: ");
                    scanf("%f", &monto);
                     bool encontrado = false;
                    for (int i = 0; i < n; i++) {
                        if (usuarios[i].no_cuenta == cuenta) {
                            encontrado = true;
                            if (usuarios[i].saldo >= monto) {
                                usuarios[i].saldo -= monto;
                                printf("Retiro realizado con exito.\n");
                                reporteCuentas();
                            } else {
                                printf("Saldo insuficiente.\n");
                            }
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("No se encontro la cuenta.\n");
                    }
                }
                break;
            case 3:
                // Aquí va el código para realizar una transacción
                printf("Has seleccionado Transaccion.\n");
                if (n == 0) {
                    printf("No hay cuentas cargadas.\n");
                } else {
                    int cuenta1, cuenta2;
                    float monto;
                    printf("Ingrese el numero de cuenta origen: ");
                    scanf("%d", &cuenta1);
                    printf("Ingrese el numero de cuenta destino: ");
                    scanf("%d", &cuenta2);
                    printf("Ingrese el monto a transferir: ");
                    scanf("%f", &monto);
                    bool encontrado = false;
                    for (int i = 0; i < n; i++) {
                        if (usuarios[i].no_cuenta == cuenta1) {
                           
                            encontrado = true;
                            if (usuarios[i].saldo >= monto) {
                                usuarios[i].saldo -= monto;
                                for (int j = 0; j < n; j++) {
                                    if (usuarios[j].no_cuenta == cuenta2) {
                                        usuarios[j].saldo += monto;
                                        printf("Transaccion realizada con exito.\n");
                                        reporteCuentas();
                                        break;
                                    }
                                }
                            } else {
                                printf("Saldo insuficiente.\n");
                            }
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("No se encontro la cuenta.\n");
                    }
                }
                break;
            case 4:
                // Aquí va el código para consultar una cuenta
                printf("Has seleccionado Consultar cuenta.\n");
                if (n == 0) {
                    printf("No hay cuentas cargadas.\n");
                } else {
                    int cuenta;
                    printf("Ingrese el numero de cuenta: ");
                    scanf("%d", &cuenta);
                    bool encontrado = false;
                    for (int i = 0; i < n; i++) {
                        if (usuarios[i].no_cuenta == cuenta) {
                            encontrado = true;
                            printf("NoCuenta: %d   Nombre: %s   Saldo: %.2f\n", 
                                usuarios[i].no_cuenta, usuarios[i].nombre, usuarios[i].saldo);
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("No se encontro la cuenta.\n");
                    }
                }
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }
    } while (opcion != 0);
}

int main(){

    char ruta[1000];  

    int opcion;

    do {
        printf("Menu:\n");
        printf("1. Carga de usuarios\n");
        printf("2. Carga de operaciones\n");
        printf("3. Operaciones individuales\n");
        printf("0. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
                case 1:
                    printf("Has elegido la opcion de carga de usuarios.\n");
                    //printf("Por favor, introduce la ruta del archivo: ");
                    //scanf("%s", ruta);
                    strcpy(ruta, "prueba_usuarios.csv");
                    pthread_mutex_init(&lock, NULL);  // Inicializamos nuestro mutex

                    pthread_t t1,t2,t3; 

                    cargaDatosArgs args1 = { 'c', ruta };
                    pthread_create(&t1, NULL, cargaDatosUsuario, &args1);

                    cargaDatosArgs args2 = { 'n', ruta };
                    pthread_create(&t2, NULL, cargaDatosUsuario, &args2);

                    cargaDatosArgs args3 = { 's', ruta };
                    pthread_create(&t3, NULL, cargaDatosUsuario, &args3);
                    
                    pthread_join(t1,NULL); 
                    pthread_join(t2,NULL); 
                    pthread_join(t3,NULL); 

                    pthread_mutex_destroy(&lock);  // Liberamos mutex de usuarios
                    verificarUsuarios();
                break;
            case 2:
                printf("Has elegido la opcion de carga de operaciones.\n");
                strcpy(ruta, "prueba_transacciones.csv");
                pthread_mutex_init(&lock, NULL);  // Inicializamos nuestro mutex

                pthread_t t5,t6,t7,t8; 

                cargaDatosArgs args5 = { 'o', ruta };
                pthread_create(&t5, NULL, cargaDatosOperaciones, &args5);

                cargaDatosArgs args6 = { '1', ruta };
                pthread_create(&t6, NULL, cargaDatosOperaciones, &args6);

                cargaDatosArgs args7 = { '2', ruta };
                pthread_create(&t7, NULL, cargaDatosOperaciones, &args7);

                cargaDatosArgs args8 = { 'm', ruta };
                pthread_create(&t8, NULL, cargaDatosOperaciones, &args8);
                
                pthread_join(t5,NULL); 
                pthread_join(t6,NULL); 
                pthread_join(t7,NULL); 
                pthread_join(t8,NULL); 

                pthread_mutex_destroy(&lock);  // Liberamos mutex de usuarios
                verificarOperaciones();
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            case 3:
                printf("Operaciones individuales\n");
                OperacionesI();
                
                break;    
            default:
                printf("Opcion no valida. Por favor, elige una opcion del menu.\n");
                break;
        }
    } while(opcion != 0);
    

    return 0;
}




// gcc -o main main.c -lpthread
// ./main