/**
 * @file EXTI_cfg.h
 * @author Amgad Samir
 * @brief This file configures the EXTI module in prebuilt configuration method
 * @version 1.00
 */

#ifndef EXTI_CFG_H_
#define EXTI_CFG_H_


/**
 * @details configure the INT0 sense control, options are: 1- EXTI_u8LOW_LEVEL
 * 														   2- EXTI_u8ON_CHANGE
 * 														   3- EXTI_u8FALLING_EDGE
 * 														   4- EXTI_u8RISING_EDGE
 */
#define INT0_SENSE_CTRL				EXTI_u8FALLING_EDGE

/**
 * @details configure the INT0 initial state, options are: 1- ENABLED
 * 														   2- DISABLED
 */
#define INT0_INITIAL_STATE			ENABLED

/**
 * @details configure the INT1 sense control, options are: 1- EXTI_u8LOW_LEVEL
 * 														   2- EXTI_u8ON_CHANGE
 * 														   3- EXTI_u8FALLING_EDGE
 * 														   4- EXTI_u8RISING_EDGE
 */
#define INT1_SENSE_CTRL				EXTI_u8FALLING_EDGE

/**
 * @details configure the INT1 initial state, options are: 1- ENABLED
 * 														   2- DISABLED
 */
#define INT1_INITIAL_STATE			ENABLED

/**
 * @details configure the INT2 sense control, options are: 1- EXTI_u8FALLING_EDGE
 * 														   2- EXTI_u8RISING_EDGE
 */
#define INT2_SENSE_CTRL				EXTI_u8FALLING_EDGE

/**
 * @details configure the INT2 initial state, options are: 1- ENABLED
 * 														   2- DISABLED
 */
#define INT2_INITIAL_STATE			ENABLED




#endif
