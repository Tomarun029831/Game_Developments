#include <stdio.h>

#define OPTION_NULL "NONOPTION"
#define OPTION_INVAIL NULL
#define OPTION_HELP {"-h", "help", "HELP"}        // help option
#define OPTION_TREE {"-t", "tree", "TREE"}        // show struct of path in data
#define OPTION_DIRECTOTY {"-d", "dir", "DIR"}     // show file or subdirectory in data
#define OPTION_REMOVE {"-rm", "remove", "REMOVE"} // remove directory, file in data
#define OPTION_ADD {"-a", "add", "ADD"}           // create directory, file in data

char *optionADD[] = OPTION_ADD;
char *optionDIRECTORY[] = OPTION_DIRECTOTY;
char *optionHELP[] = OPTION_HELP;
char *optionREMOVE[] = OPTION_REMOVE;
char *optionTREE[] = OPTION_TREE;

char **callOptions[] = {optionADD, optionDIRECTORY, optionHELP, optionREMOVE, optionTREE};

int main()
{
    printf("%s\n", callOptions[0][0]);
    return 0;
}
