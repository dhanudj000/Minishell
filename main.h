#ifndef MAIN
#define MAIN
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ext_cmd.h"
#include "int_cmd.h"
#include "check_cmd.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include "linked_list.h"
#include "npipes.h"
#include "fg_bg.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define CLEAR 	"\e[1;1H\e[2J"

#define EXT_CMD 1
#define INT_CMD 2
#define CMD_NOT_FOUND 0

#endif
