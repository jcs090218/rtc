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
 * @func rtc_create_cnd
 * @brief Create command instruction file.
 * @return { int } : error code.
 */
int rtc_create_cnd(void) {
    int result = jcs_simple_download_file_from_url(
        RTC_COMMAND_URL,
        RTC_COMMAND_OUTPUT);
    return result;
}

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

    int result = rtc_create_cnd();
    if (result != JCS_NO_ERROR) {
        jcs_error("Cannot download the command file..");
    }
}

/**
 * @func rtc_print_inc
 * @brief Print command instructions.
 */
void rtc_print_inc(void) {
    bool succes = jcs_print_file("./.rtc/rtc_cnd.jcs");

    if (!succes) {
        /* Download file. */
        int result = rtc_create_cnd();

        jcs_println("Result: %d", result);

        if (result == JCS_NO_ERROR) {
            jcs_error("Cannot download the command file.");
        } else {
            /* Try print the inc again. */
            rtc_print_inc();
        }
    }
}

/**
 * @func rtc_print_ver
 * @brief Function description here..
 */
void rtc_print_ver(void) {
    jcs_println("rtc version " RTC_MAJOR_VER ".gcc." RTC_MINOR_VER);
}

/**
 * @func rtc_process_command
 * @brief Process RTC commands.
 * @param { int } commandc : command count.
 * @param { char } commands : command vector.
 */
void rtc_process_command(int commandc, char *commands[]) {
    char *first_command;

    if (!jcs_is_safe_command(commandc, 1)) {
        rtc_init();
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
    }
    /* Commands that need inittialize before we run it. */
    else if (jcs_dir_exists(RTC_INIT_DIR)) {

        if (jcs_strcmp(first_command, "start_server")) {
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
