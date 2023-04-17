#include "SparkFun_LIS331.h"

//Set high enough to allow for G forces at top RPM
//LOW_RANGE - +/-100g for the H3LIS331DH
//MED_RANGE - +/-200g for the H3LIS331DH
//HIGH_RANGE - +/-400g for the H3LIS331DH
#define ACCEL_RANGE LIS331::HIGH_RANGE   

//Set to correspond to ACCEL_RANGE
#define ACCEL_MAX_SCALE 400

void init_accel();

float get_accel_force_g();

