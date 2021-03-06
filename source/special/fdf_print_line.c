/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_print_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viwade <viwade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 04:40:35 by viwade            #+#    #+#             */
/*   Updated: 2019/07/20 18:08:32 by viwade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#define PRECISION	3

static void
	fdf_xyz(p3d_t point)
{
	char *tmp;

	ft_putstr("#");
	tmp = ft_itoa_base((ull_t)((*(uint *)&point.col) << 8) >> 8, 16);
	ft_putstr(tmp);
	free(tmp);
	ft_putstr(" [ ");
	if (point.pos.x >= 0)
		ft_putstr(" ");
	print_double(point.pos.x, PRECISION);
	ft_putstr(" , ");
	if (point.pos.y >= 0)
		ft_putstr(" ");
	print_double(point.pos.y, PRECISION);
	ft_putstr(" , ");
	if (point.pos.z >= 0)
		ft_putstr(" ");
	print_double(point.pos.z, PRECISION);
	ft_putstr(" ]");
}

void
	fdf_print_line(mesh_t m)
{
	size_t	i;
	l3d_t	*l;

	i = 0;
	while ((i <= 100 && i < m.l_len) || !write(1, "...\n", 4))
	{
		l = (void*)&m.l[i * sizeof(l3d_t)];
		ft_putstr("line[");
		ft_putnbr(i);
		ft_putstr("]");
		if (i < 10)
			ft_putstr(" ");
		ft_putstr("\tpoint_a[ ");
		fdf_xyz(l->a[0]);
		ft_putstr(" ]\tpoint_b[ ");
		fdf_xyz(l->b[0]);
		ft_putendl(" ]");
		i++;
	}
	ft_putstr("[ ");
	ft_putnbr(m.v_len);
	ft_putstr(" ] Total Points\n");
	ft_putstr("[ ");
	ft_putnbr(m.l_len);
	ft_putstr(" ] Total Lines\n");
}

/*
**		ft_putstr("\t\tcolor[ #");
**		tmp = ft_itoa_base((ull_t)((*(uint *)&m.v[i].col) << 8) >> 8, 16);
**		ft_putstr(tmp);
**		free(tmp);
*/
