/* Fo
 * fo-integer.h: Integer datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_INTEGER_H__
#define __FO_INTEGER_H__

#include <libfo/fo-utils.h>
#include <libfo/datatype/fo-datatype.h>

G_BEGIN_DECLS

#define FO_TYPE_INTEGER              (fo_integer_get_type ())
#define FO_INTEGER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_INTEGER, FoInteger))
#define FO_INTEGER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_INTEGER, FoIntegerClass))
#define FO_IS_INTEGER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_INTEGER))
#define FO_IS_INTEGER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_INTEGER))
#define FO_INTEGER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_INTEGER, FoIntegerClass))


typedef struct _FoInteger      FoInteger;
typedef struct _FoIntegerClass FoIntegerClass;

GType       fo_integer_get_type          (void) G_GNUC_CONST;
FoDatatype *fo_integer_new               (void);
FoDatatype *fo_integer_new_with_value    (gint value);

gint        fo_integer_get_value         (FoDatatype *integer);

FoDatatype* fo_integer_get_integer_zero  (void);
FoDatatype* fo_integer_get_integer_one   (void);
FoDatatype* fo_integer_get_integer_two   (void);
FoDatatype* fo_integer_get_integer_three (void);
FoDatatype* fo_integer_get_integer_four  (void);
FoDatatype* fo_integer_get_integer_five  (void);
FoDatatype* fo_integer_get_integer_six   (void);

G_END_DECLS

#endif /* !__FO_INTEGER_H__ */
