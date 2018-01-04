/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 12:16:39 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/04 12:53:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "rt.h"

void				print_color(t_color c);
void				print_cut(t_geo *geo);
void				print_env(t_env *e);
void				print_geo(t_geo *geo);
void				print_geo_mater(t_mater *m);
void				print_lights(t_env *e);

void				free_env(t_env **e);
void				init_environment(t_env **e);

double				atof_cson(char **str);
double				clamp(double x, double up, double low);
double				deg_to_rad(double deg);
double				lerp(double t, double a, double b);
double				min(double i, double j);
double				max(double i, double j);
double				positive_smallest(double a, double b);
double				non_positive_smallest(double a, double b);

#endif
