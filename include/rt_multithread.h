/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_multithread.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:39:58 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 16:23:36 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MULTITHREAD_H

# define RT_MULTITHREAD_H

# include <pthread.h>
# include <stdatomic.h>

# include "rt.h"

# define NUM_THREADS 4
# define TILESIZE 16

typedef struct		s_thread_data
{
	int				tile_id;
	pthread_mutex_t	mutex;
	t_env			*e;
}					t_thread_data;

int					raytrace_thread(t_env *e);

#endif
