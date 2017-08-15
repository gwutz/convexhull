/* jarvis.c
 *
 * Copyright (C) 2017 Guenther Wutz <info@gunibert.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "jarvis.h"

struct _JarvisMarch
{
	GObject parent_instance;
};

G_DEFINE_TYPE (JarvisMarch, jarvis_march, G_TYPE_OBJECT)

JarvisMarch *
jarvis_march_new (void)
{
	return g_object_new (JARVIS_TYPE_MARCH, NULL);
}

static void
jarvis_march_class_init (JarvisMarchClass *klass)
{
}

static void
jarvis_march_init (JarvisMarch *self)
{
}

static SalPoint *
jarvis_march_find_start_point (JarvisMarch *self,
                               GList       *points)
{
	SalPoint *start = (SalPoint *)points->data;

	for (GList *current = points->next; current != NULL; current = current->next) {
		SalPoint *p = (SalPoint *)current->data;

		if (sal_point_get_y (p) < sal_point_get_y (start)) {
			start = p;
		} else if (sal_point_get_y (p) == sal_point_get_y (start) &&
							 sal_point_get_x (p) == sal_point_get_x (start)) {
			start = p;
		}
	}

	return start;
}

typedef enum {
	TURN_NONE,
	TURN_LEFT,
	TURN_RIGHT,
} Turn;

static Turn
jarvis_march_direction (SalPoint *p1,
                        SalPoint *p2,
                        SalPoint *p3)
{
	SalPoint *l = sal_point_sub (p3, p1);
	SalPoint *r = sal_point_sub (p2, p1);

	gint d = sal_point_crossproduct (l, r);
	g_object_unref (l);
	g_object_unref (r);

	if (d > 0) {
		return TURN_RIGHT;
	} else if (d < 0) {
		return TURN_LEFT;
	}
	return TURN_NONE;
}

static gint
jarvis_march_distance (JarvisMarch *self,
                       SalPoint    *p,
                       SalPoint    *q)
{
	gint dx = sal_point_get_x (q) - sal_point_get_x (p);
	gint dy = sal_point_get_y (q) - sal_point_get_y (p);

	return dx * dx + dy * dy;
}

static SalPoint *
jarvis_march_next_hull_point (JarvisMarch *self,
                              GList       *points,
                              SalPoint    *p)
{
	SalPoint *q = p;

	for (GList *current = points; current != NULL; current = current->next) {
		SalPoint *l = (SalPoint *)current->data;
		Turn t = jarvis_march_direction (p, q, l);

		if ((t == TURN_RIGHT) ||
				((t == TURN_NONE) && (jarvis_march_distance (self, p, l) > jarvis_march_distance (self, p, q))))
		{
			q = l;
		}
	}

	return q;
}

GList *
jarvis_march_execute_algorithm (JarvisMarch *self, GList *points)
{
	GList *hull = NULL;

	SalPoint *start = jarvis_march_find_start_point (self, points);
	hull = g_list_append (hull, start);

	SalPoint *p = start;

	do {
		p = jarvis_march_next_hull_point (self, points, p);
		if (p != start) {
			hull = g_list_append (hull, p);
		}
	} while (p != start);
	return hull;
}
