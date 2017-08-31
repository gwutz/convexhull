/* jarvis-application.c
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
#include "jarvis-application.h"
#include "jarvis-application-window.h"
#include "util.h"
#include "jarvis.h"

struct _JarvisApplication
{
	GtkApplication parent_instance;
};

G_DEFINE_TYPE (JarvisApplication, jarvis_application, GTK_TYPE_APPLICATION)

enum {
	PROP_0,
	N_PROPS
};

static GParamSpec *properties [N_PROPS];

JarvisApplication *
jarvis_application_new (void)
{
	return g_object_new (JARVIS_TYPE_APPLICATION,
											 "application-id", "org.gwutz.Jarvis",
											 "flags", G_APPLICATION_FLAGS_NONE,
											  NULL);
}

static void
jarvis_application_finalize (GObject *object)
{
	JarvisApplication *self = (JarvisApplication *)object;

	G_OBJECT_CLASS (jarvis_application_parent_class)->finalize (object);
}

static void
jarvis_application_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
	JarvisApplication *self = JARVIS_APPLICATION (object);

	switch (prop_id)
	  {
	  default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	  }
}

static void
jarvis_application_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
	JarvisApplication *self = JARVIS_APPLICATION (object);

	switch (prop_id)
	  {
	  default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	  }
}

static void
jarvis_application_class_init (JarvisApplicationClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->finalize = jarvis_application_finalize;
	object_class->get_property = jarvis_application_get_property;
	object_class->set_property = jarvis_application_set_property;
}

static void
jarvis_application_activate (JarvisApplication *self, gpointer user_data)
{
	GList *points = generate_random_points (20);
	JarvisMarch *jm = jarvis_march_new ();
	GList *hull = jarvis_march_execute_algorithm (jm, points);
	g_object_unref (jm);

	JarvisApplicationWindow *window = jarvis_application_window_new (GTK_APPLICATION (self), points, hull);

	gtk_application_add_window (GTK_APPLICATION (self), GTK_WINDOW (window));

	gtk_window_present (GTK_WINDOW (window));
}

static void
jarvis_application_init (JarvisApplication *self)
{
	g_signal_connect (self, "activate", G_CALLBACK (jarvis_application_activate), NULL);
}
