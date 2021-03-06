/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viwade <viwade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:56:41 by viwade            #+#    #+#             */
/*   Updated: 2019/07/20 16:34:44 by viwade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#define _D_D(a,b)	((double)(a)/(double)(b))

static	p3d_t
	*v_h(p3d_t *v, v3d_t c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && v[i].pos.y == c.y)
		if (v[i].pos.x == c.x + 1)
			return (&v[i]);
		else
			i++;
	return (NULL);
}

static	p3d_t
	*v_v(p3d_t *v, v3d_t c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && v[i].pos.x != c.x)
		i++;
	while (i < size && v[i].pos.x == c.x)
		if (v[i].pos.y == c.y + 1)
			return (&v[i]);
		else
			i++;
	return (NULL);
}

static void
	array_create(t_list *lst, t_line *arr)
{
	t_list	*node;

	node = lst;
	while (node)
	{
		ft_memcpy(arr, node->content, sizeof(t_line));
		arr += sizeof(t_line);
		node = node->next;
	}
	ft_lstdel(&lst, ft_del);
}

static void
	vertex_normalize(map_t m, p3d_t *v, size_t size)
{
	size_t	i;
	v3d_t	d;

	i = 0;
	d = (v3d_t){0, 0, 0};
	while ((i++ < size) || (i = 0))
		d.z = MAX(d.z, ABS(v[i - 1].pos.z));
	d = (v3d_t){(double)(m.size.x - 1) / 2, (double)(m.size.y - 1) / 2, d.z};
	while ((i++ < size) || (i = 0))
		v[i - 1].pos = (v3d_t){
			v[i - 1].pos.x - d.x, v[i - 1].pos.y - d.y, v[i - 1].pos.z};
	d = (v3d_t){MAX(d.z, (double)MAX(m.size.x - 1, m.size.y - 1)) / 2.0,
		_D_D(m.size.y, m.size.x), d.z};
	while (i++ < size)
		v[i - 1].pos = (v3d_t){
			v[i - 1].pos.x / d.x, v[i - 1].pos.y / d.x, v[i - 1].pos.z / d.x};
}

/*
**	Vertex array length must be handled separately. Cannot terminate with NULL.
**	Line array length must be handled separately. Cannot terminate with NULL.
**	/\
*/

void
	fdf_line(map_t *m, size_t size, size_t i)
{
	t_line	ln[2];
	t_list	*list;

	list = NULL;
	while (i < size)
	{
		ln[0] = (t_line){&m->mesh.v[i], i + 1 < size ? v_h(&m->mesh.v[i + 1],
			m->mesh.v[i].pos, size - i) : 0};
		ln[1] = (t_line){&m->mesh.v[i], i + m->size.x < size ?
v_v(&m->mesh.v[i + m->size.x], m->mesh.v[i].pos, size - i - m->size.x) : 0};
		if (ln[0].b)
			ft_lstpush(&list, ft_lstnew(&ln[0], sizeof(t_line)));
		if (ln[1].b)
			ft_lstpush(&list, ft_lstnew(&ln[1], sizeof(t_line)));
		i++;
	}
	m->mesh.l_len = ft_lstlen(list);
	fdf_create_line_array(
		(void*)&m->mesh.l, sizeof(*m->mesh.l) * m->mesh.l_len);
	array_create(list, (void*)m->mesh.l);
	vertex_normalize(*m, m->mesh.v, m->mesh.v_len);
	fdf_create_vertex_array((void *)&m->mesh.ref_v, m->mesh.v_len);
	ft_memcpy((void *)m->mesh.ref_v, m->mesh.v, m->mesh.v_len * sizeof(p3d_t));
}
