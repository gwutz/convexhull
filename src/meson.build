jarvis_sources = [
	'main.c',
	'jarvis.c',
	'util.c'
]

util_inc = include_directories('.')

executable('jarvis-march', jarvis_sources,
	dependencies: [glib, gobject],
	link_with: sallib,
	include_directories: [sallib_inc]
	)
