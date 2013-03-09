#include <gtk/gtk.h>

int main(int argc, char** argv)
{
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *da;

	gtk_init(&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title( GTK_WINDOW (window), "Drawing Area");

	g_signal_connect(window, "destroy", G_CALLBACK (close_window), NULL);

	gtk_container_set_border_width (GTK_CONTAINER (window), 8);

	frame = gtk_frame_new (NULL);

	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
	gtk_container_add (GTK_CONTAINER (window), frame);

	da = gtk_drawing_area_new ();

	/* set a minimum size */

	gtk_widget_set_size_request (da, 100, 100);

	gtk_container_add (GTK_CONTAINER (frame), da);


	/* Signals used to handle the backing surface */
	g_signal_connect (da, "draw",
		G_CALLBACK (draw_cb), NULL);
	g_signal_connect (da, "configure-event",
		G_CALLBACK (configure_event_cb), NULL);

	/* Event signals */
	g_signal_connect (da, "motion-notify-event",
		G_CALLBACK (motion_notify_event_cb), NULL);
	g_signal_connect (da, "button-press-event",
		G_CALLBACK (button_press_event_cb), NULL);

	/* Ask to recieve events the drawing area doesn't normally
	 * subscribe to.  In particular, we need to ask for the
	 * button press and motion notify events that we want to handle.
	 */
	gtk_widget_set_events (da, gtk_widget_get_events (da)
		| GDK_BUTTON_PRESS_MASK
		| GDK_POINTER_MOTION_MASK);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;


}
