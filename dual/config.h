/*
 * config.h
 *
 *  Created on: 2018. 5. 15.
 *      Author: kny
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* Configuration of tty-tetris
 * Need to re-compile to set the change.
 */

/* Move the shape */
#define KEY_MOVE_LEFT  'D'
#define KEY_MOVE_RIGHT 'C'
#define KEY_MOVE_DOWN 'B'

/* Change the shape position */
#define KEY_CHANGE_POSITION_NEXT 'A'

/* ' ' for space key */
#define KEY_DROP_SHAPE ' '

/* Other key */
#define KEY_PAUSE 'p'
#define KEY_QUIT  'q'

/* Timing in milisecond */
#define TIMING 300000

#endif /* CONFIG_H_ */
