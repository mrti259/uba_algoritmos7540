
#include "defendiendo_torres.h"
#include "archivos.h"
#include "configuracion.h"
#include <stdbool.h>
#include <string.h>

#define ENANOS 'G'
#define ELFOS 'L'
#define TORRE_UNO 1
#define TORRE_DOS 2

const int   MAX_DATO = 10,
            MAX_RESISTENCIA = 1000,
            MAX_DEFENSORES_EXTRAS = 20,
            MAX_DEFENSORES_INICIO = 20,
            MAX_CRITICO = 100,
            MAX_FALLO = 100;
const float MAX_VELOCIDAD = 2.0;

const char  RESISTENCIA_TORRES[] = "RESISTENCIA_TORRES=%i,%i\n",
            ENANOS_INICIO[] = "ENANOS_INICIO=%i,%i,%i,%i\n",
            ELFOS_INICIO[] = "ELFOS_INICIO=%i,%i,%i,%i\n",
            ENANOS_EXTRA[] = "ENANOS_EXTRA=%i,%i,%i\n",
            ELFOS_EXTRA[] = "ELFOS_EXTRA=%i,%i,%i\n",
            ENANOS_ANIMO[] = "ENANOS_ANIMO=%i,%i\n",
            ELFOS_ANIMO[] = "ELFOS_ANIMO=%i,%i\n",
            VELOCIDAD_CONFIG[] = "VELOCIDAD=%f\n",
            CAMINOS[] = "CAMINOS=%s\n";

/*
 * Pre: Recibe el valor numérico de un dato ingresado por el usuario.
 * Pos: Devuelve true si se ha ingresado un número mayor a 0 y menor a MAX_RESISTENCIA.
 *      Se permite la opción INDEFINIDO para vlores predeterminados del juego.
 */
bool es_resistencia_valida(int dato_num) {
    return !dato_num && (dato_num >= INDEFINIDO && dato_num < MAX_RESISTENCIA);
}

/*
 * Pre: Recibe el valor numérico de un dato ingresado por el usuario.
 * Pos: Devuelve true si el valor numérico se encuentra entre 0 y MAX_DEFENSORES_EXTRAS.
 *      Se permite la opción INDEFINIDO para valores predeterminados del juego.
 */
bool es_defensa_extra_valida(int dato_num) {
    return (dato_num >= INDEFINIDO) && (dato_num < MAX_DEFENSORES_EXTRAS);
}

/*
 * Pre: Recibe el valor numérico de un dato ingresado por el usuario.
 * Pos: Devuelve true si el valor numérico se encuentra entre 0 y MAX_DEFENSORES_INICIO.
 *      Se permite la opción INDEFINIDO para valores predeterminados del juego.
 */
bool es_defensa_inicial_valida(int dato_num) {
    return (dato_num >= INDEFINIDO) && (dato_num < MAX_DEFENSORES_INICIO);
}

/*
 * Pre: Recibe el valor numérico de un dato ingresado por el usuario.
 * Pos: Devuelve true si el valor se encuentra entre 0 y MAX_CRITICO.
 *      Se permite la opción INDEFINIDO para valores predeterminados del juego.
 */
bool es_critico_valido(int dato_num) {
    return (dato_num >= INDEFINIDO) && (dato_num < MAX_CRITICO);
}

/*
 * Pre: Recibe el valor numérico de un dato ingresado por el usuario.
 * Pos: Devuelve true si el valor se encuentra entre 0 y MAX_FALLO.
 *      Se permite la opción INDEFINIDO para valores predeferminados del juego
 */
bool es_fallo_valido(int dato_num) {
    return (dato_num >= INDEFINIDO) && (dato_num < MAX_FALLO);
}

/*
 * Pre: Recibe el valor decimal del dato ingresado por el usuario.
 * Pos: Devuelve true si el valor es mayor a 0 y menor a MAX_VELOCIDAD.
 *      Se permite la opción INDEFINIDO para el valor predeterminado del juego.
 */
bool es_velocidad_valida(double dato_num) {
    return !dato_num || (dato_num >= INDEFINIDO && dato_num < MAX_VELOCIDAD);
}

/*
 * Pre: Recibe una cadena ingresada por el usuario.
 * Pos: Devuelve true si el usuario ha ingresado algo en la cadena.
 */
bool hay_archivo(char archivo[]) {
    return strcmp(archivo, SIN_ARCHIVO);
}


/*
 * Muestra en pantalla un mensaje donde le pide al usuario ingresar los valores
 * de resistencia de las torres. Se definen uno a la vez en configuracion.
 */
void pedir_resistencia_torres(configuracion_t *configuracion) {
    int dato_num;
    char dato[MAX_DATO];
    printf("Ingrese resistencia para la Torre %i: ", TORRE_UNO);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_resistencia_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_RESISTENCIA);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.torres.resistencia_torre_1 = dato_num;
    printf("Ingrese resistencia para la Torre %i: ", TORRE_DOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_resistencia_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_RESISTENCIA);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.torres.resistencia_torre_2 = dato_num;

}

/*
 * Se pide al usuario ingresar la cantidad de defensores extras que se permitiran
 * agregar en el juego. Una vez defininos se almacenan en configuracion.
 */
void pedir_defensores_extras(configuracion_t *configuracion) {
    int dato_num;
    char dato[MAX_DATO];
    printf("Ingrese nº de defensores (%c) extras para las torres: ", ENANOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_defensa_extra_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_DEFENSORES_EXTRAS);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.torres.enanos_extra = dato_num;

    printf("Ingrese nº de defensores (%c) extras para las torres: ", ELFOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_defensa_extra_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_DEFENSORES_EXTRAS);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.torres.elfos_extra = dato_num;
}

/*
 * Se pide al usuario ingresar la cantidad defensores que se agregarán al principio del nivel.
 * Cada dato se almacenará en la configuración.
 */
void pedir_defensores_inicio(configuracion_t *configuracion, char tipo, int nivel) {
    int dato_num;
    char dato[MAX_DATO];
    printf("Ingrese nº de defensores (%c) para nivel %i: ", tipo, nivel+1);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_defensa_inicial_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_DEFENSORES_INICIO);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    if (tipo==ENANOS) configuracion->enanos_inicio[nivel] = dato_num;
    else configuracion->elfos_inicio[nivel] = dato_num;
}

/*
 * Se pide al usuario ingresar el impacto que tendrá agregar un defensor de TIPO en cada torre.
 * Cada dato se almacenara en la configuración.
 */
void pedir_costo_defensores(configuracion_t *configuracion) {
    int dato_num;
    char dato[MAX_DATO];
    printf("Ingrese costo de %c para Torre %i: ", ENANOS, TORRE_UNO);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_resistencia_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_RESISTENCIA);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->costo_enanos_torre_1 = dato_num;
    printf("Ingrese costo de %c para Torre %i: ", ENANOS, TORRE_DOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_resistencia_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_RESISTENCIA);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->costo_enanos_torre_2 = dato_num;
    printf("Ingrese costo de %c para Torre %i: ", ELFOS, TORRE_UNO);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_resistencia_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_RESISTENCIA);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->costo_elfos_torre_1 = dato_num;
    printf("Ingrese costo de %c para Torre %i: ", ELFOS, TORRE_DOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_resistencia_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_RESISTENCIA);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->costo_elfos_torre_2 = dato_num;
}

/*
 * Se pide al usuario ingresar la probabilidad dar un ataque crítico para los defensores.
 * Se almacenará en la configuración.
 */
void pedir_critico(configuracion_t *configuracion) {
    int dato_num;
    char dato[MAX_DATO];
    printf("Ingrese porcentaje de criticidad de %c: ", ENANOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_critico_valido(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_CRITICO);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.critico_gimli = dato_num;
    printf("Ingrese porcentaje de criticidad de %c: ", ELFOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_critico_valido(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_CRITICO);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.critico_legolas = dato_num;
}

/*
 * Se pide al usuario ingresar la probabilidad de fallo de los defensores
 * Se almacenará en la configuración.
 */
void pedir_fallo(configuracion_t *configuracion) {
    int dato_num;
    char dato[MAX_DATO];
    printf("Ingrese porcentaje de fallo de %c: ", ENANOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_fallo_valido(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_FALLO);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.fallo_gimli = dato_num;
    printf("Ingrese porcentaje de fallo de %c: ", ELFOS);
    scanf("%s", dato);
    dato_num = atoi(dato);
    while (!es_fallo_valido(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %i y %i: ", INDEFINIDO, MAX_FALLO);
        scanf("%s", dato);
        dato_num = atoi(dato);
    }
    configuracion->juego.fallo_legolas = dato_num;
}

/*
 * Se pide al usuario ingresar el intervalo de tiempo entre turnos.
 * El valor se almacenará en la configuración.
 */
void pedir_velocidad(configuracion_t *configuracion) {
    double dato_num;
    char dato[MAX_DATO];
    printf("Ingrese tiempo entre turnos: ");
    scanf("%s", dato);
    dato_num = atof(dato);
    while (!es_velocidad_valida(dato_num)) {
        printf("Hubo un problema. Ingresa un valor entre %d y %f: ", INDEFINIDO, MAX_VELOCIDAD);
        scanf("%s", dato);
        dato_num = atof(dato);
    }
    configuracion->velocidad = (float) dato_num;
}

/*
 * Se pide al usuario ingresar el archivo donde se encuentran los caminos a utilizar.
 * Se guarda el nombre del archivo o INDEFINIDO si se desea usar el modo predeterminado
 * del juego, pero no se comprueba la existencia de dicho archivo ni si se tienen los permisos
 * para leerlo.
 */
void pedir_camino(configuracion_t *configuracion) {
    char dato[MAX_DATO];
    printf("Ingrese un camino: ");
    scanf("%s", dato);
    while (!hay_archivo(dato)) {
        printf("Hubo un problema. Probá nuevamente: ");
        scanf("%s", dato);
    }
    strcpy(configuracion->caminos, dato);
}

/*
 * Muestra en pantalla todos los mensajes para que el usuario pueda crear
 * una configuración nueva con valores válidos.
 */
void crear_configuracion(configuracion_t *configuracion) {
    pedir_resistencia_torres(configuracion);
    pedir_defensores_extras(configuracion);
    for (int i=0; i < MAX_NIVELES; i++)
        pedir_defensores_inicio(configuracion, ENANOS, i);
    for (int i=0; i < MAX_NIVELES; i++)
        pedir_defensores_inicio(configuracion, ELFOS, i);
    pedir_costo_defensores(configuracion);
    pedir_critico(configuracion);
    pedir_fallo(configuracion);
    pedir_velocidad(configuracion);
    pedir_camino(configuracion);
}

/*
 * Inicializa la configuración cuando no se ha leído un archivo de configuración.
 */
void inicializar_configuracion(configuracion_t *configuracion) {
    configuracion->juego.torres.resistencia_torre_1 = INDEFINIDO;
    configuracion->juego.torres.resistencia_torre_2 = INDEFINIDO;
    configuracion->juego.torres.enanos_extra = INDEFINIDO;
    configuracion->juego.torres.elfos_extra = INDEFINIDO;
    configuracion->juego.critico_gimli = INDEFINIDO;
    configuracion->juego.critico_legolas = INDEFINIDO;
    configuracion->juego.fallo_gimli = INDEFINIDO;
    configuracion->juego.fallo_legolas = INDEFINIDO;
    for (int i = 0; i < MAX_NIVELES; i++) {
        configuracion->enanos_inicio[i] = INDEFINIDO;
        configuracion->elfos_inicio[i] = INDEFINIDO;
    }
    configuracion->costo_enanos_torre_1 = INDEFINIDO;
    configuracion->costo_enanos_torre_2 = INDEFINIDO;
    configuracion->costo_elfos_torre_1 = INDEFINIDO;
    configuracion->costo_elfos_torre_2 = INDEFINIDO;
    configuracion->velocidad = INDEFINIDO;
    strcpy(configuracion->caminos, "-1");
}


/*
 * Pre: Recibe la configuración que se desee guardar y el nombre del archivo que se utilizará
 * Pos: Si el archivo no existe se creará. Si existe se sobreescribirá. En él se guardarán
 *      Los datos de la configuración recibida.
 */
void escribir_configuracion(configuracion_t configuracion, char config[MAX_ARCHIVO]) {
    FILE * archivo;
    juego_t juego;
    torres_t torres;
    archivo = fopen(config, ESCRITURA);
    if (!archivo) {
        printf("No estoy teniendo permisos suficientes para escribir.\n");
        return;
    }
    juego = configuracion.juego;
    torres = juego.torres;
    fprintf(archivo, RESISTENCIA_TORRES, torres.resistencia_torre_1, torres.resistencia_torre_2);
    fprintf(archivo, ENANOS_INICIO, configuracion.enanos_inicio[0], configuracion.enanos_inicio[1], configuracion.enanos_inicio[2], configuracion.enanos_inicio[3]);
    fprintf(archivo, ELFOS_INICIO, configuracion.elfos_inicio[0], configuracion.elfos_inicio[1], configuracion.elfos_inicio[2], configuracion.elfos_inicio[3]);
    fprintf(archivo, ENANOS_EXTRA, torres.enanos_extra, configuracion.costo_enanos_torre_1, configuracion.costo_enanos_torre_2);
    fprintf(archivo, ELFOS_EXTRA, torres.elfos_extra, configuracion.costo_elfos_torre_1, configuracion.costo_elfos_torre_2);
    fprintf(archivo, ENANOS_ANIMO, juego.fallo_gimli, juego.critico_gimli);
    fprintf(archivo, ELFOS_ANIMO, juego.fallo_legolas, juego.critico_legolas);
    fprintf(archivo, VELOCIDAD_CONFIG, configuracion.velocidad);
    fprintf(archivo, CAMINOS, configuracion.caminos);
    fclose(archivo);
}


/*
 * Pre: Recibe el nombre de un archivo de configuración que se desee leer o ninguno.
 * Pos: Inicializará la configuación con los datos que se hayan podido extraer del archivo.
 *      Los valores que no se hayan podido extraer del archivo, se inicializarán con los
 *      predeterminados.
 */
void cargar_configuracion(configuracion_t *configuracion, char config[MAX_ARCHIVO]) {
    FILE* archivo;
    inicializar_configuracion(configuracion);
    if (hay_archivo(config)) {
        archivo = fopen(config, LECTURA);
        if (!archivo) {
            printf("Probá con otra configuración.\n");
            return;
        }
        /*
         * buscar etiquetas en el archivo. escanear y definir los valores
         */
        fclose(archivo);
    }
}