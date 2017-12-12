/**
 * $File: ope.c $
 * $Date: 2017-12-12 03:03:02 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright © 2017 by Shen, Jen-Chieh $
 */

#include "../rtc.h"


PRIVATE void rtc_recieve_command(char *command) {
    if (jcs_kbhit())
        gets(command);
}

PRIVATE bool rtc_is_exit_command(char *command) {
    return (jcs_strcmp(command, "rtc " RTC_CMD_CLOSE_SERVER) ||
            jcs_strcmp(command, "exit"));
}

PRIVATE void rtc_proces_server_command(char *command) {
    if (jcs_strcmp(command, "rtc " RTC_CMD_CLOSE_SERVER) ||
        jcs_strcmp(command, "exit")) {
        /* NOTE(jenchieh): nothing for close command */
    } else {
        if (!jcs_strcmp(command, "")) {
            jcs_warning("Invalid server command..");
        }
    }
}

/**
 * @func rtc_server_loop
 * @brief Do server logic here..
 * @param { int } serverfd : socket descriptor.
 */
PRIVATE void rtc_server_loop(int server_fd) {
    int clientfd;

    struct sockaddr_in client_addr;
    int addrlen = sizeof(client_addr);

    clientfd = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);

    if (clientfd)
        close(clientfd);
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

/**
 * @func rtc_start_server
 * @brief Start RTC server.
 * @param { int } commandc : command count.
 * @param { char } commands : command vector.
 */
void rtc_start_server(int commandc, char *commands[]) {
    if (!jcs_is_safe_command(commandc, 2)) {
        jcs_error("start_server should start with and 'port'.");
        return;
    }

    char *port = commands[2];

    jcs_println("Starting server...");
    jcs_println("Port: %s", port);


    int real_port = atoi(port);

    int server_fd = jcs_create_server(real_port, true, RTC_MAX_CONN);
    if (!server_fd)
        return;

    while (true) {
        char temp_command[32] = "";
        rtc_recieve_command(temp_command);

        /* First check exit. */
        if (rtc_is_exit_command(temp_command))
            break;

        rtc_proces_server_command(temp_command);

        rtc_server_loop(server_fd);
    }

    close(server_fd);
}

/**
 * @func rtc_connect
 * @brief Connect to a RTC server.
 * @param { int } commandc : command count.
 * @param { char } commands : command vector.
 */
void rtc_connect(int commandc, char *commands[]) {

}

/**
 * @func rtc_disconnect
 * @brief Disconnect from the RTC server.
 */
void rtc_disconnect(void) {

}
