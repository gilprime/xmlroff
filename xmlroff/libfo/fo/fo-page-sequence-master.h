/* Fo
 * fo-page-sequence-master.h: 'page-sequence-master' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_MASTER_H__
#define __FO_PAGE_SEQUENCE_MASTER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoPageSequenceMaster:
 *
 * Instance of the 'page-sequence-master' formatting object.
 **/
typedef struct _FoPageSequenceMaster      FoPageSequenceMaster;

/**
 * FoPageSequenceMasterClass:
 *
 * Class structure for the 'page-sequence-master' formatting object.
 **/
typedef struct _FoPageSequenceMasterClass FoPageSequenceMasterClass;

#define FO_TYPE_PAGE_SEQUENCE_MASTER              (fo_page_sequence_master_get_type ())
#define FO_PAGE_SEQUENCE_MASTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PAGE_SEQUENCE_MASTER, FoPageSequenceMaster))
#define FO_PAGE_SEQUENCE_MASTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PAGE_SEQUENCE_MASTER, FoPageSequenceMasterClass))
#define FO_IS_PAGE_SEQUENCE_MASTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PAGE_SEQUENCE_MASTER))
#define FO_IS_PAGE_SEQUENCE_MASTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PAGE_SEQUENCE_MASTER))
#define FO_PAGE_SEQUENCE_MASTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PAGE_SEQUENCE_MASTER, FoPageSequenceMasterClass))


GType        fo_page_sequence_master_get_type (void) G_GNUC_CONST;
FoFo *       fo_page_sequence_master_new      (void);

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_MASTER_H__ */
