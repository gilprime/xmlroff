/* Fo
 * fo-property-block-progression-dimension-maximum.h: 'block-progression-dimension-maximum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM_H__
#define __FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* block-progression-dimension-maximum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | <length> | <percentage> | <length-range> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM              (fo_property_block_progression_dimension_maximum_get_type ())
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM, FoPropertyBlockProgressionDimensionMaximum))
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM, FoPropertyBlockProgressionDimensionMaximumClass))
#define FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM))
#define FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM))
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM, FoPropertyBlockProgressionDimensionMaximumClass))


typedef struct _FoPropertyBlockProgressionDimensionMaximum      FoPropertyBlockProgressionDimensionMaximum;
typedef struct _FoPropertyBlockProgressionDimensionMaximumClass FoPropertyBlockProgressionDimensionMaximumClass;

GType        fo_property_block_progression_dimension_maximum_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_block_progression_dimension_maximum_new         (void);
FoProperty * fo_property_block_progression_dimension_maximum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM_H__ */
