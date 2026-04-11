#include "Reportes.h"

#include <stdio.h>

int balanceTotal(const char* nombreArchivo) {
  FILE* archivo = fopen(nombreArchivo, "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return 1;
  }

  int contador = 0;
  int caracter;

  while ((caracter = fgetc(archivo)) != EOF) {
    if (caracter == '\n') {
      contador++;
    }
  }

  fclose(archivo);

  if (contador == 0 && caracter == EOF) {
    return 0;
  }

  return contador + 1;
}

void mostrarReporteNumerico(Inventario* libros, int totalLibros, Prestamo* listaPrestamos, int totalPrestamos) {
  int librosDisponibles = 0;
  for (int i = 0; i < totalLibros; i++) {
    librosDisponibles += libros[i].ejemplares;
  }

  int librosPrestados = 0;
  for (int i = 0; i < totalPrestamos; i++) {
    librosPrestados += listaPrestamos[i].cantidad;
  }

  int totalActivos = librosDisponibles + librosPrestados;

  printf("\n1. REPORTE:\n");
  printf("  - Libros en estanteria (Disponibles):  %d\n", librosDisponibles);
  printf("  - Libros en prestamo (Activos):        %d\n", librosPrestados);
  printf("  -----------------------------------------\n");
  printf("  TOTAL DE ACTIVOS CIRCULANTES:          %d\n\n", totalActivos);
}