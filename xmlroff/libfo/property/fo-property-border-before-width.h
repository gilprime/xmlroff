/* Fo
 * fo-property-border-before-width.h: 'border-before-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_BEFORE_WIDTH_H__
#define __FO_PROPERTY_BORDER_BEFORE_WIDTH_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* border-before-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-width> | <length-conditional> | inherit */
/* Initial value: medium */

#define FO_TYPE_PROPERTY_BORDER_BEFORE_WIDTH              (fo_property_border_before_width_get_type ())
#define FO_PROPERTY_BORDER_BEFORE_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_BEFORE_WIDTH, FoPropertyBorderBeforeWidth))
#define FO_PROPERTY_BORDER_BEFORE_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_BEFORE_WIDTH, FoPropertyBorderBeforeWidthClass))
#define FO_IS_PROPERTY_BORDER_BEFORE_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_BEFORE_WIDTH))
#define FO_IS_PROPERTY_BORDER_BEFORE_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_BEFORE_WIDTH))
#define FO_PROPERTY_BORDER_BEFORE_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_BEFORE_WIDTH, FoPropertyBorderBeforeWidthClass))


typedef struct _FoPropertyBorderBeforeWidth      FoPropertyBorderBeforeWidth;
typedef struct _FoPropertyBorderBeforeWidthClass FoPropertyBorderBeforeWidthClass;

GType        fo_property_border_before_width_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_before_width_new         (void);
FoProperty * fo_property_border_before_width_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_BEFORE_WIDTH_H__ */
