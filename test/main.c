/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:50:54 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 12:39:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/font.h"
#include "images/images.h"

# ifdef __APPLE__
#  define WINDOW_WIDTH	1280
#  define WINDOW_HEIGHT	720
# else
#  define WINDOW_WIDTH	1900
#  define WINDOW_HEIGHT	990
# endif /* __APPLE__ */

void	ft_init_mlx_f(t_data *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (ft_error("Error: Could not allocate memory\n"), exit(1));
	mlx->window = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TTF Parser demo");
	if (!mlx->window)
		exit(1);
	mlx->image = ft_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->image)
		exit(1);
}

int	ft_loop_hook_events(void *param)
{
	t_data	*mlx;

	mlx = (t_data *)param;
	mlx_do_sync(mlx->mlx);
	return (0);
}

/**
 * @brief Stops and exits the game cleanly
 * 
 */
int	ft_stop_mlx(t_data *mlx)
{
	if (mlx->image != NULL)
		ft_delete_image(mlx->mlx, &(mlx->image));
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
#ifndef __APPLE__
	mlx_destroy_display(mlx);
#endif /* __APPLE__ */
	free(mlx->mlx);
	exit(EXIT_SUCCESS);
}

void	ft_init_mlx_hook(t_data *mlx)
{
	mlx_hook(mlx->window, 0x11, 1L << 0, &ft_stop_mlx, mlx);
	mlx_loop_hook(mlx->mlx, &ft_loop_hook_events, mlx);
}

int	main(int ac, char **av)
{
	t_data	mlx;

	ft_bzero(&mlx, sizeof(t_data));
	ft_init_mlx_f(&mlx);
	ft_init_mlx_hook(&mlx);
	// t_data.image = ft_crea
	mlx_loop(mlx.mlx);
	return (0);
}
