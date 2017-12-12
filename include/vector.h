/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 13:22:20 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/12 13:54:46 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <math.h>

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_vec4
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_vec4;

double				vec3_dot(t_vec3 v1, t_vec3 v2);
double				vec3_norm(t_vec3 v);

t_vec3				*vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3				*vec3_cross_prod(t_vec3 *v1, t_vec3 *v2);
t_vec3				*vec3_div(t_vec3 v0, double factor);
t_vec3				*vec3_mult(t_vec3 *v, double factor);
t_vec3				*vec3_new(double x, double y, double z);
t_vec3				*vec3_sub(t_vec3 v1, t_vec3 v2);

t_vec3				vec3_add_stack(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_div_stack(t_vec3 v0, double factor);
t_vec3				vec3_cross_prod_stack(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_mult_stack(t_vec3 v, double factor);
t_vec3				vec3_normalize_stack(t_vec3 v);
t_vec3				vec3_sub_stack(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_stack(double x, double y, double z);

void				vec3_mult_fact(t_vec3 *v, double factor);
void				vec3_normalize(t_vec3 *v);
void				vec3_print(t_vec3 v);
void				vec3_rev(t_vec3 *v);
void				vec3_set(double x, double y, double z, t_vec3 *v);
void				vec3_trans(t_vec3 t, t_vec3 *v);

double				vec4_norm(t_vec4 v);
t_vec4				vec4_normalize_stack(t_vec4 v);

t_vec4				vec4_stack(double x, double y, double w, double z);
t_vec4				*vec4_new(double x, double y, double z, double w);

#endif
