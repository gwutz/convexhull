pointtest = executable ('pointtest', 'sal-point-test.c', dependencies: [glib, gobject],
	link_with: sallib,
	include_directories: [sallib_inc])

randomtest = executable ('randomtest', ['random-points-test.c', '../src/util.c'], dependencies: [glib, gobject],
	link_with: sallib,
	include_directories: [sallib_inc, util_inc])

test('pointtest', pointtest)
test('randomtest', randomtest)
