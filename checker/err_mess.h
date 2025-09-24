/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mess.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:03:10 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 14:23:07 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MESS_H
# define ERR_MESS_H

# define GOOD_EXIT 0
# define EXIT_FAILURE 1
# define GOOD 1
# define ERROR 0

# define ERR_ARG "Error\n./cub3d [file]\n"
# define ERR_CUB "Error\nThe file is not a .cub\n"
# define ERR_FILE "Error\nThis is not a file\n"
# define ERR_COLOR "Error\ncolors R,G,B range [0,255]\n"
# define ERR_MISS_TEX "Error\nIt's necessary a texture for NO, SO, EA and WE\n"
# define ERR_MUCH_TEX "Error\nIt's necessary ONE texture for NO, SO, EA and WE\n"
# define ERR_MISS_COL "Error\nIt's necessary a color for F and C\n"
# define ERR_MUCH_COL "Error\nIt's necessary ONE color for F and C\n"
# define ERR_CHAR "Error\nMap must contain only: 0, 1, N, S, W, E\n"
# define ERR_SPAWN "Error\nThe map must contain a N, S, W or E\n"
# define ERR_MULT_SPAWN "Error\nThe map must contain one N, S, W or E\n"
# define ERR_EMPTY "Error\nThere is in the map an empty line\n"
# define ERR_WALL "Error\nThe wall is not complete\n"
# define ERR_TEX_MISS "Error\nA texture miss\n"

typedef struct s_element
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}		t_element;

#endif