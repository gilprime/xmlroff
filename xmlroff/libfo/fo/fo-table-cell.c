/* Fo
 * fo-table-cell.c: 'table-cell' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-cbpbp-fo-private.h"
#include "fo/fo-table-border-fo-private.h"
#include "fo/fo-table-cell-private.h"
#include "fo/fo-table-cell-area.h"
#include "fo-context-util.h"
#include "fo/fo-table.h"
#include "property/fo-property-border.h"
#include "property/fo-property-padding.h"
#include "property/fo-property-background-color.h"
#include "property/fo-property-background-image.h"
#include "property/fo-property-block-progression-dimension.h"
#include "property/fo-property-border-after-color.h"
#include "property/fo-property-border-after-precedence.h"
#include "property/fo-property-border-after-style.h"
#include "property/fo-property-border-after-width.h"
#include "property/fo-property-border-before-color.h"
#include "property/fo-property-border-before-precedence.h"
#include "property/fo-property-border-before-style.h"
#include "property/fo-property-border-before-width.h"
#include "property/fo-property-border-bottom-color.h"
#include "property/fo-property-border-bottom-style.h"
#include "property/fo-property-border-bottom-width.h"
#include "property/fo-property-border-end-color.h"
#include "property/fo-property-border-end-precedence.h"
#include "property/fo-property-border-end-style.h"
#include "property/fo-property-border-end-width.h"
#include "property/fo-property-border-left-color.h"
#include "property/fo-property-border-left-style.h"
#include "property/fo-property-border-left-width.h"
#include "property/fo-property-border-right-color.h"
#include "property/fo-property-border-right-style.h"
#include "property/fo-property-border-right-width.h"
#include "property/fo-property-border-start-color.h"
#include "property/fo-property-border-start-precedence.h"
#include "property/fo-property-border-start-style.h"
#include "property/fo-property-border-start-width.h"
#include "property/fo-property-border-top-color.h"
#include "property/fo-property-border-top-style.h"
#include "property/fo-property-border-top-width.h"
#include "property/fo-property-column-number.h"
#include "property/fo-property-display-align.h"
#include "property/fo-property-height.h"
#include "property/fo-property-id.h"
#include "property/fo-property-inline-progression-dimension.h"
#include "property/fo-property-number-columns-spanned.h"
#include "property/fo-property-number-rows-spanned.h"
#include "property/fo-property-padding-after.h"
#include "property/fo-property-padding-before.h"
#include "property/fo-property-padding-bottom.h"
#include "property/fo-property-padding-end.h"
#include "property/fo-property-padding-left.h"
#include "property/fo-property-padding-right.h"
#include "property/fo-property-padding-start.h"
#include "property/fo-property-padding-top.h"
#include "property/fo-property-role.h"
#include "property/fo-property-source-document.h"
#include "property/fo-property-width.h"

/**
 * SECTION:fo-table-cell
 * @short_description: 'table-cell' formatting object
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;fo_table-cell">http://www.w3.org/TR/xsl11/&num;fo_table-cell</ulink>
 */

enum {
  PROP_0,
  PROP_COLUMN,
  PROP_BACKGROUND_COLOR,
  PROP_BACKGROUND_IMAGE,
  PROP_BLOCK_PROGRESSION_DIMENSION,
  PROP_BORDER_AFTER_COLOR,
  PROP_BORDER_AFTER_PRECEDENCE,
  PROP_BORDER_AFTER_STYLE,
  PROP_BORDER_AFTER_WIDTH,
  PROP_BORDER_BEFORE_COLOR,
  PROP_BORDER_BEFORE_PRECEDENCE,
  PROP_BORDER_BEFORE_STYLE,
  PROP_BORDER_BEFORE_WIDTH,
  PROP_BORDER_BOTTOM_COLOR,
  PROP_BORDER_BOTTOM_STYLE,
  PROP_BORDER_BOTTOM_WIDTH,
  PROP_BORDER_END_COLOR,
  PROP_BORDER_END_PRECEDENCE,
  PROP_BORDER_END_STYLE,
  PROP_BORDER_END_WIDTH,
  PROP_BORDER_LEFT_COLOR,
  PROP_BORDER_LEFT_STYLE,
  PROP_BORDER_LEFT_WIDTH,
  PROP_BORDER_RIGHT_COLOR,
  PROP_BORDER_RIGHT_STYLE,
  PROP_BORDER_RIGHT_WIDTH,
  PROP_BORDER_START_COLOR,
  PROP_BORDER_START_PRECEDENCE,
  PROP_BORDER_START_STYLE,
  PROP_BORDER_START_WIDTH,
  PROP_BORDER_TOP_COLOR,
  PROP_BORDER_TOP_STYLE,
  PROP_BORDER_TOP_WIDTH,
  PROP_COLUMN_NUMBER,
  PROP_DISPLAY_ALIGN,
  PROP_HEIGHT,
  PROP_ID,
  PROP_INLINE_PROGRESSION_DIMENSION,
  PROP_NUMBER_COLUMNS_SPANNED,
  PROP_NUMBER_ROWS_SPANNED,
  PROP_PADDING_AFTER,
  PROP_PADDING_BEFORE,
  PROP_PADDING_BOTTOM,
  PROP_PADDING_END,
  PROP_PADDING_LEFT,
  PROP_PADDING_RIGHT,
  PROP_PADDING_START,
  PROP_PADDING_TOP,
  PROP_ROLE,
  PROP_SOURCE_DOCUMENT,
  PROP_WIDTH
};

static void _class_init            (FoTableCellClass *klass);
static void _cbpbp_fo_init         (FoCBPBPFoIface *iface);
static void _table_border_fo_init  (FoTableBorderFoIface *iface);
static void _finalize              (GObject      *object);
static void _get_property          (GObject      *object,
                                    guint         prop_id,
                                    GValue       *value,
                                    GParamSpec   *pspec);
static void _set_property          (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec);
static void _validate              (FoFo         *fo,
                                    FoContext    *current_context,
                                    FoContext    *parent_context,
                                    GError      **error);
static void _update_from_context   (FoFo         *fo,
                                    FoContext    *context);
static void _debug_dump_properties (FoFo         *fo,
                                    gint          depth);

static gpointer parent_class;

/**
 * fo_table_cell_get_type:
 * 
 * Register the #FoTableCell object type.
 * 
 * Return value: #GType value of the #FoTableCell object type.
 **/
GType
fo_table_cell_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoTableCellClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoTableCell),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      static const GInterfaceInfo fo_cbpbp_fo_info =
	{
	  (GInterfaceInitFunc) _cbpbp_fo_init,	 /* interface_init */
	  NULL,
	  NULL
	};

      static const GInterfaceInfo fo_table_border_fo_info =
	{
	  (GInterfaceInitFunc) _table_border_fo_init, /* interface_init */
	  NULL,
	  NULL
	};

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "FoTableCell",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_CBPBP_FO,
                                   &fo_cbpbp_fo_info);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_TABLE_BORDER_FO,
                                   &fo_table_border_fo_info);
    }

  return object_type;
}

/**
 * _class_init:
 * @klass: #FoTableCellClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoTableCellClass.
 **/
static void
_class_init (FoTableCellClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = _finalize;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  fofo_class->validate_content =
    fo_fo_validate_content_block_plus;
  fofo_class->validate2 = _validate;
  fofo_class->update_from_context = _update_from_context;
  fofo_class->debug_dump_properties = _debug_dump_properties;
  fofo_class->generate_reference_area = TRUE;
  fofo_class->area_new2 =
    fo_table_cell_area_new2;

  g_object_class_install_property
    (object_class,
     PROP_COLUMN,
     g_param_spec_object ("column",
			  _("Column"),
			  _("Column object for this table-cell"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BACKGROUND_COLOR,
     g_param_spec_object ("background-color",
			  _("Background Color"),
			  _("Background Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BACKGROUND_IMAGE,
     g_param_spec_object ("background-image",
			  _("Background Image"),
			  _("Background Image property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BLOCK_PROGRESSION_DIMENSION,
     g_param_spec_object ("block-progression-dimension",
			  _("Block Progression Dimension"),
			  _("Block Progression Dimension property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_COLOR,
     g_param_spec_object ("border-after-color",
			  _("Border After Color"),
			  _("Border After Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_PRECEDENCE,
     g_param_spec_object ("border-after-precedence",
			  _("Border After Precedence"),
			  _("Border After Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_STYLE,
     g_param_spec_object ("border-after-style",
			  _("Border After Style"),
			  _("Border After Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_WIDTH,
     g_param_spec_object ("border-after-width",
			  _("Border After Width"),
			  _("Border After Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_COLOR,
     g_param_spec_object ("border-before-color",
			  _("Border Before Color"),
			  _("Border Before Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_PRECEDENCE,
     g_param_spec_object ("border-before-precedence",
			  _("Border Before Precedence"),
			  _("Border Before Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_STYLE,
     g_param_spec_object ("border-before-style",
			  _("Border Before Style"),
			  _("Border Before Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_WIDTH,
     g_param_spec_object ("border-before-width",
			  _("Border Before Width"),
			  _("Border Before Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_COLOR,
     g_param_spec_object ("border-bottom-color",
			  _("Border Bottom Color"),
			  _("Border Bottom Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_STYLE,
     g_param_spec_object ("border-bottom-style",
			  _("Border Bottom Style"),
			  _("Border Bottom Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_WIDTH,
     g_param_spec_object ("border-bottom-width",
			  _("Border Bottom Width"),
			  _("Border Bottom Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_COLOR,
     g_param_spec_object ("border-end-color",
			  _("Border End Color"),
			  _("Border End Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_PRECEDENCE,
     g_param_spec_object ("border-end-precedence",
			  _("Border End Precedence"),
			  _("Border End Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_STYLE,
     g_param_spec_object ("border-end-style",
			  _("Border End Style"),
			  _("Border End Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_WIDTH,
     g_param_spec_object ("border-end-width",
			  _("Border End Width"),
			  _("Border End Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_COLOR,
     g_param_spec_object ("border-left-color",
			  _("Border Left Color"),
			  _("Border Left Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_STYLE,
     g_param_spec_object ("border-left-style",
			  _("Border Left Style"),
			  _("Border Left Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_WIDTH,
     g_param_spec_object ("border-left-width",
			  _("Border Left Width"),
			  _("Border Left Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_COLOR,
     g_param_spec_object ("border-right-color",
			  _("Border Right Color"),
			  _("Border Right Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_STYLE,
     g_param_spec_object ("border-right-style",
			  _("Border Right Style"),
			  _("Border Right Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_WIDTH,
     g_param_spec_object ("border-right-width",
			  _("Border Right Width"),
			  _("Border Right Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_COLOR,
     g_param_spec_object ("border-start-color",
			  _("Border Start Color"),
			  _("Border Start Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_PRECEDENCE,
     g_param_spec_object ("border-start-precedence",
			  _("Border Start Precedence"),
			  _("Border Start Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_STYLE,
     g_param_spec_object ("border-start-style",
			  _("Border Start Style"),
			  _("Border Start Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_WIDTH,
     g_param_spec_object ("border-start-width",
			  _("Border Start Width"),
			  _("Border Start Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_COLOR,
     g_param_spec_object ("border-top-color",
			  _("Border Top Color"),
			  _("Border Top Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_STYLE,
     g_param_spec_object ("border-top-style",
			  _("Border Top Style"),
			  _("Border Top Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_WIDTH,
     g_param_spec_object ("border-top-width",
			  _("Border Top Width"),
			  _("Border Top Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_COLUMN_NUMBER,
     g_param_spec_object ("column-number",
			  _("Column Number"),
			  _("Column Number property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_DISPLAY_ALIGN,
     g_param_spec_object ("display-align",
			  _("Display Align"),
			  _("Display Align property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_HEIGHT,
     g_param_spec_object ("height",
			  _("Height"),
			  _("Height property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_INLINE_PROGRESSION_DIMENSION,
     g_param_spec_object ("inline-progression-dimension",
			  _("Inline Progression Dimension"),
			  _("Inline Progression Dimension property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_NUMBER_COLUMNS_SPANNED,
     g_param_spec_object ("number-columns-spanned",
			  _("Number Columns Spanned"),
			  _("Number Columns Spanned property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_NUMBER_ROWS_SPANNED,
     g_param_spec_object ("number-rows-spanned",
			  _("Number Rows Spanned"),
			  _("Number Rows Spanned property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_AFTER,
     g_param_spec_object ("padding-after",
			  _("Padding After"),
			  _("Padding After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_BEFORE,
     g_param_spec_object ("padding-before",
			  _("Padding Before"),
			  _("Padding Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_BOTTOM,
     g_param_spec_object ("padding-bottom",
			  _("Padding Bottom"),
			  _("Padding Bottom property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_END,
     g_param_spec_object ("padding-end",
			  _("Padding End"),
			  _("Padding End property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_LEFT,
     g_param_spec_object ("padding-left",
			  _("Padding Left"),
			  _("Padding Left property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_RIGHT,
     g_param_spec_object ("padding-right",
			  _("Padding Right"),
			  _("Padding Right property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_START,
     g_param_spec_object ("padding-start",
			  _("Padding Start"),
			  _("Padding Start property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_TOP,
     g_param_spec_object ("padding-top",
			  _("Padding Top"),
			  _("Padding Top property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ROLE,
     g_param_spec_object ("role",
			  _("Role"),
			  _("Role property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SOURCE_DOCUMENT,
     g_param_spec_object ("source-document",
			  _("Source Document"),
			  _("Source Document property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WIDTH,
     g_param_spec_object ("width",
			  _("Width"),
			  _("Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * _cbpbp_fo_init:
 * @iface: #FoCBPBPFoIFace structure for this class.
 * 
 * Initialize #FoCBPBPFoIface interface for this class.
 **/
static void
_cbpbp_fo_init (FoCBPBPFoIface *iface)
{
  iface->get_background_color = fo_table_cell_get_background_color;
  iface->get_border_after_color = fo_table_cell_get_border_after_color;
  iface->get_border_after_style = fo_table_cell_get_border_after_style;
  iface->get_border_after_width = fo_table_cell_get_border_after_width;
  iface->get_border_before_color = fo_table_cell_get_border_before_color;
  iface->get_border_before_style = fo_table_cell_get_border_before_style;
  iface->get_border_before_width = fo_table_cell_get_border_before_width;
  iface->get_border_end_color = fo_table_cell_get_border_end_color;
  iface->get_border_end_style = fo_table_cell_get_border_end_style;
  iface->get_border_end_width = fo_table_cell_get_border_end_width;
  iface->get_border_start_color = fo_table_cell_get_border_start_color;
  iface->get_border_start_style = fo_table_cell_get_border_start_style;
  iface->get_border_start_width = fo_table_cell_get_border_start_width;
  iface->get_padding_after = fo_table_cell_get_padding_after;
  iface->get_padding_before = fo_table_cell_get_padding_before;
  iface->get_padding_end = fo_table_cell_get_padding_end;
  iface->get_padding_start = fo_table_cell_get_padding_start;
}

/**
 * _table_border_fo_init:
 * @iface: #FoTableBorderFoIFace structure for this class.
 * 
 * Initialize #FoTableBorderFoIface interface for this class.
 **/
static void
_table_border_fo_init (FoTableBorderFoIface *iface)
{
  iface->get_background_color = fo_table_cell_get_background_color;
  iface->get_border_after_color = fo_table_cell_get_border_after_color;
  iface->get_border_after_precedence = fo_table_cell_get_border_after_precedence;
  iface->get_border_after_style = fo_table_cell_get_border_after_style;
  iface->get_border_after_width = fo_table_cell_get_border_after_width;
  iface->get_border_before_color = fo_table_cell_get_border_before_color;
  iface->get_border_before_precedence = fo_table_cell_get_border_before_precedence;
  iface->get_border_before_style = fo_table_cell_get_border_before_style;
  iface->get_border_before_width = fo_table_cell_get_border_before_width;
  iface->get_border_end_color = fo_table_cell_get_border_end_color;
  iface->get_border_end_precedence = fo_table_cell_get_border_end_precedence;
  iface->get_border_end_style = fo_table_cell_get_border_end_style;
  iface->get_border_end_width = fo_table_cell_get_border_end_width;
  iface->get_border_start_color = fo_table_cell_get_border_start_color;
  iface->get_border_start_precedence = fo_table_cell_get_border_start_precedence;
  iface->get_border_start_style = fo_table_cell_get_border_start_style;
  iface->get_border_start_width = fo_table_cell_get_border_start_width;
}

/**
 * _finalize:
 * @object: #FoTableCell object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoTableCell.
 **/
static void
_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_table_cell_set_background_color (fo, NULL);
  fo_table_cell_set_background_image (fo, NULL);
  fo_table_cell_set_block_progression_dimension (fo, NULL);
  fo_table_cell_set_border_after_color (fo, NULL);
  fo_table_cell_set_border_after_precedence (fo, NULL);
  fo_table_cell_set_border_after_style (fo, NULL);
  fo_table_cell_set_border_after_width (fo, NULL);
  fo_table_cell_set_border_before_color (fo, NULL);
  fo_table_cell_set_border_before_precedence (fo, NULL);
  fo_table_cell_set_border_before_style (fo, NULL);
  fo_table_cell_set_border_before_width (fo, NULL);
  fo_table_cell_set_border_bottom_color (fo, NULL);
  fo_table_cell_set_border_bottom_style (fo, NULL);
  fo_table_cell_set_border_bottom_width (fo, NULL);
  fo_table_cell_set_border_end_color (fo, NULL);
  fo_table_cell_set_border_end_precedence (fo, NULL);
  fo_table_cell_set_border_end_style (fo, NULL);
  fo_table_cell_set_border_end_width (fo, NULL);
  fo_table_cell_set_border_left_color (fo, NULL);
  fo_table_cell_set_border_left_style (fo, NULL);
  fo_table_cell_set_border_left_width (fo, NULL);
  fo_table_cell_set_border_right_color (fo, NULL);
  fo_table_cell_set_border_right_style (fo, NULL);
  fo_table_cell_set_border_right_width (fo, NULL);
  fo_table_cell_set_border_start_color (fo, NULL);
  fo_table_cell_set_border_start_precedence (fo, NULL);
  fo_table_cell_set_border_start_style (fo, NULL);
  fo_table_cell_set_border_start_width (fo, NULL);
  fo_table_cell_set_border_top_color (fo, NULL);
  fo_table_cell_set_border_top_style (fo, NULL);
  fo_table_cell_set_border_top_width (fo, NULL);
  fo_table_cell_set_column_number (fo, NULL);
  fo_table_cell_set_display_align (fo, NULL);
  fo_table_cell_set_height (fo, NULL);
  fo_table_cell_set_id (fo, NULL);
  fo_table_cell_set_inline_progression_dimension (fo, NULL);
  fo_table_cell_set_number_columns_spanned (fo, NULL);
  fo_table_cell_set_number_rows_spanned (fo, NULL);
  fo_table_cell_set_padding_after (fo, NULL);
  fo_table_cell_set_padding_before (fo, NULL);
  fo_table_cell_set_padding_bottom (fo, NULL);
  fo_table_cell_set_padding_end (fo, NULL);
  fo_table_cell_set_padding_left (fo, NULL);
  fo_table_cell_set_padding_right (fo, NULL);
  fo_table_cell_set_padding_start (fo, NULL);
  fo_table_cell_set_padding_top (fo, NULL);
  fo_table_cell_set_role (fo, NULL);
  fo_table_cell_set_source_document (fo, NULL);
  fo_table_cell_set_width (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * _get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoTableCell.
 **/
static void
_get_property (GObject    *object,
               guint       prop_id,
               GValue     *value,
               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_background_image (fo_fo)));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_block_progression_dimension (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_after_precedence (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_before_precedence (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_end_precedence (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_start_precedence (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_border_top_width (fo_fo)));
      break;
    case PROP_COLUMN_NUMBER:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_column_number (fo_fo)));
      break;
    case PROP_DISPLAY_ALIGN:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_display_align (fo_fo)));
      break;
    case PROP_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_height (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_id (fo_fo)));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_inline_progression_dimension (fo_fo)));
      break;
    case PROP_NUMBER_COLUMNS_SPANNED:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_number_columns_spanned (fo_fo)));
      break;
    case PROP_NUMBER_ROWS_SPANNED:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_number_rows_spanned (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_padding_top (fo_fo)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_source_document (fo_fo)));
      break;
    case PROP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_cell_get_width (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * _set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoTableCell.
 **/
static void
_set_property (GObject      *object,
               guint         prop_id,
               const GValue *value,
               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      fo_table_cell_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_table_cell_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      fo_table_cell_set_block_progression_dimension (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_table_cell_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_PRECEDENCE:
      fo_table_cell_set_border_after_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_table_cell_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_table_cell_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_table_cell_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_PRECEDENCE:
      fo_table_cell_set_border_before_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_table_cell_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_table_cell_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_table_cell_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_table_cell_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_table_cell_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_table_cell_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_PRECEDENCE:
      fo_table_cell_set_border_end_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_table_cell_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_table_cell_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_table_cell_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_table_cell_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_table_cell_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_table_cell_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_table_cell_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_table_cell_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_table_cell_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_PRECEDENCE:
      fo_table_cell_set_border_start_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_table_cell_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_table_cell_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_table_cell_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_table_cell_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_table_cell_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_COLUMN_NUMBER:
      fo_table_cell_set_column_number (fo_fo, g_value_get_object (value));
      break;
    case PROP_DISPLAY_ALIGN:
      fo_table_cell_set_display_align (fo_fo, g_value_get_object (value));
      break;
    case PROP_HEIGHT:
      fo_table_cell_set_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_table_cell_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      fo_table_cell_set_inline_progression_dimension (fo_fo, g_value_get_object (value));
      break;
    case PROP_NUMBER_COLUMNS_SPANNED:
      fo_table_cell_set_number_columns_spanned (fo_fo, g_value_get_object (value));
      break;
    case PROP_NUMBER_ROWS_SPANNED:
      fo_table_cell_set_number_rows_spanned (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_table_cell_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_table_cell_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_table_cell_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_table_cell_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_table_cell_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_table_cell_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_table_cell_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_table_cell_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_table_cell_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_table_cell_set_source_document (fo_fo, g_value_get_object (value));
      break;
    case PROP_WIDTH:
      fo_table_cell_set_width (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_table_cell_new:
 * 
 * Creates a new #FoTableCell initialized to default value.
 * 
 * Return value: the new #FoTableCell.
 **/
FoFo*
fo_table_cell_new (void)
{
  return FO_FO (g_object_new (fo_table_cell_get_type (),
                              NULL));
}

/**
 * fo_table_cell_resolve_column:
 * @fo: #FoTableCell
 * 
 * Resolve the value of the 'column' property of @fo.
 **/
void
fo_table_cell_resolve_column (FoFo *fo)
{
  FoNode *fo_node;
  FoFo *column;
  FoTableCell *fo_table_cell;
  gint column_number;
  gint number_columns_spanned;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo));

  fo_table_cell = FO_TABLE_CELL (fo);
  column_number =
    fo_integer_get_value (fo_property_get_value (fo_table_cell->column_number));
  number_columns_spanned =
    fo_integer_get_value (fo_property_get_value (fo_table_cell->number_columns_spanned));

  fo_node = fo_node_get_ancestor_or_self_by_type (FO_NODE (fo),
						  FO_TYPE_TABLE);

  column = fo_table_get_column (FO_FO (fo_node),
				column_number,
				number_columns_spanned);

  fo_table_cell->column = column;
}

/**
 * fo_table_cell_resolve_number_columns_spanned:
 * @fo: #FoTableCell
 * 
 * Resolve the value of the 'number-columns-spanned' property of @fo.
 **/
void
fo_table_cell_resolve_number_columns_spanned (FoFo *fo)
{
  FoDatatype *number_columns_spanned_datatype = NULL;

  g_return_if_fail (FO_IS_TABLE_CELL (fo));
  g_return_if_fail (FO_TABLE_CELL (fo)->number_columns_spanned == NULL ||
		    FO_IS_PROPERTY_NUMBER_COLUMNS_SPANNED (FO_TABLE_CELL (fo)->number_columns_spanned));

#if defined(LIBFO_DEBUG) && 0
  fo_object_debug_dump (FO_TABLE_CELL (fo)->column_number, 0);
#endif

  if (FO_TABLE_CELL (fo)->number_columns_spanned != NULL)
    number_columns_spanned_datatype =
      fo_property_get_value (FO_TABLE_CELL (fo)->number_columns_spanned);

  if (number_columns_spanned_datatype != NULL)
    {
      return;
    }
  else
    {
      fo_table_cell_set_number_columns_spanned (fo,
						fo_property_number_columns_spanned_get_initial ());
    }
}

/**
 * fo_table_cell_resolve_number_rows_spanned:
 * @fo: #FoTableCell
 * 
 * Resolve the value of the 'number-rows-spanned' property of @fo.
 **/
void
fo_table_cell_resolve_number_rows_spanned (FoFo *fo)
{
  FoDatatype *number_rows_spanned_datatype = NULL;

  g_return_if_fail (FO_IS_TABLE_CELL (fo));
  g_return_if_fail (FO_TABLE_CELL (fo)->number_rows_spanned == NULL ||
		    FO_IS_PROPERTY_NUMBER_ROWS_SPANNED (FO_TABLE_CELL (fo)->number_rows_spanned));

#if defined(LIBFO_DEBUG) && 0
  fo_object_debug_dump (FO_TABLE_CELL (fo)->column_number, 0);
#endif

  if (FO_TABLE_CELL (fo)->number_rows_spanned != NULL)
    number_rows_spanned_datatype =
      fo_property_get_value (FO_TABLE_CELL (fo)->number_rows_spanned);

  if (number_rows_spanned_datatype != NULL)
    {
      return;
    }
  else
    {
      fo_table_cell_set_number_rows_spanned (fo,
					     fo_property_number_rows_spanned_get_initial ());
    }
}

/**
 * fo_table_cell_resolve_column_number:
 * @fo:    #FoTableCell
 * @error: #GError
 * 
 * Resolve the column number of @fo.
 **/
void
fo_table_cell_resolve_column_number (FoFo    *fo,
				     GError **error)
{
  FoFo *table;
  FoTableCell *table_cell;
  FoProperty *column_number_property;
  FoDatatype *column_number_datatype = NULL;
  GError *tmp_error = NULL;
  gint column_number;
  gint new_column_number;
  gint rows_spanned;
  gint columns_spanned;

  g_return_if_fail (FO_IS_TABLE_CELL (fo));
  g_return_if_fail (FO_TABLE_CELL (fo)->column_number == NULL ||
		    FO_IS_PROPERTY_COLUMN_NUMBER (FO_TABLE_CELL (fo)->column_number));
  g_return_if_fail (error == NULL || *error == NULL);

  table = FO_FO (fo_node_get_ancestor_or_self_by_type (FO_NODE (fo),
						       FO_TYPE_TABLE));

  table_cell = FO_TABLE_CELL (fo);
#if defined(LIBFO_DEBUG) && 0
  g_message ("cell_resolve_column_number:: before:");
  fo_object_debug_dump (table_cell->column_number, 0);
#endif

  if (table_cell->column_number != NULL)
    column_number_datatype =
      fo_property_get_value (table_cell->column_number);

  if (column_number_datatype != NULL)
    column_number = fo_integer_get_value (column_number_datatype);
  else
    column_number = 0;

  rows_spanned = fo_integer_get_value (fo_property_get_value (table_cell->number_rows_spanned));
  columns_spanned = fo_integer_get_value (fo_property_get_value (table_cell->number_columns_spanned));

#if defined(LIBFO_DEBUG) && 0
  g_message ("table_cell_resolve_column_number: column_number: %d; columns_spanned: %d; rows_spanned: %d",
	     column_number,
	     columns_spanned,
	     rows_spanned);
#endif

  new_column_number =
    fo_table_span_info_resolve_column_number (table,
					      fo,
					      column_number,
					      columns_spanned,
					      rows_spanned,
					      &tmp_error);
#if defined(LIBFO_DEBUG) && 0
  g_message ("cell_resolve_column_number:: after:");
  g_message ("%s",
	     fo_object_debug_sprintf (fo));
  fo_table_span_info_debug_dump (table, 0);
#endif

      column_number_datatype =
	fo_integer_new_with_value (new_column_number);

      column_number_property = fo_property_column_number_new ();
      fo_property_set_value (column_number_property,
			     column_number_datatype);

      fo_table_cell_set_column_number (fo,
				       column_number_property);
}

/* old */
#if defined(LIBFO_DEBUG) && 0
  if (FO_TABLE_CELL (fo)->column_number != NULL)
    column_number_datatype =
      fo_property_column_number_get_value (FO_TABLE_CELL (fo)->column_number);

  if (column_number_datatype != NULL)
    return;

  prev_sibling = fo_node_prev_sibling (FO_NODE (fo));

#if defined(LIBFO_DEBUG) && 0
  g_message ("cell_resolve_number_column:: prev_sibling: %s",
	     fo_object_debug_sprintf (prev_sibling));
#endif

  if (!prev_sibling)
    {
      FoProperty *column_number = fo_property_column_number_new ();

      fo_property_column_number_set_value (column_number,
					   fo_integer_get_integer_one ());

      fo_table_cell_set_column_number (fo,
				       column_number);
    }
  else
    {
      FoProperty *prev_column_number;
      FoProperty *prev_column_span;
      FoProperty *column_number;
      FoDatatype *prev_column_number_datatype;
      FoDatatype *prev_column_span_datatype;
      FoDatatype *column_number_datatype;
      gint prev_column_number_value;
      gint prev_column_span_value;
      gint column_number_value;

      prev_column_number =
	fo_table_cell_get_column_number (FO_FO (prev_sibling));
      prev_column_span =
	fo_table_cell_get_number_columns_spanned (FO_FO (prev_sibling));

      prev_column_number_datatype =
	fo_property_column_number_get_value (prev_column_number);
      prev_column_span_datatype =
	fo_property_number_columns_spanned_get_value (prev_column_span);

      prev_column_number_value =
	fo_integer_get_value (prev_column_number_datatype);
      prev_column_span_value =
	fo_integer_get_value (prev_column_span_datatype);

      column_number_value =
	prev_column_number_value +
	prev_column_span_value;

#if defined(LIBFO_DEBUG) && 0
      g_message ("cell_resolve_column_number:: prev_num: %d; prev_span: %d; num: %d",
		 prev_column_number_value,
		 prev_column_span_value,
		 column_number_value);
#endif
      column_number_datatype =
	fo_integer_new_with_value (column_number_value);

      column_number = fo_property_column_number_new ();
      fo_property_column_number_set_value (column_number,
					   column_number_datatype);

      fo_table_cell_set_column_number (fo,
				       column_number);
    }

#if defined(LIBFO_DEBUG) && 0
      g_message ("cell_resolve_column_number:: after:");
      fo_object_debug_dump (FO_TABLE_CELL (fo)->column_number, 0);
#endif
#endif

/**
 * _validate:
 * @fo:              #FoTableCell object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
static void
_validate (FoFo      *fo,
           FoContext *current_context,
           FoContext *parent_context,
           GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_context_util_border_resolve (current_context, parent_context);
  fo_context_util_paddings_resolve (current_context, parent_context);
  fo_context_util_height_width_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * _update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
static void
_update_from_context (FoFo      *fo,
                      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_table_cell_set_background_color (fo,
			  fo_context_get_background_color (context));
  fo_table_cell_set_background_image (fo,
			  fo_context_get_background_image (context));
  fo_table_cell_set_block_progression_dimension (fo,
			  fo_context_get_block_progression_dimension (context));
  fo_table_cell_set_border_after_color (fo,
			  fo_context_get_border_after_color (context));
  fo_table_cell_set_border_after_precedence (fo,
			  fo_context_get_border_after_precedence (context));
  fo_table_cell_set_border_after_style (fo,
			  fo_context_get_border_after_style (context));
  fo_table_cell_set_border_after_width (fo,
			  fo_context_get_border_after_width (context));
  fo_table_cell_set_border_before_color (fo,
			  fo_context_get_border_before_color (context));
  fo_table_cell_set_border_before_precedence (fo,
			  fo_context_get_border_before_precedence (context));
  fo_table_cell_set_border_before_style (fo,
			  fo_context_get_border_before_style (context));
  fo_table_cell_set_border_before_width (fo,
			  fo_context_get_border_before_width (context));
  fo_table_cell_set_border_bottom_color (fo,
			  fo_context_get_border_bottom_color (context));
  fo_table_cell_set_border_bottom_style (fo,
			  fo_context_get_border_bottom_style (context));
  fo_table_cell_set_border_bottom_width (fo,
			  fo_context_get_border_bottom_width (context));
  fo_table_cell_set_border_end_color (fo,
			  fo_context_get_border_end_color (context));
  fo_table_cell_set_border_end_precedence (fo,
			  fo_context_get_border_end_precedence (context));
  fo_table_cell_set_border_end_style (fo,
			  fo_context_get_border_end_style (context));
  fo_table_cell_set_border_end_width (fo,
			  fo_context_get_border_end_width (context));
  fo_table_cell_set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  fo_table_cell_set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  fo_table_cell_set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  fo_table_cell_set_border_right_color (fo,
			  fo_context_get_border_right_color (context));
  fo_table_cell_set_border_right_style (fo,
			  fo_context_get_border_right_style (context));
  fo_table_cell_set_border_right_width (fo,
			  fo_context_get_border_right_width (context));
  fo_table_cell_set_border_start_color (fo,
			  fo_context_get_border_start_color (context));
  fo_table_cell_set_border_start_precedence (fo,
			  fo_context_get_border_start_precedence (context));
  fo_table_cell_set_border_start_style (fo,
			  fo_context_get_border_start_style (context));
  fo_table_cell_set_border_start_width (fo,
			  fo_context_get_border_start_width (context));
  fo_table_cell_set_border_top_color (fo,
			  fo_context_get_border_top_color (context));
  fo_table_cell_set_border_top_style (fo,
			  fo_context_get_border_top_style (context));
  fo_table_cell_set_border_top_width (fo,
			  fo_context_get_border_top_width (context));
  /*
  fo_table_cell_set_column_number (fo,
			  fo_context_get_column_number (context));
  */
  fo_table_cell_set_display_align (fo,
			  fo_context_get_display_align (context));
  fo_table_cell_set_height (fo,
			  fo_context_get_height (context));
  fo_table_cell_set_id (fo,
			  fo_context_get_id (context));
  fo_table_cell_set_inline_progression_dimension (fo,
			  fo_context_get_inline_progression_dimension (context));
  /*
  fo_table_cell_set_number_columns_spanned (fo,
			  fo_context_get_number_columns_spanned (context));
  */
  fo_table_cell_set_number_rows_spanned (fo,
			  fo_context_get_number_rows_spanned (context));
  fo_table_cell_set_padding_after (fo,
			  fo_context_get_padding_after (context));
  fo_table_cell_set_padding_before (fo,
			  fo_context_get_padding_before (context));
  fo_table_cell_set_padding_bottom (fo,
			  fo_context_get_padding_bottom (context));
  fo_table_cell_set_padding_end (fo,
			  fo_context_get_padding_end (context));
  fo_table_cell_set_padding_left (fo,
			  fo_context_get_padding_left (context));
  fo_table_cell_set_padding_right (fo,
			  fo_context_get_padding_right (context));
  fo_table_cell_set_padding_start (fo,
			  fo_context_get_padding_start (context));
  fo_table_cell_set_padding_top (fo,
			  fo_context_get_padding_top (context));
  fo_table_cell_set_role (fo,
			  fo_context_get_role (context));
  fo_table_cell_set_source_document (fo,
			  fo_context_get_source_document (context));
  fo_table_cell_set_width (fo,
			  fo_context_get_width (context));
}

/**
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
static void
_debug_dump_properties (FoFo *fo,
                        gint  depth)
{
  FoTableCell *fo_table_cell;
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *column_string;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo));

  fo_table_cell = FO_TABLE_CELL (fo);

  column_string = fo_object_debug_sprintf (fo_table_cell->column);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%scolumn: %s",
	 indent,
	 column_string);

  g_free (column_string);
  g_free (indent);

  fo_object_debug_dump (fo_table_cell->background_color, depth);
  fo_object_debug_dump (fo_table_cell->background_image, depth);
  fo_object_debug_dump (fo_table_cell->block_progression_dimension, depth);
  fo_object_debug_dump (fo_table_cell->border_after_color, depth);
  fo_object_debug_dump (fo_table_cell->border_after_precedence, depth);
  fo_object_debug_dump (fo_table_cell->border_after_style, depth);
  fo_object_debug_dump (fo_table_cell->border_after_width, depth);
  fo_object_debug_dump (fo_table_cell->border_before_color, depth);
  fo_object_debug_dump (fo_table_cell->border_before_precedence, depth);
  fo_object_debug_dump (fo_table_cell->border_before_style, depth);
  fo_object_debug_dump (fo_table_cell->border_before_width, depth);
  fo_object_debug_dump (fo_table_cell->border_bottom_color, depth);
  fo_object_debug_dump (fo_table_cell->border_bottom_style, depth);
  fo_object_debug_dump (fo_table_cell->border_bottom_width, depth);
  fo_object_debug_dump (fo_table_cell->border_end_color, depth);
  fo_object_debug_dump (fo_table_cell->border_end_precedence, depth);
  fo_object_debug_dump (fo_table_cell->border_end_style, depth);
  fo_object_debug_dump (fo_table_cell->border_end_width, depth);
  fo_object_debug_dump (fo_table_cell->border_left_color, depth);
  fo_object_debug_dump (fo_table_cell->border_left_style, depth);
  fo_object_debug_dump (fo_table_cell->border_left_width, depth);
  fo_object_debug_dump (fo_table_cell->border_right_color, depth);
  fo_object_debug_dump (fo_table_cell->border_right_style, depth);
  fo_object_debug_dump (fo_table_cell->border_right_width, depth);
  fo_object_debug_dump (fo_table_cell->border_start_color, depth);
  fo_object_debug_dump (fo_table_cell->border_start_precedence, depth);
  fo_object_debug_dump (fo_table_cell->border_start_style, depth);
  fo_object_debug_dump (fo_table_cell->border_start_width, depth);
  fo_object_debug_dump (fo_table_cell->border_top_color, depth);
  fo_object_debug_dump (fo_table_cell->border_top_style, depth);
  fo_object_debug_dump (fo_table_cell->border_top_width, depth);
  fo_object_debug_dump (fo_table_cell->column_number, depth);
  fo_object_debug_dump (fo_table_cell->display_align, depth);
  fo_object_debug_dump (fo_table_cell->height, depth);
  fo_object_debug_dump (fo_table_cell->id, depth);
  fo_object_debug_dump (fo_table_cell->inline_progression_dimension, depth);
  fo_object_debug_dump (fo_table_cell->number_columns_spanned, depth);
  fo_object_debug_dump (fo_table_cell->number_rows_spanned, depth);
  fo_object_debug_dump (fo_table_cell->padding_after, depth);
  fo_object_debug_dump (fo_table_cell->padding_before, depth);
  fo_object_debug_dump (fo_table_cell->padding_bottom, depth);
  fo_object_debug_dump (fo_table_cell->padding_end, depth);
  fo_object_debug_dump (fo_table_cell->padding_left, depth);
  fo_object_debug_dump (fo_table_cell->padding_right, depth);
  fo_object_debug_dump (fo_table_cell->padding_start, depth);
  fo_object_debug_dump (fo_table_cell->padding_top, depth);
  fo_object_debug_dump (fo_table_cell->role, depth);
  fo_object_debug_dump (fo_table_cell->source_document, depth);
  fo_object_debug_dump (fo_table_cell->width, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_table_cell_get_column:
 * @fo_fo: The @FoFo object
 *
 * Gets the column property of @table_cell
 *
 * Return value: The "column" property value
**/
FoFo*
fo_table_cell_get_column (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->column;
}

/*
 * These get/set functions are completely auto-generated.
 */

/**
 * fo_table_cell_get_background_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "background-color" property of @fo_fo.
 *
 * Return value: The "background-color" property value.
**/
FoProperty *
fo_table_cell_get_background_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->background_color;
}

/**
 * fo_table_cell_set_background_color:
 * @fo_fo: The #FoFo object.
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color.
 **/
void
fo_table_cell_set_background_color (FoFo *fo_fo,
		         FoProperty *new_background_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_background_color == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_COLOR (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref_sink (new_background_color);
    }
  if (fo_table_cell->background_color != NULL)
    {
      g_object_unref (fo_table_cell->background_color);
    }
  fo_table_cell->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "background-color");*/
}

/**
 * fo_table_cell_get_background_image:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "background-image" property of @fo_fo.
 *
 * Return value: The "background-image" property value.
**/
FoProperty *
fo_table_cell_get_background_image (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->background_image;
}

/**
 * fo_table_cell_set_background_image:
 * @fo_fo: The #FoFo object.
 * @new_background_image: The new "background-image" property value.
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image.
 **/
void
fo_table_cell_set_background_image (FoFo *fo_fo,
		         FoProperty *new_background_image)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_background_image == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref_sink (new_background_image);
    }
  if (fo_table_cell->background_image != NULL)
    {
      g_object_unref (fo_table_cell->background_image);
    }
  fo_table_cell->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_table_cell), "background-image");*/
}

/**
 * fo_table_cell_get_block_progression_dimension:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "block-progression-dimension" property of @fo_fo.
 *
 * Return value: The "block-progression-dimension" property value.
**/
FoProperty *
fo_table_cell_get_block_progression_dimension (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->block_progression_dimension;
}

/**
 * fo_table_cell_set_block_progression_dimension:
 * @fo_fo: The #FoFo object.
 * @new_block_progression_dimension: The new "block-progression-dimension" property value.
 * 
 * Sets the "block-progression-dimension" property of @fo_fo to @new_block_progression_dimension.
 **/
void
fo_table_cell_set_block_progression_dimension (FoFo *fo_fo,
		         FoProperty *new_block_progression_dimension)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_block_progression_dimension == NULL) ||
		    FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION (new_block_progression_dimension));

  if (new_block_progression_dimension != NULL)
    {
      g_object_ref_sink (new_block_progression_dimension);
    }
  if (fo_table_cell->block_progression_dimension != NULL)
    {
      g_object_unref (fo_table_cell->block_progression_dimension);
    }
  fo_table_cell->block_progression_dimension = new_block_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_table_cell), "block-progression-dimension");*/
}

/**
 * fo_table_cell_get_border_after_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-after-color" property of @fo_fo.
 *
 * Return value: The "border-after-color" property value.
**/
FoProperty *
fo_table_cell_get_border_after_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_after_color;
}

/**
 * fo_table_cell_set_border_after_color:
 * @fo_fo: The #FoFo object.
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color.
 **/
void
fo_table_cell_set_border_after_color (FoFo *fo_fo,
		         FoProperty *new_border_after_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_after_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref_sink (new_border_after_color);
    }
  if (fo_table_cell->border_after_color != NULL)
    {
      g_object_unref (fo_table_cell->border_after_color);
    }
  fo_table_cell->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-after-color");*/
}

/**
 * fo_table_cell_get_border_after_precedence:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-after-precedence" property of @fo_fo.
 *
 * Return value: The "border-after-precedence" property value.
**/
FoProperty *
fo_table_cell_get_border_after_precedence (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_after_precedence;
}

/**
 * fo_table_cell_set_border_after_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_after_precedence: The new "border-after-precedence" property value.
 * 
 * Sets the "border-after-precedence" property of @fo_fo to @new_border_after_precedence.
 **/
void
fo_table_cell_set_border_after_precedence (FoFo *fo_fo,
		         FoProperty *new_border_after_precedence)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_after_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_PRECEDENCE (new_border_after_precedence));

  if (new_border_after_precedence != NULL)
    {
      g_object_ref_sink (new_border_after_precedence);
    }
  if (fo_table_cell->border_after_precedence != NULL)
    {
      g_object_unref (fo_table_cell->border_after_precedence);
    }
  fo_table_cell->border_after_precedence = new_border_after_precedence;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-after-precedence");*/
}

/**
 * fo_table_cell_get_border_after_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-after-style" property of @fo_fo.
 *
 * Return value: The "border-after-style" property value.
**/
FoProperty *
fo_table_cell_get_border_after_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_after_style;
}

/**
 * fo_table_cell_set_border_after_style:
 * @fo_fo: The #FoFo object.
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style.
 **/
void
fo_table_cell_set_border_after_style (FoFo *fo_fo,
		         FoProperty *new_border_after_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_after_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref_sink (new_border_after_style);
    }
  if (fo_table_cell->border_after_style != NULL)
    {
      g_object_unref (fo_table_cell->border_after_style);
    }
  fo_table_cell->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-after-style");*/
}

/**
 * fo_table_cell_get_border_after_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-after-width" property of @fo_fo.
 *
 * Return value: The "border-after-width" property value.
**/
FoProperty *
fo_table_cell_get_border_after_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_after_width;
}

/**
 * fo_table_cell_set_border_after_width:
 * @fo_fo: The #FoFo object.
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width.
 **/
void
fo_table_cell_set_border_after_width (FoFo *fo_fo,
		         FoProperty *new_border_after_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_after_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref_sink (new_border_after_width);
    }
  if (fo_table_cell->border_after_width != NULL)
    {
      g_object_unref (fo_table_cell->border_after_width);
    }
  fo_table_cell->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-after-width");*/
}

/**
 * fo_table_cell_get_border_before_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-before-color" property of @fo_fo.
 *
 * Return value: The "border-before-color" property value.
**/
FoProperty *
fo_table_cell_get_border_before_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_before_color;
}

/**
 * fo_table_cell_set_border_before_color:
 * @fo_fo: The #FoFo object.
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color.
 **/
void
fo_table_cell_set_border_before_color (FoFo *fo_fo,
		         FoProperty *new_border_before_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_before_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref_sink (new_border_before_color);
    }
  if (fo_table_cell->border_before_color != NULL)
    {
      g_object_unref (fo_table_cell->border_before_color);
    }
  fo_table_cell->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-before-color");*/
}

/**
 * fo_table_cell_get_border_before_precedence:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-before-precedence" property of @fo_fo.
 *
 * Return value: The "border-before-precedence" property value.
**/
FoProperty *
fo_table_cell_get_border_before_precedence (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_before_precedence;
}

/**
 * fo_table_cell_set_border_before_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_before_precedence: The new "border-before-precedence" property value.
 * 
 * Sets the "border-before-precedence" property of @fo_fo to @new_border_before_precedence.
 **/
void
fo_table_cell_set_border_before_precedence (FoFo *fo_fo,
		         FoProperty *new_border_before_precedence)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_before_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_PRECEDENCE (new_border_before_precedence));

  if (new_border_before_precedence != NULL)
    {
      g_object_ref_sink (new_border_before_precedence);
    }
  if (fo_table_cell->border_before_precedence != NULL)
    {
      g_object_unref (fo_table_cell->border_before_precedence);
    }
  fo_table_cell->border_before_precedence = new_border_before_precedence;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-before-precedence");*/
}

/**
 * fo_table_cell_get_border_before_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-before-style" property of @fo_fo.
 *
 * Return value: The "border-before-style" property value.
**/
FoProperty *
fo_table_cell_get_border_before_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_before_style;
}

/**
 * fo_table_cell_set_border_before_style:
 * @fo_fo: The #FoFo object.
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style.
 **/
void
fo_table_cell_set_border_before_style (FoFo *fo_fo,
		         FoProperty *new_border_before_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_before_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref_sink (new_border_before_style);
    }
  if (fo_table_cell->border_before_style != NULL)
    {
      g_object_unref (fo_table_cell->border_before_style);
    }
  fo_table_cell->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-before-style");*/
}

/**
 * fo_table_cell_get_border_before_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-before-width" property of @fo_fo.
 *
 * Return value: The "border-before-width" property value.
**/
FoProperty *
fo_table_cell_get_border_before_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_before_width;
}

/**
 * fo_table_cell_set_border_before_width:
 * @fo_fo: The #FoFo object.
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width.
 **/
void
fo_table_cell_set_border_before_width (FoFo *fo_fo,
		         FoProperty *new_border_before_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_before_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref_sink (new_border_before_width);
    }
  if (fo_table_cell->border_before_width != NULL)
    {
      g_object_unref (fo_table_cell->border_before_width);
    }
  fo_table_cell->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-before-width");*/
}

/**
 * fo_table_cell_get_border_bottom_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-bottom-color" property of @fo_fo.
 *
 * Return value: The "border-bottom-color" property value.
**/
FoProperty *
fo_table_cell_get_border_bottom_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_bottom_color;
}

/**
 * fo_table_cell_set_border_bottom_color:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color.
 **/
void
fo_table_cell_set_border_bottom_color (FoFo *fo_fo,
		         FoProperty *new_border_bottom_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_bottom_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref_sink (new_border_bottom_color);
    }
  if (fo_table_cell->border_bottom_color != NULL)
    {
      g_object_unref (fo_table_cell->border_bottom_color);
    }
  fo_table_cell->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-bottom-color");*/
}

/**
 * fo_table_cell_get_border_bottom_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-bottom-style" property of @fo_fo.
 *
 * Return value: The "border-bottom-style" property value.
**/
FoProperty *
fo_table_cell_get_border_bottom_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_bottom_style;
}

/**
 * fo_table_cell_set_border_bottom_style:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style.
 **/
void
fo_table_cell_set_border_bottom_style (FoFo *fo_fo,
		         FoProperty *new_border_bottom_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_bottom_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref_sink (new_border_bottom_style);
    }
  if (fo_table_cell->border_bottom_style != NULL)
    {
      g_object_unref (fo_table_cell->border_bottom_style);
    }
  fo_table_cell->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-bottom-style");*/
}

/**
 * fo_table_cell_get_border_bottom_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-bottom-width" property of @fo_fo.
 *
 * Return value: The "border-bottom-width" property value.
**/
FoProperty *
fo_table_cell_get_border_bottom_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_bottom_width;
}

/**
 * fo_table_cell_set_border_bottom_width:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width.
 **/
void
fo_table_cell_set_border_bottom_width (FoFo *fo_fo,
		         FoProperty *new_border_bottom_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_bottom_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref_sink (new_border_bottom_width);
    }
  if (fo_table_cell->border_bottom_width != NULL)
    {
      g_object_unref (fo_table_cell->border_bottom_width);
    }
  fo_table_cell->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-bottom-width");*/
}

/**
 * fo_table_cell_get_border_end_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-end-color" property of @fo_fo.
 *
 * Return value: The "border-end-color" property value.
**/
FoProperty *
fo_table_cell_get_border_end_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_end_color;
}

/**
 * fo_table_cell_set_border_end_color:
 * @fo_fo: The #FoFo object.
 * @new_border_end_color: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color.
 **/
void
fo_table_cell_set_border_end_color (FoFo *fo_fo,
		         FoProperty *new_border_end_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_end_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref_sink (new_border_end_color);
    }
  if (fo_table_cell->border_end_color != NULL)
    {
      g_object_unref (fo_table_cell->border_end_color);
    }
  fo_table_cell->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-end-color");*/
}

/**
 * fo_table_cell_get_border_end_precedence:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-end-precedence" property of @fo_fo.
 *
 * Return value: The "border-end-precedence" property value.
**/
FoProperty *
fo_table_cell_get_border_end_precedence (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_end_precedence;
}

/**
 * fo_table_cell_set_border_end_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_end_precedence: The new "border-end-precedence" property value.
 * 
 * Sets the "border-end-precedence" property of @fo_fo to @new_border_end_precedence.
 **/
void
fo_table_cell_set_border_end_precedence (FoFo *fo_fo,
		         FoProperty *new_border_end_precedence)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_end_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_PRECEDENCE (new_border_end_precedence));

  if (new_border_end_precedence != NULL)
    {
      g_object_ref_sink (new_border_end_precedence);
    }
  if (fo_table_cell->border_end_precedence != NULL)
    {
      g_object_unref (fo_table_cell->border_end_precedence);
    }
  fo_table_cell->border_end_precedence = new_border_end_precedence;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-end-precedence");*/
}

/**
 * fo_table_cell_get_border_end_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-end-style" property of @fo_fo.
 *
 * Return value: The "border-end-style" property value.
**/
FoProperty *
fo_table_cell_get_border_end_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_end_style;
}

/**
 * fo_table_cell_set_border_end_style:
 * @fo_fo: The #FoFo object.
 * @new_border_end_style: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style.
 **/
void
fo_table_cell_set_border_end_style (FoFo *fo_fo,
		         FoProperty *new_border_end_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_end_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref_sink (new_border_end_style);
    }
  if (fo_table_cell->border_end_style != NULL)
    {
      g_object_unref (fo_table_cell->border_end_style);
    }
  fo_table_cell->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-end-style");*/
}

/**
 * fo_table_cell_get_border_end_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-end-width" property of @fo_fo.
 *
 * Return value: The "border-end-width" property value.
**/
FoProperty *
fo_table_cell_get_border_end_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_end_width;
}

/**
 * fo_table_cell_set_border_end_width:
 * @fo_fo: The #FoFo object.
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width.
 **/
void
fo_table_cell_set_border_end_width (FoFo *fo_fo,
		         FoProperty *new_border_end_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_end_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref_sink (new_border_end_width);
    }
  if (fo_table_cell->border_end_width != NULL)
    {
      g_object_unref (fo_table_cell->border_end_width);
    }
  fo_table_cell->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-end-width");*/
}

/**
 * fo_table_cell_get_border_left_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-left-color" property of @fo_fo.
 *
 * Return value: The "border-left-color" property value.
**/
FoProperty *
fo_table_cell_get_border_left_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_left_color;
}

/**
 * fo_table_cell_set_border_left_color:
 * @fo_fo: The #FoFo object.
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color.
 **/
void
fo_table_cell_set_border_left_color (FoFo *fo_fo,
		         FoProperty *new_border_left_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_left_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref_sink (new_border_left_color);
    }
  if (fo_table_cell->border_left_color != NULL)
    {
      g_object_unref (fo_table_cell->border_left_color);
    }
  fo_table_cell->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-left-color");*/
}

/**
 * fo_table_cell_get_border_left_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-left-style" property of @fo_fo.
 *
 * Return value: The "border-left-style" property value.
**/
FoProperty *
fo_table_cell_get_border_left_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_left_style;
}

/**
 * fo_table_cell_set_border_left_style:
 * @fo_fo: The #FoFo object.
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style.
 **/
void
fo_table_cell_set_border_left_style (FoFo *fo_fo,
		         FoProperty *new_border_left_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_left_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref_sink (new_border_left_style);
    }
  if (fo_table_cell->border_left_style != NULL)
    {
      g_object_unref (fo_table_cell->border_left_style);
    }
  fo_table_cell->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-left-style");*/
}

/**
 * fo_table_cell_get_border_left_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-left-width" property of @fo_fo.
 *
 * Return value: The "border-left-width" property value.
**/
FoProperty *
fo_table_cell_get_border_left_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_left_width;
}

/**
 * fo_table_cell_set_border_left_width:
 * @fo_fo: The #FoFo object.
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width.
 **/
void
fo_table_cell_set_border_left_width (FoFo *fo_fo,
		         FoProperty *new_border_left_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_left_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref_sink (new_border_left_width);
    }
  if (fo_table_cell->border_left_width != NULL)
    {
      g_object_unref (fo_table_cell->border_left_width);
    }
  fo_table_cell->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-left-width");*/
}

/**
 * fo_table_cell_get_border_right_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-right-color" property of @fo_fo.
 *
 * Return value: The "border-right-color" property value.
**/
FoProperty *
fo_table_cell_get_border_right_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_right_color;
}

/**
 * fo_table_cell_set_border_right_color:
 * @fo_fo: The #FoFo object.
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color.
 **/
void
fo_table_cell_set_border_right_color (FoFo *fo_fo,
		         FoProperty *new_border_right_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_right_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref_sink (new_border_right_color);
    }
  if (fo_table_cell->border_right_color != NULL)
    {
      g_object_unref (fo_table_cell->border_right_color);
    }
  fo_table_cell->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-right-color");*/
}

/**
 * fo_table_cell_get_border_right_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-right-style" property of @fo_fo.
 *
 * Return value: The "border-right-style" property value.
**/
FoProperty *
fo_table_cell_get_border_right_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_right_style;
}

/**
 * fo_table_cell_set_border_right_style:
 * @fo_fo: The #FoFo object.
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style.
 **/
void
fo_table_cell_set_border_right_style (FoFo *fo_fo,
		         FoProperty *new_border_right_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_right_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref_sink (new_border_right_style);
    }
  if (fo_table_cell->border_right_style != NULL)
    {
      g_object_unref (fo_table_cell->border_right_style);
    }
  fo_table_cell->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-right-style");*/
}

/**
 * fo_table_cell_get_border_right_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-right-width" property of @fo_fo.
 *
 * Return value: The "border-right-width" property value.
**/
FoProperty *
fo_table_cell_get_border_right_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_right_width;
}

/**
 * fo_table_cell_set_border_right_width:
 * @fo_fo: The #FoFo object.
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width.
 **/
void
fo_table_cell_set_border_right_width (FoFo *fo_fo,
		         FoProperty *new_border_right_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_right_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref_sink (new_border_right_width);
    }
  if (fo_table_cell->border_right_width != NULL)
    {
      g_object_unref (fo_table_cell->border_right_width);
    }
  fo_table_cell->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-right-width");*/
}

/**
 * fo_table_cell_get_border_start_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-start-color" property of @fo_fo.
 *
 * Return value: The "border-start-color" property value.
**/
FoProperty *
fo_table_cell_get_border_start_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_start_color;
}

/**
 * fo_table_cell_set_border_start_color:
 * @fo_fo: The #FoFo object.
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color.
 **/
void
fo_table_cell_set_border_start_color (FoFo *fo_fo,
		         FoProperty *new_border_start_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_start_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref_sink (new_border_start_color);
    }
  if (fo_table_cell->border_start_color != NULL)
    {
      g_object_unref (fo_table_cell->border_start_color);
    }
  fo_table_cell->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-start-color");*/
}

/**
 * fo_table_cell_get_border_start_precedence:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-start-precedence" property of @fo_fo.
 *
 * Return value: The "border-start-precedence" property value.
**/
FoProperty *
fo_table_cell_get_border_start_precedence (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_start_precedence;
}

/**
 * fo_table_cell_set_border_start_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_start_precedence: The new "border-start-precedence" property value.
 * 
 * Sets the "border-start-precedence" property of @fo_fo to @new_border_start_precedence.
 **/
void
fo_table_cell_set_border_start_precedence (FoFo *fo_fo,
		         FoProperty *new_border_start_precedence)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_start_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_PRECEDENCE (new_border_start_precedence));

  if (new_border_start_precedence != NULL)
    {
      g_object_ref_sink (new_border_start_precedence);
    }
  if (fo_table_cell->border_start_precedence != NULL)
    {
      g_object_unref (fo_table_cell->border_start_precedence);
    }
  fo_table_cell->border_start_precedence = new_border_start_precedence;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-start-precedence");*/
}

/**
 * fo_table_cell_get_border_start_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-start-style" property of @fo_fo.
 *
 * Return value: The "border-start-style" property value.
**/
FoProperty *
fo_table_cell_get_border_start_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_start_style;
}

/**
 * fo_table_cell_set_border_start_style:
 * @fo_fo: The #FoFo object.
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style.
 **/
void
fo_table_cell_set_border_start_style (FoFo *fo_fo,
		         FoProperty *new_border_start_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_start_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref_sink (new_border_start_style);
    }
  if (fo_table_cell->border_start_style != NULL)
    {
      g_object_unref (fo_table_cell->border_start_style);
    }
  fo_table_cell->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-start-style");*/
}

/**
 * fo_table_cell_get_border_start_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-start-width" property of @fo_fo.
 *
 * Return value: The "border-start-width" property value.
**/
FoProperty *
fo_table_cell_get_border_start_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_start_width;
}

/**
 * fo_table_cell_set_border_start_width:
 * @fo_fo: The #FoFo object.
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width.
 **/
void
fo_table_cell_set_border_start_width (FoFo *fo_fo,
		         FoProperty *new_border_start_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_start_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref_sink (new_border_start_width);
    }
  if (fo_table_cell->border_start_width != NULL)
    {
      g_object_unref (fo_table_cell->border_start_width);
    }
  fo_table_cell->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-start-width");*/
}

/**
 * fo_table_cell_get_border_top_color:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-top-color" property of @fo_fo.
 *
 * Return value: The "border-top-color" property value.
**/
FoProperty *
fo_table_cell_get_border_top_color (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_top_color;
}

/**
 * fo_table_cell_set_border_top_color:
 * @fo_fo: The #FoFo object.
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color.
 **/
void
fo_table_cell_set_border_top_color (FoFo *fo_fo,
		         FoProperty *new_border_top_color)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_top_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref_sink (new_border_top_color);
    }
  if (fo_table_cell->border_top_color != NULL)
    {
      g_object_unref (fo_table_cell->border_top_color);
    }
  fo_table_cell->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-top-color");*/
}

/**
 * fo_table_cell_get_border_top_style:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-top-style" property of @fo_fo.
 *
 * Return value: The "border-top-style" property value.
**/
FoProperty *
fo_table_cell_get_border_top_style (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_top_style;
}

/**
 * fo_table_cell_set_border_top_style:
 * @fo_fo: The #FoFo object.
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style.
 **/
void
fo_table_cell_set_border_top_style (FoFo *fo_fo,
		         FoProperty *new_border_top_style)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_top_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref_sink (new_border_top_style);
    }
  if (fo_table_cell->border_top_style != NULL)
    {
      g_object_unref (fo_table_cell->border_top_style);
    }
  fo_table_cell->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-top-style");*/
}

/**
 * fo_table_cell_get_border_top_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "border-top-width" property of @fo_fo.
 *
 * Return value: The "border-top-width" property value.
**/
FoProperty *
fo_table_cell_get_border_top_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->border_top_width;
}

/**
 * fo_table_cell_set_border_top_width:
 * @fo_fo: The #FoFo object.
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width.
 **/
void
fo_table_cell_set_border_top_width (FoFo *fo_fo,
		         FoProperty *new_border_top_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_border_top_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref_sink (new_border_top_width);
    }
  if (fo_table_cell->border_top_width != NULL)
    {
      g_object_unref (fo_table_cell->border_top_width);
    }
  fo_table_cell->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "border-top-width");*/
}

/**
 * fo_table_cell_get_column_number:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "column-number" property of @fo_fo.
 *
 * Return value: The "column-number" property value.
**/
FoProperty *
fo_table_cell_get_column_number (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->column_number;
}

/**
 * fo_table_cell_set_column_number:
 * @fo_fo: The #FoFo object.
 * @new_column_number: The new "column-number" property value.
 * 
 * Sets the "column-number" property of @fo_fo to @new_column_number.
 **/
void
fo_table_cell_set_column_number (FoFo *fo_fo,
		         FoProperty *new_column_number)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_column_number == NULL) ||
		    FO_IS_PROPERTY_COLUMN_NUMBER (new_column_number));

  if (new_column_number != NULL)
    {
      g_object_ref_sink (new_column_number);
    }
  if (fo_table_cell->column_number != NULL)
    {
      g_object_unref (fo_table_cell->column_number);
    }
  fo_table_cell->column_number = new_column_number;
  /*g_object_notify (G_OBJECT (fo_table_cell), "column-number");*/
}

/**
 * fo_table_cell_get_display_align:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "display-align" property of @fo_fo.
 *
 * Return value: The "display-align" property value.
**/
FoProperty *
fo_table_cell_get_display_align (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->display_align;
}

/**
 * fo_table_cell_set_display_align:
 * @fo_fo: The #FoFo object.
 * @new_display_align: The new "display-align" property value.
 * 
 * Sets the "display-align" property of @fo_fo to @new_display_align.
 **/
void
fo_table_cell_set_display_align (FoFo *fo_fo,
		         FoProperty *new_display_align)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_display_align == NULL) ||
		    FO_IS_PROPERTY_DISPLAY_ALIGN (new_display_align));

  if (new_display_align != NULL)
    {
      g_object_ref_sink (new_display_align);
    }
  if (fo_table_cell->display_align != NULL)
    {
      g_object_unref (fo_table_cell->display_align);
    }
  fo_table_cell->display_align = new_display_align;
  /*g_object_notify (G_OBJECT (fo_table_cell), "display-align");*/
}

/**
 * fo_table_cell_get_height:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "height" property of @fo_fo.
 *
 * Return value: The "height" property value.
**/
FoProperty *
fo_table_cell_get_height (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->height;
}

/**
 * fo_table_cell_set_height:
 * @fo_fo: The #FoFo object.
 * @new_height: The new "height" property value.
 * 
 * Sets the "height" property of @fo_fo to @new_height.
 **/
void
fo_table_cell_set_height (FoFo *fo_fo,
		         FoProperty *new_height)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_height == NULL) ||
		    FO_IS_PROPERTY_HEIGHT (new_height));

  if (new_height != NULL)
    {
      g_object_ref_sink (new_height);
    }
  if (fo_table_cell->height != NULL)
    {
      g_object_unref (fo_table_cell->height);
    }
  fo_table_cell->height = new_height;
  /*g_object_notify (G_OBJECT (fo_table_cell), "height");*/
}

/**
 * fo_table_cell_get_id:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_table_cell_get_id (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->id;
}

/**
 * fo_table_cell_set_id:
 * @fo_fo: The #FoFo object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_fo to @new_id.
 **/
void
fo_table_cell_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_id == NULL) ||
		    FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref_sink (new_id);
    }
  if (fo_table_cell->id != NULL)
    {
      g_object_unref (fo_table_cell->id);
    }
  fo_table_cell->id = new_id;
  /*g_object_notify (G_OBJECT (fo_table_cell), "id");*/
}

/**
 * fo_table_cell_get_inline_progression_dimension:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "inline-progression-dimension" property of @fo_fo.
 *
 * Return value: The "inline-progression-dimension" property value.
**/
FoProperty *
fo_table_cell_get_inline_progression_dimension (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->inline_progression_dimension;
}

/**
 * fo_table_cell_set_inline_progression_dimension:
 * @fo_fo: The #FoFo object.
 * @new_inline_progression_dimension: The new "inline-progression-dimension" property value.
 * 
 * Sets the "inline-progression-dimension" property of @fo_fo to @new_inline_progression_dimension.
 **/
void
fo_table_cell_set_inline_progression_dimension (FoFo *fo_fo,
		         FoProperty *new_inline_progression_dimension)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_inline_progression_dimension == NULL) ||
		    FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION (new_inline_progression_dimension));

  if (new_inline_progression_dimension != NULL)
    {
      g_object_ref_sink (new_inline_progression_dimension);
    }
  if (fo_table_cell->inline_progression_dimension != NULL)
    {
      g_object_unref (fo_table_cell->inline_progression_dimension);
    }
  fo_table_cell->inline_progression_dimension = new_inline_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_table_cell), "inline-progression-dimension");*/
}

/**
 * fo_table_cell_get_number_columns_spanned:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "number-columns-spanned" property of @fo_fo.
 *
 * Return value: The "number-columns-spanned" property value.
**/
FoProperty *
fo_table_cell_get_number_columns_spanned (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->number_columns_spanned;
}

/**
 * fo_table_cell_set_number_columns_spanned:
 * @fo_fo: The #FoFo object.
 * @new_number_columns_spanned: The new "number-columns-spanned" property value.
 * 
 * Sets the "number-columns-spanned" property of @fo_fo to @new_number_columns_spanned.
 **/
void
fo_table_cell_set_number_columns_spanned (FoFo *fo_fo,
		         FoProperty *new_number_columns_spanned)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_number_columns_spanned == NULL) ||
		    FO_IS_PROPERTY_NUMBER_COLUMNS_SPANNED (new_number_columns_spanned));

  if (new_number_columns_spanned != NULL)
    {
      g_object_ref_sink (new_number_columns_spanned);
    }
  if (fo_table_cell->number_columns_spanned != NULL)
    {
      g_object_unref (fo_table_cell->number_columns_spanned);
    }
  fo_table_cell->number_columns_spanned = new_number_columns_spanned;
  /*g_object_notify (G_OBJECT (fo_table_cell), "number-columns-spanned");*/
}

/**
 * fo_table_cell_get_number_rows_spanned:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "number-rows-spanned" property of @fo_fo.
 *
 * Return value: The "number-rows-spanned" property value.
**/
FoProperty *
fo_table_cell_get_number_rows_spanned (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->number_rows_spanned;
}

/**
 * fo_table_cell_set_number_rows_spanned:
 * @fo_fo: The #FoFo object.
 * @new_number_rows_spanned: The new "number-rows-spanned" property value.
 * 
 * Sets the "number-rows-spanned" property of @fo_fo to @new_number_rows_spanned.
 **/
void
fo_table_cell_set_number_rows_spanned (FoFo *fo_fo,
		         FoProperty *new_number_rows_spanned)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_number_rows_spanned == NULL) ||
		    FO_IS_PROPERTY_NUMBER_ROWS_SPANNED (new_number_rows_spanned));

  if (new_number_rows_spanned != NULL)
    {
      g_object_ref_sink (new_number_rows_spanned);
    }
  if (fo_table_cell->number_rows_spanned != NULL)
    {
      g_object_unref (fo_table_cell->number_rows_spanned);
    }
  fo_table_cell->number_rows_spanned = new_number_rows_spanned;
  /*g_object_notify (G_OBJECT (fo_table_cell), "number-rows-spanned");*/
}

/**
 * fo_table_cell_get_padding_after:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-after" property of @fo_fo.
 *
 * Return value: The "padding-after" property value.
**/
FoProperty *
fo_table_cell_get_padding_after (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_after;
}

/**
 * fo_table_cell_set_padding_after:
 * @fo_fo: The #FoFo object.
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after.
 **/
void
fo_table_cell_set_padding_after (FoFo *fo_fo,
		         FoProperty *new_padding_after)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_after == NULL) ||
		    FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref_sink (new_padding_after);
    }
  if (fo_table_cell->padding_after != NULL)
    {
      g_object_unref (fo_table_cell->padding_after);
    }
  fo_table_cell->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-after");*/
}

/**
 * fo_table_cell_get_padding_before:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-before" property of @fo_fo.
 *
 * Return value: The "padding-before" property value.
**/
FoProperty *
fo_table_cell_get_padding_before (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_before;
}

/**
 * fo_table_cell_set_padding_before:
 * @fo_fo: The #FoFo object.
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before.
 **/
void
fo_table_cell_set_padding_before (FoFo *fo_fo,
		         FoProperty *new_padding_before)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_before == NULL) ||
		    FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref_sink (new_padding_before);
    }
  if (fo_table_cell->padding_before != NULL)
    {
      g_object_unref (fo_table_cell->padding_before);
    }
  fo_table_cell->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-before");*/
}

/**
 * fo_table_cell_get_padding_bottom:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-bottom" property of @fo_fo.
 *
 * Return value: The "padding-bottom" property value.
**/
FoProperty *
fo_table_cell_get_padding_bottom (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_bottom;
}

/**
 * fo_table_cell_set_padding_bottom:
 * @fo_fo: The #FoFo object.
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom.
 **/
void
fo_table_cell_set_padding_bottom (FoFo *fo_fo,
		         FoProperty *new_padding_bottom)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_bottom == NULL) ||
		    FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref_sink (new_padding_bottom);
    }
  if (fo_table_cell->padding_bottom != NULL)
    {
      g_object_unref (fo_table_cell->padding_bottom);
    }
  fo_table_cell->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-bottom");*/
}

/**
 * fo_table_cell_get_padding_end:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-end" property of @fo_fo.
 *
 * Return value: The "padding-end" property value.
**/
FoProperty *
fo_table_cell_get_padding_end (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_end;
}

/**
 * fo_table_cell_set_padding_end:
 * @fo_fo: The #FoFo object.
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end.
 **/
void
fo_table_cell_set_padding_end (FoFo *fo_fo,
		         FoProperty *new_padding_end)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_end == NULL) ||
		    FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref_sink (new_padding_end);
    }
  if (fo_table_cell->padding_end != NULL)
    {
      g_object_unref (fo_table_cell->padding_end);
    }
  fo_table_cell->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-end");*/
}

/**
 * fo_table_cell_get_padding_left:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-left" property of @fo_fo.
 *
 * Return value: The "padding-left" property value.
**/
FoProperty *
fo_table_cell_get_padding_left (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_left;
}

/**
 * fo_table_cell_set_padding_left:
 * @fo_fo: The #FoFo object.
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left.
 **/
void
fo_table_cell_set_padding_left (FoFo *fo_fo,
		         FoProperty *new_padding_left)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_left == NULL) ||
		    FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref_sink (new_padding_left);
    }
  if (fo_table_cell->padding_left != NULL)
    {
      g_object_unref (fo_table_cell->padding_left);
    }
  fo_table_cell->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-left");*/
}

/**
 * fo_table_cell_get_padding_right:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-right" property of @fo_fo.
 *
 * Return value: The "padding-right" property value.
**/
FoProperty *
fo_table_cell_get_padding_right (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_right;
}

/**
 * fo_table_cell_set_padding_right:
 * @fo_fo: The #FoFo object.
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right.
 **/
void
fo_table_cell_set_padding_right (FoFo *fo_fo,
		         FoProperty *new_padding_right)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_right == NULL) ||
		    FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref_sink (new_padding_right);
    }
  if (fo_table_cell->padding_right != NULL)
    {
      g_object_unref (fo_table_cell->padding_right);
    }
  fo_table_cell->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-right");*/
}

/**
 * fo_table_cell_get_padding_start:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-start" property of @fo_fo.
 *
 * Return value: The "padding-start" property value.
**/
FoProperty *
fo_table_cell_get_padding_start (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_start;
}

/**
 * fo_table_cell_set_padding_start:
 * @fo_fo: The #FoFo object.
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start.
 **/
void
fo_table_cell_set_padding_start (FoFo *fo_fo,
		         FoProperty *new_padding_start)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_start == NULL) ||
		    FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref_sink (new_padding_start);
    }
  if (fo_table_cell->padding_start != NULL)
    {
      g_object_unref (fo_table_cell->padding_start);
    }
  fo_table_cell->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-start");*/
}

/**
 * fo_table_cell_get_padding_top:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "padding-top" property of @fo_fo.
 *
 * Return value: The "padding-top" property value.
**/
FoProperty *
fo_table_cell_get_padding_top (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->padding_top;
}

/**
 * fo_table_cell_set_padding_top:
 * @fo_fo: The #FoFo object.
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top.
 **/
void
fo_table_cell_set_padding_top (FoFo *fo_fo,
		         FoProperty *new_padding_top)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_padding_top == NULL) ||
		    FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref_sink (new_padding_top);
    }
  if (fo_table_cell->padding_top != NULL)
    {
      g_object_unref (fo_table_cell->padding_top);
    }
  fo_table_cell->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_table_cell), "padding-top");*/
}

/**
 * fo_table_cell_get_role:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "role" property of @fo_fo.
 *
 * Return value: The "role" property value.
**/
FoProperty *
fo_table_cell_get_role (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->role;
}

/**
 * fo_table_cell_set_role:
 * @fo_fo: The #FoFo object.
 * @new_role: The new "role" property value.
 * 
 * Sets the "role" property of @fo_fo to @new_role.
 **/
void
fo_table_cell_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_role == NULL) ||
		    FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref_sink (new_role);
    }
  if (fo_table_cell->role != NULL)
    {
      g_object_unref (fo_table_cell->role);
    }
  fo_table_cell->role = new_role;
  /*g_object_notify (G_OBJECT (fo_table_cell), "role");*/
}

/**
 * fo_table_cell_get_source_document:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "source-document" property of @fo_fo.
 *
 * Return value: The "source-document" property value.
**/
FoProperty *
fo_table_cell_get_source_document (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->source_document;
}

/**
 * fo_table_cell_set_source_document:
 * @fo_fo: The #FoFo object.
 * @new_source_document: The new "source-document" property value.
 * 
 * Sets the "source-document" property of @fo_fo to @new_source_document.
 **/
void
fo_table_cell_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_source_document == NULL) ||
		    FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref_sink (new_source_document);
    }
  if (fo_table_cell->source_document != NULL)
    {
      g_object_unref (fo_table_cell->source_document);
    }
  fo_table_cell->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_table_cell), "source-document");*/
}

/**
 * fo_table_cell_get_width:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "width" property of @fo_fo.
 *
 * Return value: The "width" property value.
**/
FoProperty *
fo_table_cell_get_width (FoFo *fo_fo)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_val_if_fail (fo_table_cell != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_CELL (fo_table_cell), NULL);

  return fo_table_cell->width;
}

/**
 * fo_table_cell_set_width:
 * @fo_fo: The #FoFo object.
 * @new_width: The new "width" property value.
 * 
 * Sets the "width" property of @fo_fo to @new_width.
 **/
void
fo_table_cell_set_width (FoFo *fo_fo,
		         FoProperty *new_width)
{
  FoTableCell *fo_table_cell = (FoTableCell *) fo_fo;

  g_return_if_fail (fo_table_cell != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_table_cell));
  g_return_if_fail ((new_width == NULL) ||
		    FO_IS_PROPERTY_WIDTH (new_width));

  if (new_width != NULL)
    {
      g_object_ref_sink (new_width);
    }
  if (fo_table_cell->width != NULL)
    {
      g_object_unref (fo_table_cell->width);
    }
  fo_table_cell->width = new_width;
  /*g_object_notify (G_OBJECT (fo_table_cell), "width");*/
}
