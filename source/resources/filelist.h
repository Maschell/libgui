#ifndef _FILELIST_H_
#define _FILELIST_H_
#include <dynamic_libs/os_types.h>

typedef struct _ResourceFile
{
	const char *filename;
	const u8   *DefaultFile;
	const u32  &DefaultFileSize;
	u8		   *CustomFile;
	u32		    CustomFileSize;
} ResourceFile;

ResourceFile * getResourceList();

#endif
