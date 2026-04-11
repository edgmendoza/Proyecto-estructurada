#include "prestamos.h"

// libreria ctype con funciones para trabajar con caracteres
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void menuPrestamos(Inventario* libros, int totalLibros, Prestamo* listaP, int* totalP) {
  int opcion;
  do {
    printf("\n\t--- GESTION DE PRESTAMOS ---\n");
    printf("1. Realizar Prestamo\n");
    printf("2. Registrar Devolucion\n");
    printf("3. Volver al Menu Principal\n");
    printf("Seleccione una opcion: ");
    // Validar que el usuario ingrese un numero
    if (scanf("%d", &opcion) != 1) {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
      opcion = -1;
    }

    switch (opcion) {
      case 1:
        realizarPrestamo(libros, totalLibros, listaP, totalP);
        break;
      case 2:
        realizarDevolucion(libros, totalLibros, listaP, totalP);
        break;
      case 3:
        printf("Regresando al menu principal...\n");
        break;
      default:
        printf("Opcion no valida. Intente de nuevo.\n");
    }
  } while (opcion != 3);
}

// convertir cadenas de texto a minusculas con la funcion tolower de la libreria ctype
void aMinusculas(char* cadena) {
  for (int i = 0; cadena[i]; i++) {
    cadena[i] = (char)tolower((unsigned char)cadena[i]);
  }
}

int calcularDias(int d1, int m1, int a1, int d2, int m2, int a2) {
  struct tm t1 = {0};
  struct tm t2 = {0};

  t1.tm_mday = d1;
  t1.tm_mon = m1 - 1;
  t1.tm_year = a1 - 1900;

  t2.tm_mday = d2;
  t2.tm_mon = m2 - 1;
  t2.tm_year = a2 - 1900;

  time_t time1 = mktime(&t1);
  time_t time2 = mktime(&t2);

  double segundos = difftime(time2, time1);
  return (int)((segundos / 86400.0) + 0.5);
}

void realizarPrestamo(Inventario* libros, int totalLibros, Prestamo* listaP, int* totalP) {
  // si se excede el max de prestamos entonces
  if (*totalP >= MAX_PRESTAMOS) {
    printf("Error: Limite de registros de prestamos alcanzado.\n");
    return;
  }

  char isbnAux[20];
  printf("\n--- Nuevo Prestamo ---\n");
  printf("Ingrese el ISBN del libro: ");
  scanf(" %19s", isbnAux);

  // busqueda de libro por ISBN con la funcion strcmp
  Inventario* libroPtr = NULL;
  for (int i = 0; i < totalLibros; i++) {
    if (strcmp(libros[i].isbn, isbnAux) == 0) {
      libroPtr = &libros[i];
      break;
    }
  }

  if (libroPtr == NULL) {
    printf("Error: El ISBN '%s' no existe en el inventario.\n", isbnAux);
  } else if (libroPtr->ejemplares <= 0) {
    printf("Aviso: No hay ejemplares disponibles de '%s'.\n", libroPtr->titulo);
  } else {
    char nombreAux[100];
    int dAux, mAux, aAux;

    printf("Nombre y Apellido del usuario: ");

    scanf(" %99[^\n]", nombreAux);
    aMinusculas(nombreAux);
    printf("Fecha de prestamo (dd mm aaaa): ");
    scanf("%d %d %d", &dAux, &mAux, &aAux);

    // Buscar si ya existe este mismo prestamo
    int indexEncontrado = -1;
    for (int i = 0; i < *totalP; i++) {
      if (strcmp(listaP[i].isbnLibro, isbnAux) == 0 &&
          strcmp(listaP[i].nombreUsuario, nombreAux) == 0 &&
          listaP[i].diaP == dAux && listaP[i].mesP == mAux && listaP[i].anioP == aAux) {
        indexEncontrado = i;
        break;
      }
    }

    // en caso de aver encontrado un prestamo igual ya existente
    if (indexEncontrado != -1) {
      listaP[indexEncontrado].cantidad++;
      // Si no se encontro el mismo se agrega como uno nuevo
    } else {
      Prestamo* nuevo = &listaP[*totalP];
      strcpy(nuevo->isbnLibro, isbnAux);
      strcpy(nuevo->nombreUsuario, nombreAux);
      nuevo->diaP = dAux;
      nuevo->mesP = mAux;
      nuevo->anioP = aAux;
      nuevo->cantidad = 1;
      (*totalP)++;
    }

    libroPtr->ejemplares--;

    guardarPrestamos(listaP, *totalP);

    gestionarInventario(libros, totalLibros);

    printf("\n>>> Prestamo registrado exitosamente.\n");
    printf("Libro: %s | Ejemplares restantes: %d\n", libroPtr->titulo, libroPtr->ejemplares);
  }
}

void realizarDevolucion(Inventario* libros, int totalLibros, Prestamo* listaP, int* totalP) {
  char usuario[100];
  char isbnDevolver[20];
  int encontrado = 0;
  printf("\n--- Registro de Devolucion ---\n");
  printf("Ingrese Nombre y Apellido del usuario: ");
  scanf(" %[^\n]", usuario);
  aMinusculas(usuario);
  printf("Ingrese el ISBN del libro a devolver: ");
  scanf(" %19s", isbnDevolver);
  for (int i = 0; i < *totalP; i++) {
    if (strcmp(listaP[i].nombreUsuario, usuario) == 0 &&
        strcmp(listaP[i].isbnLibro, isbnDevolver) == 0) {
      encontrado = 1;
      int cantDevolver = 1;
      if (listaP[i].cantidad > 1) {
        printf("Usted tiene %d copias prestadas. Cuantas desea devolver? ", listaP[i].cantidad);
        if (scanf("%d", &cantDevolver) != 1) {
          while (getchar() != '\n');
          cantDevolver = 1;
        }
        if (cantDevolver <= 0 || cantDevolver > listaP[i].cantidad) {
          printf("Error: Cantidad a devolver invalida.\n");
          return;
        }
      }
      printf("Fecha de devolucion hoy (dd mm aaaa): ");
      scanf("%d %d %d", &listaP[i].diaD, &listaP[i].mesD, &listaP[i].anioD);
      int dias = calcularDias(listaP[i].diaP, listaP[i].mesP, listaP[i].anioP,
                              listaP[i].diaD, listaP[i].mesD, listaP[i].anioD);
      if (dias < 0) {
        printf("Error: La fecha de devolucion no puede ser menor a la de prestamo.\n");
        return;
      }
      printf("\nTiempo transcurrido: %d dias.\n", dias);
      // multas
      if (dias > 10) {
        int multa = (dias - 10) * 20 * cantDevolver;
        printf("ALERTA: Retraso de %d dias detectado.\n", dias - 10);
        printf("MULTA A PAGAR: L. %d.00\n", multa);
      } else {
        printf("Devolucion a tiempo. Sin multas.\n");
      }
      // devolver libro, por isbn
      for (int j = 0; j < totalLibros; j++) {
        if (strcmp(libros[j].isbn, listaP[i].isbnLibro) == 0) {
          libros[j].ejemplares += cantDevolver;
          break;
        }
      }

      listaP[i].cantidad -= cantDevolver;
      if (listaP[i].cantidad == 0) {
        for (int k = i; k < *totalP - 1; k++) {
          listaP[k] = listaP[k + 1];
        }
        (*totalP)--;
      }

      guardarPrestamos(listaP, *totalP);

      gestionarInventario(libros, totalLibros);
      printf(">>> Inventario actualizado. Gracias.\n");
      return;
    }
  }
  if (!encontrado) {
    printf("No se encontro un prestamo activo para el usuario '%s' con el ISBN '%s'.\n", usuario, isbnDevolver);
  }
}

void guardarPrestamos(Prestamo* listaP, int totalP) {
  FILE* archivo = fopen("data/Prestamos.txt", "w");
  if (archivo == NULL) {
    printf("Error al abrir archivo de prestamos para escribir.\n");
    return;
  }

  for (int i = 0; i < totalP; i++) {
    fprintf(archivo, "%s|%s|%d|%d|%d|%d\n",
            listaP[i].isbnLibro,
            listaP[i].nombreUsuario,
            listaP[i].diaP, listaP[i].mesP, listaP[i].anioP,
            listaP[i].cantidad);
  }
  fclose(archivo);
}

// lee los datos del Prestamos.txt para cargarlos en memoria
// el dato de entrada listaP es un puntero a la estructura prestamos
int cargarPrestamos(Prestamo* listaP) {
  FILE* archivo = fopen("data/Prestamos.txt", "r");
  if (archivo == NULL) return 0;

  int i = 0;
  // cargar todos los elementos en memoria
  while (fscanf(archivo, " %19[^|]|%99[^|]|%d|%d|%d|%d\n",
                listaP[i].isbnLibro,
                listaP[i].nombreUsuario,
                &listaP[i].diaP, &listaP[i].mesP, &listaP[i].anioP,
                &listaP[i].cantidad) != EOF) {
    i++;
  }
  fclose(archivo);
  return i;
}