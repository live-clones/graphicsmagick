==============
Fuzzing README
==============

This directory contains fuzzers for GraphicsMagick's APIs, written using the
libFuzzer API: https://llvm.org/docs/LibFuzzer.html

These are automatically run by Google's OSS-Fuzz infrastructure:
https://github.com/google/oss-fuzz

See https://google.github.io/oss-fuzz/advanced-topics/reproducing/ for instructions for building/executing oss-fuzz targets locally.

Check GM build status::

  xdg-open https://oss-fuzz-build-logs.storage.googleapis.com/index.html#graphicsmagick

Check GM open issues::

  xdg-open https://issues.oss-fuzz.com/savedsearches/6886196

Read OSS-Fuzz usage documentation::

  xdg-open https://google.github.io/oss-fuzz/

Clone the OSS-Fuzz git repository::

  $ git clone --depth=1 https://github.com/google/oss-fuzz.git
  $ cd oss-fuzz

List existing Docker images::

  docker image ls

Clean up dangling (stale) Docker images::

  docker ps -a -q | xargs -I {} docker rm {} ; docker images -q -f dangling=true | xargs -I {} docker rmi -f {}; docker volume ls -qf dangling=true | xargs -I {} docker volume rm {}

Pull the latest Docker images::

  $ python3 infra/helper.py pull_images

Optionally remove the existing build directory (in git checkout):

  sudo rm -rf build

Optionally remove the existing project image::

  docker image rm gcr.io/oss-fuzz/graphicsmagick

Build the project image::

  python3 infra/helper.py build_image graphicsmagick

Build project fuzzer target::

  python3 infra/helper.py build_fuzzers --sanitizer <address/memory/undefined> \
    --architecture <x86_64/i386> graphicsmagick

  python3 infra/helper.py build_fuzzers --sanitizer address --architecture x86_64 graphicsmagick
  python3 infra/helper.py build_fuzzers --sanitizer memory --architecture x86_64 graphicsmagick
  python3 infra/helper.py build_fuzzers --sanitizer undefined --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers --sanitizer address --architecture i386 graphicsmagick
  # Following is broken due to missing ASAN library
  #python3 infra/helper.py build_fuzzers --sanitizer memory --architecture i386 graphicsmagick
  python3 infra/helper.py build_fuzzers --sanitizer undefined --architecture i386 graphicsmagick

Reproduce using local source checkout (mount local sources into the running container)::

  python3 infra/helper.py build_fuzzers \
    --sanitizer <address/memory/undefined> graphicsmagick <source_path>

  python3 infra/helper.py build_fuzzers --sanitizer address --architecture x86_64 graphicsmagick <source_path>
  python3 infra/helper.py reproduce graphicsmagick <fuzz_target_name> <testcase_path>

Reproducing bugs::

  $ python3 infra/helper.py reproduce graphicsmagick <fuzz_target_name> <testcase_path>

Check the build (this can take very long!)::

  python3 infra/helper.py build_fuzzers --sanitizer <address/memory/undefined> \
    --engine <libfuzzer/afl/honggfuzz/centipede> --architecture <x86_64/i386> graphicsmagick

  python3 infra/helper.py check_build  --sanitizer <address/memory/undefined> \
    --engine <libfuzzer/afl/honggfuzz/centipede> --architecture <x86_64/i386> graphicsmagick \
    <fuzz_target_name>

  python3 infra/helper.py build_fuzzers  --engine libfuzzer --sanitizer address   --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine libfuzzer --sanitizer address   --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine libfuzzer --sanitizer memory    --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine libfuzzer --sanitizer memory    --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine libfuzzer --sanitizer undefined --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine libfuzzer --sanitizer undefined --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine libfuzzer --sanitizer coverage --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine libfuzzer --sanitizer coverage --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine afl       --sanitizer address   --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine afl       --sanitizer address   --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine honggfuzz --sanitizer address   --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine honggfuzz --sanitizer address   --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine libfuzzer --sanitizer address   --architecture i386 graphicsmagick
  python3 infra/helper.py check_build    --engine libfuzzer --sanitizer address   --architecture i386 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine none      --sanitizer address   --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine none      --sanitizer address   --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine centipede --sanitizer address   --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine centipede --sanitizer address   --architecture x86_64 graphicsmagick

  python3 infra/helper.py build_fuzzers  --engine centipede --sanitizer none      --architecture x86_64 graphicsmagick
  python3 infra/helper.py check_build    --engine centipede --sanitizer none      --architecture x86_64 graphicsmagick

Get a shell into the container and compile::

  python3 infra/helper.py shell --engine libfuzzer --sanitizer address --architecture x86_64 graphicsmagick
    or
  python3 infra/helper.py shell --engine libfuzzer --sanitizer memory --architecture x86_64 graphicsmagick
    or
  python3 infra/helper.py shell --engine libfuzzer --sanitizer undefined --architecture x86_64 graphicsmagick
  compile 2>&1 | tee build.log

Copy fuzzing build script into running container (given simultaneous shell session)::

  docker cp fuzzing/oss-fuzz-build.sh $(docker ps -lq):/src/graphicsmagick/fuzzing/oss-fuzz-build.sh

  for file in oss-fuzz-build.sh utils.cc coder_list.cc ; do docker cp fuzzing/$file $(docker ps -lq):/src/graphicsmagick/fuzzing/ ; done

  Then use 'compile 2>&1 | tee build.log'.  This executes
  /src/build.sh while in the initial "/src/graphicsmagick" directory
  but does some other things as well.

Build Directory Products
------------------------

When the oss-fuzz build is performed within the Docker container, a
'build' directory is created and the directories 'out' and 'work' may
be accessed from the host OS.  The directory build/out/graphicsmagick
contains the build products for oss-fuzz's fuzzer, and the directory
build/work/graphicsmagick includes the build directory.  In
particular, build/work/graphicsmagick/bin includes static executables
for 'gm', and static executables for the the other software which was
built and installed (e.g. , which are capable of running under the host OS
without the docker container.  This is useful for testing.

Building A Starter Corpus
--------------------------


Building dependencies for development
-------------------------------------

Jasper
++++++

  git clone https://github.com/jasper-software/jasper.git jasper

  rm -rf ~/build/jasper
  mkdir -p ~/build/jasper
  cd ~/build/jasper
  cmake -G "Unix Makefiles" -H"$SRC/jasper" \
              -DCMAKE_BUILD_TYPE=Release \
              -DCMAKE_CXX_COMPILER=g++ \
              -DCMAKE_CXX_FLAGS='-O -g' \
              -DCMAKE_C_COMPILER=gcc \
              -DCMAKE_C_FLAGS='-O -g' \
              -DCMAKE_INSTALL_RPATH='/usr/local/lib'\
              -DCMAKE_INSTALL_PREFIX=/usr/local \
              -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
              -DBUILD_SHARED_LIBS=on \
              -DJAS_ENABLE_LIBHEIF=true \
              -DJAS_ENABLE_LIBJPEG=true \
              -DJAS_ENABLE_OPENGL=true \
              -DJAS_ENABLE_PROGRAMS=true \
              -DJAS_ENABLE_SHARED=true \
              -DJAS_ENABLE_BMP_CODEC=on \
              -DJAS_ENABLE_HEIC_CODEC=on \
              -DJAS_ENABLE_JP2_CODEC=on \
              -DJAS_ENABLE_JPC_CODEC=on \
              -DJAS_ENABLE_MIF_CODEC=off \
              -DJAS_ENABLE_PGX_CODEC=on \
              -DJAS_ENABLE_PNM_CODEC=on \
              -DJAS_ENABLE_RAS_CODEC=on \
              -DJAS_INCLUDE_BMP_CODEC=true \
              -DJAS_INCLUDE_JP2_CODEC=true \
              -DJAS_INCLUDE_JPC_CODEC=true \
              -DJAS_INCLUDE_JPG_CODEC=true \
              -DJAS_INCLUDE_MIF_CODEC=false \
              -DJAS_INCLUDE_PGX_CODEC=true \
              -DJAS_INCLUDE_PNM_CODEC=true \
              -DJAS_INCLUDE_RAS_CODEC=true \
              ~/src/jasper
  make -j"$(nproc)"
  make install

Building libheif (and dependencies) for development
---------------------------------------------------

de265
+++++

Sources come from https://github.com/strukturag/libde265.

This library provides both decoder and encoder for H.265/HEVC.

With sources under ~/src/libde265::

  rm -rf ~/build/libde265
  mkdir -p ~/build/libde265
  cd ~/build/libde265
  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=ON -DENABLE_SDL=OFF -DENABLE_DECODER=ON -DENABLE_ENCODER=ON ~/src/libde265
  make -j 8
  make install

x265
++++

Sources come from https://bitbucket.org/multicoreware/x265_git/src/master.

This library provides a H.265/HEVC encoder.

With sources under ~/src/x265-stable::

  [ May need to do 'mv .git .git-mv' ]

  rm -rf ~/build/x265-stable
  mkdir -p ~/build/x265-stable
  cd ~/build/x265-stable
  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DENABLE_ASSEMBLY:BOOL=ON -DX265_LATEST_TAG=TRUE ~/src/x265-stable/source
  make -j 8
  make install

openh264
++++++++

Sources come from https://github.com/cisco/openh264.

The openh264 build is based on a well-designed pure GNU Makefile.

  git clone https://github.com/cisco/openh264 ~/src/openh264

With sources under ~/src/openh264::

  rm -rf ~/build/openh264
  mkdir -p ~/build/openh264
  cd ~/build/openh264
  make -j 8 -f ~/src/openh264/Makefile OS=linux CC=gcc CXX=g++ CFLAGS_OPT='-O3' LDFLAGS='-Wl,-rpath=/usr/local/lib' ARCH=x86_64 USE_ASM=No BUILDTYPE=Release PREFIX=/usr/local clean
  make -j 8 -f ~/src/openh264/Makefile OS=linux CC=gcc CXX=g++ CFLAGS_OPT='-O3' LDFLAGS='-Wl,-rpath=/usr/local/lib' ARCH=x86_64 USE_ASM=No BUILDTYPE=Release PREFIX=/usr/local
  make -j 8 -f ~/src/openh264/Makefile OS=linux CC=gcc CXX=g++ CFLAGS_OPT='-O3' LDFLAGS='-Wl,-rpath=/usr/local/lib' ARCH=x86_64 USE_ASM=No BUILDTYPE=Release PREFIX=/usr/local install

aom
+++

Sources come from https://aomedia.googlesource.com/aom.

  git clone --depth 1 --branch main https://aomedia.googlesource.com/aom ~/src/aom

With sources under ~/src/aom::

  rm -rf ~/build/aom
  mkdir -p ~/build/aom
  cd ~/build/aom
  cmake -DAOM_TARGET_CPU=generic -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=TRUE ~/src/aom
  cmake --build . -- -j$(nproc)
  cmake --install .

libjpeg-turbo
+++++++++++++

Sources come from https://github.com/libjpeg-turbo/libjpeg-turbo.

  git clone https://github.com/libjpeg-turbo/libjpeg-turbo ~/src/libjpeg-turbo

With sources under ~/src/libjpeg-turbo::

  rm -rf  ~/build/libjpeg-turbo
  mkdir -p ~/build/libjpeg-turbo
  cd ~/build/libjpeg-turbo
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=ON -DWITH_JPEG8=1 ~/src/libjpeg-turbo
  cmake --build . -- -j$(nproc)
  cmake --install .

openjpeg
++++++++

Sources come from https://github.com/uclouvain/openjpeg.

  git clone https://github.com/uclouvain/openjpeg ~/src/openjpeg

With sources under ~/src/openjpeg::

  rm -rf ~/build/openjpeg
  mkdir -p ~/build/openjpeg
  cd ~/build/openjpeg
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON ~/src/openjpeg
  cmake --build . -- -j$(nproc)
  cmake --install .

libjxl
+++++++

Sources come from https://github.com/libjxl/libjxl.git.

The initial git checkout (from project at https://github.com/libjxl) looks like::

  git clone https://github.com/libjxl/libjxl.git --recursive --shallow-submodules ~/src/libjxl

After the initial checkout, 'git pull' will automatically take care of submodules.

Then see procedure in libjxl/BUILDING.md.  Based on that, do this::

  rm -rf ~/build/libjxl
  mkdir -p ~/build/libjxl
  cd ~/build/libjxl
  cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE ~/src/libjxl
  cmake --build . -- -j$(nproc)
  cmake --install .

vvdec
+++++

Project is at https://github.com/fraunhoferhhi/vvdec

The initial git checkout (from project at https://github.com/fraunhoferhhi/vvdec) looks like::

  git clone https://github.com/fraunhoferhhi/vvdec.git ~/src/vvdec

  rm -rf ~/build/vvdec
  mkdir -p ~/build/vvdec
  cd ~/build/vvdec
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DVVDEC_ENABLE_BITSTREAM_DOWNLOAD=OFF -DBUILD_SHARED_LIBS=TRUE ~/src/vvdec
  cmake --build . -- -j$(nproc)
  cmake --install .

vvenc
+++++

Project is at https://github.com/fraunhoferhhi/vvenc

The initial git checkout (from project at https://github.com/fraunhoferhhi/vvenc) looks like::

  git clone https://github.com/fraunhoferhhi/vvenc.git ~/src/vvenc

  rm -rf ~/build/vvenc
  mkdir -p ~/build/vvenc
  cd ~/build/vvenc
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=TRUE ~/src/vvenc
  cmake --build . -- -j$(nproc)
  cmake --install .

libx264
+++++++

Project is at https://code.videolan.org/videolan/x264

  libx264 provides only a H.264 encoder

  git clone https://code.videolan.org/videolan/x264.git/ ~/src/x264

  While 'configure' is provided, it is not an Autoconf configure script!

  cd ~/src/x264
  rm -rf ~/build/x264
  mkdir -p ~/build/x264
  cd ~/build/x264
  CC=gcc-13 CXX=g++-13 LDFLAGS='-L/usr/local/lib -Wl,-rpath,/usr/local/lib' ~/src/x264/configure --prefix=/usr/local --enable-shared --enable-static
  make -j 8
  make install

OpenJPH
+++++++

Project is at https://github.com/aous72/OpenJPH

  git clone https://github.com/aous72/OpenJPH.git ~/src/OpenJPH

  rm -rf ~/build/OpenJPH
  mkdir -p ~/build/OpenJPH
  cd ~/build/OpenJPH
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=TRUE ~/src/OpenJPH
  cmake --build . -- -j$(nproc)
  cmake --install .

libheif
+++++++

Sources come from https://github.com/strukturag/libheif.git

  git clone https://github.com/strukturag/libheif.git ~/src/libheif

  rm -rf ~/build/libheif
  mkdir -p ~/build/libheif
  cd ~/build/libheif
  cmake -DBUILD_SHARED_LIBS=on -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=on -DWITH_JPEG_DECODER=on -DWITH_JPEG_ENCODER=on -DWITH_OpenJPEG_ENCODER=on -DWITH_OpenJPEG_DECODER=on -DWITH_UNCOMPRESSED_CODEC=on -DWITH_OPENJPH_ENCODER=on -DWITH_OPENJPH_ENCODER_PLUGIN=off -DWITH_VVDEC=on -DWITH_VVDEC_PLUGIN=off -DWITH_VVENC=on -DWITH_VVENC_PLUGIN=off ~/src/libheif
  cmake --build . -- -j$(nproc)
  cmake --install .

Cmake should produce this in its configuration summary::

  === Supported formats ===
  format        decoding   encoding
  AVC             YES        YES
  AVIF            YES        YES
  HEIC            YES        YES
  JPEG            YES        YES
  JPEG2000        YES        YES
  JPEG2000-HT     YES        YES
  Uncompressed    YES        YES
  VVC             YES        YES

Check for expected configuration using::

  heif-enc --list-encoders
  heif-dec --list-decoders

libwmf
++++++

Sources come from https://github.com/caolanm/libwmf

  git clone https://github.com/caolanm/libwmf.git ~/src/libwmf

  autoreconf -fiv
  ./configure \
        --prefix=/usr/local \
        --enable-heavy \
        --enable-shared \
        --enable-static \
        CC=gcc-13 CXX=g++-13 \
        CPPFLAGS="-I/usr/local/include" \
        CFLAGS='-g -fPIC -Wall -Winline -W -Wformat-security -Wpointer-arith -Wdisabled-optimization -Wmissing-noreturn -Wno-unknown-pragmas -Wunused-but-set-variable -Wsign-compare' \
        LDFLAGS='-L/usr/local/lib -Wl,-rpath,/usr/local/lib'
