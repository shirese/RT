/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negativity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:52:17 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/14 12:52:18 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int         is_scene_dug(t_geo *geo)
{
    t_geo *tmp;

    tmp = geo;
    while (tmp)
    {
        if (tmp->neg)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

int         is_geo_dug(t_geo *geo)
{
    if (geo->neg)
        return (1);
    return (0);
}
