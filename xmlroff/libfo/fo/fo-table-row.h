/* Fo
 * fo-table_row.h: 'table-row' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_TABLE_ROW_H__
#define __FO_TABLE_ROW_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoTableRow      FoTableRow;
typedef struct _FoTableRowClass FoTableRowClass;

#define FO_TYPE_TABLE_ROW              (fo_table_row_get_type ())
#define FO_TABLE_ROW(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TABLE_ROW, FoTableRow))
#define FO_TABLE_ROW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TABLE_ROW, FoTableRowClass))
#define FO_IS_TABLE_ROW(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TABLE_ROW))
#define FO_IS_TABLE_ROW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TABLE_ROW))
#define FO_TABLE_ROW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TABLE_ROW, FoTableRowClass))


GType        fo_table_row_get_type      (void) G_GNUC_CONST;
FoFo *       fo_table_row_new (void);

FoProperty * fo_table_row_get_background_color (FoFo       *fo_fo);
void         fo_table_row_set_background_color (FoFo       *fo_fo,
						FoProperty *new_background_color);
FoProperty * fo_table_row_get_background_image (FoFo       *fo_fo);
void         fo_table_row_set_background_image (FoFo       *fo_fo,
                                                FoProperty *new_background_image);
FoProperty * fo_table_row_get_block_progression_dimension (FoFo       *fo_fo);
void         fo_table_row_set_block_progression_dimension (FoFo       *fo_fo,
                                                           FoProperty *new_block_progression_dimension);
FoProperty * fo_table_row_get_border_after_color (FoFo       *fo_fo);
void         fo_table_row_set_border_after_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_after_color);
FoProperty * fo_table_row_get_border_after_precedence (FoFo       *fo_fo);
void         fo_table_row_set_border_after_precedence (FoFo       *fo_fo,
                                                       FoProperty *new_border_after_precedence);
FoProperty * fo_table_row_get_border_after_style (FoFo       *fo_fo);
void         fo_table_row_set_border_after_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_after_style);
FoProperty * fo_table_row_get_border_after_width (FoFo       *fo_fo);
void         fo_table_row_set_border_after_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_after_width);
FoProperty * fo_table_row_get_border_before_color (FoFo       *fo_fo);
void         fo_table_row_set_border_before_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_before_color);
FoProperty * fo_table_row_get_border_before_precedence (FoFo       *fo_fo);
void         fo_table_row_set_border_before_precedence (FoFo       *fo_fo,
                                                        FoProperty *new_border_before_precedence);
FoProperty * fo_table_row_get_border_before_style (FoFo       *fo_fo);
void         fo_table_row_set_border_before_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_before_style);
FoProperty * fo_table_row_get_border_before_width (FoFo       *fo_fo);
void         fo_table_row_set_border_before_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_before_width);
FoProperty * fo_table_row_get_border_bottom_color (FoFo       *fo_fo);
void         fo_table_row_set_border_bottom_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_bottom_color);
FoProperty * fo_table_row_get_border_bottom_style (FoFo       *fo_fo);
void         fo_table_row_set_border_bottom_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_bottom_style);
FoProperty * fo_table_row_get_border_bottom_width (FoFo       *fo_fo);
void         fo_table_row_set_border_bottom_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_bottom_width);
FoProperty * fo_table_row_get_border_end_color (FoFo       *fo_fo);
void         fo_table_row_set_border_end_color (FoFo       *fo_fo,
                                                FoProperty *new_border_end_color);
FoProperty * fo_table_row_get_border_end_precedence (FoFo       *fo_fo);
void         fo_table_row_set_border_end_precedence (FoFo       *fo_fo,
                                                     FoProperty *new_border_end_precedence);
FoProperty * fo_table_row_get_border_end_style (FoFo       *fo_fo);
void         fo_table_row_set_border_end_style (FoFo       *fo_fo,
                                                FoProperty *new_border_end_style);
FoProperty * fo_table_row_get_border_end_width (FoFo       *fo_fo);
void         fo_table_row_set_border_end_width (FoFo       *fo_fo,
                                                FoProperty *new_border_end_width);
FoProperty * fo_table_row_get_border_left_color (FoFo       *fo_fo);
void         fo_table_row_set_border_left_color (FoFo       *fo_fo,
                                                 FoProperty *new_border_left_color);
FoProperty * fo_table_row_get_border_left_style (FoFo       *fo_fo);
void         fo_table_row_set_border_left_style (FoFo       *fo_fo,
                                                 FoProperty *new_border_left_style);
FoProperty * fo_table_row_get_border_left_width (FoFo       *fo_fo);
void         fo_table_row_set_border_left_width (FoFo       *fo_fo,
                                                 FoProperty *new_border_left_width);
FoProperty * fo_table_row_get_border_right_color (FoFo       *fo_fo);
void         fo_table_row_set_border_right_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_right_color);
FoProperty * fo_table_row_get_border_right_style (FoFo       *fo_fo);
void         fo_table_row_set_border_right_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_right_style);
FoProperty * fo_table_row_get_border_right_width (FoFo       *fo_fo);
void         fo_table_row_set_border_right_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_right_width);
FoProperty * fo_table_row_get_border_start_color (FoFo       *fo_fo);
void         fo_table_row_set_border_start_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_start_color);
FoProperty * fo_table_row_get_border_start_precedence (FoFo       *fo_fo);
void         fo_table_row_set_border_start_precedence (FoFo       *fo_fo,
                                                       FoProperty *new_border_start_precedence);
FoProperty * fo_table_row_get_border_start_style (FoFo       *fo_fo);
void         fo_table_row_set_border_start_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_start_style);
FoProperty * fo_table_row_get_border_start_width (FoFo       *fo_fo);
void         fo_table_row_set_border_start_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_start_width);
FoProperty * fo_table_row_get_border_top_color (FoFo       *fo_fo);
void         fo_table_row_set_border_top_color (FoFo       *fo_fo,
                                                FoProperty *new_border_top_color);
FoProperty * fo_table_row_get_border_top_style (FoFo       *fo_fo);
void         fo_table_row_set_border_top_style (FoFo       *fo_fo,
                                                FoProperty *new_border_top_style);
FoProperty * fo_table_row_get_border_top_width (FoFo       *fo_fo);
void         fo_table_row_set_border_top_width (FoFo       *fo_fo,
                                                FoProperty *new_border_top_width);
FoProperty * fo_table_row_get_break_after (FoFo       *fo_fo);
void         fo_table_row_set_break_after (FoFo       *fo_fo,
                                           FoProperty *new_break_after);
FoProperty * fo_table_row_get_break_before (FoFo       *fo_fo);
void         fo_table_row_set_break_before (FoFo       *fo_fo,
                                            FoProperty *new_break_before);
FoProperty * fo_table_row_get_height (FoFo       *fo_fo);
void         fo_table_row_set_height (FoFo       *fo_fo,
                                      FoProperty *new_height);
FoProperty * fo_table_row_get_id (FoFo       *fo_fo);
void         fo_table_row_set_id (FoFo       *fo_fo,
                                  FoProperty *new_id);
FoProperty * fo_table_row_get_keep_together (FoFo       *fo_fo);
void         fo_table_row_set_keep_together (FoFo       *fo_fo,
                                             FoProperty *new_keep_together);
FoProperty * fo_table_row_get_keep_together_within_column (FoFo       *fo_fo);
void         fo_table_row_set_keep_together_within_column (FoFo       *fo_fo,
                                                           FoProperty *new_keep_together_within_column);
FoProperty * fo_table_row_get_keep_together_within_line (FoFo       *fo_fo);
void         fo_table_row_set_keep_together_within_line (FoFo       *fo_fo,
                                                         FoProperty *new_keep_together_within_line);
FoProperty * fo_table_row_get_keep_together_within_page (FoFo       *fo_fo);
void         fo_table_row_set_keep_together_within_page (FoFo       *fo_fo,
                                                         FoProperty *new_keep_together_within_page);
FoProperty * fo_table_row_get_keep_with_next (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_next (FoFo       *fo_fo,
                                              FoProperty *new_keep_with_next);
FoProperty * fo_table_row_get_keep_with_next_within_column (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                            FoProperty *new_keep_with_next_within_column);
FoProperty * fo_table_row_get_keep_with_next_within_line (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_next_within_line);
FoProperty * fo_table_row_get_keep_with_next_within_page (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_next_within_page);
FoProperty * fo_table_row_get_keep_with_previous (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_previous (FoFo       *fo_fo,
                                                  FoProperty *new_keep_with_previous);
FoProperty * fo_table_row_get_keep_with_previous_within_column (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                                FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_table_row_get_keep_with_previous_within_line (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                              FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_table_row_get_keep_with_previous_within_page (FoFo       *fo_fo);
void         fo_table_row_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                              FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_table_row_get_padding_after (FoFo       *fo_fo);
void         fo_table_row_set_padding_after (FoFo       *fo_fo,
                                             FoProperty *new_padding_after);
FoProperty * fo_table_row_get_padding_before (FoFo       *fo_fo);
void         fo_table_row_set_padding_before (FoFo       *fo_fo,
                                              FoProperty *new_padding_before);
FoProperty * fo_table_row_get_padding_bottom (FoFo       *fo_fo);
void         fo_table_row_set_padding_bottom (FoFo       *fo_fo,
                                              FoProperty *new_padding_bottom);
FoProperty * fo_table_row_get_padding_end (FoFo       *fo_fo);
void         fo_table_row_set_padding_end (FoFo       *fo_fo,
                                           FoProperty *new_padding_end);
FoProperty * fo_table_row_get_padding_left (FoFo       *fo_fo);
void         fo_table_row_set_padding_left (FoFo       *fo_fo,
                                            FoProperty *new_padding_left);
FoProperty * fo_table_row_get_padding_right (FoFo       *fo_fo);
void         fo_table_row_set_padding_right (FoFo       *fo_fo,
                                             FoProperty *new_padding_right);
FoProperty * fo_table_row_get_padding_start (FoFo       *fo_fo);
void         fo_table_row_set_padding_start (FoFo       *fo_fo,
                                             FoProperty *new_padding_start);
FoProperty * fo_table_row_get_padding_top (FoFo       *fo_fo);
void         fo_table_row_set_padding_top (FoFo       *fo_fo,
                                           FoProperty *new_padding_top);
FoProperty * fo_table_row_get_role (FoFo       *fo_fo);
void         fo_table_row_set_role (FoFo       *fo_fo,
                                    FoProperty *new_role);
FoProperty * fo_table_row_get_source_document (FoFo       *fo_fo);
void         fo_table_row_set_source_document (FoFo       *fo_fo,
                                               FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_TABLE_ROW_H__ */
