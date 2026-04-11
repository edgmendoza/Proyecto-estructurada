#include "inventario.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gestionarInventario(Inventario* libros, int numLibros) {
  FILE* archivo = fopen("data/Inventario.txt", "w");
  if (archivo == NULL) return;

  for (int i = 0; i < numLibros; i++) {
    fprintf(archivo, "%s|%s|%s|%d|%d\n",
            libros[i].titulo, libros[i].autor,
            libros[i].isbn, libros[i].anio, libros[i].ejemplares);
  }
  fclose(archivo);
}

void menuLibros(Inventario* libros, int* numLibros) {
  int opcion;
  do {
    printf("\n\t--- GESTION DE INVENTARIO ---\n");
    printf("1. Agregar libro\n");
    printf("2. Mostrar libros\n");
    printf("3. Buscar libro\n");
    printf("4. Volver al Menu Principal\n");
    printf("Seleccione una opcion: ");
    if (scanf("%d", &opcion) != 1) {
      while (getchar() != '\n');
      opcion = -1;
    }

    switch (opcion) {
      case 1:
        agregarLibros(libros, numLibros);
        break;
      case 2:
        listarLibros(libros, *numLibros);
        break;
      case 3:
        buscarLibro(libros, *numLibros);
        break;
      case 4:
        gestionarInventario(libros, *numLibros);
        printf("Regresando...\n");
        break;
      default:
        printf("Opcion no valida.\n");
    }
  } while (opcion != 4);
}

int cargarLibros(Inventario* libros) {
  FILE* archivo = fopen("data/Inventario.txt", "r");
  if (archivo == NULL) return 0;

  int i = 0;
  while (fscanf(archivo, " %49[^|]|%49[^|]|%19[^|]|%d|%d\n",
                libros[i].titulo, libros[i].autor,
                libros[i].isbn, &libros[i].anio, &libros[i].ejemplares) != EOF) {
    i++;
  }
  fclose(archivo);
  return i;
}

void agregarLibros(Inventario* libros, int* numLibros) {
  Inventario nuevoLibro;
  printf("Ingrese el titulo del libro: ");
  scanf(" %[^\n]", nuevoLibro.titulo);
  printf("Ingrese el autor del libro: ");
  scanf(" %[^\n]", nuevoLibro.autor);
  printf("Ingrese el ISBN (6 digitos): ");
  scanf("%6s", nuevoLibro.isbn);
  printf("Ingrese el anio del libro: ");
  scanf("%d", &nuevoLibro.anio);
  printf("Ingrese el numero de ejemplares: ");
  scanf("%d", &nuevoLibro.ejemplares);

  libros[*numLibros] = nuevoLibro;
  (*numLibros)++;

  printf("Libro agregado con exito.\n");
}
void listarLibros(Inventario* libros, int numLibros) {
  if (numLibros == 0) {
    printf("No hay libros en el inventario\n");
    return;
  }
  printf("\n%-35s | %-25s | %-15s | %-6s | %-10s\n", "Titulo", "Autor", "ISBN", "Anio", "Ejemplares");
  printf("------------------------------------------------------------------------------------------------------\n");
  for (int i = 0; i < numLibros; i++) {
    printf("%-35.35s | %-25.25s | %-15.15s | %-6d | %-10d\n", libros[i].titulo, libros[i].autor, libros[i].isbn, libros[i].anio, libros[i].ejemplares);
  }
}

void buscarLibro(Inventario* libros, int numLibros) {
  int opcion;
  char textoBuscado[50];
  int encontrado = 0;

  printf("\nBuscar libro por:\n");
  printf("1. Titulo\n");
  printf("2. Autor\n");
  printf("Seleccione una opcion: ");
  if (scanf("%d", &opcion) != 1) {
    while (getchar() != '\n');
    opcion = -1;
  }

  printf("Ingrese el texto a buscar: ");
  scanf(" %[^\n]", textoBuscado);

  char textoNormalizado[50];
  strcpy(textoNormalizado, textoBuscado);
  normalizarLetras(textoNormalizado);

  for (int i = 0; i < numLibros; i++) {
    char tituloNorm[50];
    char autorNorm[50];
    strcpy(tituloNorm, libros[i].titulo);
    strcpy(autorNorm, libros[i].autor);
    normalizarLetras(tituloNorm);
    normalizarLetras(autorNorm);

    if ((opcion == 1 && strstr(tituloNorm, textoNormalizado) != NULL) || (opcion == 2 && strstr(autorNorm, textoNormalizado) != NULL)) {
      printf("\nLibro encontrado:\n");
      printf("Titulo: %s\n", libros[i].titulo);
      printf("Autor: %s\n", libros[i].autor);
      printf("ISBN: %s\n", libros[i].isbn);
      printf("Anio: %d\n", libros[i].anio);
      printf("Ejemplares: %d\n", libros[i].ejemplares);

      encontrado = 1;
    }
  }

  if (!encontrado) {
    printf("No se encontraron resultados.\n");
  }
}

void normalizarLetras(char* cadena) {
  for (int i = 0; cadena[i]; i++) {
    cadena[i] = tolower(cadena[i]);
  }
}