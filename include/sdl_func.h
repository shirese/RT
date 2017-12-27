/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 10:23:28 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/27 16:09:06 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_FUNC_H
# define SDL_FUNC_H

int					check_drag_event(SDL_Event event, t_env *e);

void				sdl_get_event(SDL_Event event, t_env *e);
void				sdl_draw_point(SDL_Renderer *rend, int x, int y, t_color c);
int					sdl_init(t_env **e);
void				sdl_render(t_env *e);
void				sdl_stop(t_env *e);

void				release_virtual_plane(t_geo **virtual_plane);
void				render_loading_bar(int x, int y, t_env *e);
void				setup_virtual_plane(t_geo **virtual_plane);

#endif
