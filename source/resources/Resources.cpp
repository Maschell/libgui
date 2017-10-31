
#include <malloc.h>
#include <string.h>
#include "Resources.h"
#include "filelist.h"
#include <system/AsyncDeleter.h>
#include <fs/FSUtils.h>
#include "gui/GuiImageAsync.h"
#include "gui/GuiSound.h"

Resources * Resources::instance = NULL;

void Resources::Clear(){
    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return;

	for(s32 i = 0; ResourceList[i].filename != NULL; ++i)
	{
		if(ResourceList[i].CustomFile)
		{
			free(ResourceList[i].CustomFile);
			ResourceList[i].CustomFile = NULL;
		}

		if(ResourceList[i].CustomFileSize != 0)
			ResourceList[i].CustomFileSize = 0;
	}

	if(instance)
        delete instance;

    instance = NULL;
}

bool Resources::LoadFiles(const char * path)
{
	if(!path)
		return false;

	bool result = false;
	Clear();

	ResourceFile * ResourceList = getResourceList();
	if(ResourceList == NULL) return false;

	for(s32 i = 0; ResourceList[i].filename != NULL; ++i)
	{
        std::string fullpath(path);
        fullpath += "/";
        fullpath += ResourceList[i].filename;

        u8 * buffer = NULL;
        u32 filesize = 0;

        FSUtils::LoadFileToMem(fullpath.c_str(), &buffer, &filesize);

        ResourceList[i].CustomFile = buffer;
        ResourceList[i].CustomFileSize = (u32) filesize;
        result |= (buffer != 0);
	}

	return result;
}

const u8 * Resources::GetFile(const char * filename)
{
    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return NULL;

	for(s32 i = 0; ResourceList[i].filename != NULL; ++i)
	{
		if(strcasecmp(filename, ResourceList[i].filename) == 0)
		{
			return (ResourceList[i].CustomFile ? ResourceList[i].CustomFile : ResourceList[i].DefaultFile);
		}
	}

	return NULL;
}

u32 Resources::GetFileSize(const char * filename)
{
    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return 0;

	for(s32 i = 0; ResourceList[i].filename != NULL; ++i)
	{
		if(strcasecmp(filename, ResourceList[i].filename) == 0)
		{
			return (ResourceList[i].CustomFile ? ResourceList[i].CustomFileSize : ResourceList[i].DefaultFileSize);
		}
	}
	return 0;
}

GuiImageData * Resources::GetImageData(const char * filename)
{
    if(!instance)
        instance = new Resources;

    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return NULL;

    std::map<std::string, std::pair<u32, GuiImageData *> >::iterator itr = instance->imageDataMap.find(std::string(filename));
    if(itr != instance->imageDataMap.end())
    {
        itr->second.first++;
        return itr->second.second;
    }

	for(s32 i = 0; ResourceList[i].filename != NULL; ++i)
	{
		if(strcasecmp(filename, ResourceList[i].filename) == 0)
		{
			const u8 * buff = ResourceList[i].CustomFile ? ResourceList[i].CustomFile : ResourceList[i].DefaultFile;
			const u32 size = ResourceList[i].CustomFile ? ResourceList[i].CustomFileSize : ResourceList[i].DefaultFileSize;

			if(buff == NULL)
                return NULL;

            GuiImageData * image = new GuiImageData(buff, size);
            instance->imageDataMap[std::string(filename)].first = 1;
            instance->imageDataMap[std::string(filename)].second = image;

            return image;
		}
	}

	return NULL;
}

void Resources::RemoveImageData(GuiImageData * image)
{
    std::map<std::string, std::pair<u32, GuiImageData *> >::iterator itr;

    for(itr = instance->imageDataMap.begin(); itr != instance->imageDataMap.end(); itr++)
    {
        if(itr->second.second == image)
        {
            itr->second.first--;

            if(itr->second.first == 0)
            {
                AsyncDeleter::pushForDelete( itr->second.second );
                instance->imageDataMap.erase(itr);
            }
            break;
        }
    }
}

GuiSound * Resources::GetSound(const char * filename)
{
    if(!instance)
        instance = new Resources;

    std::map<std::string, std::pair<u32, GuiSound *> >::iterator itr = instance->soundDataMap.find(std::string(filename));
    if(itr != instance->soundDataMap.end())
    {
        itr->second.first++;
        return itr->second.second;
    }

    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return NULL;

	for(s32 i = 0; ResourceList[i].filename != NULL; ++i)
	{
		if(strcasecmp(filename, ResourceList[i].filename) == 0)
		{
			const u8 * buff = ResourceList[i].CustomFile ? ResourceList[i].CustomFile : ResourceList[i].DefaultFile;
			const u32 size = ResourceList[i].CustomFile ? ResourceList[i].CustomFileSize : ResourceList[i].DefaultFileSize;

			if(buff == NULL)
                return NULL;

            GuiSound * sound = new GuiSound(buff, size);
            instance->soundDataMap[std::string(filename)].first = 1;
            instance->soundDataMap[std::string(filename)].second = sound;

            return sound;
		}
	}

	return NULL;
}

void Resources::RemoveSound(GuiSound * sound)
{
    std::map<std::string, std::pair<u32, GuiSound *> >::iterator itr;

    for(itr = instance->soundDataMap.begin(); itr != instance->soundDataMap.end(); itr++)
    {
        if(itr->second.second == sound)
        {
            itr->second.first--;

            if(itr->second.first == 0)
            {
                AsyncDeleter::pushForDelete( itr->second.second );
                instance->soundDataMap.erase(itr);
            }
            break;
        }
    }
}
