/* libfo
 * libfo-version.h: libfo version
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __LIBFO_VERSION_H__
#define __LIBFO_VERSION_H__

/* libfo-features.h is autogenerated.  The constants it defines are
   documented here. */
#include <libfo/libfo-features.h>
#include <glib.h>

G_BEGIN_DECLS

/**
 * SECTION:libfo-version
 * @short_description: libfo version checking
 *
 * The capital-letter macros defined here can be used to check the
 * version of libfo at compile-time, and to
 * <emphasis>encode</emphasis> libfo versions into integers. The
 * functions can be used to check the version of the linked libfo
 * library at run-time.
 */

/**
 * LIBFO_VERSION_MAJOR:
 *
 * The major component of the version of libfo available at
 * compile-time.
 */

/**
 * LIBFO_VERSION_MINOR:
 *
 * The minor component of the version of libfo available at
 * compile-time.
 */

/**
 * LIBFO_VERSION_MICRO:
 *
 * The micro component of the version of libfo available at
 * compile-time.
 */

/**
 * LIBFO_VERSION_STRING:
 *
 * A string literal containing the version of libfo available at
 * compile-time.
 */


/**
 * LIBFO_PIXELS_PER_INCH:
 *
 * Pixels per inch for use with graphics without intrinsic size.
 */


/**
 * LIBFO_VERSION_ENCODE:
 * @major: the major component of the version number
 * @minor: the minor component of the version number
 * @micro: the micro component of the version number
 *
 *
 * This macro encodes the given libfo version into an integer. The
 * numbers returned by #LIBFO_VERSION and libfo_version() are encoded
 * using this macro. Two encoded version numbers can be compared as
 * integers.
 */
#define LIBFO_VERSION_ENCODE(major, minor, micro) (     \
	  ((major) * 10000)                             \
	+ ((minor) *   100)                             \
	+ ((micro) *     1))

/**
 * LIBFO_VERSION:
 *
 * The version of libfo available at compile-time, encoded using
 * LIBFO_VERSION_ENCODE().
 */
#define LIBFO_VERSION LIBFO_VERSION_ENCODE(     \
	LIBFO_VERSION_MAJOR,                    \
	LIBFO_VERSION_MINOR,                    \
	LIBFO_VERSION_MICRO)

/**
 * LIBFO_VERSION_CHECK:
 * @major: the major component of the version number
 * @minor: the minor component of the version number
 * @micro: the micro component of the version number
 *
 * Checks that the version of libfo available at compile-time is
 * not older than the provided version number.
 */
#define LIBFO_VERSION_CHECK(major,minor,micro)    \
	(LIBFO_VERSION >= LIBFO_VERSION_ENCODE(major,minor,micro))


/* Return encoded version of libfo at run-time */
int libfo_version (void);

/* Return run-time libfo version as an string */
const char * libfo_version_string (void);

/* Check that run-time libfo is as new as required */
const char * libfo_version_check (int required_major,
				  int required_minor,
				  int required_micro);

int libfo_pixels_per_inch (void);

typedef struct {
  const gchar *nick;
  const gchar *name;
  gint         version;
  const gchar *version_string;
} LibfoVersionInfo;

const LibfoVersionInfo * libfo_version_backend_info (void);

G_END_DECLS

#endif /* __LIBFO_VERSION_H__ */
