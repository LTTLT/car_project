#ifndef __MOTOR_DATA_H__
#define __MOTOR_DATA_H__
#include "wcnm.h"
#include "struct_typedef.h"
typedef struct
{
	fp32 v[4];
	fp32 speed_set[4];
	
} motor_data;


extern const  motor_data *get_chassis_data_point(void);
#endif
