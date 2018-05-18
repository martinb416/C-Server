#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/poll.h>
#include <unistd.h>

#define LOCALHOST	"127.0.0.1"
#define DEF_PORT	"6969"

void *run_server(void *port);