/* utli.c
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
#include "util.h"

GList*
generate_random_points (gint n)
{
	GList *list = NULL;
	GRand *rand = g_rand_new ();

	for (int i = 0; i < n; i++) {
		gint x = g_rand_int_range (rand, -15, 15);
		gint y = g_rand_int_range (rand, -15, 15);

		SalPoint *p = sal_point_new (x, y);

		list = g_list_prepend (list, p);
	}

	return list;
}
