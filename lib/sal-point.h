/* sal-point.h
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
#ifndef SAL_POINT_H
#define SAL_POINT_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SAL_TYPE_POINT (sal_point_get_type())

G_DECLARE_FINAL_TYPE (SalPoint, sal_point, SAL, POINT, GObject)

SalPoint *sal_point_new (gint x, gint y);
gint      sal_point_get_x (SalPoint *self);
gint      sal_point_get_y (SalPoint *self);
SalPoint *sal_point_add (SalPoint *self,
                         SalPoint *other);
SalPoint *sal_point_sub (SalPoint *self,
                         SalPoint *other);
gint      sal_point_crossproduct (SalPoint *self,
                                  SalPoint *other);
G_END_DECLS

#endif /* SAL_POINT_H */

