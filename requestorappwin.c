#include <gtk/gtk.h>

#include "requestorapp.h"
#include "requestorappwin.h"

struct _RequestorAppWindow
{
  GtkApplicationWindow parent;
};

G_DEFINE_TYPE(RequestorAppWindow, requestor_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void requestor_app_window_init(RequestorAppWindow *app)
{
}

static void requestor_app_window_class_init(RequestorAppWindowClass *class)
{
}

RequestorAppWindow *requestor_app_window_new(RequestorApp *app)
{
  return g_object_new (REQUESTOR_APP_WINDOW_TYPE, "application", app, NULL);
}

void requestor_app_window_open(RequestorAppWindow *win, GFile *file)
{
}

