/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:31:54 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/08 01:35:35 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define SHELL_RED "\033[0;31m"
# define SHELL_YELLOW "\033[0;33m"
# define SHELL_END_COLOR "\033[m"
# define TEXT_COLOR 0x1A1A1D
# define BACKGROUND 0x1A1A1D
# define MENU_BACKGROUND 0x950740
# define BLACK 0x000000
# define WHITE 0xFFFFFF

// return percent according to begin and end
double	ft_percent(int start, int end, int current);
// color start, color end and curent percent on the slope
int		ft_gradient(int start, int end, double percent);
int		palette_one(double percent);
int		palette_two(double percent, int z);
int		palette_three(double percent);
int		palette_four(double percent);
int		palette_five(double percent);
#endif
