#include "Error/error.h"
#include <unistd.h>

int print_error(const char *message)
{
	write(STDERR_FILENO, message, sizeof(message));
	return (1);
}