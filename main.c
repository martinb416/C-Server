/*
 * Main program file. Handles startup, service initialization,
 * and shutdown commands
 *
 * Author: Martin Buitrago
 * 2018
*/

#include <stdlib.h>
#include <stdio.h>
#include <argp.h>
#include <signal.h>
#include <string.h>

#define DEF_PORT 6969

/****************************************
* ARGP global variables and definitions *
****************************************/
const char *argp_program_version = "C-Server 0.01";
const char *argp_program_bug_address = "<fake@martin.sexy>";


/* Program description */
static char argp_prog_desc[] = "I don't know yet...";
/* A description of the arguments accepted. */
static char args_doc[] = "";


/* The options we understand. */
static struct argp_option options[] = {
	{"verbose",	'v', 0, 0, "Produce verbose output" },
	{"quiet",	'q', 0, 0, "Don't produce any output" },
	{"silent",	's', 0, OPTION_ALIAS },
	{"port",	'p', "PORT", 0, "Bind to given port (Default: 6969)"},
	{ 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments{
	int silent,
		verbose,
		port;
};

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state){
	struct arguments *arguments = state->input;

	switch (key){
		case 'q': case 's':
			arguments->silent = 1;
			break;
		case 'v':
			arguments->verbose = 1;
			break;
		case 'p':
			arguments->port = atoi(arg);
			if(arguments->port < 1025 || arguments->port > 65535){
				printf("Invalid port number, defaulting to %d\n", DEF_PORT);
				arguments->port = DEF_PORT;
			}
			break;
		case ARGP_KEY_ARG:
		case ARGP_KEY_END:
			// if (state->arg_num < 2) /* Not enough arguments. */
			// argp_usage (state);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp ={options, parse_opt, args_doc, argp_prog_desc};


/****************************
* Signal handler overwrites *
****************************/
void sigint_handler(int sig){
	printf("%s\n", "\nCaught sigint, Exiting NOW!");
	exit(0);
}

// SIGNWINCH -- TODO (maybe)

/***********************
* Enter program here! *
***********************/

int main(int argc, char *argv[]){
	struct arguments arguments;

	signal(SIGINT, sigint_handler);

	arguments.silent = 0;
	arguments.verbose = 0;
	arguments.port = DEF_PORT;

	argp_parse (&argp, argc, argv, 0, 0, &arguments);
	

	return 0;
}