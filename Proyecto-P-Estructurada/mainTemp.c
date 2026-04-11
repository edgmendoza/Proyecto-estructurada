#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funciones propias
#include "Inventario/inventario.h"
#include "Menu/Menu.h"
#include "Prestamos/prestamos.h"

int main() {
  // inicializar variables
  Inventario libros[100];
  int numLibros = 0;

  Prestamo listaPrestamos[MAX_PRESTAMOS];
  int totalPrestamos = 0;

  // cargar datos
  numLibros = cargarLibros(libros);
  totalPrestamos = cargarPrestamos(listaPrestamos);

  printf("   SISTEMA BIBLIOTECARIO (TEST MAIN)\n\n");

  // actualizar datos
  menuPrincipal(libros, &numLibros, listaPrestamos, &totalPrestamos);

  printf("Saliendo...\n");

  // guardar datos
  gestionarInventario(libros, numLibros);
  guardarPrestamos(listaPrestamos, totalPrestamos);

  return 0;
}