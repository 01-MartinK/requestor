#include <gtk/gtk.h>

#include "requestorapp.h"
#include "requestorappwin.h"

struct _RequestorAppWindow
{
  GtkApplicationWindow parent;

  GtkWidget *stack;
  GtkWidget *gears;
  GtkEntry *url_entry;
  GtkDropDown *request_type;
};

G_DEFINE_TYPE(RequestorAppWindow, requestor_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void on_request_button_send(GtkButton *button, RequestorAppWindow *self)
{
  const char *url = gtk_editable_get_text(GTK_EDITABLE(self->url_entry));
  const guint pos = gtk_drop_down_get_selected(GTK_DROP_DOWN(self->request_type));
  // check if position in invalid
  if (pos != GTK_INVALID_LIST_POSITION) {
    GtkStringList *list = GTK_STRING_LIST(gtk_drop_down_get_model(GTK_DROP_DOWN(self->request_type)));
    const char *type = gtk_string_list_get_string(list, pos);
    g_print("Test button function: %s%s\n", type, url);
  }
  else {
    g_error("[GtkDropDown] Index outside of list");
  }
}

static void requestor_app_window_init(RequestorAppWindow *win)
{
  GtkBuilder *builder;
  GMenuModel *menu;

  gtk_widget_init_template(GTK_WIDGET (win));
  
  builder = gtk_builder_new_from_resource("/org/mk/requestor/gears-menu.ui");
  menu = G_MENU_MODEL(gtk_builder_get_object(builder, "menu"));
  gtk_menu_button_set_menu_model(GTK_MENU_BUTTON (win->gears), menu);
  g_object_unref(builder);
}

static void requestor_app_window_class_init(RequestorAppWindowClass *class)
{
  gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS (class), "/org/mk/requestor/window.ui");

  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS (class), RequestorAppWindow, stack);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS (class), RequestorAppWindow, gears);
  gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS (class), on_request_button_send);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS (class), RequestorAppWindow, url_entry);
  gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS (class), RequestorAppWindow, request_type);
}

RequestorAppWindow *requestor_app_window_new(RequestorApp *app)
{
  return g_object_new (REQUESTOR_APP_WINDOW_TYPE, "application", app, NULL);
}

void requestor_app_window_open(RequestorAppWindow *win, GFile *file)
{
  char *basename;
  GtkWidget *scrolled, *view;
  char *contents;
  gsize length;

  basename = g_file_get_basename(file);

  scrolled = gtk_scrolled_window_new();
  gtk_widget_set_hexpand(scrolled, TRUE);
  gtk_widget_set_vexpand(scrolled, TRUE);
  view = gtk_text_view_new();
  
  gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view), FALSE);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), view);
  
  gtk_stack_add_titled(GTK_STACK(win->stack), scrolled, basename, basename);

  if (g_file_load_contents(file, NULL, &contents, &length, NULL, NULL))
  {
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gtk_text_buffer_set_text(buffer, contents, length);
    g_free(contents);
  }

  g_free(basename);
}

