/* Fo
 * fo-marker.c: Marker formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-marker.h"


enum {
  PROP_0
};

struct _FoMarker
{
  FoFo parent_instance;

};

struct _FoMarkerClass
{
  FoFoClass parent_class;
  
};

static void fo_marker_class_init  (FoMarkerClass *klass);
static void fo_marker_finalize    (GObject           *object);
static void fo_marker_debug_dump_properties (FoFo *fo, gint depth);

static gpointer parent_class;

GType
fo_marker_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoMarkerClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_marker_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoMarker),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoMarker",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_marker_class_init (FoMarkerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_marker_finalize;

  FO_FO_CLASS (klass)->debug_dump_properties = fo_marker_debug_dump_properties;
  FO_FO_CLASS (klass)->allow_mixed_content = TRUE;
}

static void
fo_marker_finalize (GObject *object)
{
  FoMarker *fo_marker;

  fo_marker = FO_MARKER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_marker_new:
 * 
 * Creates a new #FoMarker initialized to default value.
 * 
 * Return value: the new #FoMarker
 **/
FoFo*
fo_marker_new (void)
{
  return FO_FO (g_object_new (fo_marker_get_type (),
			      NULL));
}

void
fo_marker_debug_dump_properties (FoFo *fo,
				 gint  depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MARKER (fo));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s(No properties)",
	 indent);

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}
