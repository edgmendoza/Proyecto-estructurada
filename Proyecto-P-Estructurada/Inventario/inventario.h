#ifndef INVENTARIO_H
#define INVENTARIO_H

typedef struct
{
  char titulo[50];
  char autor[50];
  char isbn[20];
  int anio;
  int ejemplares;

} Inventario;

void gestionarInventario(Inventario* libros, int numLibros);
int cargarLibros(Inventario* libros);
void agregarLibros(Inventario* libros, int* numLibros);
void listarLibros(Inventario* libros, int numLibros);
void buscarLibro(Inventario* libros, int numLibros);
void menuLibros(Inventario* libros, int* numLibros);
void normalizarLetras(char* cadena);

#endif
