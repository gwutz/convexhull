/* random-points-test.c
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
#include <glib.h>
#include <locale.h>
#include "util.h"

void
test_random_points ()
{
	gint n = 5;
	GList *points = generate_random_points (n);

	g_assert_cmpint (g_list_length (points), ==, n);

	for (GList *next = points; next != NULL; next = next->next) {
		SalPoint *p = (SalPoint *)next->data;

		g_assert (SAL_IS_POINT (p));
	}
}

gint
main (gint   argc,
      gchar *argv[])
{

	setlocale (LC_ALL, "");

	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/randompoints/randompoints", test_random_points);

	return g_test_run ();
}
