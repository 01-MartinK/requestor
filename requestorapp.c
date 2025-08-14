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
