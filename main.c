/*
 * Main program file. Handles startup, service initialization,
 * and shutdown commands
 *
 * Author: Martin Buitrago
 * 2018
*/

#include <argp.h>
#include <signal.h>
#include <pthread.h>

#include "common.h"
#include "server.h"

#define IP_LEN		46 // IPV4 mapped to IPV6, plus null terminator

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
	{"address", 'a', "ADDR", 0, "Address to bind (Default: 127.0.0.1)"},
	{ 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments{
	char ip[IP_LEN];
	char *port;
	int silent,
		verbose;
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
		case 'p': // TODO: Clean this to protect against attacks (e.g. NOP)
			if(atoi(arg) < 1025 || atoi(arg) > 65535)
				printf("Invalid port number, defaulting to %s\n", DEF_PORT);
			else
				arguments->port = arg;
			break;
		case 'a':
			if(1){
				printf("Not sure this would make sense");
			}
			break;
		case ARGP_KEY_ARG:
		case ARGP_KEY_END:
			if(!arguments->port)
				arguments->port = DEF_PORT;
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
	pthread_t server_thread;

	signal(SIGINT, sigint_handler);

	memset(&arguments, 0, sizeof(struct arguments));
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	// Cast port string as void pointer for pthread
	pthread_create(&server_thread, 0, run_server, (void*)arguments.port);

	while(1){
		//Something
	}

	return 0;
}