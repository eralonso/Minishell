#include "stdio.h"
#include "unistd.h"
#include "limits.h"

int main(void)
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("\n\nThe actual directory is: %s\n", path);
	return (0);
}
