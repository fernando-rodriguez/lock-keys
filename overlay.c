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
#include "overlay.h"

static guint timer_id = 0;
static GtkWidget* overlay_label = NULL;
static GtkWidget* overlay_window = NULL;
static guint timeout_secs = 2;
static gdouble overlay_opacity = 1.0;

static gboolean autohide_window(gpointer data)
{
	gtk_widget_hide(GTK_WIDGET(overlay_window));
	timer_id = 0;
	return FALSE;
}

static void create_window()
{
	g_debug("Creating overlay window");
	gint width, height;
	gint screen_width, screen_height;
	GdkScreen* screen;

	width = 150;
	height = 150;

	overlay_window = gtk_window_new (GTK_WINDOW_POPUP);
	screen = gtk_window_get_screen(GTK_WINDOW(overlay_window));
	screen_width = gdk_screen_get_width(screen);
	screen_height = gdk_screen_get_height(screen);

	gtk_window_set_keep_above(GTK_WINDOW(overlay_window), TRUE);
	gtk_window_resize(GTK_WINDOW(overlay_window), width, height);
	gtk_window_move(GTK_WINDOW(overlay_window), 
		(screen_width / 2) - (width / 2), (screen_height) - (height) - 100);
	gtk_container_set_border_width (GTK_CONTAINER(overlay_window), 10);

	overlay_label = gtk_label_new("A");
	gtk_container_add(GTK_CONTAINER(overlay_window), overlay_label);

	gtk_widget_show(overlay_label);

}

void overlay_state_set(gboolean enabled)
{
	if (enabled)
	{
		if (overlay_window == NULL)
			create_window();
	}
	else
	{
		gtk_widget_destroy(overlay_label);
		gtk_widget_destroy(overlay_window);
		overlay_label = NULL;
		overlay_window = NULL;
	}
}

void overlay_caps_lock_set(gboolean caps_lock)
{
	/*
	gchar* markup = g_markup_printf_escaped(
		"<span size=\"100000\">%s</span>", (caps_lock ? "A" : "a"));

	gtk_label_set_markup(GTK_LABEL(label), markup);
	g_free(markup);
	*/
	if (overlay_window != NULL)
	{
		if (caps_lock)
		{
			gtk_label_set_markup(
				GTK_LABEL(overlay_label), "<span size=\"100000\">A</span>");
		}
		else
		{
			gtk_label_set_markup(
				GTK_LABEL(overlay_label), "<span size=\"100000\">a</span>");
		}
	}
}

void overlay_show()
{

	if (overlay_window ==  NULL)
		return;

	g_debug("opacity: %f", overlay_opacity);
	gtk_widget_show(GTK_WIDGET(overlay_window));
	gtk_widget_set_opacity(GTK_WIDGET(overlay_window), overlay_opacity);

	if (timer_id)
		g_source_remove(timer_id);

	timer_id = g_timeout_add_seconds(
		timeout_secs, autohide_window, NULL);


}

void overlay_opacity_set(gdouble opacity)
{
	g_debug("Setting overlay opacity");
	overlay_opacity = opacity;
}

void overlay_timeout_set(guint seconds)
{
	timeout_secs = seconds;
}

