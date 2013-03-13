/*
 * nautilus-extension-mtime.h - Extension to display mtime in ISO-8601 format
 *
 * Copyright (C) 2013		Andrew Clayton <andrew@digital-domain.net>
 *
 * Released under the GNU General Public License version 2
 * See COPYING
 */

#ifndef _NAUTILUS_EXTENSION_MTIME_
#define _NAUTILUS_EXTENSION_MTIME_

void nautilus_module_initialize(GTypeModule *module);
void nautilus_module_shutdown(void);
void nautilus_module_list_types(const GType **types, int *num_types);
static void mtime_extension_column_provider_iface_init(
		NautilusColumnProviderIface *iface);
static void mtime_extension_info_provider_iface_init(
		NautilusInfoProviderIface *iface);
static void mtime_extension_register_type(GTypeModule *module);
GType mtime_extension_get_type(void);
static GList *mtime_extension_get_columns(NautilusColumnProvider *provider);
static NautilusOperationResult mtime_extension_update_file_info(
	NautilusInfoProvider *provider,
	NautilusFileInfo *file,
	GClosure *update_complete,
	NautilusOperationHandle **handle);

#endif /* _NAUTILUS_EXTENSION_MTIME_ */
