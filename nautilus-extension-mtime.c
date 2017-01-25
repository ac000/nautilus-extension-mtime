/*
 * nautilus-extension-mtime.c - Extension to display mtime in ISO-8601 format
 *
 * Copyright (C) 2013, 2017	Andrew Clayton <andrew@digital-domain.net>
 *
 * Released under the GNU General Public License version 2
 * See COPYING
 */

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include <libnautilus-extension/nautilus-column-provider.h>
#include <libnautilus-extension/nautilus-info-provider.h>

#include "nautilus-extension-mtime.h"

#define ISO_8601_FMT	"%04d-%02d-%02d %02d:%02d:%02d"

typedef struct {
	GObject parent_slot;
} MTimeExt;

typedef struct {
	GObjectClass parent_slot;
} MTimeExtClass;

static GType provider_types[1];
static GType mtime_extension_type;

void nautilus_module_initialize(GTypeModule *module)
{
	mtime_extension_register_type(module);
	provider_types[0] = mtime_extension_get_type();
}

void nautilus_module_shutdown(void)
{
	/* Any module-specific shutdown */
}

void nautilus_module_list_types(const GType **types, int *num_types)
{
	*types = provider_types;
	*num_types = G_N_ELEMENTS(provider_types);
}

static void mtime_extension_column_provider_iface_init(
		NautilusColumnProviderIface *iface)
{
	iface->get_columns = mtime_extension_get_columns;
}

static void mtime_extension_info_provider_iface_init(
		NautilusInfoProviderIface *iface)
{
	iface->update_file_info = mtime_extension_update_file_info;
}

static void mtime_extension_register_type(GTypeModule *module)
{
	static const GTypeInfo info = {
		sizeof(MTimeExtClass),
		(GBaseInitFunc)NULL,
		(GBaseFinalizeFunc)NULL,
		(GClassInitFunc)NULL,
		NULL,
		NULL,
		sizeof(MTimeExt),
		0,
		(GInstanceInitFunc)NULL,
	};

	static const GInterfaceInfo column_provider_iface_info = {
		(GInterfaceInitFunc)mtime_extension_column_provider_iface_init,
		NULL,
		NULL
	};

	static const GInterfaceInfo info_provider_iface_info = {
		(GInterfaceInitFunc)mtime_extension_info_provider_iface_init,
		NULL,
		NULL
	};

	mtime_extension_type = g_type_module_register_type(module,
			G_TYPE_OBJECT,
			"MTimeExt",
			&info, 0);

	/* ... add interfaces ... */
	g_type_module_add_interface(module,
			mtime_extension_type,
			NAUTILUS_TYPE_COLUMN_PROVIDER,
			&column_provider_iface_info);

	g_type_module_add_interface(module,
			mtime_extension_type,
			NAUTILUS_TYPE_INFO_PROVIDER,
			&info_provider_iface_info);
}

GType mtime_extension_get_type(void)
{
	return mtime_extension_type;
}

/* Column interfaces */
static GList *mtime_extension_get_columns(NautilusColumnProvider *provider)
{
	NautilusColumn *column;

	column = nautilus_column_new("MTimeExt::mtime_data_column",
			"MTimeExt::mtime_data",
			"Modified Time",
			"Show full mtime");
	return g_list_append(NULL, column);
}

/* Info interfaces */
static NautilusOperationResult mtime_extension_update_file_info(
		NautilusInfoProvider *provider,
		NautilusFileInfo *file,
		GClosure *update_complete,
		NautilusOperationHandle **handle)
{
	char datetime[32];
	struct stat sb;
	struct tm *tm;
	GFile *loc;

	loc = nautilus_file_info_get_location(file);
	stat(g_file_get_path(loc), &sb);

	tm = localtime(&sb.st_mtime);
	g_snprintf(datetime, sizeof(datetime), ISO_8601_FMT,
			tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
			tm->tm_hour, tm->tm_min, tm->tm_sec);
	nautilus_file_info_add_string_attribute(file,
			"MTimeExt::mtime_data", datetime);

	return NAUTILUS_OPERATION_COMPLETE;
}
