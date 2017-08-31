/* sal-point.c
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

#include "sal-point.h"

struct _SalPoint
{
	GObject parent_instance;

	gint x;
	gint y;
};

G_DEFINE_TYPE (SalPoint, sal_point, G_TYPE_OBJECT)

enum {
	PROP_0,
	PROP_X,
	PROP_Y,
	N_PROPS
};

static GParamSpec *properties [N_PROPS];

SalPoint *
sal_point_new (gint x, gint y)
{
	return g_object_new (SAL_TYPE_POINT,
											 "x", x,
											 "y", y,
											 NULL);
}

static void
sal_point_finalize (GObject *object)
{
	SalPoint *self = (SalPoint *)object;

	G_OBJECT_CLASS (sal_point_parent_class)->finalize (object);
}

static void
sal_point_get_property (GObject    *object,
                        guint       prop_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
	SalPoint *self = SAL_POINT (object);

	switch (prop_id)
	  {
		case PROP_X:
			g_value_set_int (value, self->x);
			break;
		case PROP_Y:
			g_value_set_int (value, self->y);
			break;
	  default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	  }
}

static void
sal_point_set_property (GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
	SalPoint *self = SAL_POINT (object);

	switch (prop_id)
	  {
		case PROP_X:
			self->x = g_value_get_int (value);
			break;
		case PROP_Y:
			self->y = g_value_get_int (value);
			break;
	  default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	  }
}

static void
sal_point_class_init (SalPointClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->finalize = sal_point_finalize;
	object_class->get_property = sal_point_get_property;
	object_class->set_property = sal_point_set_property;

	properties[PROP_X] =
		g_param_spec_int ("x",
											"X",
											"the x coordinate",
											G_MININT,
											G_MAXINT,
											0,
											G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY
											| G_PARAM_STATIC_STRINGS);

	properties[PROP_Y] =
		g_param_spec_int ("y",
											"Y",
											"the y coordinate",
											G_MININT,
											G_MAXINT,
											0,
											G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY
											| G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
sal_point_init (SalPoint *self)
{
}

gint
sal_point_get_x (SalPoint *self)
{
	return self->x;
}

gint
sal_point_get_y (SalPoint *self)
{
	return self->y;
}

SalPoint *
sal_point_add (SalPoint *self,
               SalPoint *other)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (other != NULL, NULL);

	gint x, y;

	x = self->x + other->x;
	y = self->y + other->y;

	return sal_point_new (x, y);
}

SalPoint *
sal_point_sub (SalPoint *self,
               SalPoint *other)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (other != NULL, NULL);

	gint x, y;

	x = self->x - other->x;
	y = self->y - other->y;

	return sal_point_new (x, y);
}

gint
sal_point_crossproduct (SalPoint *self,
                        SalPoint *other)
{
	g_return_val_if_fail (self != NULL, 0);
	g_return_val_if_fail (other != NULL, 0);

	return self->x * other->y - other->x * self->y;
}

gchar*
sal_point_to_string (SalPoint *self)
{
	return g_strdup_printf ("%d %d", self->x, self->x);
}
