/* fetch written in C for OpenBSD and Linux eventually  */
/* thanks to https://github.com/rbaylon/bsdsplash for the default ascii art */
/* to compile do 'doas make install' and run 'cof' */
/* deps - a shell, awk */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* change to where your ascii image is */
#define PATH "/home/will/.config/cfetch/conf"
#define MODC 7 

#ifdef __OpenBSD__ 
#define NAME "sysctl -n hw.vendor"
#define CPU "sysctl -n hw.model"
#define MEM "sysctl -n hw.physmem"
#endif

/* No Linux support yet 
* will do this tomorrow :-)*/
#ifdef __linux
#define NAME "NAME"
#define CPU "CPU"
#define MEM "MEM"
#endif

#define UPTIME "uptime |awk '{print $3}'"
#define SHELL "echo $SHELL"
#define OS "uname -a"

char *part, *string;
char read[1024];

FILE *pipe, *art;


static void
clean(char *string, FILE *pipe)
{
	free(string);
	pclose(pipe);
} 

static void
print(const char *type, const char *string)
{
	/* im lazy */
	if(strcmp(string, "MEM") == 0)
		printf("%s - %s Bytes", type, string);
	else
		printf("%s - %s", type, string);
}

static void
print_ascii(FILE *art)
{
	while(fgets(read, sizeof(read), art) != NULL)
		printf("%s", read);
}

static void
ascii(void)
{
	if((art = fopen(PATH, "r")) == NULL)
		printf("check image path\n");
	else
	{
		print_ascii(art);	
		fclose(art);

	}
}

static void
open_pipe(char *cmd, char *type)
{
	pipe = popen(cmd, "r");
	part = malloc(1024);
	fgets(part, 1024, pipe);
	print(type, part);
	clean(part, pipe);
} 

static void
parser(int count)
{
	char *type;
	switch(count)
	{
		case 1:
			type = "NAME";
			open_pipe(NAME, type);
			break;
		case 2:
			type = "OS";
			open_pipe(OS, type);
			break;
		case 3:
			type = "SHELL";
			open_pipe(SHELL, type);
			break;
		case 4:
			type = "CPU";
			open_pipe(CPU, type);
			break;
		case 5:
			type = "MEM";
			open_pipe(MEM, type);
			break;
		case 6:
			type = "UPTIME";
			open_pipe(UPTIME, type);	
			break;	
	}
}

int
main(void)
{
	ascii();
	for(int i = 0; i != MODC; i++)
		parser(i);
	return 0;	
}
