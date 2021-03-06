#ifndef __TEST4_H
#define __TEST4_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "i8042.h"
#include "i8254.h"



int timer_subscribe_int(void);
int timer_unsubscribe_int();
int mouse_subscribe_int(void);
int mouse_unsubscribe_int();
unsigned long kbd_read();
int kbd_send_command(unsigned long cmd);
int kbd_send(unsigned long cmd) ;
int mouse_send(unsigned long cmd);

/** @defgroup test4 test4
 * @{
 *
 * Functions for testing the kbd code
 */

/** 
 * @brief To test packet reception via interrupts 
 * 
 * Displays the packets received from the mouse
 * Exits after receiving the number of packets received in argument
 * 
 * @param cnt Number of packets to receive and display before exiting
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int test_packet(unsigned short cnt);

/** 
 * @brief To test handling of more than one interrupt
 * 
 *  Similar test_packet() except that it 
 *  should terminate if no packets are received for idle_time seconds
 * 
 * @param idle_time Number of seconds without packets before exiting
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int test_async(unsigned short idle_time);

/** 
 * @brief To test reading and parsing of configuration
 * 
 *  Reads mouse configuration and displays it in a human-friendly way
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int test_config(void);


/** 
 * @brief To test state machine implementation
 * 
 *  Similar test_packet() except that it 
 *  should terminate if user moves the mouse continuously 
 *    with a positive slope
 * 
 * @param length minimum length of movement (mouse units)
 *  in the y-direction. If positive, upwards movement, otherwise r
 *  downwards.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

typedef enum {
	INIT, DRAW, COMP
} state_t;
typedef enum {
	RDOWN, RUP, MOVE
} ev_type_t;

typedef struct {
	state_t state;
	ev_type_t type;
} event_t;

int test_gesture(short length);
void check_state(event_t *evt, unsigned int negative, long deltax, long deltay, short length);

#endif /* __TEST_4.H */
