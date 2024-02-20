# Documentación del Programa `monitor.c`

## Descripción General

El programa `monitor.c` es una aplicación en C que crea dos procesos hijos y ejecuta un comando de SystemTap para rastrear las llamadas al sistema de estos procesos hijos.

## Código Fuente

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <pthread.h> 
#include <sys/wait.h>
#include <signal.h>

void handle_sigint(int sig) 
{ 
    printf("Recibida señal SIGINT\n"); 
    exit(0);
} 

int main(){
    signal(SIGINT, handle_sigint); 

    char command[100];
    
    int procesoHijo1 = fork();

    if(procesoHijo1 == 0){

        char *argv[] = {NULL};
        execv("./proceso", argv);
    
    } else {
        int procesoHijo2 = fork();
        
        if(procesoHijo2 == 0){
            char *argv[] = {NULL};
            execv("./proceso", argv);
        } else {

            sprintf(command, "%s %d %d %s", "sudo stap trace.stp ", procesoHijo1, procesoHijo2, " > syscall.log");
            system(command);
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}
```

## Detalles de Implementación

### Manejador de Señales

La función `handle_sigint(int sig)` se invoca cuando se recibe una señal SIGINT (generalmente enviada desde el teclado con Ctrl+C). Cuando se recibe esta señal, el programa imprime un mensaje y luego termina.

### Función Principal

La función `main()` realiza las siguientes operaciones:

- Registra `handle_sigint` como el manejador de la señal SIGINT con la llamada a `signal(SIGINT, handle_sigint)`.

- Crea un proceso hijo con `fork()`. El valor devuelto por `fork()` es 0 en el proceso hijo, por lo que el código dentro del primer bloque `if` se ejecuta solo en el proceso hijo. Este proceso hijo ejecuta el programa llamado "proceso" con `execv("./proceso", argv)`.

- En el proceso padre, `fork()` devuelve el PID del proceso hijo, por lo que crea otro proceso hijo y ejecuta el mismo programa "proceso".

- En el proceso padre original, después de crear los dos procesos hijos, construye un comando para ejecutar un script de SystemTap llamado "trace.stp" con los PIDs de los dos procesos hijos como argumentos. Este comando se ejecuta con `system(command)`.

## Detalles de Implementación

### Apertura de Archivo

La función `open("practica1.txt", O_RDWR | O_CREAT, 0777 )` se utiliza para abrir el archivo "practica1.txt". Si el archivo no existe, se crea con permisos 0777 (lectura, escritura y ejecución para todos los usuarios).

### Generación de Caracteres Aleatorios

Se inicializa un array `alphanum[]` con todos los caracteres alfanuméricos. Luego, en un bucle, se selecciona un carácter aleatorio de este array y se añade a `buffer[]`. Este proceso se repite 8 veces para generar una cadena de 8 caracteres.

### Operaciones Aleatorias

Se genera un número aleatorio entre 0 y 2. Dependiendo del número generado, se realiza una de las siguientes operaciones:

- **Escritura (caso 0)**: Se escribe la cadena generada aleatoriamente en el archivo.

- **Lectura (caso 1)**: Se leen 8 caracteres del archivo y se imprimen.

- **Mover el puntero (caso 2)**: Se mueve el puntero del archivo a una posición aleatoria.

### Bucle Infinito

Todas estas operaciones se realizan en un bucle infinito. Después de cada operación, el programa se pone a dormir durante un tiempo aleatorio entre 1 y 3 segundos antes de repetir el ciclo.