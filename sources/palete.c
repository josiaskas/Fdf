/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 22:58:52 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/04 23:24:59 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/color.h"

int	palete_one(double percent)
{
	if (percent < 0.2)
		return (COLOR_DISCO);
	else if (percent < 0.4)
		return (COLOR_BRICK_RED);
	else if (percent < 0.6)
		return (COLOR_FLAMINGO);
	else if (percent < 0.8)
		return (COLOR_JAFFA);
	else
		return (COLOR_SAFFRON);
}

int	palete_two(double percent)
{
	if (percent < 0.1)
		return (0x370617);
	else if (percent < 0.2)
		return (0x6A040F);
	else if (percent < 0.3)
		return (0x9D0208);
	else if (percent < 0.4)
		return (0xD00000);
	else if (percent < 0.5)
		return (0xDC2F02);
	else if (percent < 0.6)
		return (0xE85D04);
	else if (percent < 0.7)
		return (0xF48C06);
	else if (percent < 0.8)
		return (0xFAA307);
	else
		return (0xFFBA08);
}

int	palete_three(double percent)
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
