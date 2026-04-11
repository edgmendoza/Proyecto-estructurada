#ifndef REPORTES_H
#define REPORTES_H

#include "../Inventario/inventario.h"
#include "../Prestamos/prestamos.h"

int balanceTotal(const char* nombreArchivo);
void mostrarReporteNumerico(Inventario* libros, int totalLibros, Prestamo* listaPrestamos, int totalPrestamos);

#endif