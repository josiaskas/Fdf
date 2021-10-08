/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:53:20 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/08 01:59:17 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/color.h"

int	palette_one(double percent)
{
	if (percent < 0.2)
		return (0x9A1F6A);
	else if (percent < 0.4)
		return (0xC2294E);
	else if (percent < 0.6)
		return (0xEC4B27);
	else if (percent < 0.8)
		return (0xEF8633);
	else
		return (0xF3AF3D);
}

int	palette_two(double percent, int z)
{
	if (z >= 8)
		return (palette_three(percent));
	else if (z >= 4)
		return (0xffff00);
	else if (z >= 2)
		return (0xff8000);
	else if (z >= 0)
		return (0x40ff00);
	else if (z == 0)
		return (0x00ffff);
	else if (z < 0)
		return (0x0080ff);
	else
		return (0x0000ff);
}

int	palette_three(double percent)
{
	if (percent < 0.1)
		return (0x277DA1);
	else if (percent < 0.2)
		return (0x577590);
	else if (percent < 0.3)
		return (0x4D908E);
	else if (percent < 0.4)
		return (0x43AA8B);
	else if (percent < 0.5)
		return (0x90BE6D);
	else if (percent < 0.6)
		return (0xF9C74F);
	else if (percent < 0.7)
		return (0xF9844A);
	else if (percent < 0.8)
		return (0xF8961E);
	else if (percent < 0.9)
		return (0xF3722C);
	else
		return (0xF94144);
}

int	palette_four(double percent)
{
	if (percent < 0.2)
		return (0x5F0F40);
	else if (percent < 0.4)
		return (0x9A031E);
	else if (percent < 0.6)
		return (0xFB8B24);
	else if (percent < 0.8)
		return (0xE36414);
	else
		return (0x0F4C5C);
}

int	palette_five(double percent)
{
	if (percent < 0.1)
		return (0x4D1A7F);
	else if (percent < 0.3)
		return (0xCC99FF);
	else if (percent < 0.5)
		return (0xEDBDFF);
	else if (percent < 0.6)
		return (0xFFE8FA);
	else if (percent < 0.8)
		return (0xFF91BF);
	else
		return (0xF7638F);
}
