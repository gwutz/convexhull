/* main.c
 *
 * Copyright (C) 2017 Günther Wutz <info@gunibert.de>
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

#include "jarvis-application.h"

gint
main (gint   argc,
      gchar *argv[])
{
	/* g_set_prgname ("Jarvis March"); */
	/* g_set_application_name ("Jarvis March"); */

	JarvisApplication *app = jarvis_application_new ();

	return g_application_run (G_APPLICATION (app), argc, argv);
	/* GList *points = generate_random_points (20); */
	/* JarvisMarch *jm = jarvis_march_new (); */
	/* GList *hull = jarvis_march_execute_algorithm (jm, points); */

	/* for (GList *current = hull; current != NULL; current = current->next) { */
	/* 	g_print ("%s\n", sal_point_to_string ((SalPoint*)current->data)); */
	/* } */
}
