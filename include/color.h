/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirese <shirese@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 12:25:50 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/01 21:55:26 by shirese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "rt.h"

void				color_print(t_color c);
void				color_clamp(t_color *c, double min, double max);
void				color_add_no_clamp(t_color c1, t_color *c2);
void				color_add(t_color c1, t_color *c2);
void				color_div_fac(t_color *c, int fac);
void				color_div(t_color c1, t_color *c2);
void				color_mult(t_color c1, t_color *c2);
void				color_set(t_color c, t_color *c_to_set);
t_color				color_new_stack(double r, double g, double b);
t_color				*color_new(double r, double g, double b);

#endif
