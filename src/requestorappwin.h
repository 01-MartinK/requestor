#pragma once

#include <gtk/gtk.h>
#include "requestorapp.h"

#define REQUESTOR_APP_WINDOW_TYPE (requestor_app_window_get_type ())
G_DECLARE_FINAL_TYPE (RequestorAppWindow, requestor_app_window, REQUESTOR, APP_WINDOW, GtkApplicationWindow)

RequestorAppWindow *requestor_app_window_new (RequestorApp *app);
void requestor_app_window_open (RequestorAppWindow *win, GFile *file);
