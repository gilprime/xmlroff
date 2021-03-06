/* Fo
 * fo-property-space-start-minimum.c: 'space-start-minimum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-space-start-minimum.h"
#include "property/fo-property-util.h"

/* space-start-minimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

struct _FoPropertySpaceStartMinimum
{
  FoProperty parent_instance;
};

struct _FoPropertySpaceStartMinimumClass
{
  FoPropertyClass parent_class;
};

static void fo_property_space_start_minimum_init         (FoPropertySpaceStartMinimum      *property_space_start_minimum);
static void fo_property_space_start_minimum_class_init   (FoPropertySpaceStartMinimumClass *klass);
static void fo_property_space_start_minimum_finalize     (GObject       *object);

static FoDatatype* fo_property_space_start_minimum_validate (FoDatatype *datatype,
                                                              FoContext  *context,
                                                              GError    **error);

static const gchar class_name[] = "space-start-minimum";
static gpointer parent_class;

/**
 * fo_property_space_start_minimum_get_type:
 * 
 * Register the #FoPropertySpaceStartMinimum type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertySpaceStartMinimum.
 **/
GType
fo_property_space_start_minimum_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertySpaceStartMinimumClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_space_start_minimum_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertySpaceStartMinimum),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_space_start_minimum_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_space_start_minimum_init:
 * @space_start_minimum: #FoPropertySpaceStartMinimum object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertySpaceStartMinimum.
 **/
void
fo_property_space_start_minimum_init (FoPropertySpaceStartMinimum *space_start_minimum)
{
  FO_PROPERTY (space_start_minimum)->value =
    g_object_ref (fo_length_get_length_zero ());
}

/**
 * fo_property_space_start_minimum_class_init:
 * @klass: #FoPropertySpaceStartMinimumClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertySpaceStartMinimumClass.
 **/
void
fo_property_space_start_minimum_class_init (FoPropertySpaceStartMinimumClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_space_start_minimum_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_space_start_minimum_validate;
  property_class->get_initial =
    fo_property_space_start_minimum_get_initial;
}

/**
 * fo_property_space_start_minimum_finalize:
 * @object: #FoPropertySpaceStartMinimum object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertySpaceStartMinimum.
 **/
void
fo_property_space_start_minimum_finalize (GObject *object)
{
  FoPropertySpaceStartMinimum *space_start_minimum;

  space_start_minimum = FO_PROPERTY_SPACE_START_MINIMUM (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_space_start_minimum_new:
 * 
 * Creates a new #FoPropertySpaceStartMinimum initialized to default value.
 * 
 * Return value: the new #FoPropertySpaceStartMinimum.
 **/
FoProperty*
fo_property_space_start_minimum_new (void)
{
  FoProperty* space_start_minimum;

  space_start_minimum =
    FO_PROPERTY (g_object_new (fo_property_space_start_minimum_get_type (),
                               NULL));

  return space_start_minimum;
}

/**
 * fo_property_space_start_minimum_validate:
 * @datatype: #FoDatatype to be validated against allowed datatypes and
 *            values for current property.
 * @context:  #FoContext object from which to possibly inherit values.
 * @error:    Information about any error that has occurred.
 * 
 * Validates @datatype against allowed values.  Returns @datatype, a
 * replacement datatype value, or NULL if validation failed.
 * 
 * Return value: Valid datatype value or NULL.
 **/
FoDatatype*
fo_property_space_start_minimum_validate (FoDatatype *datatype,
                                           FoContext  *context,
                                           GError    **error)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_LENGTH (datatype))
    {
      return datatype;
    }
  else
    {
      gchar *datatype_sprintf = fo_object_sprintf (datatype);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_DATATYPE,
		   _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE]),
		   class_name,
		   datatype_sprintf,
		   g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

      g_object_unref (datatype);

      g_free (datatype_sprintf);

      return NULL;
    }
}

/**
 * fo_property_space_start_minimum_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_space_start_minimum_get_initial (void)
{
  static FoProperty *space_start_minimum = NULL;

  if (space_start_minimum == NULL)
    {
      space_start_minimum =
	fo_property_space_start_minimum_new ();
    }

  return space_start_minimum;
}
