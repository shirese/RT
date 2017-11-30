/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_multithread.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirese <shirese@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:39:58 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/30 20:37:39 by shirese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MULTITHREAD

# define RT_MULTITHREAD

#include <pthread.h>
#include <stdatomic.h>

#include "rt.h"

#define NUM_THREADS 4
#define TILESIZE 16

typedef struct		s_thread_data
{
	int				tile_id;
	pthread_mutex_t	mutex;
	t_env			*e;
}					t_thread_data;

int					raytrace_thread(t_env *e);

#endif
