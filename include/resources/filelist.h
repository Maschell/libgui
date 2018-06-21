#ifndef _FILELIST_H_
#define _FILELIST_H_

#include <stdint.h>

typedef struct _ResourceFile {
    const char *filename;
    const uint8_t   *DefaultFile;
    const uint32_t  &DefaultFileSize;
    uint8_t		   *CustomFile;
    uint32_t		    CustomFileSize;
} ResourceFile;

ResourceFile * getResourceList();

#endif
