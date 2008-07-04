/* libfo
 * libfo-version.c: libfo version
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * Inspired by Pango and Cairo version APIs.
 *
 * See COPYING for the status of this software.
 */

#include <config.h>
#include <libfo/fo-utils.h>
#include "libfo/libfo-features.h"
#include "libfo/libfo-version.h"
#if ENABLE_CAIRO
#include <libfo/fo-doc-cairo.h>
#endif
#if ENABLE_GP
#include <libfo/fo-doc-gp.h>
#endif

/**
 * libfo_version:
 *
 * This is similar to the macro %LIBFO_VERSION except that it returns
 * the encoded version of libfo available at run-time, as opposed
 * to the version available at compile-time.
 *
 * A version number can be encoded into an integer using
 * LIBFO_VERSION_ENCODE().
 *
 * Returns value: The encoded version of libfo library
 *   available at run time.
 **/
int
libfo_version (void)
{
  return LIBFO_VERSION;
}

/**
 * libfo_version_string:
 *
 * This is similar to the macro %LIBFO_VERSION_STRING except that it
 * returns the version of libfo available at run-time, as opposed
 * to the version available at compile-time.
 *
 * Returns value: A string containing the version of libfo library
 *   available at run time.
 *   The returned string is owned by libfo and should not be modified
 *   or freed.
 **/
const char *
libfo_version_string (void)
{
  return LIBFO_VERSION_STRING;
}

/**
 * libfo_version_check:
 * @required_major: the required major version.
 * @required_minor: the required minor version.
 * @required_micro: the required major version.
 *
 * Checks that the libfo library in use is compatible with the
 * given version. Generally you would pass in the constants
 * %LIBFO_VERSION_MAJOR, %LIBFO_VERSION_MINOR, %LIBFO_VERSION_MICRO as the
 * three arguments to this function; that produces a check that the
 * library in use at run-time is compatible with the version of
 * libfo the application or module was compiled against.
 *
 * Compatibility is defined by two things: first the version
 * of the running library is newer than the version
 * @required_major.required_minor.@required_micro. Second
 * the running library must be binary compatible with the
 * version @required_major.required_minor.@required_micro
 * (same major version.)
 *
 * For compile-time version checking use LIBFO_VERSION_CHECK().
 *
 * Return value: %NULL if the libfo library is compatible with the
 *   given version, or a string describing the version mismatch.  The
 *   returned string is owned by libfo and should not be modified
 *   or freed.
 **/
const char*
libfo_version_check (int required_major,
		     int required_minor,
		     int required_micro)
{
  gint libfo_effective_micro = 100 * XMLROFF_VERSION_MINOR + XMLROFF_VERSION_MICRO;
  gint required_effective_micro = 100 * required_minor + required_micro;

  if (required_major < XMLROFF_VERSION_MAJOR)
    return "libfo version too new (major mismatch)";
  if (required_effective_micro < libfo_effective_micro - XMLROFF_BINARY_AGE)
    return "libfo version too new (micro mismatch)";
  if (required_effective_micro > libfo_effective_micro)
    return "libfo version too old (micro mismatch)";
  return NULL;
}

/**
 * libfo_pixels_per_inch:
 *
 * This is similar to the macro %LIBFO_PIXELS_PER_INCH except that it
 * returns the encoded pixels per inch of libfo available at run-time,
 * as opposed to the pixels per inch available at compile-time.
 *
 * Returns value: The encoded pixels per inch of libfo library
 *   available at run time.
 **/
int
libfo_pixels_per_inch (void)
{
  return PIXELS_PER_INCH;
}

enum {
#if ENABLE_CAIRO
  CAIRO_INFO,
#endif
#if ENABLE_GP
  GP_INFO,
#endif
  NULL_INFO,
  INFO_LIMIT
};

const LibfoVersionInfo *
libfo_version_backend_info (void)
{
  static LibfoVersionInfo * backend_info = NULL;

  if (backend_info == NULL)
    {
      backend_info = g_new0 (LibfoVersionInfo, INFO_LIMIT);

#if ENABLE_CAIRO
      backend_info[CAIRO_INFO].nick = "cairo";
      backend_info[CAIRO_INFO].name =
	g_type_name (fo_doc_cairo_get_type ());
      backend_info[CAIRO_INFO].version =
	fo_doc_version_from_name (g_type_name (fo_doc_cairo_get_type ()));
      backend_info[CAIRO_INFO].version_string =
	fo_doc_version_string_from_name (g_type_name (fo_doc_cairo_get_type ()));

#endif

#if ENABLE_GP
      backend_info[GP_INFO].nick = "gp";
      backend_info[GP_INFO].name =
	g_type_name (fo_doc_gp_get_type ());
      backend_info[GP_INFO].version =
	fo_doc_version_from_name (g_type_name (fo_doc_gp_get_type ()));
      backend_info[GP_INFO].version_string =
	fo_doc_version_string_from_name (g_type_name (fo_doc_gp_get_type ()));
#endif
    }

  return backend_info;
}