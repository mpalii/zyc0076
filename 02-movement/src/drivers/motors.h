#ifndef MOTORS_H_
#define MOTORS_H_

#include <stdint-gcc.h>

void motors_init(void);
void set_speed(uint8_t speed);
void set_direction(uint8_t direction);

#endif /* MOTORS_H_ */