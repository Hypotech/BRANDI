#ifndef ANIMACION_HPP
#define ANIMACION_HPP

#ifdef __WINDOWS__
#include <windows.h>
#endif

#include <GL/freeglut.h>

/**
 *@def DEF_floorGridScale
 *@brief Especifica la escala de la rejilla
 *@def DEF_floorGridXSteps
 *@brief Especifica el tamaño de los cuadros en el eje x
 *@def DEF_floorGridZSteps
 *@brief Especifica el tamaño de los cuadros en el eje z
 */

/* Constantes simbolicas que determinan
 * el tamanio y proporcion del piso*/
#define DEF_floorGridScale	4.0
#define DEF_floorGridXSteps	10.0
#define DEF_floorGridZSteps	10.0
//###################################//

#define PI 3.1416

void config_Simulador(const int);

void initLuz(); //inicializa la luz
void Escenario(); //crea los solidos que recrean brandi asi como el ambiente alrededor
void VentCambios(int w, int h); //comportamiento al redimensionar la ventana o maximizar.
void controlaTeclasEspec(int key,int x, int y); //respuesta a las teclas presionadas
void circulo(); //funcion de utilidad para dibujar circulos
void DibujarRotor(GLfloat separacion, const GLfloat *const ColorMater,GLfloat angulo); //funcion de utilidad para dibujar 2 circulos que simulan ser los rotores
void limitar_Motores(void);

#endif
