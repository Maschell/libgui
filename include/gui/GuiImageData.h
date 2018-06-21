/****************************************************************************
 * Copyright (C) 2015 Dimok
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#ifndef GUI_IMAGEDATA_H_
#define GUI_IMAGEDATA_H_

#include <gd.h>
#include <system/AsyncDeleter.h>
#include <gui/gx2_ext.h>
#include <gx2/texture.h>

class GuiImageData : public AsyncDeleter::Element {
public:
    //!Constructor
    GuiImageData();
    //!\param img Image data
    //!\param imgSize The image size
    GuiImageData(const uint8_t * img, int32_t imgSize, GX2TexClampMode textureClamp = GX2_TEX_CLAMP_MODE_CLAMP, GX2SurfaceFormat textureFormat = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8);
    //!Destructor
    virtual ~GuiImageData();
    //!Load image from buffer
    //!\param img Image data
    //!\param imgSize The image size
    void loadImage(const uint8_t * img, int32_t imgSize, GX2TexClampMode textureClamp = GX2_TEX_CLAMP_MODE_CLAMP, GX2SurfaceFormat textureFormat = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8);
    //! getter functions
    const GX2Texture * getTexture() const {
        return texture;
    };
    const GX2Sampler * getSampler() const {
        return sampler;
    };
    //!Gets the image width
    //!\return image width
    int32_t getWidth() const {
        if(texture) return texture->surface.width;
        else return 0;
    };
    //!Gets the image height
    //!\return image height
    int32_t getHeight() const {
        if(texture) return texture->surface.height;
        else return 0;
    };
    //! release memory of the image data
    void releaseData(void);
private:
    void gdImageToUnormR8G8B8A8(gdImagePtr gdImg, uint32_t *imgBuffer, uint32_t width, uint32_t height, uint32_t pitch);
    void gdImageToUnormR5G6B5(gdImagePtr gdImg, uint16_t *imgBuffer, uint32_t width, uint32_t height, uint32_t pitch);

    GX2Texture *texture;
    GX2Sampler *sampler;

    enum eMemoryTypes {
        eMemTypeMEM2,
        eMemTypeMEM1,
        eMemTypeMEMBucket
    };

    uint8_t memoryType;
};

#endif
