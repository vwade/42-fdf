/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_print_vertex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viwade <viwade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 04:40:35 by viwade            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/07/14 15:02:03 by viwade           ###   ########.fr       */
=======
/*   Updated: 2019/07/13 05:05:46 by viwade           ###   ########.fr       */
>>>>>>> 9b0b01f62d18b835b9acaa0d691d4dc890214a31
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	fdf_print_vertex(mesh_t m)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < m.v_len)
	{
		ft_putstr("v[");
		ft_putnbr(i);
<<<<<<< HEAD
		ft_putstr("]\t\tcolor[ #");
		tmp = ft_itoa_base((ull_t)((*(uint *)&m.v[i].col) << 8) >> 8, 16);
		ft_putstr(tmp);
		free(tmp);
		ft_putstr(" ]    pos[ ");
=======
		ft_putstr("]\tcolor[ #");
		tmp = ft_itoa_base((ull_t)((*(uint *)&m.v[i].col) << 8) >> 8, 16);
		ft_putstr(tmp);
		free(tmp);
		ft_putstr(" ]\tpos[ ");
>>>>>>> 9b0b01f62d18b835b9acaa0d691d4dc890214a31
		print_double(m.v[i].pos.x, 6);
		ft_putstr(" , ");
		print_double(m.v[i].pos.y, 6);
		ft_putstr(" , ");
		print_double(m.v[i].pos.z, 6);
		ft_putstr(" ]\n");
		i++;
	}
}