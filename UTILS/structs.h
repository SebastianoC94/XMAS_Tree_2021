#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef enum
{
  TO_MINIMUM = 0,
  TO_MAXIMUM = 1
}DIRECTION;

typedef enum
{
  NORMAL_SPEED = 1,
  DOUBLE_SPEED = 2,
  TRIPLE_SPEED = 3
}LED_CHANGE_SPEED;

typedef struct
{
  uint8_t num_slots_on_array;
  DIRECTION direction;
  LED_CHANGE_SPEED speed;
}LED_Descr;

typedef struct
{
  LED_Descr descr[NUM_LED_USED];
}LED_Manager;

#endif // __STRUCTS_H__