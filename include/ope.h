#ifndef __OPE_H__
/**
 * $File: ope.h $
 * $Date: 2017-12-12 03:03:40 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2017 by Shen, Jen-Chieh $
 */
#define __OPE_H__


/**
 * @func rtc_init
 * @brief Initialize the RTC application.
 */
void rtc_init(void);

/**
 * @func rtc_print_inc
 * @brief Print command instructions.
 */
void rtc_print_inc(void);

/**
 * @func rtc_print_ver
 * @brief Function description here..
 */
void rtc_print_ver(void);

/**
 * @func rtc_status
 * @brief RTC status command.
 */
void rtc_status(void);

/**
 * @func rtc_start_server
 * @brief Start RTC server.
 * @param { int } commandc : command count.
 * @param { char } commands : command vector.
 */
void rtc_start_server(int commandc, char *commands[]);

/**
 * @func rtc_connect
 * @brief Connect to a RTC server.
 * @param { int } commandc : command count.
 * @param { char } commands : command vector.
 */
void rtc_connect(int commandc, char *commands[]);

/**
 * @func rtc_disconnect
 * @brief Disconnect from the RTC server.
 */
void rtc_disconnect(void);

#endif /* __OPE_H__ */
