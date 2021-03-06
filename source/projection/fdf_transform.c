/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viwade <viwade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:11:32 by viwade            #+#    #+#             */
/*   Updated: 2019/07/20 16:51:11 by viwade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#define D2RAD(n)	(PI * (n) / 180.0)

v3d_t
	fdf_transform(v3d_t v, tfm_t t)
{
	v3d_t	angle;

	v = (v3d_t){
		t.scale.x * v.x + t.translate.x,
		t.scale.y * v.y + t.translate.y,
		t.scale.z * v.z + t.translate.z};
	angle = (v3d_t){D2RAD(t.rotate.x), D2RAD(t.rotate.y), D2RAD(t.rotate.z)};
	v = (v3d_t){
		v.x * (1),
		v.y * cos(angle.x) - v.z * sin(angle.x),
		v.z * cos(angle.x) + v.y * sin(angle.x)};
	v = (v3d_t){
		v.x * cos(angle.y) + v.z * sin(angle.y),
		v.y * (1),
		v.z * cos(angle.y) - v.x * sin(angle.y)};
	v = (v3d_t){
		v.x * cos(angle.z) + v.y * sin(angle.z),
		v.y * cos(angle.z) - v.x * sin(angle.z),
		v.z * (1)};
	return (v);
}

v3d_t
	fdf_rotate2d(v2d_t t, v3d_t v)
{
	t = (v2d_t){D2RAD((double)t.x), D2RAD((double)t.y)};
	v = (v3d_t){
		v.x * (1),
		v.y * cos(t.x) - v.z * sin(t.x),
		v.z * cos(t.x) + v.y * sin(t.x)};
	v = (v3d_t){
		v.x * cos(t.y) + v.z * sin(t.y),
		v.y * (1),
		v.z * cos(t.y) - v.x * sin(t.y)};
	return ((v3d_t){
			v.x + t.x,
			v.y + t.y,
			v.z});
}
