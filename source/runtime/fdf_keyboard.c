/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viwade <viwade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:42:26 by viwade            #+#    #+#             */
/*   Updated: 2019/07/21 17:03:29 by viwade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#define K_MVR(t)	{t.x += 1.0 / 42.0;}
#define K_MVL(t)	{t.x -= 1.0 / 42.0;}
#define K_MVD(t)	{t.y += 1.0 / 42.0;}
#define K_MVU(t)	{t.y -= 1.0 / 42.0;}
#define K_SCL0(s,v)	(0<s&&s<0.03125?-1:(s<0?1/v:v))
#define K_SCL1(s,v)	(-0.03125<s&&s<0?-1:(s<0?v:1/v))
#define K_SCLX(s,v)	{s.x *= v<1?K_SCL0(s.x,v):K_SCL1(s.x,v);}
#define K_SCLY(s,v)	{s.y *= v<1?K_SCL0(s.y,v):K_SCL1(s.y,v);}
#define K_SCLZ(s,v)	{s.z *= v<1?K_SCL0(s.z,v):K_SCL1(s.z,v);}
#define K_MV2(k,t,r)	IF_C(r=k[KEY_ARROW_UP],K_MVU(t))
#define K_MV1(k,t,r)	IF_C(r=k[KEY_ARROW_DOWN],K_MVD(t);K_MV2(k,t,r))
#define K_MV0(k,t,r)	IF_C(r=k[KEY_ARROW_LEFT],K_MVL(t);K_MV1(k,t,r))
#define K_MOV(k,t,r)	IF_C(r=k[KEY_ARROW_RIGHT],K_MVR(t);K_MV0(k,t,r))
#define K_SC0(k,s,r)	IF_C(r=k[KEY_NUM_MINUS],K_SCLZ(t))
#define K_SCL(k,s,r)	IF_C(r=k[KEY_NUM_PLUS],K_SCLZ(s);K_SC0(s))

int
	key_press(int key, fdf_t *o)
{
	o->key[key] = 1;
	IF_C(key == KEY_P, o->iso = o->iso ? 0 : 1);
	IF_C(o->mode += key == KEY_C, fdf_color_mode(o));
	IF_C(key == KEY_R, fdf_reset(o));
	return (key);
}

int
	key_release(int key, fdf_t *o)
{
	IF_C(key == KEY_ESC, exit(0));
	return (!(o->key[key] = 0));
}

int
	key_event(int key, fdf_t *o)
{
	if (o->key[key])
		;
	return (1);
}

void
	*fdf_keyboard(size_t i)
{
	if (i == 1)
		return (key_press);
	if (i == 2)
		return (key_release);
	if (i == 3)
		return (key_event);
	return (0);
}
