#ifndef PRESTAMOS_H
#define PRESTAMOS_H

// llamar a la funcion inventario para usar en prestamos
#include "../Inventario/inventario.h"

#define MAX_PRESTAMOS 100

typedef struct {
  char isbnLibro[20];
  char nombreUsuario[100];
  // variables fecha del prestamo
  int diaP, mesP, anioP;
  // variables fecha de devolucion
  int diaD, mesD, anioD;
  int cantidad;
} Prestamo;

void menuPrestamos(Inventario* libros, int totalLibros, Prestamo* listaP, int* totalP);

void realizarPrestamo(Inventario* libros, int totalLibros, Prestamo* listaP, int* totalP);
void realizarDevolucion(Inventario* libros, int totalLibros, Prestamo* listaP, int* totalP);

int calcularDias(int d1, int m1, int a1, int d2, int m2, int a2);

void guardarPrestamos(Prestamo* listaP, int totalP);
int cargarPrestamos(Prestamo* listaP);

#endif