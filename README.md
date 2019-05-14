# libgui
[![Build Status](https://travis-ci.org/Maschell/libgui.svg?branch=master)](https://travis-ci.org/Maschell/libgui)  

## Usage
Following steps are required for initialization:
```C
InitOSFunctionPointers();   // Load OS functions
InitPadScoreFunctionPointers();
InitVPadFunctionPointers(); // Input functions for GUI control
InitFSFunctionPointers();   // To load file from the SD Card
InitGX2FunctionPointers();  // For rendering
InitAXFunctionPointers();   // For sound

mount_sd_fat("sd");			// Mounting the SD Card
memoryInitialize();			// Initialize memory management

//DO GUI STUFF HERE!

memoryRelease();
unmount_sd_fat("sd");
```

Link the application with:
```Makefile
-lgui -lutils -ldynamiclibs -lfreetype -lgd -lpng -ljpeg -lz -lmad -lvorbisidec -logg -lbz2
```

You also need to add the include path to your Makefile. Example:

```Makefile
export INCLUDE	:= [...] -I$(PORTLIBS)/include/freetype2 \
						 -I$(PORTLIBS)/include/libgui \
						 -I$(PORTLIBS)/include
```

TODO: provide more information

## Dependencies
To be able to use libgui, you need to install the following dependencies:

- Application needs to be loaded from the [homebrew_launcher](https://github.com/dimok789/homebrew_launcher)
- [libutils](https://github.com/Maschell/libutils) for common functions.
- [dynamic_libs](https://github.com/Maschell/dynamic_libs/tree/lib) for access to the functions.

- Install the required portlibs via `(dkp) pacman -Syu ppc-zlib ppc-libmad ppc-libogg ppc-libgd ppc-freetype ppc-libjpeg-turbo ppc-libpng ppc-libvorbisidec ppc-glm ppc-bzip2`

# Use the prebuilt files from a Docker image.
The image `wiiulegacy/libgui` on [Docker Hub](https://hub.docker.com/r/wiiulegacy/libgui/) provides a prebuilt library in the `/artifacts` directory. Copy it into your DevkitPPC portlibs folder.  

Example:  
```
COPY --from=wiiulegacy/libgui:0.1 /artifacts $DEVKITPRO/portlibs
```

# Credits
- Orignally based on https://github.com/dborth/libwiigui
- Wii U port / modification / new functions / sound / much more by dimok.
- Minor changes by Maschell
