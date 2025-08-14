app_resources = gnome.compile_resources('requestorapp_resources', 'requestorapp.gresource.xml', source_dir: meson.current_source_dir())

executable('requestorapp','requestorapp.c','requestorappwin.c', 'main.c', app_resources, dependencies: libgtk_dep, c_args: common_cflags)
