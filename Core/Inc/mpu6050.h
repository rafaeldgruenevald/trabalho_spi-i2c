/*
 * mpu6050.h
 *
 *  Created on: May 20, 2025
 *      Author: rafae
 */
#include <stdint.h>

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#define DEVICE_ADDRESS 	0x68

#define FS_GYRO_250 	0
#define FS_GYRO_500 	8
#define FS_GYRO_1000 	9
#define FS_GYRO_2000 	10

#define FS_ACC_2G 	0
#define FS_ACC_4G 	8
#define FS_ACC_8G 	9
#define FS_ACC_16G 	10

#define REG_CONFIG_GYRO 27
#define REG_CONFIG_ACC 	28
#define REG_USR_CTRL 	107
#define REG_EIXO_X 		59
#define REG_EIXO_Y 		61

#define SET_ZERO_POINT_Y 3900
#define SET_ZERO_POINT_X -300
#define MAX_POINT_X 	 800
#define MIN_POINT_X 	 -1000
#define MAX_POINT_Y 	 800
#define MIN_POINT_Y 	 -1000

void mpu6050_init();
uint16_t mpu6050_read_x();
uint16_t mpu6050_read_y();
#endif /* INC_MPU6050_H_ */
