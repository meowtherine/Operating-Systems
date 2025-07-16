#include "framebuffer.h"  // for fb_write_char, fb_write_string, fb_clear_screen
#include "string.h"       // for strtok, strcmp
#include "keyboard.h"     // for keyboard_getchar, readline
#ifndef __cplusplus
typedef enum { false = 0, true = 1 } bool;
#endif
#define NULL ((void*)0)
#define MAX_INPUT_LENGTH 128

struct command {
    const char* name;
    void (*function)(char* args);
};

// Forward declarations of command functions
void cmd_echo(char* args);
void cmd_clear(char* args);
void cmd_help(char* args);
void cmd_version(char* args);
void cmd_shutdown(char* args);

// Command list
struct command commands[] = {
    {"echo", cmd_echo},
    {"clear", cmd_clear},
    {"help", cmd_help},
    {"version", cmd_version},
    {"shutdown", cmd_shutdown},
    {NULL, NULL} 
};
void cmd_echo(char* args) {
    if (args) {
        fb_write_string(args);
    }
    fb_write_char('\n');
}

void cmd_clear(char* args) {
    (void)args; 
    fb_clear();
}

void cmd_help(char* args) {
    (void)args; 
    fb_write_string("Available commands:\n");
    for (int i = 0; commands[i].name != NULL; i++) {
        fb_write_string(" - ");
        fb_write_string(commands[i].name);
        fb_write_char('\n');
    }
}

void cmd_version(char* args) {
    (void)args; // unused
    fb_write_string("MyOS version 0.1\n");
}

void cmd_shutdown(char* args) {
    (void)args; // unused
    fb_write_string("Shutting down...\n");
    // TODO: Add shutdown procedure here
}
void terminal_run() {
    char input[MAX_INPUT_LENGTH];

    while (true) {
        fb_write_string("myos> ");  

        int len = readline(input, MAX_INPUT_LENGTH);
        if (len <= 0) {
            continue; 
        }

        char* command = strtok(input, " ");
        char* args = strtok(NULL, ""); 

        if (!command) {
            continue;
        }

        bool found = false;
        for (int i = 0; commands[i].name != NULL; i++) {
            if (strcmp(command, commands[i].name) == 0) {
                commands[i].function(args);
                found = true;
                break;
            }
        }

        if (!found) {
            fb_write_string("Unknown command: ");
            fb_write_string(command);
            fb_write_char('\n');
        }
    }
}
