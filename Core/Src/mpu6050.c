/*
 * mpu6050.c
 *
 *  Created on: May 20, 2025
 *      Author: rafae
 */
#include <mpu6050.h>
#include <main.h>
#include <stdio.h>
#include <math.h>

extern I2C_HandleTypeDef hi2c1;

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

int16_t mpu6050_read_x() {
	uint8_t data[2];
	int16_t x_acc, x_disp;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_EIXO_X, 1, data, 2,
			100);
	x_acc = ((int16_t) data[0] << 8) + data[1];
	x_disp = (int) ((128 / 16200.0) * (x_acc + 8200));
	printf("ponto x acelerometro = %d \n", x_acc);
	printf("ponto x display = %d \n", x_disp); // max_esquerda = 8100; max_direita = -8100;
	return x_acc;
}

int16_t mpu6050_read_y() {
	uint8_t data[2];
	int16_t y_acc, y_disp;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_EIXO_Y, 1, data,
			2, 100);
	y_acc = ((int16_t) data[0] << 8) + data[1]; // max_frente = -8100; max_tras = 8100;
	y_acc += SET_ZERO_POINT_Y;
	y_disp = (int) ((8 / 810.0) * (y_acc + 8200));
	printf("ponto y acelerometro = %d \n", y_acc);
	printf("ponto y display = %d \n", y_disp);
	return y_acc;
}


