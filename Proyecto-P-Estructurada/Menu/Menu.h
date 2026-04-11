#ifndef MENU_H
#define MENU_H

#include "../Inventario/inventario.h"
#include "../Prestamos/prestamos.h"
#include "../Reportes/Reportes.h"

void menuPrincipal(Inventario* libros, int* pNumLibros, Prestamo* listaPrestamos, int* pTotalPrestamos);

#endif