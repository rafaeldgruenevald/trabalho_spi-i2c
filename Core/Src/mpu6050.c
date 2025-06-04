/*
 * mpu6050.c
 *
 *  Created on: May 20, 2025
 *      Author: rafae
 */
#include <main.h>
#include <stdio.h>
#include <math.h>
#include <mpu6050.h>

extern I2C_HandleTypeDef hi2c1;
/*
 * Inicia o periferico mpu6050, checando se o mesmo esta pronto
 * configurando o giroscopio, acelerometro e se certificando de
 * que estamos fora do modo de descanco.
 * Os registradores, endresso do dispositivo e outras informacoes
 * foram retiradas do datasheet e mapa de registradores.
 *
 * Links:
 * - https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
 * - https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 */
void mpu6050_init() {
	HAL_StatusTypeDef err = HAL_I2C_IsDeviceReady(&hi2c1,
			(DEVICE_ADDRESS << 1) + 0,
			1, 100);
	if (err != HAL_ERROR) {
		printf("Dispositivo conectado e pronto! \n");
	}

	uint8_t tempData = FS_GYRO_500;
	err = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS << 1) + 0, REG_CONFIG_GYRO,
			1, &tempData, 1,
			100);
	if (err != HAL_ERROR) {
		printf("Configurando giroscopio \n");
	}

	tempData = FS_ACC_4G;
	err = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS << 1) + 0, REG_CONFIG_ACC,
			1, &tempData, 1, 100);
	if (err != HAL_ERROR) {
		printf("Configurando acelerometro \n");
	}

	tempData = 0;
	err = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS << 1) + 0, REG_USR_CTRL, 1,
			&tempData, 1, 100);
	if (err != HAL_ERROR) {
		printf("Saindo do modo de descanco \n");
	}
}
/*
 * Le o eixo X e transforma de maneira linear os pontos para o equivalente
 * do display. Para uso mais preciso eh necessario inicialmente rodar o codigo
 * e encontrar o ponto zero, ponto maximo e minimo. O valor retornado ja esta
 * pronto para ser colocado no display.
 */
uint16_t mpu6050_read_x() {
	uint8_t data[2];
	int16_t x_acc;
	uint16_t x_disp;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_EIXO_X, 1, data, 2,
			100);
	x_acc = ((int16_t) data[0] << 8) + data[1];
	x_acc = (int16_t) (((x_acc + SET_ZERO_POINT_X) * 1000.0 / FS_ACC_4G)
			/ 1000.0);
	printf("ponto x acelerometro = %d \n", x_acc);
	x_disp = ((((x_acc * -1) - MIN_POINT_X) * (128 - 0))
			/ (MAX_POINT_X - MIN_POINT_X)
			+ 0);
	printf("ponto x filtrado= %d \n", x_disp);
	// max_esquerda = -1000; max_direita = 950;
	return x_disp;
}
/*
 * Le o eixo Y e transforma de maneira linear os pontos para o equivalente
 * do display. Para uso mais preciso eh necessario inicialmente rodar o codigo
 * e encontrar o ponto zero, ponto maximo e minimo. O valor retornado ja esta
 * pronto para ser colocado no display.
 */
uint16_t mpu6050_read_y() {
	uint8_t data[2];
	int16_t y_acc;
	uint16_t y_disp;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_EIXO_Y, 1, data,
			2, 100);
	y_acc = ((int16_t) data[0] << 8) + data[1]; // max_frente = 950; max_tras = -800;
	y_acc = (int16_t) (((y_acc + SET_ZERO_POINT_Y) * 1000.0 / FS_ACC_4G)
			/ 1000.0);
	printf("ponto y acelerometro = %d \n", y_acc);
	y_disp = (((y_acc - MIN_POINT_Y) * (160 - 0)) / (MAX_POINT_Y - MIN_POINT_Y)
			+ 0);
	printf("ponto y filtrado= %d \n", y_disp);
	return y_disp;
}


