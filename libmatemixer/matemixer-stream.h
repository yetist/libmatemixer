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

#ifndef MATEMIXER_STREAM_H
#define MATEMIXER_STREAM_H

#include <math.h>
#include <glib.h>
#include <glib-object.h>

#include <libmatemixer/matemixer-device.h>
#include <libmatemixer/matemixer-enums.h>
#include <libmatemixer/matemixer-port.h>

G_BEGIN_DECLS

#ifdef INFINITY
#define MATE_MIXER_INFINITY INFINITY
#else
#define MATE_MIXER_INFINITY G_MAXDOUBLE
#endif

#define MATE_MIXER_TYPE_STREAM                  \
        (mate_mixer_stream_get_type ())
#define MATE_MIXER_STREAM(o)                    \
        (G_TYPE_CHECK_INSTANCE_CAST ((o), MATE_MIXER_TYPE_STREAM, MateMixerStream))
#define MATE_MIXER_IS_STREAM(o)                 \
        (G_TYPE_CHECK_INSTANCE_TYPE ((o), MATE_MIXER_TYPE_STREAM))
#define MATE_MIXER_STREAM_GET_INTERFACE(o)      \
        (G_TYPE_INSTANCE_GET_INTERFACE ((o), MATE_MIXER_TYPE_STREAM, MateMixerStreamInterface))

typedef struct _MateMixerStream           MateMixerStream; /* dummy object */
typedef struct _MateMixerStreamInterface  MateMixerStreamInterface;

struct _MateMixerStreamInterface
{
    GTypeInterface parent_iface;

    /*< private >*/
    const gchar *            (*get_name)               (MateMixerStream          *stream);
    const gchar *            (*get_description)        (MateMixerStream          *stream);
    MateMixerDevice *        (*get_device)             (MateMixerStream          *stream);
    MateMixerStreamFlags     (*get_flags)              (MateMixerStream          *stream);
    MateMixerStreamState     (*get_state)              (MateMixerStream          *stream);
    gboolean                 (*get_mute)               (MateMixerStream          *stream);
    gboolean                 (*set_mute)               (MateMixerStream          *stream,
                                                        gboolean                  mute);
    guint                    (*get_num_channels)       (MateMixerStream          *stream);
    guint                    (*get_volume)             (MateMixerStream          *stream);
    gboolean                 (*set_volume)             (MateMixerStream          *stream,
                                                        guint                     volume);
    gdouble                  (*get_decibel)            (MateMixerStream          *stream);
    gboolean                 (*set_decibel)            (MateMixerStream          *stream,
                                                        gdouble                   decibel);
    MateMixerChannelPosition (*get_channel_position)   (MateMixerStream          *stream,
                                                        guint                     channel);
    guint                    (*get_channel_volume)     (MateMixerStream          *stream,
                                                        guint                     channel);
    gboolean                 (*set_channel_volume)     (MateMixerStream          *stream,
                                                        guint                     channel,
                                                        guint                     volume);
    gdouble                  (*get_channel_decibel)    (MateMixerStream          *stream,
                                                        guint                     channel);
    gboolean                 (*set_channel_decibel)    (MateMixerStream          *stream,
                                                        guint                     channel,
                                                        gdouble                   decibel);
    gboolean                 (*has_position)           (MateMixerStream          *stream,
                                                        MateMixerChannelPosition  position);
    guint                    (*get_position_volume)    (MateMixerStream          *stream,
                                                        MateMixerChannelPosition  position);
    gboolean                 (*set_position_volume)    (MateMixerStream          *stream,
                                                        MateMixerChannelPosition  position,
                                                        guint                     volume);
    gdouble                  (*get_position_decibel)   (MateMixerStream          *stream,
                                                        MateMixerChannelPosition  position);
    gboolean                 (*set_position_decibel)   (MateMixerStream          *stream,
                                                        MateMixerChannelPosition  position,
                                                        gdouble                   decibel);
    gfloat                   (*get_balance)            (MateMixerStream          *stream);
    gboolean                 (*set_balance)            (MateMixerStream          *stream,
                                                        gfloat                    balance);
    gfloat                   (*get_fade)               (MateMixerStream          *stream);
    gboolean                 (*set_fade)               (MateMixerStream          *stream,
                                                        gfloat                    fade);
    gboolean                 (*suspend)                (MateMixerStream          *stream);
    gboolean                 (*resume)                 (MateMixerStream          *stream);
    gboolean                 (*monitor_start)          (MateMixerStream          *stream);
    void                     (*monitor_stop)           (MateMixerStream          *stream);
    gboolean                 (*monitor_is_running)     (MateMixerStream          *stream);
    const GList *            (*list_ports)             (MateMixerStream          *stream);
    MateMixerPort *          (*get_active_port)        (MateMixerStream          *stream);
    gboolean                 (*set_active_port)        (MateMixerStream          *stream,
                                                        const gchar              *port);
    guint                    (*get_min_volume)         (MateMixerStream          *stream);
    guint                    (*get_max_volume)         (MateMixerStream          *stream);
    guint                    (*get_normal_volume)      (MateMixerStream          *stream);
    guint                    (*get_base_volume)        (MateMixerStream          *stream);

    /* Signals */
    void                     (*monitor_value)          (MateMixerStream          *stream,
                                                        gdouble                   value);
};

GType                    mate_mixer_stream_get_type               (void) G_GNUC_CONST;

const gchar *            mate_mixer_stream_get_name               (MateMixerStream          *stream);
const gchar *            mate_mixer_stream_get_description        (MateMixerStream          *stream);
MateMixerDevice *        mate_mixer_stream_get_device             (MateMixerStream          *stream);
MateMixerStreamFlags     mate_mixer_stream_get_flags              (MateMixerStream          *stream);
MateMixerStreamState     mate_mixer_stream_get_state              (MateMixerStream          *stream);

gboolean                 mate_mixer_stream_get_mute               (MateMixerStream          *stream);
gboolean                 mate_mixer_stream_set_mute               (MateMixerStream          *stream,
                                                                   gboolean                  mute);

guint                    mate_mixer_stream_get_num_channels       (MateMixerStream          *stream);

guint                    mate_mixer_stream_get_volume             (MateMixerStream          *stream);
gboolean                 mate_mixer_stream_set_volume             (MateMixerStream          *stream,
                                                                   guint                     volume);

gdouble                  mate_mixer_stream_get_decibel            (MateMixerStream          *stream);
gboolean                 mate_mixer_stream_set_decibel            (MateMixerStream          *stream,
                                                                   gdouble                   decibel);

MateMixerChannelPosition mate_mixer_stream_get_channel_position   (MateMixerStream          *stream,
                                                                   guint                     channel);

guint                    mate_mixer_stream_get_channel_volume     (MateMixerStream          *stream,
                                                                   guint                     channel);
gboolean                 mate_mixer_stream_set_channel_volume     (MateMixerStream          *stream,
                                                                   guint                     channel,
                                                                   guint                     volume);

gdouble                  mate_mixer_stream_get_channel_decibel    (MateMixerStream          *stream,
                                                                   guint                     channel);
gboolean                 mate_mixer_stream_set_channel_decibel    (MateMixerStream          *stream,
                                                                   guint                     channel,
                                                                   gdouble                   decibel);

gboolean                 mate_mixer_stream_has_position           (MateMixerStream          *stream,
                                                                   MateMixerChannelPosition  position);

guint                    mate_mixer_stream_get_position_volume    (MateMixerStream          *stream,
                                                                   MateMixerChannelPosition  position);
gboolean                 mate_mixer_stream_set_position_volume    (MateMixerStream          *stream,
                                                                   MateMixerChannelPosition  position,
                                                                   guint                     volume);

gdouble                  mate_mixer_stream_get_position_decibel   (MateMixerStream          *stream,
                                                                   MateMixerChannelPosition  position);
gboolean                 mate_mixer_stream_set_position_decibel   (MateMixerStream          *stream,
                                                                   MateMixerChannelPosition  position,
                                                                   gdouble                   decibel);

gfloat                   mate_mixer_stream_get_balance            (MateMixerStream          *stream);
gboolean                 mate_mixer_stream_set_balance            (MateMixerStream          *stream,
                                                                   gfloat                    balance);

gfloat                   mate_mixer_stream_get_fade               (MateMixerStream          *stream);
gboolean                 mate_mixer_stream_set_fade               (MateMixerStream          *stream,
                                                                   gfloat                    fade);

gboolean                 mate_mixer_stream_suspend                (MateMixerStream          *stream);
gboolean                 mate_mixer_stream_resume                 (MateMixerStream          *stream);

gboolean                 mate_mixer_stream_monitor_start          (MateMixerStream          *stream);
void                     mate_mixer_stream_monitor_stop           (MateMixerStream          *stream);

gboolean                 mate_mixer_stream_monitor_is_running     (MateMixerStream          *stream);

const GList *            mate_mixer_stream_list_ports             (MateMixerStream          *stream);

MateMixerPort *          mate_mixer_stream_get_active_port        (MateMixerStream          *stream);
gboolean                 mate_mixer_stream_set_active_port        (MateMixerStream          *stream,
                                                                   const gchar              *port);

guint                    mate_mixer_stream_get_min_volume         (MateMixerStream          *stream);
guint                    mate_mixer_stream_get_max_volume         (MateMixerStream          *stream);
guint                    mate_mixer_stream_get_normal_volume      (MateMixerStream          *stream);
guint                    mate_mixer_stream_get_base_volume        (MateMixerStream          *stream);

G_END_DECLS

#endif /* MATEMIXER_STREAM_H */