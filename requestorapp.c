#include <gtk/gtk.h>

#include "requestorapp.h"
#include "requestorappwin.h"

struct _RequestorApp
{
  GtkApplication parent;
};

G_DEFINE_TYPE(RequestorApp, requestor_app, GTK_TYPE_APPLICATION);

static void requestor_app_init(RequestorApp *app)
{
}

static void preferences_activated(GSimpleAction *action, GVariant *parameter, gpointer app)
{

}

static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app)
{
  g_application_quit (G_APPLICATION (app));
}

static GActionEntry app_entries[] =
  {
    { "preferences", preferences_activated, NULL, NULL, NULL },
    { "quit", quit_activated, NULL, NULL, NULL }
  };

static void requestor_app_startup(GApplication *app)
{
  const char *quit_accels[2] = { "<Ctrl>Q", NULL };

  G_APPLICATION_CLASS (requestor_app_parent_class)->startup (app);

  g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries, G_N_ELEMENTS (app_entries), app);

  gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.quit", quit_accels);
}

static void requestor_app_activate(GApplication *app)
{
  RequestorAppWindow *win;

  win = requestor_app_window_new (REQUESTOR_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void requestor_app_open(GApplication *app, GFile **files, int n_files, const char *hint)
{
  GList *windows;
  RequestorAppWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = REQUESTOR_APP_WINDOW (windows->data);
  else
    win = requestor_app_window_new (REQUESTOR_APP (app));

  for (i = 0; i < n_files; i++)
    requestor_app_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}

static void requestor_app_class_init(RequestorAppClass *class)
{
  G_APPLICATION_CLASS (class)->activate = requestor_app_activate;
  G_APPLICATION_CLASS (class)->open = requestor_app_open;
}

RequestorApp *requestor_app_new(void)
{
  return g_object_new (REQUESTOR_APP_TYPE, "application-id", "org.mk.requestor", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
