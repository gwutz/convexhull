#include <glib.h>
#include <locale.h>
#include "sal-point.h"

void
test_point_creation ()
{
	SalPoint *point = sal_point_new (10, 10);
	g_assert (point != NULL);
}

void
test_point_add ()
{
	SalPoint *first = sal_point_new (10, 10);
	SalPoint *second = sal_point_new (10, 10);

	SalPoint *added = sal_point_add (first, second);

	g_assert_cmpint (sal_point_get_x(added), ==, 20);
	g_assert_cmpint (sal_point_get_y(added), ==, 20);
}

gint
main (gint   argc,
      gchar *argv[])
{

	setlocale (LC_ALL, "");

	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/sallib/point", test_point_creation);
	g_test_add_func ("/sallib/point_add", test_point_add);

	return g_test_run ();
}
