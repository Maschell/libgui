
#include <malloc.h>
#include <string.h>
#include <resources/Resources.h>
#include <resources/filelist.h>
#include <system/AsyncDeleter.h>
#include <fs/FSUtils.h>
#include <gui/GuiImageAsync.h>
#include <gui/GuiSound.h>

Resources * Resources::instance = NULL;

void Resources::Clear() {
    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return;

    for(int32_t i = 0; ResourceList[i].filename != NULL; ++i) {
        if(ResourceList[i].CustomFile) {
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

bool Resources::LoadFiles(const char * path) {
    if(!path)
        return false;

    bool result = false;
    Clear();

    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return false;

    for(int32_t i = 0; ResourceList[i].filename != NULL; ++i) {
        std::string fullpath(path);
        fullpath += "/";
        fullpath += ResourceList[i].filename;

        uint8_t * buffer = NULL;
        uint32_t filesize = 0;

        FSUtils::LoadFileToMem(fullpath.c_str(), &buffer, &filesize);

        ResourceList[i].CustomFile = buffer;
        ResourceList[i].CustomFileSize = (uint32_t) filesize;
        result |= (buffer != 0);
    }

    return result;
}

const uint8_t * Resources::GetFile(const char * filename) {
    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return NULL;

    for(int32_t i = 0; ResourceList[i].filename != NULL; ++i) {
        if(strcasecmp(filename, ResourceList[i].filename) == 0) {
            return (ResourceList[i].CustomFile ? ResourceList[i].CustomFile : ResourceList[i].DefaultFile);
        }
    }

    return NULL;
}

uint32_t Resources::GetFileSize(const char * filename) {
    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return 0;

    for(int32_t i = 0; ResourceList[i].filename != NULL; ++i) {
        if(strcasecmp(filename, ResourceList[i].filename) == 0) {
            return (ResourceList[i].CustomFile ? ResourceList[i].CustomFileSize : ResourceList[i].DefaultFileSize);
        }
    }
    return 0;
}

GuiImageData * Resources::GetImageData(const char * filename) {
    if(!instance)
        instance = new Resources;

    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return NULL;

    std::map<std::string, std::pair<uint32_t, GuiImageData *> >::iterator itr = instance->imageDataMap.find(std::string(filename));
    if(itr != instance->imageDataMap.end()) {
        itr->second.first++;
        return itr->second.second;
    }

    for(int32_t i = 0; ResourceList[i].filename != NULL; ++i) {
        if(strcasecmp(filename, ResourceList[i].filename) == 0) {
            const uint8_t * buff = ResourceList[i].CustomFile ? ResourceList[i].CustomFile : ResourceList[i].DefaultFile;
            const uint32_t size = ResourceList[i].CustomFile ? ResourceList[i].CustomFileSize : ResourceList[i].DefaultFileSize;

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

void Resources::RemoveImageData(GuiImageData * image) {
    std::map<std::string, std::pair<uint32_t, GuiImageData *> >::iterator itr;

    for(itr = instance->imageDataMap.begin(); itr != instance->imageDataMap.end(); itr++) {
        if(itr->second.second == image) {
            itr->second.first--;

            if(itr->second.first == 0) {
                AsyncDeleter::pushForDelete( itr->second.second );
                instance->imageDataMap.erase(itr);
            }
            break;
        }
    }
}

GuiSound * Resources::GetSound(const char * filename) {
    if(!instance)
        instance = new Resources;

    std::map<std::string, std::pair<uint32_t, GuiSound *> >::iterator itr = instance->soundDataMap.find(std::string(filename));
    if(itr != instance->soundDataMap.end()) {
        itr->second.first++;
        return itr->second.second;
    }

    ResourceFile * ResourceList = getResourceList();
    if(ResourceList == NULL) return NULL;

    for(int32_t i = 0; ResourceList[i].filename != NULL; ++i) {
        if(strcasecmp(filename, ResourceList[i].filename) == 0) {
            const uint8_t * buff = ResourceList[i].CustomFile ? ResourceList[i].CustomFile : ResourceList[i].DefaultFile;
            const uint32_t size = ResourceList[i].CustomFile ? ResourceList[i].CustomFileSize : ResourceList[i].DefaultFileSize;

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

void Resources::RemoveSound(GuiSound * sound) {
    std::map<std::string, std::pair<uint32_t, GuiSound *> >::iterator itr;

    for(itr = instance->soundDataMap.begin(); itr != instance->soundDataMap.end(); itr++) {
        if(itr->second.second == sound) {
            itr->second.first--;

            if(itr->second.first == 0) {
                AsyncDeleter::pushForDelete( itr->second.second );
                instance->soundDataMap.erase(itr);
            }
            break;
        }
    }
}
