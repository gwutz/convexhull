/* jarvis-application.h
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

#ifndef JARVIS_APPLICATION_H
#define JARVIS_APPLICATION_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define JARVIS_TYPE_APPLICATION (jarvis_application_get_type())

G_DECLARE_FINAL_TYPE (JarvisApplication, jarvis_application, JARVIS, APPLICATION, GtkApplication)

JarvisApplication *jarvis_application_new (void);

G_END_DECLS

#endif /* JARVIS_APPLICATION_H */

