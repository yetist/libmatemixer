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

#ifndef PULSE_STREAM_H
#define PULSE_STREAM_H

#include <glib.h>
#include <glib-object.h>

#include <libmatemixer/matemixer-device.h>
#include <libmatemixer/matemixer-stream.h>

#include <pulse/pulseaudio.h>

#include "pulse-connection.h"
#include "pulse-monitor.h"

G_BEGIN_DECLS

#define PULSE_TYPE_STREAM                       \
        (pulse_stream_get_type ())
#define PULSE_STREAM(o)                         \
        (G_TYPE_CHECK_INSTANCE_CAST ((o), PULSE_TYPE_STREAM, PulseStream))
#define PULSE_IS_STREAM(o)                      \
        (G_TYPE_CHECK_INSTANCE_TYPE ((o), PULSE_TYPE_STREAM))
#define PULSE_STREAM_CLASS(k)                   \
        (G_TYPE_CHECK_CLASS_CAST ((k), PULSE_TYPE_STREAM, PulseStreamClass))
#define PULSE_IS_STREAM_CLASS(k)                \
        (G_TYPE_CHECK_CLASS_TYPE ((k), PULSE_TYPE_STREAM))
#define PULSE_STREAM_GET_CLASS(o)               \
        (G_TYPE_INSTANCE_GET_CLASS ((o), PULSE_TYPE_STREAM, PulseStreamClass))

typedef struct _PulseStream         PulseStream;
typedef struct _PulseStreamClass    PulseStreamClass;
typedef struct _PulseStreamPrivate  PulseStreamPrivate;

struct _PulseStream
{
    GObject parent;

    /*< private >*/
    PulseStreamPrivate *priv;
};

struct _PulseStreamClass
{
    GObjectClass parent_class;

    gboolean      (*set_mute)        (MateMixerStream *stream,
                                      gboolean         mute);
    gboolean      (*set_volume)      (MateMixerStream *stream,
                                      pa_cvolume      *volume);

    gboolean      (*set_active_port) (MateMixerStream *stream,
                                      const gchar     *port_name);

    gboolean      (*suspend)         (MateMixerStream *stream);
    gboolean      (*resume)          (MateMixerStream *stream);

    PulseMonitor *(*create_monitor)  (MateMixerStream *stream);
};

GType            pulse_stream_get_type               (void) G_GNUC_CONST;

guint32          pulse_stream_get_index              (PulseStream           *stream);
PulseConnection *pulse_stream_get_connection         (PulseStream           *stream);
PulseMonitor *   pulse_stream_get_monitor            (PulseStream           *stream);

gboolean         pulse_stream_update_name            (PulseStream           *stream,
                                                      const gchar           *name);
gboolean         pulse_stream_update_description     (PulseStream           *stream,
                                                      const gchar           *description);
gboolean         pulse_stream_update_device          (PulseStream           *stream,
                                                      MateMixerDevice       *device);
gboolean         pulse_stream_update_flags           (PulseStream           *stream,
                                                      MateMixerStreamFlags   flags);
gboolean         pulse_stream_update_state           (PulseStream           *stream,
                                                      MateMixerStreamState   state);
gboolean         pulse_stream_update_mute            (PulseStream           *stream,
                                                      gboolean               mute);

gboolean         pulse_stream_update_volume          (PulseStream           *stream,
                                                      const pa_cvolume      *volume,
                                                      const pa_channel_map  *map,
                                                      pa_volume_t            base_volume);

gboolean         pulse_stream_update_channel_map     (PulseStream           *stream,
                                                      const pa_channel_map  *map);

gboolean         pulse_stream_update_ports           (PulseStream           *stream,
                                                      GList                 *ports);
gboolean         pulse_stream_update_active_port     (PulseStream           *stream,
                                                      const gchar           *port_name);

G_END_DECLS

#endif /* PULSE_STREAM_H */