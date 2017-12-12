/**
 * $File: main.c $
 * $Date: 2017-12-03 12:07:45 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../rtc.h"


/**
 * @func rtc_process_command
 * @brief Process RTC commands.
 * @param { int } commandc : command count.
 * @param { char } commands : command vector.
 */
void rtc_process_command(int commandc, char *commands[]) {
    char *first_command;

    if (!jcs_is_safe_command(commandc, 1)) {
        rtc_print_inc();
        return;
    }

    first_command = commands[1];

    if (jcs_strcmp(first_command, RTC_CMD_INIT)) {
        rtc_init();
    } else if (jcs_strcmp(first_command, RTC_CMD_VERSION_CHECK)) {
        rtc_print_ver();
    } else if (jcs_strcmp(first_command, RTC_CMD_HELP)) {
        rtc_print_inc();
    } else if (jcs_dir_exists(RTC_INIT_DIR)) {
        /* Commands that need inittialize before we run it. */
        if (jcs_strcmp(first_command, RTC_CMD_STATUS)) {
            rtc_status();
        } else if (jcs_strcmp(first_command, RTC_CMD_START_SERVER)) {
            rtc_start_server(commandc, commands);
        } else if (jcs_strcmp(first_command, RTC_CMD_CONNECT)) {
            rtc_connect(commandc, commands);
        } else if (jcs_strcmp(first_command, RTC_CMD_DISCONNECT)) {
            rtc_disconnect();
        } else {
            jcs_error("You should initialize init before using RTC serivce..");
        }
    } else {
        jcs_error("No command listed...");
        rtc_print_inc();
    }

}

/**
 * @func main
 * @brief Program entry point.
 * @param { int } argc : argument count.
 * @param { char } argv : argument vector.
 * @return { int } : 0, exit success. 1, exit failure.
 */
int main(int argc, char *argv[]) {
    rtc_process_command(argc, argv);


    /* --------------- */
    return 0;
}
