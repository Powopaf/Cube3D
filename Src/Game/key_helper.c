/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_herper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:52:13 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/25 16:52:14 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game/key.h"
#include <math.h>

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2.0 * PI);
	if (angle < 0.0)
		angle += 2.0 * PI;
	return (angle);
}
