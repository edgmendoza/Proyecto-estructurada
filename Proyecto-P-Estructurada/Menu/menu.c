#include "Menu.h"

#include <stdio.h>

void menuPrincipal(Inventario* libros, int* pNumLibros, Prestamo* listaPrestamos, int* pTotalPrestamos) {
  int opcion = 0, opcion2 = 0;

  do {
    printf("1. Gestion de Libros.\n");
    printf("2. Gestion de prestamos de libros.\n");
    printf("3. Reportes.\n");
    printf("4. Salir del programa.\n");
    printf("Elija la opcion que desee realizar: ");
    scanf("%d", &opcion);

    switch (opcion) {
      case 1:
        menuLibros(libros, pNumLibros);
        break;

      case 2:
        menuPrestamos(libros, *pNumLibros, listaPrestamos, pTotalPrestamos);
        break;

      case 3:
        mostrarReporteNumerico(libros, *pNumLibros, listaPrestamos, *pTotalPrestamos);
        break;
      case 4:
        break;
      default:
        printf("Elija una de las 4 opciones\n");
    }

  } while (opcion != 4);
}