#ifndef _TRACKINGKINECT_HPP_
#define _TRACKINGKINECT_HPP_

/**
 * @brief constante pi con 3 decimales de precición
 */
#define PI 3.1416

/**
 * @brief Define una estructura para almacenar coodenadas 2-D
 * @details Solo permite almacenar valores enteros de coordenas.
 */
typedef struct
{
	int x, y;
}coordenada2D;

int GetKinectFrame();
void gotoxy(int,int);
void ini_Kinect(void);

void ModificarVentana(int,int);
coordenada2D Convertir_a_espacio_80x25(LONG, LONG);
float Convierte_a_Angulo(const coordenada2D, const coordenada2D);

void Libera_Kinect();

#endif /* _TKINECT_HPP_ */
