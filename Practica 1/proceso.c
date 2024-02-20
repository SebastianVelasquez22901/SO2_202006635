#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

void main(){

    int fd = open("practica1.txt", O_RDWR | O_CREAT, 0777 );

    char buffer[9];  // Buffer para la cadena aleatoria y la lectura del archivo
    char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    srand(time(NULL));  // Inicializa la semilla del generador de números aleatorios

    while(1){
        int operation = rand() % 3;  // Genera un número aleatorio entre 0 y 2

        switch(operation) {
            case 0:  // Escritura
                for (int i = 0; i < 8; i++) {
                    buffer[i] = alphanum[rand() % (sizeof(alphanum) - 1)];  // Genera un carácter alfanumérico aleatorio
                }
                buffer[8] = '\0';  // Termina la cadena con un carácter nulo
                write(fd, buffer, strlen(buffer));  // Escribe la cadena aleatoria en el archivo
                break;
            case 1:  // Lectura
                read(fd, buffer, 8);  // Lee 8 caracteres del archivo
                buffer[8] = '\0';  // Termina la cadena con un carácter nulo
                printf("Leído del archivo: %s\n", buffer);
                break;
            case 2:  // Mover el puntero
                lseek(fd, rand() % 100, SEEK_SET);  // Mueve el puntero a una posición aleatoria
                break;
        }

        sleep(rand() % 3 + 1);  // Duerme durante un tiempo aleatorio entre 1 y 3 segundos
    }
}