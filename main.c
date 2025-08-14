#include <gtk/gtk.h>

#include "requestorapp.h"

int main (int argc, char *argv[])
{
  return g_application_run (G_APPLICATION (requestor_app_new ()), argc, argv);
}
