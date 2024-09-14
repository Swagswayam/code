#include <stdio.h>
#include <gtk/gtk.h>

void load_css(const char *css_file) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    if (!gtk_css_provider_load_from_path(provider, css_file, NULL)) {
        g_printerr("Failed to load CSS file: %s\n", css_file);
    }

    GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(screen));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Application with CSS");

    // Load CSS styles
    load_css("styles.css"); // Specify the path to your CSS file here

    // Create and configure GTK widgets...

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
