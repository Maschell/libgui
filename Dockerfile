FROM wiiulegacy/core:0.1

# Get dependencies
COPY --from=wiiulegacy/dynamic_libs:0.1 /artifacts $DEVKITPRO/portlibs
COPY --from=wiiulegacy/libutils:0.1 /artifacts $DEVKITPRO/portlibs

# Get latest libgui from git
RUN git clone https://github.com/Maschell/libgui && cd libgui && git checkout v0.1
WORKDIR libgui

# install other dependencies
RUN dkp-pacman -Syyu --noconfirm ppc-zlib ppc-libmad ppc-libogg ppc-libgd ppc-freetype ppc-libjpeg-turbo ppc-libpng ppc-libvorbisidec ppc-glm ppc-bzip2

RUN make && \
	find $DEVKITPRO/portlibs -maxdepth 10 -type f -delete && \
	rm -rf $DEVKITPRO/portlibs/ppc/include && \
	make install && \
	cp -r ${DEVKITPRO}/portlibs /artifacts

WORKDIR /artifacts
