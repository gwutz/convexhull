pointtest = executable ('pointtest', 'sal-point-test.c', dependencies: [glib, gobject],
	link_with: sallib,
	include_directories: [sallib_inc])

test('pointtest', pointtest)
