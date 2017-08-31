/* jarvis-applicatoin-window.c
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

#include "jarvis-application-window.h"
#include "sal-point.h"
#include "math.h"
#include "util.h"
#include "jarvis.h"

struct _JarvisApplicationWindow
{
	GtkApplicationWindow parent_instance;
	GList *points;
	GList *hull;
};

G_DEFINE_TYPE (JarvisApplicationWindow, jarvis_application_window, GTK_TYPE_APPLICATION_WINDOW)

enum {
	PROP_0,
	PROP_POINTS,
	PROP_HULL,
	N_PROPS
};

static GParamSpec *properties [N_PROPS];

JarvisApplicationWindow *
jarvis_application_window_new (GtkApplication *app, GList *points, GList *hull)
{
	return g_object_new (JARVIS_TYPE_APPLICATION_WINDOW,
											 "application", app,
											 "points", points,
											 "hull", hull,
											  NULL);
}

static void
jarvis_application_window_finalize (GObject *object)
{
	JarvisApplicationWindow *self = (JarvisApplicationWindow *)object;

	g_list_free (self->hull);
	g_list_free_full (self->points, g_object_unref);

	G_OBJECT_CLASS (jarvis_application_window_parent_class)->finalize (object);
}

static void
jarvis_application_window_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
	JarvisApplicationWindow *self = JARVIS_APPLICATION_WINDOW (object);

	switch (prop_id)
	  {
		case PROP_POINTS:
			g_value_set_pointer (value, self->points);
			break;
		case PROP_HULL:
			g_value_set_pointer (value, self->hull);
			break;
	  default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	  }
}

static void
jarvis_application_window_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
	JarvisApplicationWindow *self = JARVIS_APPLICATION_WINDOW (object);

	switch (prop_id)
	  {
		case PROP_POINTS:
			if (self->points != NULL) {
				g_list_free_full (self->points, g_object_unref);
			}
			self->points = g_value_get_pointer (value);
			break;
		case PROP_HULL:
			if (self->hull != NULL) {
				g_list_free (self->hull);
			}
			self->hull = g_value_get_pointer (value);
			break;
	  default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	  }
}

static void
jarvis_application_draw_points (JarvisApplicationWindow *self,
                                GList                   *points,
                                cairo_t                 *cr)
{
	cairo_save (cr);

	gint width, height;
	gtk_window_get_size (GTK_WINDOW (self), &width, &height);

	gint width_middle = width / 2;
	gint height_middle = height / 2;

	/* cairo_new_path (cr); */
	for (GList *current = points; current != NULL; current = current->next) {
		SalPoint *p = SAL_POINT (current->data);
		cairo_arc (cr,
							 width_middle + sal_point_get_x (p),
							 height_middle - sal_point_get_y (p),
							 4,
							 0,
							 2 * M_PI);
		cairo_fill (cr);
	}

	cairo_restore (cr);
}

static void
jarvis_application_draw_hull (JarvisApplicationWindow *self,
                              GList                   *hull,
                              cairo_t                 *cr)
{
	cairo_save (cr);

	gint width, height;
	gtk_window_get_size (GTK_WINDOW (self), &width, &height);

	gint width_middle = width / 2;
	gint height_middle = height / 2;

	cairo_new_path (cr);
	cairo_set_source_rgb (cr, 1.0, 0., 0.);
	SalPoint *first_point = SAL_POINT (hull->data);
	cairo_move_to (cr,
								 width_middle + sal_point_get_x (first_point),
								 height_middle - sal_point_get_y (first_point));

	for (GList *current = hull->next; current != NULL; current = current->next) {
		SalPoint *p = SAL_POINT (current->data);

		cairo_line_to (cr, width_middle + sal_point_get_x (p), height_middle - sal_point_get_y (p));
	}

	cairo_close_path (cr);
	cairo_stroke (cr);

	for (GList *current = hull; current != NULL; current = current->next) {
		SalPoint *p = SAL_POINT (current->data);
		cairo_arc (cr,
							 width_middle + sal_point_get_x (p),
							 height_middle - sal_point_get_y (p),
							 4,
							 0,
							 2 * M_PI);
		cairo_fill (cr);
	}

	cairo_restore (cr);
}

static gboolean
jarvis_application_window_on_draw (GtkWidget    *widget,
                                   cairo_t      *cr,
                                   gpointer      user_data)
{
	JarvisApplicationWindow *self = JARVIS_APPLICATION_WINDOW (user_data);
	cairo_save (cr);
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_paint (cr);
	cairo_restore (cr);

	jarvis_application_draw_points (self, self->points, cr);
	jarvis_application_draw_hull (self, self->hull, cr);

	cairo_save (cr);

	gint width, height;
	gtk_window_get_size (GTK_WINDOW (self), &width, &height);

	gint width_middle = width / 2;
	gint height_middle = height / 2;

	cairo_new_path (cr);
	cairo_set_line_width (cr, 0.25);
	cairo_set_tolerance (cr, 0.1);
	cairo_move_to (cr, 0, height_middle);
	cairo_line_to (cr, width, height_middle);
	cairo_stroke (cr);

	cairo_move_to (cr, width_middle, 0);
	cairo_line_to (cr, width_middle, height);
	cairo_stroke (cr);

	cairo_restore (cr);
	return TRUE;
}

static void
jarvis_application_window_set_data (JarvisApplicationWindow *self,
                                    GList                   *points,
                                    GList                   *hull)
{
	g_object_set (self, "points", points, "hull", hull, NULL);
}


static void
jarvis_application_window_refresh (GtkButton *refresh_btn,
                                   gpointer   user_data)
{
	JarvisApplicationWindow *self = JARVIS_APPLICATION_WINDOW (user_data);

	GList *points = generate_random_points (20);
	JarvisMarch *jm = jarvis_march_new ();
	GList *hull = jarvis_march_execute_algorithm (jm, points);
	g_object_unref (jm);

	jarvis_application_window_set_data (self, points, hull);

	gtk_widget_queue_draw (GTK_WIDGET (self));
}


static void
jarvis_application_window_class_init (JarvisApplicationWindowClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->finalize = jarvis_application_window_finalize;
	object_class->get_property = jarvis_application_window_get_property;
	object_class->set_property = jarvis_application_window_set_property;

	properties[PROP_POINTS] =
		g_param_spec_pointer ("points", "Points", "all points", G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

	properties[PROP_HULL] =
		g_param_spec_pointer ("hull", "Hull", "convex Hull", G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties (object_class, N_PROPS, properties);

	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass), "/org/gwutz/jarvis/window.ui");
	gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (klass),
																								"jarvis_application_window_on_draw",
																								G_CALLBACK (jarvis_application_window_on_draw));
	gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (klass),
																								"jarvis_application_window_refresh",
																								G_CALLBACK (jarvis_application_window_refresh));
}

static void
jarvis_application_window_init (JarvisApplicationWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}
