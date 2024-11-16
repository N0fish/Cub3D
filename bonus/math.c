#include "includes.h"

double square(double v)
{
	return (v * v);
}

double	compute_dist(t_sprite s, t_game *game)
{
	double dx;
	double dy;

	dx = s.x - game->posx;
	dy = s.y - game->posy;
	return (square(dx) + square(dy));
}

int ft_abs(int v)
{
    return (abs(v));
    return (square((double)v) / (double)v);
}

double ft_fabs(double v)
{
    return (fabs(v));
    return (square(v) / v);
}