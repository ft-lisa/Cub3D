#include "../cub3d.h"

void texture(char* line, t_element* map)
{
        if (ft_strlen(line) < 3)
                return;
        if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ' )
                map->no++;
        else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ' )
                map->so++;
        else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ' )
                map->we++;
        else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ' )
                map->ea++;      
}

/* 
F 220,100,0
F 220,100,0,
F 220,10a0,0
F 2200,100,0
F     220,100,0
F 220,100
F 220,100,
F 220,110,0a
F 220,100,0
F     220,100,0
F 220,100,51,54,
*/

int check_num_color(char* line, int comma)
{
        int num;
        int cont;

        while(*line != '\0')
        {
                num = 0;
                cont = 0;
                while(*line >= '0' && *line <= '9')
                {
                        cont = 1;
                        num = num * 10 + *line - 48;
                        if (num > 255)
                                return(printf(ERR_COLOR), ERROR);
                        line++;
                }
                if (cont == 0)
                        return(printf(ERR_COLOR), ERROR);
                if (*line == '\n' || *line == '\0')
                        break;
                if (*line != ',')
                        return(printf(ERR_COLOR), ERROR);
                comma++;
                line++;
        }
        if (comma == 2)
                return(GOOD);
        return(printf(ERR_COLOR), ERROR);
}

int color(char* line, t_element* map)
{
        if (line[0] == 'C' && line[1] == ' ')
                map->c++;
        else if (line[0] == 'F' && line[1] == ' ')
                map->f++;
        else
                return(GOOD);
        line++;
        line = pass_space(line);
        return(check_num_color(line, 0));
        
}