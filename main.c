/* fetch written in C for OpenBSD and Linux eventually  */
/* thanks to https://github.com/rbaylon/bsdsplash for the default ascii art */
/* to compile do 'doas make install' and run 'cof' */
/* deps - a shell, awk , free, uname, grep */
#include <stdio.h>
#include <stdlib.h>

/* change to where your ascii image is */
#define PATH "/home/will/.config/cfetch/conf"
#define MODC 7 

#ifdef __OpenBSD__
char *cmds[7] = 
{
	"uname -nm",
	"sysctl -n hw.model",
	"uname -sr",
	"echo $SHELL",
	"uname -v",
	"uptime |awk '{print $3 $4}'",
	"sysctl -n hw.physmem",	
};
#endif

#ifdef __linux
char *cmds[7] = 
{
	"uname -nmi",
	"uname -p",
	"uname -o",
	"echo $SHELL",
	"uname -r",
	"uptime |awk '{print $3}'",
	"free | grep Mem | awk '{print $2}'",	
};
#endif

char *type[7] =
{
	"NAME",
	"CPU",
	"OS",
	"SHELL",
	"KERNEL",
	"UPTIME",
	"MEMORY BYTES",
};

static void
clean(char *string, FILE *pipe)
{
	free(string);
	pclose(pipe);
} 

static void
ascii(void)
{
	FILE *art;
	char read[1024];
	if((art = fopen(PATH, "r")) == NULL)
	{
		printf("check image path\n");
		exit(1);
	}else
	{
		while(fgets(read, sizeof(read), art) != NULL)
			printf("%s", read);

		fclose(art);
	}
}

static void
open_pipe(char *cmd, char *type)
{
	FILE *pipe;
	char *part;
	pipe = popen(cmd, "r");
	part = malloc(1024);
	fgets(part, 1024, pipe);
	printf("%s - %s", type, part);
	clean(part, pipe);
} 

int
main(void)
{
	ascii();
	for(int i = 0; i != MODC; i++)
		open_pipe(cmds[i], type[i]);
	return 0;	
}
