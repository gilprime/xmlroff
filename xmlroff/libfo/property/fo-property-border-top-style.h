/* Fo
 * fo-property-border-top-style.h: 'border-top-style' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_TOP_STYLE_H__
#define __FO_PROPERTY_BORDER_TOP_STYLE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* border-top-style */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-style> | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_BORDER_TOP_STYLE              (fo_property_border_top_style_get_type ())
#define FO_PROPERTY_BORDER_TOP_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_TOP_STYLE, FoPropertyBorderTopStyle))
#define FO_PROPERTY_BORDER_TOP_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_TOP_STYLE, FoPropertyBorderTopStyleClass))
#define FO_IS_PROPERTY_BORDER_TOP_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_TOP_STYLE))
#define FO_IS_PROPERTY_BORDER_TOP_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_TOP_STYLE))
#define FO_PROPERTY_BORDER_TOP_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_TOP_STYLE, FoPropertyBorderTopStyleClass))


typedef struct _FoPropertyBorderTopStyle      FoPropertyBorderTopStyle;
typedef struct _FoPropertyBorderTopStyleClass FoPropertyBorderTopStyleClass;

GType        fo_property_border_top_style_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_top_style_new         (void);
FoProperty * fo_property_border_top_style_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_TOP_STYLE_H__ */
