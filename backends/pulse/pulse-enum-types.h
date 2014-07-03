/*
 * Copyright (C) 2014 Michal Ratajsky <michal.ratajsky@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the licence, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PULSE_ENUM_TYPES_H
#define PULSE_ENUM_TYPES_H

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/*
 * GTypes are not generated by glib-mkenums, see:
 * https://bugzilla.gnome.org/show_bug.cgi?id=621942
 */

#define PULSE_TYPE_CONNECTION_STATE (pulse_connection_state_get_type ())
GType pulse_connection_state_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* PULSE_ENUM_TYPES_H */