FROM wiiulegacy/core:0.1

# Get dependencies
COPY --from=wiiulegacy/dynamic_libs:0.1 /artifacts $DEVKITPRO/portlibs
COPY --from=wiiulegacy/libutils:0.1 /artifacts $DEVKITPRO/portlibs

# Get latest libgui from git
RUN git clone https://github.com/Maschell/libgui && cd libgui && git checkout v0.1
WORKDIR libgui

# install other dependencies
RUN 7z x -y ./libs/portlibs.zip -o${DEVKITPRO}

RUN make && \
	find $DEVKITPRO/portlibs -maxdepth 10 -type f -delete && \
	rm -rf $DEVKITPRO/portlibs/ppc/include && \
	make install && \
	7z x -y ./libs/portlibs.zip -o${DEVKITPRO} && \
	cp -r ${DEVKITPRO}/portlibs /artifacts

WORKDIR /artifacts
