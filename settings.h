/*
 * lock-keys - Caps lock indicator fo linux laptops
 * Copyright (C) 2014 Fernando Rodriguez (frodriguez.developer@outlook.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>

typedef struct
{
	gdouble opacity;
	gboolean overlay;
	gint timeout;
	gboolean autostart;
}
LK_SETTINGS;

extern LK_SETTINGS lk_settings;

void settings_load();
void settings_save();
void settings_dialog_show();
