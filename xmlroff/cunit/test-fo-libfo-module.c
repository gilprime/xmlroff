/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include <CUnit/Basic.h>
#include <libfo/fo-libfo-basic.h>
#include <libfo/fo-libfo-module.h>
#include <libfo/fo-doc.h>
#include <libfo/fo-doc-gp.h>
#include <libfo/fo-doc-cairo.h>
#include <cairo/cairo.h>

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
static int
init_suite (void)
{
  fo_libfo_init ();

  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
static int
clean_suite (void)
{
  fo_libfo_shutdown ();

  return 0;
}

static void
test_fo_libfo_module_version (void)
{
  CU_ASSERT_EQUAL (fo_libfo_module_version_from_name (NULL),
		   0);

  CU_ASSERT_EQUAL (fo_libfo_module_version_from_name ("bogus"),
		   0);

  /* Class that is not a FoDoc subtype should return unknown
     format. */
  CU_ASSERT_EQUAL (fo_libfo_module_version_from_name (g_type_name (fo_object_get_type ())),
		   0);

  CU_ASSERT_EQUAL (fo_libfo_module_version_from_name (g_type_name (fo_doc_get_type ())),
		   0);

  CU_ASSERT_EQUAL (fo_libfo_module_version_from_name (g_type_name (fo_doc_cairo_get_type ())),
		   cairo_version ());
#if ENABLE_GP
  CU_ASSERT_EQUAL (fo_libfo_module_version_from_name (g_type_name (fo_doc_gp_get_type ())),
		   0);
#endif
}

static void
test_fo_libfo_module_version_string (void)
{
  CU_ASSERT_EQUAL (fo_libfo_module_version_string_from_name (NULL),
		   NULL);

  CU_ASSERT_EQUAL (fo_libfo_module_version_string_from_name ("bogus"),
		   NULL);

  /* Class that is not a FoDoc subtype should return unknown
     format. */
  CU_ASSERT_EQUAL (fo_libfo_module_version_string_from_name (g_type_name (fo_object_get_type ())),
		   NULL);

  CU_ASSERT_EQUAL (fo_libfo_module_version_string_from_name (g_type_name (fo_doc_get_type ())),
		   NULL);

  CU_ASSERT_EQUAL (fo_libfo_module_version_string_from_name (g_type_name (fo_doc_cairo_get_type ())),
		   cairo_version_string ());

#if ENABLE_GP
  CU_ASSERT_EQUAL (fo_libfo_module_version_string_from_name (g_type_name (fo_doc_gp_get_type ())),
		   NULL);
#endif
}

static CU_TestInfo test_array[] = {
  { "FoLibfoModule get version",
    test_fo_libfo_module_version },
  { "FoLibfoModule get version string",
    test_fo_libfo_module_version_string },
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  { "fo-libfo-module", init_suite, clean_suite, test_array },
  CU_SUITE_INFO_NULL,
};

CU_SuiteInfo *
test_fo_libfo_module_get_suites (void)
{
  return suites;
}

