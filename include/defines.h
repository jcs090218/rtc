#ifndef __DEFINES_H__
/**
 * $File: defines.h $
 * $Date: 2017-12-03 12:09:50 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2017 by Shen, Jen-Chieh $
 */
#define __DEFINES_H__


#include <stdint.h>

/* RTC Configuration */
#define RTC_MAJOR_VER "1.0.0"
#define RTC_MINOR_VER "1"
#define RTC_INIT_DIR "./.rtc"

#define RTC_COMMAND_URL "http://www.jcs-profile.com/public/rtc/rtc_cnd.jcs"
#define RTC_COMMAND_OUTPUT "./.rtc/rtc_cnd.jcs"

#define RTC_MAX_CONN 30


/**
 * @def RTC_FILE_MODE
 * @brief File mode number when create file.
 */
#define RTC_FILE_MODE 0700

/**
 * @def RTC_DIR_MODE
 * @brief File mode number when create directory.
 */
#define RTC_DIR_MODE 0700

#endif /* __DEFINES_H__ */
