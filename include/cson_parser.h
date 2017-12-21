/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 11:57:04 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 16:19:25 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSON_PARSER_H
# define CSON_PARSER_H

# include "rt.h"

int					cson_parse(int fd, t_env *e);

int					parse_geo(int *fd, char **line, t_env *e);
int					parse_light(int *fd, char **line, t_env *e);
int					parse_camera(int *fd, char **line, t_env *e);
int					parse_window(int *fd, char **line, t_env *e);

int					add_cone(int *fd, char **line, t_env *e);
int					add_cylinder(int *fd, char **line, t_env *e);
int					add_paraboloid(int *fd, char **line, t_env *e);
int					add_plane(int *fd, char **line, t_env *e);
int					add_sphere(int *fd, char **line, t_env *e);
int					add_disk(int *fd, char **line, t_env *e);

#endif
