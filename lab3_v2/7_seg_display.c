/*
 * 7_seg_display.c
 *
 *  Created on: Sep 22, 2021
 *      Author: ngocc
 */
#include "main.h"
#include "7_seg_display.h"



static int Led7Buffer[NO_OF_LED7] = {0,0,0,0};
static int currentLED = 0;
static uint8_t displayData[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D
								,0x7D, 0X07, 0X7F, 0X6F};

//this function display value on a 7-seg LED
void display7SEG(int value) {
	uint8_t temp = displayData[value];
	for(int i = 0; i < 7; i++) {
		if (temp % 2 == 1) {
			HAL_GPIO_WritePin(PORT_USED_DISPLAY, START_PIN << i, TURN_ON_SEGMENT);
		} else {
			HAL_GPIO_WritePin(PORT_USED_DISPLAY, START_PIN << i, TURN_OFF_SEGMENT);
		}
		temp = temp >> 1;
	}
}

//this function choose a 7-seg LED among multiple LED to turn on.
void scanLED() {
	//turn off all LED
	for(int i = 0; i < NO_OF_LED7; i++) {
		HAL_GPIO_WritePin(PORT_ENABLE, START_ENABLE_PIN << i, DISABLE_LED);
	}
	//update LED value
	display7SEG(Led7Buffer[currentLED]);
	//turn that LED on
	HAL_GPIO_WritePin(PORT_ENABLE, START_ENABLE_PIN << currentLED, ENABLE_LED);

	currentLED = (currentLED + 1) % NO_OF_LED7;
}

//this function update Buffer. this buffer will be showed on all LEDs
void updateBuffer(int value1, int value2) {
	Led7Buffer[0] = value1/10;
	Led7Buffer[1] = value1%10;
	Led7Buffer[2] = value2/10;
	Led7Buffer[3] = value2%10;

}