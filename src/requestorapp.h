#pragma once

#include <gtk/gtk.h>

#define REQUESTOR_APP_TYPE (requestor_app_get_type ())
G_DECLARE_FINAL_TYPE (RequestorApp, requestor_app, REQUESTOR, APP, GtkApplication)

RequestorApp *requestor_app_new (void);
