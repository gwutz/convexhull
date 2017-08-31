/* jarvis-application-window.h
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

#ifndef JARVIS_APPLICATION_WINDOW_H
#define JARVIS_APPLICATION_WINDOW_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define JARVIS_TYPE_APPLICATION_WINDOW (jarvis_application_window_get_type())

G_DECLARE_FINAL_TYPE (JarvisApplicationWindow, jarvis_application_window, JARVIS, APPLICATION_WINDOW, GtkApplicationWindow)

JarvisApplicationWindow *jarvis_application_window_new (GtkApplication *app, GList *points, GList *hull);

G_END_DECLS

#endif /* JARVIS_APPLICATION_WINDOW_H */

