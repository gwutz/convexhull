jarvis_sources = [
	'main.c',
	'jarvis.c',
	'util.c',
	'jarvis-application.c',
	'jarvis-application-window.c'
]

gnome = import('gnome')

resources = gnome.compile_resources('jarvis-resources', 'jarvis-resources.xml')

gtk = dependency('gtk+-3.0')

util_inc = include_directories('.')

executable('jarvis-march', resources + jarvis_sources,
	dependencies: [glib, gobject, gtk],
	link_with: sallib,
	include_directories: [sallib_inc],
	install: true
	)
