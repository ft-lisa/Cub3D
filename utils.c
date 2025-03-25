#include "err_mess.h"
#include "cub3d.h"

char* pass_space(char* line)
{
        while(*line != '\0' && *line == ' ')
                line++;
        return(line);
}