/* Fo
 * fo-property-border-left-width.h: 'border-left-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_LEFT_WIDTH_H__
#define __FO_PROPERTY_BORDER_LEFT_WIDTH_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* border-left-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-width> | inherit */
/* Initial value: medium */

#define FO_TYPE_PROPERTY_BORDER_LEFT_WIDTH              (fo_property_border_left_width_get_type ())
#define FO_PROPERTY_BORDER_LEFT_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_LEFT_WIDTH, FoPropertyBorderLeftWidth))
#define FO_PROPERTY_BORDER_LEFT_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_LEFT_WIDTH, FoPropertyBorderLeftWidthClass))
#define FO_IS_PROPERTY_BORDER_LEFT_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_LEFT_WIDTH))
#define FO_IS_PROPERTY_BORDER_LEFT_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_LEFT_WIDTH))
#define FO_PROPERTY_BORDER_LEFT_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_LEFT_WIDTH, FoPropertyBorderLeftWidthClass))


typedef struct _FoPropertyBorderLeftWidth      FoPropertyBorderLeftWidth;
typedef struct _FoPropertyBorderLeftWidthClass FoPropertyBorderLeftWidthClass;

GType        fo_property_border_left_width_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_left_width_new         (void);
FoProperty * fo_property_border_left_width_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_LEFT_WIDTH_H__ */
