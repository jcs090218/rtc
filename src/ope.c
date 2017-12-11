/**
 * $File: ope.c $
 * $Date: 2017-12-12 03:03:02 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2017 by Shen, Jen-Chieh $
 */

#include "../rtc.h"


/**
 * @func rtc_init
 * @brief Initialize the RTC application.
 */
void rtc_init(void) {
    bool reinit = jcs_safe_remove_dir_recursive(RTC_INIT_DIR);

    jcs_safe_create_dir(RTC_INIT_DIR, RTC_DIR_MODE);

    char currentDir[PATH_MAX];
    jcs_get_current_dir(currentDir, sizeof(currentDir));

    if (!reinit) {
        jcs_println(
            "Initialize empty RTC repository in %s/.rtc/",
            currentDir);
    } else {
        jcs_println(
            "Reinitialized existing RTC repository in %s/.rtc/",
            currentDir);
    }
}

/**
 * @func rtc_print_inc
 * @brief Print command instructions.
 */
void rtc_print_inc(void) {
    jcs_print_file("./rtc_cnd.jcs");
}

/**
 * @func rtc_print_ver
 * @brief Function description here..
 */
void rtc_print_ver(void) {
    jcs_println("rtc version " RTC_MAJOR_VER ".gcc." RTC_MINOR_VER);
}

/**
 * @func rtc_status
 * @brief RTC status command.
 */
void rtc_status(void) {

}
