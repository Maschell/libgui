# libgui
[![Build Status](https://travis-ci.org/Maschell/libgui.svg?branch=wut)](https://travis-ci.org/Maschell/libgui/tree/wut)  

## Usage
Following steps are required for initialization:
```C
memoryInitialize();			// Initialize memory management

//DO GUI STUFF HERE!

memoryRelease();
```

Link the application with:
```Makefile
-lguiwut -lutilswut -lfreetype -lgd -lpng -ljpeg -lmad -lvorbisidec -lzlib125
```

You also need to add the include path to your Makefile. Example:

```Makefile
export INCLUDE	:= [...] -I$(PORTLIBS)/include/freetype2 \
						 -I$(WUT_ROOT)/include/libguiwut \
						 -I$(PORTLIBS)/include
```

TODO: provide more information

## Dependencies
To be able to use libgui, you need to install the following dependencies:

- Application needs to be loaded from the [homebrew_launcher](https://github.com/dimok789/homebrew_launcher)
- [libutils](https://github.com/Maschell/libutils/tree/wut) (WUT branch) for common functions.
- [wut](https://github.com/decaf-emu/wut)

And other portable libraries that can be found in the "libs" folder of this repository. Extract the "portlibs.zip" into your devkitPro directory.  
`7z x -y ./libs/portlibs.zip -o${DEVKITPRO}`  
This package includes:

- freetype2 
- libgd 
- libpng 
- libjpeg
- libmad 
- vorbisidec

# Credits
- Orignally based on https://github.com/dborth/libwiigui
- Wii U port / modification / new functions / sound / much more by dimok.
- Minor changes by Maschell
