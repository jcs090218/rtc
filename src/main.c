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

    if (jcs_strcmp(first_command, "init")) {
        rtc_init();
    } else if (jcs_strcmp(first_command, "--version")) {
        rtc_print_ver();
    } else if (jcs_strcmp(first_command, "--help")) {
        rtc_print_inc();
    } else if (jcs_dir_exists(RTC_INIT_DIR)) {
        /* Commands that need inittialize before we run it. */
        if (jcs_strcmp(first_command, "status")) {
            rtc_status();
        } else if (jcs_strcmp(first_command, "start_server")) {
            if (!jcs_is_safe_command(commandc, 2) ||
                !jcs_is_safe_command(commandc, 3)) {
                jcs_error("start_server should start with"
                          "%hostname% and %port%.");
                return;
            }

            char *hostname = commands[2];
            char *port = commands[3];

            jcs_println("Starting server...");
            jcs_println("Hostanem: %s", hostname);
            jcs_println("Port: %s", port);

            if (!jcs_is_valid_ip_address(hostname)) {
                jcs_error("Invalid IP/Hostname..");
                return;
            }

            int real_port = atoi(port);

        } else if (jcs_strcmp(first_command, "close_server")) {

        } else if (jcs_strcmp(first_command, "connect")) {

        } else if (jcs_strcmp(first_command, "disconnect")) {

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
