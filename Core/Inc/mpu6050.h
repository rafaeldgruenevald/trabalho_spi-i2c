/*
 * mpu6050.h
 *
 *  Created on: May 20, 2025
 *      Author: rafae
 */

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

#define SET_ZERO_POINT_Y 3800
#define SET_ZERO_POINT_X 3000

void mpu6050_init();
int16_t mpu6050_read_x();
int16_t mpu6050_read_y();
#endif /* INC_MPU6050_H_ */
