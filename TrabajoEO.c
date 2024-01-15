#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 50
#define MAX_FACTURAS 50
#define MAX_CLIENTES 50

// Funciones de Productos
void mostrarProductos();
int buscarProducto(const char nombreBuscar[MAX_NOMBRE], char nombres[MAX_PRODUCTOS][MAX_NOMBRE], int numProductos);
void mandarProducto(int numeroProducto, char nombre[MAX_NOMBRE], float precio, int cantidad);
void editarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos);
void leerProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos);
void eliminarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos);
void consultarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos);

// Funciones de Facturación
void facturar(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos, int *numFacturas);
void buscarFactura(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos);
void verListadoFacturas(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos, int numFacturas);

// Funciones de Clientes
void mostrarClientes(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes);
int buscarCliente(const char nombreBuscar[MAX_NOMBRE], char nombres[MAX_CLIENTES][MAX_NOMBRE], int numClientes);
void ingresarCliente(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int *numClientes);
void modificarCliente(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes);
void consultarCliente(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes);
void verListadoClientes(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes);

// Función principal (main)
void mostrarProductos() {
    FILE *archivo = fopen("baseDatosProductos.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        return;
    }

    printf("\n*** Lista de productos ***\n");

    char nombre[MAX_NOMBRE];
    float precio;
    int cantidad;

    while (fscanf(archivo, "%*d %s %f %d", nombre, &precio, &cantidad) == 3) {
        printf("%s - Precio: %.2f - Cantidad: %d\n", nombre, precio, cantidad);
    }

    fclose(archivo);
}

int buscarProducto(const char nombreBuscar[MAX_NOMBRE], char nombres[MAX_PRODUCTOS][MAX_NOMBRE], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombreBuscar) == 0) {
            return i;
        }
    }
    return -1;
}

void mandarProducto(int numeroProducto, char nombre[MAX_NOMBRE], float precio, int cantidad) {
    FILE *archivo = fopen("baseDatosProductos.txt", "a+");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
    } else {
        fprintf(archivo, "%d %s %.2f %d\n", numeroProducto, nombre, precio, cantidad);
    }

    fclose(archivo);
}

void editarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos) {
    printf("\n*** Editar producto***\n");
    if (numProductos == 0) {
        printf("No hay productos en el inventario.\n");
        return;
    }

    mostrarProductos();

    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del producto que desea editar: ");
    scanf("%s", nombreBuscar);

    int indiceProducto = buscarProducto(nombreBuscar, nombres, numProductos);

    if (indiceProducto != -1) {
        printf("Ingrese el nuevo nombre del producto: ");
        scanf("%s", nombres[indiceProducto]);
        printf("Ingrese el nuevo precio del producto: ");
        scanf("%f", &precios[indiceProducto]);
        printf("Ingrese la nueva cantidad en inventario: ");
        scanf("%d", &cantidades[indiceProducto]);

        printf("Producto \"%s\" editado con éxito.\n", nombreBuscar);

        FILE *archivo = fopen("baseDatosProductos.txt", "w");
        for (int j = 0; j < numProductos; j++) {
            fprintf(archivo, "%d %s %.2f %d\n", j + 1, nombres[j], precios[j], cantidades[j]);
        }
        fclose(archivo);
    } else {
        printf("Producto \"%s\" no encontrado.\n", nombreBuscar);
    }
}

void leerProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos) {
    int rep, ooo = 0;

    printf("Cuantos productos quiere agregar?");
    scanf("%d", &rep);

    FILE *archivo = fopen("baseDatosProductos.txt", "a+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura y escritura.\n");
        return;
    }

    // Leer el contenido actual del archivo y cargarlo en los arreglos
    for (int i = 0; i < *numProductos; i++) {
        fscanf(archivo, "%*d %s %f %d", nombres[i], &precios[i], &cantidades[i]);
    }

    do {
        if (*numProductos < MAX_PRODUCTOS) {
            int numeroProducto = *numProductos + 1; // Asignar un número único al producto

            printf("\nIngrese el nombre del producto: ");
            scanf("%s", nombres[*numProductos]);

            printf("Ingrese el precio del producto: ");
            scanf("%f", &precios[*numProductos]);

            printf("Ingrese la cantidad en inventario del producto: ");
            scanf("%d", &cantidades[*numProductos]);

            // Mandar producto al archivo
            fprintf(archivo, "%d %s %.2f %d\n", numeroProducto, nombres[*numProductos], precios[*numProductos], cantidades[*numProductos]);

            (*numProductos)++;

            printf("Producto %d agregado con éxito.\n", numeroProducto);
        } else {
            printf("El inventario está lleno. No se puede agregar más productos.\n");
        }

        ooo++;

    } while (ooo < rep);

    fclose(archivo);
}

void eliminarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos) {
    printf("\n*** Eliminar producto ***\n");

    mostrarProductos();

    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf("%s", nombreBuscar);

    int indiceProducto = buscarProducto(nombreBuscar, nombres, *numProductos);

    if (indiceProducto != -1) {
        for (int i = indiceProducto; i < *numProductos - 1; i++) {
            strcpy(nombres[i], nombres[i + 1]);
            precios[i] = precios[i + 1];
            cantidades[i] = cantidades[i + 1];
        }
        (*numProductos)--;

        printf("Producto \"%s\" eliminado con éxito.\n", nombreBuscar);

        FILE *archivo = fopen("baseDatosPerros.txt", "w");
        for (int j = 0; j < *numProductos; j++) {
            fprintf(archivo, "%s %.2f %d\n", nombres[j], precios[j], cantidades[j]);
        }
        fclose(archivo);
    } else {
        printf("Producto \"%s\" no encontrado.\n", nombreBuscar);
    }
}

void consultarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos) {
    FILE *archivo = fopen("baseDatosProductos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        return;
    }

    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del producto que desea consultar: ");
    scanf("%s", nombreBuscar);

    int indiceProducto = buscarProducto(nombreBuscar, nombres, numProductos);

    if (indiceProducto != -1) {
        printf("Producto encontrado:\n");
        printf("%s - Precio: %.2f - Cantidad: %d\n", nombres[indiceProducto], precios[indiceProducto], cantidades[indiceProducto]);
    } else {
        printf("Producto \"%s\" no encontrado.\n", nombreBuscar);
    }

    fclose(archivo);
}

// Funciones de Facturación

void facturar(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos, int *numFacturas) {
    printf("\n*** Facturación ***\n");

    printf("Lista de productos disponibles:\n");
    mostrarProductos();

    printf("Ingrese el nombre del cliente: ");
    char nombreCliente[MAX_NOMBRE];
    scanf("%s", nombreCliente);

    printf("Cantidad de productos a facturar: ");
    int cantidadProductos;
    scanf("%d", &cantidadProductos);

    float totalFactura = 0.0;
    printf("Productos a facturar:\n");

    for (int i = 0; i < cantidadProductos; i++) {
        printf("%d. %s - Precio: %.2f - Cantidad en inventario: %d\n", i + 1, nombres[i], precios[i], cantidades[i]);
        totalFactura += precios[i];
    }

    printf("Total de la factura: %.2f\n", totalFactura);

    
    for (int i = 0; i < cantidadProductos; i++) {
        cantidades[i] -= 1; 
    }

   
    FILE *facturasArchivo = fopen("facturas.txt", "a+");
    fprintf(facturasArchivo, "Cliente: %s - Total: %.2f\n", nombreCliente, totalFactura);
    fclose(facturasArchivo);

    printf("Factura generada con éxito.\n");
    (*numFacturas)++;
}

void buscarFactura(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos) {
    printf("\n*** Buscar Factura ***\n");

    FILE *facturasArchivo = fopen("facturas.txt", "r");

    if (facturasArchivo == NULL) {
        printf("No hay facturas registradas.\n");
        return;
    }

    char nombreCliente[MAX_NOMBRE];
    float totalFactura;

    while (fscanf(facturasArchivo, "Cliente: %s - Total: %f", nombreCliente, &totalFactura) == 2) {
        printf("Cliente: %s - Total: %.2f\n", nombreCliente, totalFactura);
    }

    fclose(facturasArchivo);
}

void verListadoFacturas(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos, int numFacturas) {
    printf("\n*** Listado de Facturas ***\n");

    FILE *facturasArchivo = fopen("facturas.txt", "r");

    if (facturasArchivo == NULL) {
        printf("No hay facturas registradas.\n");
        return;
    }

    char nombreCliente[MAX_NOMBRE];
    float totalFactura;

    while (fscanf(facturasArchivo, "Cliente: %s - Total: %f", nombreCliente, &totalFactura) == 2) {
        printf("Cliente: %s - Total: %.2f\n", nombreCliente, totalFactura);
    }

    fclose(facturasArchivo);
}

// Funciones de Clientes

void mostrarClientes(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes) {
    printf("\n*** Listado de Clientes ***\n");

    for (int i = 0; i < numClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nombre: %s\n", nombres[i]);
        printf("Dirección: %s\n", direcciones[i]);
        printf("Teléfono: %s\n", telefonos[i]);
        printf("\n");
    }
}

int buscarCliente(const char nombreBuscar[MAX_NOMBRE], char nombres[MAX_CLIENTES][MAX_NOMBRE], int numClientes) {
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(nombres[i], nombreBuscar) == 0) {
            return i;
        }
    }
    return -1;
}

void ingresarCliente(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int *numClientes) {
    printf("\n*** Ingresar Cliente ***\n");

    if (*numClientes < MAX_CLIENTES) {
        printf("Ingrese el nombre del cliente: ");
        scanf("%s", nombres[*numClientes]);

        printf("Ingrese la dirección del cliente: ");
        scanf("%s", direcciones[*numClientes]);

        printf("Ingrese el teléfono del cliente: ");
        scanf("%s", telefonos[*numClientes]);

        (*numClientes)++;

        printf("Cliente ingresado con éxito.\n");
    } else {
        printf("Limite de clientes alcanzado. No se puede ingresar más clientes.\n");
    }
}

void modificarCliente(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes) {
    printf("\n*** Modificar Cliente ***\n");

    if (numClientes == 0) {
        printf("No hay clientes registrados.\n");
        return;
    }

    mostrarClientes(nombres, direcciones, telefonos, numClientes);

    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del cliente que desea modificar: ");
    scanf("%s", nombreBuscar);

    int indiceCliente = buscarCliente(nombreBuscar, nombres, numClientes);

    if (indiceCliente != -1) {
        printf("Ingrese el nuevo nombre del cliente: ");
        scanf("%s", nombres[indiceCliente]);

        printf("Ingrese la nueva dirección del cliente: ");
        scanf("%s", direcciones[indiceCliente]);

        printf("Ingrese el nuevo teléfono del cliente: ");
        scanf("%s", telefonos[indiceCliente]);

        printf("Cliente \"%s\" modificado con éxito.\n", nombreBuscar);
    } else {
        printf("Cliente \"%s\" no encontrado.\n", nombreBuscar);
    }
}

void consultarCliente(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes) {
    printf("\n*** Consultar Cliente ***\n");

    if (numClientes == 0) {
        printf("No hay clientes registrados.\n");
        return;
    }

    mostrarClientes(nombres, direcciones, telefonos, numClientes);

    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del cliente que desea consultar: ");
    scanf("%s", nombreBuscar);

    int indiceCliente = buscarCliente(nombreBuscar, nombres, numClientes);

    if (indiceCliente != -1) {
        printf("Cliente %d:\n", indiceCliente + 1);
        printf("Nombre: %s\n", nombres[indiceCliente]);
        printf("Dirección: %s\n", direcciones[indiceCliente]);
        printf("Teléfono: %s\n", telefonos[indiceCliente]);
        printf("\n");
    } else {
        printf("Cliente \"%s\" no encontrado.\n", nombreBuscar);
    }
}

void verListadoClientes(char nombres[MAX_CLIENTES][MAX_NOMBRE], char direcciones[MAX_CLIENTES][MAX_NOMBRE], char telefonos[MAX_CLIENTES][MAX_NOMBRE], int numClientes) {
    printf("\n*** Listado de Clientes ***\n");

    if (numClientes == 0) {
        printf("No hay clientes registrados.\n");
        return;
    }

    mostrarClientes(nombres, direcciones, telefonos, numClientes);
}

int main(void) {
    int opcion;
    int numProductos = 0;
    int numFacturas = 0;
    int numClientes = 0;

    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    float precios[MAX_PRODUCTOS];
    int cantidades[MAX_PRODUCTOS];

    char nombresClientes[MAX_CLIENTES][MAX_NOMBRE];
    char direccionesClientes[MAX_CLIENTES][MAX_NOMBRE];
    char telefonosClientes[MAX_CLIENTES][MAX_NOMBRE];

    do {
        printf("Sistema de Gestión\n");
        printf("Opciones:\n");
        printf("1- Ingresar Producto           ");
        printf("2- Modificar Producto\n");
        printf("3- Eliminar Producto           ");
        printf("4- Vender Productos\n");
        printf("5- Ver productos               ");
        printf("6- Ingresar Cliente\n");
        printf("7- Modificar Cliente           ");
        printf("8- Consultar Cliente\n");
        printf("9- Ver listado de clientes     ");
        printf("10- Facturar\n");
        printf("11- Buscar Factura             ");
        printf("12- Ver listado de facturas\n");
        printf("13- Salir\n");
        printf("Ingrese una opcion:   ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                leerProducto(nombres, precios, cantidades, &numProductos);
                printf("\n");
                break;

            case 2:
                editarProducto(nombres, precios, cantidades, numProductos);
                printf("\n");
                break;

            case 3:
                eliminarProducto(nombres, precios, cantidades, &numProductos);
                printf("\n");
                break;

            case 4:
                consultarProducto(nombres, precios, cantidades, numProductos);
                printf("\n");
                break;

            case 5:
                mostrarProductos();
                printf("\n");
                break;

            case 6:
                ingresarCliente(nombresClientes, direccionesClientes, telefonosClientes, &numClientes);
                printf("\n");
                break;

            case 7:
                modificarCliente(nombresClientes, direccionesClientes, telefonosClientes, numClientes);
                printf("\n");
                break;

            case 8:
                consultarCliente(nombresClientes, direccionesClientes, telefonosClientes, numClientes);
                printf("\n");
                break;

            case 9:
                verListadoClientes(nombresClientes, direccionesClientes, telefonosClientes, numClientes);
                printf("\n");
                break;

            case 10:
                facturar(nombres, precios, cantidades, numProductos, &numFacturas);
                printf("\n");
                break;

            case 11:
                buscarFactura(nombres, precios, cantidades, numProductos);
                printf("\n");
                break;

            case 12:
                verListadoFacturas(nombres, precios, cantidades, numProductos, numFacturas);
                printf("\n");
                break;

            case 13:
                printf("Cerrando Programa\n");
                printf("\n");
                break;

            default:
                printf("Opcion no valida\n");
                printf("\n");
                break;
        }
    } while (opcion != 13);

    return 0;
}

