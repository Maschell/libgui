# libgui


## Usage
Following steps are required for initialization:
```
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
```
-lgui -lutils -ldynamiclibs -lfreetype -lgd -lpng -ljpeg -lz  -lmad -lvorbisidec
```

You also need to add the include path to your Makefile. Example:

```
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

And other portable libraries that can be found in the "libs" folder of this repository. Extract the "portlibs.zip" into your devkitPro directory.
This package includes:

- freetype2 
- libgd 
- libpng 
- libjpeg 
- libz  
- libmad 
- vorbisidec

# Credits
- Orignally based on https://github.com/dborth/libwiigui
- Wii U port / modification / new functions / sound / much more by dimok.
- Minor changes by Maschell