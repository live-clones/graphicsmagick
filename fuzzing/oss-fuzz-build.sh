#!/bin/bash -eu

# This shell script is intended to be run from OSS-Fuzz's build
# environment. We intend to eventually refactor it to be easy to run
# locally.
#
# For local testing of fuzzing/oss-fuzz-build.sh in 'compile' mode do:
#
# Check 'compile' prompt for docker container id
# (e.g. '04a46e46f7af'). Can also check the output of 'docker ps -lq'.
#
# Then do:
#
# ~/src/GM% docker cp fuzzing/oss-fuzz-build.sh 04a46e46f7af:/src/graphicsmagick/fuzzing/oss-fuzz-build.sh
#
# or maybe"
#
# ~/src/GM% docker cp fuzzing/oss-fuzz-build.sh $(docker ps -lq):/src/graphicsmagick/fuzzing/oss-fuzz-build.sh
# ~/src/GM% docker cp fuzzing/coder_fuzzer.cc $(docker ps -lq):/src/graphicsmagick/fuzzing/
#
# Execute in the oss-fuzz shell environment like "/src/build.sh 2>&1 | tee build.sh" while
# in the initial "/src/graphicsmagick" directory.
#
#
# Useful environment variables:
#
# SANITIZER={address/memory/undefined}
# ARCHITECTURE={x86_64/i386}
# FUZZING_ENGINE
# LIB_FUZZING_ENGINE
# FUZZER_LDFLAGS
# FUZZING_LANGUAGE
# WORK=/work
# OUT=/out
# SRC=/src

printf "SANITIZER=%s\n" "${SANITIZER}"
printf "ARCHITECTURE=%s\n" "${ARCHITECTURE}"
printf "FUZZING_ENGINE=%s\n" "${FUZZING_ENGINE}"
printf "LIB_FUZZING_ENGINE=%s\n" "${LIB_FUZZING_ENGINE}"
printf "FUZZER_LDFLAGS=%s\n" "${FUZZER_LDFLAGS}"
printf "WORK=%s\n" "${WORK}"
printf "OUT=%s\n" "${OUT}"
printf "SRC=%s\n" "${SRC}"

# Libtiff build now requires autoconf-archive
apt install autoconf-archive

enable_aom=true
enable_bzip2=true
enable_freetype=true
enable_heif=true
enable_jasper=true
enable_jbig=true
enable_jpeg=true
enable_jxl=true
enable_lcms=true
enable_libde265=true
enable_libwmf=true
enable_libzip=true
enable_openh264=true
enable_openjpeg=true
enable_openjph=true
enable_png=true
enable_tiff=true
enable_vvdec=true
enable_vvenc=true
enable_webp=true
enable_x264=true
enable_x265=true
enable_xml=true
enable_xz=true
enable_zlib=true
enable_zstd=true

if [ "${SANITIZER}" = 'memory' ]
then
  # Libzip uses the host OpenSSL, which is not built for sanitizing.
  enable_libzip=false
fi

export PKG_CONFIG_PATH="${WORK}/lib/pkgconfig"
export PKG_CONFIG='pkg-config --static'
export VERBOSE=TRUE

# Disable system-provided strlcpy() and strlcat() in Autoconf scripts
export ac_cv_func_strlcpy=no
export ac_cv_func_strlcat=no

# Disable colorized output during build (since 2023 in clang)
# Can also add -fno-color-diagnostics or set TERM=dumb.
#export NO_COLOR=1
GM_SOURCE="${SRC}"/graphicsmagick

# Don't check Coverage in CI as it gets killed
if [[ -n "${OSS_FUZZ_CI-}" && "$SANITIZER" = coverage ]]; then
  touch "${OUT}"/exit
  exit 0
fi

# Shell function to return an on/off string based on truth value
# Use like:
#
#  foo=$(tv_on_off $enable_vvdec))
#
#    or
#
#  foo=$(tv_on_off [ -f "/path/to/expected/file" ])
function tv_on_off() {
  if "$@"; then
    echo "on"
  else
    echo "off"
  fi
}

# If doing oss-fuzz CI testing, then only include primary-class
# coders to improve chances of success
if [ -n "${OSS_FUZZ_CI-}" ]; then
    export MAGICK_CODER_STABILITY=PRIMARY
else
    export MAGICK_CODER_STABILITY=UNSTABLE
fi

printf "SRC=%s\n" "${SRC}"
printf "WORK=%s\n" "${WORK}"
ls -l "${WORK}"
printf "OUT=%s\n" "${OUT}"
ls -l "${OUT}"

rm -f "${OUT}"/*_fuzzer

BUILD="${WORK}"/build

set -x

# For some reason, libxml2 requires automake 1.16.3 or later, and this
# is handled by Dockerfile rules!

# build zlib
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static zlib --libs
#    -L/work/lib -lz
if ($enable_zlib) && [ -d "${SRC}"/zlib ]
then
    printf "\n\n=== Building zlib...\n"
    ZLIB_SRC="${SRC}/zlib"
    ZLIB_BUILD="${BUILD}/zlib"
    rm -rf "${ZLIB_BUILD}"
    mkdir -p "${ZLIB_BUILD}"
    (
        cd "${ZLIB_BUILD}"
        "${ZLIB_SRC}"/configure \
                   --static \
                   --prefix="${WORK}"
        make -j"$(nproc)" CFLAGS="${CFLAGS} -fPIC"
        make install
    )
fi

# build xz
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static liblzma --libs
#    -L/work/lib -llzma -pthread -lpthread
if ($enable_xz) && [ -d "${SRC}"/xz ]
then
    printf "\n\n=== Building xz...\n"
    (
        XZ_SRC="${SRC}"/xz
        XZ_BUILD="${BUILD}"/xz
        mkdir -p "${XZ_BUILD}"
        cd "${XZ_SRC}"
        ./autogen.sh --no-po4a --no-doxygen
        cd "${XZ_BUILD}"
        "${XZ_SRC}"/configure \
            --disable-assembler \
            --disable-doc \
            --disable-doxygen \
            --disable-lzip-decoder \
            --disable-lzma-links \
            --disable-lzmadec \
            --disable-lzmainfo \
            --disable-microlzma \
            --disable-nls \
            --disable-scripts \
            --disable-shared \
            --disable-xz \
            --disable-xzdec \
            --enable-static \
            --enable-threads=no \
            --with-pic=yes \
            --prefix="${WORK}"
        make -j"$(nproc)"
        make install
    )
fi

# build zstd
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libzstd --libs
#    -L/usr/local/lib -lzstd -pthread
if ($enable_zstd) && [ -d "${SRC}"/zstd ]
then
    printf "\n\n==== Building zstd...\n"
    (
        ZSTD_SRC="${SRC}"/zstd
        ZSTD_BUILD="${BUILD}"/zstd
        rm -rf "${ZSTD_BUILD}"
        mkdir -p "${ZSTD_BUILD}"
        cd "${ZSTD_BUILD}"
        cmake \
            -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_CXX_COMPILER="${CXX}" \
            -DCMAKE_CXX_FLAGS="${CXXFLAGS} -fPIC" \
            -DCMAKE_C_COMPILER="${CC}" \
            -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
            -DCMAKE_INSTALL_PREFIX="${WORK}" \
            -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
            -DZSTD_BUILD_SHARED=OFF \
            -DZSTD_BUILD_STATIC=ON \
            "${ZSTD_SRC}"/build/cmake
        make -j"$(nproc)"
        make install
    )
fi

# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libpng --libs
#    -L/work/lib -lpng16 -lm -lz
if ($enable_png) && [ -d "${SRC}"/libpng ]
then
    printf "\n\n=== Building libpng...\n"
    (
        PNG_SRC="${SRC}"/libpng
        PNG_BUILD="${BUILD}"/libpng
        cd "${PNG_SRC}"
        autoreconf -fiv
        rm -rf "${PNG_BUILD}"
        mkdir -p "${PNG_BUILD}"
        cd "${PNG_BUILD}"
        "${PNG_SRC}"/configure \
                  --prefix="${WORK}" \
                  --disable-shared \
                  --enable-static \
                  CPPFLAGS="-I${WORK}/include" \
                  CFLAGS="${CFLAGS} -fPIC" \
                  LDFLAGS="${LDFLAGS:-} -L${WORK}/lib"
        make clean
        make -j"$(nproc)"
        make install
    )
fi

if ($enable_xml) && [ -d "${SRC}"/libxml2 ]
then
    printf "\n\n=== Building libxml2...\n"
    (
        LIBXML2_SRC="${SRC}"/libxml2
        LIBXML2_BUILD="${BUILD}"/libxml2
        cd "${LIBXML2_SRC}"
        autoreconf -fiv

        rm -rf "${LIBXML2_BUILD}"
        mkdir -p "${LIBXML2_BUILD}"
        cd "${LIBXML2_BUILD}"

        #
        # Build is patterned after libxml2/fuzz/oss-fuzz-build.sh
        #
        # Don't enable zlib and liblzma with MSan
        if [ "$SANITIZER" = memory ]; then
            LIBXML2_EXTRA_CONFIG=''
        else
            LIBXML2_EXTRA_CONFIG='--with-zlib --with-lzma'
        fi
        # shellcheck disable=SC2086
        "${LIBXML2_SRC}"/configure \
                      --disable-shared \
                      --without-debug \
                      --without-http \
                      --without-python \
                      ${LIBXML2_EXTRA_CONFIG} \
                      --prefix="${WORK}"
        make -j"$(nproc)"
        make install
    )
fi

# build libjpeg-turbo
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjpeg --libs
#     -L/work/lib -ljpeg
if ($enable_jpeg) && [ -d "${SRC}"/libjpeg-turbo ]
then
    printf "\n\n=== Building libjpeg-turbo...\n"
    (
        LIBJPEG_SRC="${SRC}"/libjpeg-turbo
        LIBJPEG_BUILD="${BUILD}"/libjpeg-turbo

        rm -rf "${LIBJPEG_BUILD}"
        mkdir -p "${LIBJPEG_BUILD}"
        cd "${LIBJPEG_BUILD}"
        cmake . \
              -DCMAKE_BUILD_TYPE=Debug \
              -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
              -DCMAKE_INSTALL_PREFIX="${WORK}" \
              -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
              -DENABLE_SHARED=off \
              -DENABLE_STATIC=on \
              -DWITH_JPEG8=1 \
              -DWITH_SIMD=0 \
              "${LIBJPEG_SRC}"
        make -j"$(nproc)"
        make install
    )
fi

if ($enable_webp) && [ -d "${SRC}"/libwebp ]
   then
       # Build webp
       # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libwebp --libs
       #    -L/work/lib -lwebp -lm -lsharpyuv -lm
       printf "\n\n=== Building libwebp...\n"
       (
           LIBWEP_SRC="${SRC}"/libwebp
           LIBWEP_BUILD="${BUILD}"/libwebp

           rm -rf "${LIBWEP_BUILD}"
           mkdir -p "${LIBWEP_BUILD}"
           cd "${LIBWEP_BUILD}"

           cd "${LIBWEP_SRC}"
           autoreconf -fiv

           cd "${LIBWEP_BUILD}"
           #PKG_CONFIG_PATH="${WORK}/lib/pkgconfig" PKG_CONFIG='pkg-config --static'
           "${LIBWEP_SRC}"/configure \
               CPPFLAGS="-I${WORK}/include" \
               CFLAGS="${CFLAGS} -fPIC" \
               LDFLAGS="${LDFLAGS:-} -L${WORK}/lib" \
               --disable-gif \
               --disable-gl \
               --disable-jpeg \
               --disable-png \
               --disable-sdl \
               --disable-shared \
               --disable-tiff \
               --disable-wic \
               --enable-libwebpmux \
               --enable-static \
               --prefix="${WORK}"
           make V=1 -j"$(nproc)"
           make install
       )
fi

if ($enable_bzip2) && [ -d "${SRC}"/bzip2 ]
then
    printf "\n\n=== Building bzip2...\n"
    (
        BZIP2_SRC="${SRC}"/bzip2
        BZIP2_BUILD="${BUILD}"/bzip2

        rm -rf "${BZIP2_BUILD}"
        mkdir -p "${BZIP2_BUILD}"
        cd "${BZIP2_BUILD}"

        cmake -G "Unix Makefiles" \
              -DCMAKE_BUILD_TYPE=Debug \
              -DCMAKE_C_COMPILER="${CC}" \
              -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
              -DCMAKE_INSTALL_PREFIX="${WORK}" \
              -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
              -DENABLE_LIB_ONLY=ON \
              -DENABLE_SHARED_LIB=OFF \
              -DENABLE_STATIC_LIB=ON \
              "${BZIP2_SRC}"
        make clean
        make -j"$(nproc)"
        make install
        mv "${WORK}/lib/libbz2_static.a" "${WORK}/lib/libbz2.a"
    )
fi

# Build libjbig
if ($enable_jbig) && [ -d "${SRC}"/jbigkit ]
then
    printf "\n\n=== Building jbigkit...\n"
    (
        JBIGKIT_SRC="${SRC}"/jbigkit
        JBIGKIT_BUILD="${BUILD}"/jbigkit

        LNDIR="${SRC}"/graphicsmagick/lndir.sh

        rm -rf "${JBIGKIT_BUILD}"
        mkdir -p "${JBIGKIT_BUILD}"
        cd "${JBIGKIT_BUILD}"

        # Create link tree to source directory
        sh "${LNDIR}" "${JBIGKIT_SRC}"

        cd ./libjbig

        sed -i 's/^CC =/# CC =/g' Makefile
        sed -i 's/^CFLAGS =/# CFLAGS =/g' Makefile
        make clean
        make

        cp -p -- *.a "${WORK}/lib/"
        cp -p -- *.h "${WORK}/include/"
    )
fi

# FXIME: Add libdeflate, and libdeflate build here

# Build OpenJPEG
if ($enable_openjpeg) && [ -d "${SRC}"/openjpeg ]
then
    printf "\n\n=== Building openjpeg...\n"
    (
        OPENJPEG_SRC="${SRC}"/openjpeg
        OPENJPEG_BUILD="${BUILD}"/openjpeg

        rm -rf "${OPENJPEG_BUILD}"
        mkdir -p "${OPENJPEG_BUILD}"
        cd "${OPENJPEG_BUILD}"

        cmake -G "Unix Makefiles" \
              -DCMAKE_BUILD_TYPE=Debug \
              -DCMAKE_C_COMPILER="${CC}" \
              -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
              -DCMAKE_INSTALL_PREFIX="${WORK}" \
              -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
              -DBUILD_CODEC=OFF \
              -DBUILD_SHARED_LIBS=OFF \
              -DBUILD_STATIC_LIBS=ON \
              "${OPENJPEG_SRC}"
        make clean
        make -j"$(nproc)"
        make install
    )
fi

# Build libtiff
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libtiff-4 --libs
#  -L/work/lib -L/usr/local/lib -L/work/lib -ltiff -lwebp -lzstd -llzma -ljpeg -lz -lm -lwebp -lm -lsharpyuv -lm -lzstd -pthread -llzma -pthread -lpthread -ljpeg -lz
if ($enable_tiff) && [ -d "${SRC}"/libtiff ]
then
    printf "\n\n=== Building libtiff...\n"
    (
        LIBTIFF_SRC="${SRC}"/libtiff
        LIBTIFF_BUILD="${BUILD}"/libtiff

        rm -rf "${LIBTIFF_BUILD}"
        mkdir -p "${LIBTIFF_BUILD}"
        cd "${LIBTIFF_BUILD}"

        if true ; then

            # Use Autotools
            cd "${LIBTIFF_SRC}"
            sed -i 's/2\.71/2\.69/' configure.ac
            autoreconf -fiv

            cd "${LIBTIFF_BUILD}"
            "${LIBTIFF_SRC}"/configure \
                          CPPFLAGS="-I${WORK}/include" \
                          CFLAGS="${CFLAGS} -fPIC" \
                          LDFLAGS="${LDFLAGS:-} -L${WORK}/lib" \
                          --disable-contrib \
                          --disable-ld-version-script \
                          --disable-old-jpeg \
                          --disable-jbig \
                          --disable-shared \
                          --disable-silent-rules \
                          --disable-tests \
                          --enable-static \
                          --enable-tools \
                          --prefix="${WORK}"
            make -j"$(nproc)"
            make install

        else

            # Use cmake
            cmake \
                -DCMAKE_BUILD_TYPE=Debug \
                -DCMAKE_CXX_COMPILER="${CXX}" \
                -DCMAKE_CXX_FLAGS="${CXXFLAGS} -fPIC" \
                -DCMAKE_C_COMPILER="${CC}" \
                -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                -DCMAKE_INSTALL_PREFIX="${WORK}" \
                -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                -DBUILD_SHARED_LIBS=OFF \
                "${SRC}/libtiff"
            make -j"$(nproc)"
            make install

        fi
    )
fi

# Build liblcms2
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static lcms2 --libs
#    -L/work/lib -llcms2 -lm -lpthread
# liblcms2 does not test for library dependencies using pkg-config!
# LIBS="`pkg-config --static --libs-only-l zlib libjpeg libtiff-4`"
if ($enable_lcms) && [ -d "${SRC}"/Little-CMS ]
then
    printf "\n\n=== Building Little-CMS...\n"
    (
        LCMS_SRC="${SRC}"/Little-CMS
        LCMS_BUILD="${BUILD}"/Little-CMS

        cd "${LCMS_SRC}"
        autoreconf -fiv

        rm -rf "${LCMS_BUILD}"
        mkdir -p "${LCMS_BUILD}"
        cd "${LCMS_BUILD}"

        "${LCMS_SRC}"/configure \
                     CPPFLAGS="-I${WORK}/include" \
                     CFLAGS="${CFLAGS} -fPIC" \
                     LDFLAGS="${LDFLAGS:-} -L${WORK}/lib" \
                     --disable-shared \
                     --enable-static \
                     --prefix="${WORK}" \
                     --without-jpeg \
                     --without-tiff \
                     --without-zlib
        make -j"$(nproc)"
        make install
    )
fi

if ($enable_jxl) && [ -d "${SRC}"/libjxl ]
then
    # Build libjxl
    #  PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjxl_threads --libs
    #    -L/work/lib -ljxl_threads -lm
    #  PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjxl --libs
    #    -L/work/lib -L -ljxl -lm -lhwy -lbrotlienc -lbrotlidec -lbrotlicommon -ljxl_cms -lm
    #
    # Removed -DJPEGXL_FORCE_SYSTEM_LCMS2=true
    # Added -DJPEGXL_ENABLE_SKCMS=true
    printf "\n\n=== Building libjxl...\n"
    (
        LIBJXL_SRC="${SRC}"/libjxl
        LIBJXL_BUILD="${BUILD}/libjxl"

        rm -rf "${LIBJXL_BUILD}"
        mkdir -p "${LIBJXL_BUILD}"
        cd "${LIBJXL_BUILD}"

        cmake \
            -DBUILD_SHARED_LIBS=false \
            -DBUILD_TESTING=off \
            -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_CXX_FLAGS="-DHWY_DISABLED_TARGETS=HWY_SSSE3 ${CXXFLAGS} -fPIC" \
            -DCMAKE_C_FLAGS="-DHWY_DISABLED_TARGETS=HWY_SSSE3 ${CFLAGS} -fPIC" \
            -DCMAKE_INSTALL_PREFIX="${WORK}" \
            -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
            -DJPEGXL_ENABLE_BENCHMARK=false \
            -DJPEGXL_ENABLE_EXAMPLES=false \
            -DJPEGXL_ENABLE_FUZZERS=false \
            -DJPEGXL_ENABLE_JPEGLI=false \
            -DJPEGXL_ENABLE_JPEGLI=false \
            -DJPEGXL_ENABLE_MANPAGES=OFF \
            -DJPEGXL_ENABLE_SJPEG=false \
            -DJPEGXL_ENABLE_SKCMS=false \
            -DJPEGXL_ENABLE_TOOLS=true \
            -DJPEGXL_ENABLE_VIEWERS=false \
            -DJPEGXL_FORCE_SYSTEM_LCMS2=false \
            "${LIBJXL_SRC}"

        make -j"$(nproc)"
        # libjxl claims to require libjxl_cms, but does not build/install one!
        #sed -i 's/ libjxl_cms//' ./lib/libjxl.pc

        printf "Installing libjxl...\n"
        make install
        (
            printf "Installing brotli...\n"
            cd third_party/brotli
            make install
            #cp third_party/brotli/*.a "${WORK}"/lib
            #cp third_party/brotli/*.pc "${WORK}"/lib/pkgconfig
        )
        printf "==================\n"
        printf "JXL version info\n"
        "${WORK}"/bin/cjxl --version
        printf "==================\n"
    )
fi

# Build freetype
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static freetype2 --libs
#    -L/work/lib -lfreetype -lpng16 -lm -lz
#
# See freetype2-testing/fuzzing/scripts and freetype2-testing/fuzzing/scripts/build/freetype.sh
#
# Freetype build may depend on bzip2, brotli, zlib, and libpng:
# configure --enable-static --disable-shared --with-brotli --with-bzip2 --with-zlib --with-png --without-harfbuzz
# Uses env BZIP2_CFLAGS, BZIP2_LIBS, BROTLI_CFLAGS, BROTLI_LIBS, ZLIB_CFLAGS, ZLIB_LIBS, LIBPNG_CFLAGS, LIBPNG_LIBS
#
# Disable 'harfbuzz' to avoid compilation error of autofit module due
# to "use of undeclared identifier 'RTLD_DEFAULT'".
if ($enable_freetype) && [ -d "${SRC}"/freetype ]
then
    printf "\n\n=== Building freetype...\n"
    (
        FREETYPE_SRC="${SRC}"/freetype
        FREETYPE_BUILD="${BUILD}"/freetype

        rm -rf "${FREETYPE_BUILD}"
        mkdir -p "${FREETYPE_BUILD}"

        cd "${FREETYPE_SRC}"
        ./autogen.sh

        cd "${FREETYPE_BUILD}"
        # --with-brotli --with-bzip2 --with-zlib --with-png --without-harfbuzz
        "${FREETYPE_SRC}"/configure \
                         CPPFLAGS="-I${WORK}/include" \
                         CFLAGS="${CFLAGS} -fPIC" \
                         LDFLAGS="${LDFLAGS:-} -L${WORK}/lib" \
                         --enable-static \
                         --disable-shared \
                         --with-brotli \
                         --with-bzip2 \
                         --with-zlib \
                         --with-png \
                         --without-harfbuzz \
                         --enable-freetype-config \
                         --prefix="${WORK}"
        make -j"$(nproc)"
        make install
    )
fi

if ($enable_heif) && [ -d "${SRC}"/libheif ]
then
    # Build libx264 (H.264 encoder)

    if ($enable_x264) && [ -d "${SRC}"/x264 ]
    then
        (
            LIBX264_SRC="${SRC}"/x264

            if [ -d "${LIBX264_SRC}" ]
            then
                LIBX264_BUILD="${BUILD}"/x264
                rm -rf "${LIBX264_BUILD}"
                mkdir -p "${LIBX264_BUILD}"
                cd "${LIBX264_BUILD}"

                printf "\n\n=== Building libx264 ...\n"
                "${LIBX264_SRC}"/configure \
                                --prefix="${WORK}" \
                                --enable-static \
                                --disable-bashcompletion \
                                --disable-opencl \
                                --disable-asm \
                                --disable-cli \
                                --extra-cflags="-I${WORK}/include ${CFLAGS} -fPIC" \
                                --extra-ldflags="${LDFLAGS:-} -L${WORK}/lib"
                make -j"$(nproc)"
                make install
            fi
        )
    fi

    # Build libx265 (a C++ library)
    #
    # libx265 is an open-source software library that encodes video
    # into the H.265/HEVC format.
    #
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static x265 --libs
    #    -L/work/lib -lx265 -lc++ -lm -lrt -lm -ldl -lgcc_s -lgcc -lgcc_s -lgcc -lrt -ldl
    # include(Version) # determine X265_VERSION and X265_LATEST_TAG
    #

    # The source for this is in source/x265.pc.in
    if ($enable_x265) && [ -d "${SRC}"/x265 ]
    then
        (
            LIBX265_SRC="${SRC}"/x265
            LIBX265_BUILD="${BUILD}"/x265

           # If source/cmake/Version.cmake detects that the source
           # code is managed by git, it fails to build or install the
           # x265.pc file that libheif demands!
           if [ -d "${LIBX265_SRC}"/.git ]
           then
               mv -f "${LIBX265_SRC}"/.git "${LIBX265_SRC}"/.git-moved
           fi

           rm -rf "${LIBX265_BUILD}"
           mkdir -p "${LIBX265_BUILD}"
           cd "${LIBX265_BUILD}"

           printf "\n\n=== Building libx265...\n"
           cmake -G "Unix Makefiles" \
                 -DCMAKE_BUILD_TYPE=Debug \
                 -DCMAKE_CXX_COMPILER="${CXX}" \
                 -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
                 -DCMAKE_C_COMPILER="${CC}" \
                 -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                 -DCMAKE_INSTALL_PREFIX="${WORK}" \
                 -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                 -DENABLE_ASSEMBLY:BOOL=OFF \
                 -DENABLE_SHARED:STRING=off \
                 -DX265_LATEST_TAG=TRUE \
                 "${LIBX265_SRC}"/source

           make clean
           make -j"$(nproc)" x265-static
           make install

           # Restore original git directory
           if [ -d "${LIBX265_SRC}/.git-moved" ]
           then
               mv -f "${LIBX265_SRC}/.git-moved" "${LIBX265_SRC}/.git"
           fi
        )
    fi

    # Build libde265 (a C++ library)
    #
    # libde265 is an open-source C library that serves as a decoder
    # and encoder for the H.265/HEVC video compression
    # standard. Libx265 also provides an encoder.
    #
    # We will use only its decoder functionality (and use libx265 for
    # encode).
    #
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libde265 --libs
    #     -L/work/lib -lde265 -lc++
    if ($enable_libde265) && [ -d "${SRC}"/libde265 ]
    then
        (
            printf "\n\n=== Building libde265...\n"

            LIBDE265_SRC="${SRC}"/libde265
            LIBDE265_BUILD="${BUILD}"/libde265

            rm -rf "${LIBDE265_BUILD}"
            mkdir -p "${LIBDE265_BUILD}"
            cd "${LIBDE265_BUILD}"

            cmake -G "Unix Makefiles" \
                  -DCMAKE_BUILD_TYPE=Debug \
                  -DCMAKE_CXX_COMPILER="${CXX}" \
                  -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
                  -DCMAKE_C_COMPILER="${CC}" \
                  -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                  -DCMAKE_INSTALL_RPATH='/usr/local/lib' \
                  -DCMAKE_INSTALL_PREFIX="${WORK}" \
                  -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                  -DBUILD_SHARED_LIBS=OFF \
                  -DENABLE_SDL=OFF \
                  -DENABLE_DECODER=ON \
                  -DENABLE_ENCODER=OFF \
                  "${LIBDE265_SRC}"
            make clean
            make -j"$(nproc)"
            make install
       )
    fi

    # Build openh264
    if ($enable_openh264) && [ -d "${SRC}"/openh264 ]
    then
        printf "\n\n=== Building openh264...\n"
        (
            OPENH64_SRC="${SRC}"/openh264
            OPENH64_BUILD="${BUILD}"/openh264

            rm -rf "${OPENH64_BUILD}"
            mkdir -p "${OPENH64_BUILD}"
            cd "${OPENH64_BUILD}"

            # Enable a verbose build (Yes/No)
            VERBOSE=Yes

            #cd "${OPENH64_SRC}"
            # Build using 'make', which is a GNU Makefile
            if [[ ${CXXFLAGS} = *sanitize=memory* ]]; then
                ASM_BUILD=No
            else
                ASM_BUILD=Yes
            fi
            #  make -C ${OPENH64_SRC} SRC_PATH=${OPENH64_SRC} -j"$(nproc)" ARCH="${ARCHITECTURE}" USE_ASM="${ASM_BUILD}" BUILDTYPE=Debug clean

            #make V="${VERBOSE}" -C "${OPENH64_SRC}" SRC_PATH="${OPENH64_SRC}"/ -j"$(nproc)" OS=linux ARCH="${ARCHITECTURE}" USE_ASM="${ASM_BUILD}" BUILDTYPE=Debug clean
            make V="${VERBOSE}" -C "${OPENH64_SRC}" SRC_PATH="${OPENH64_SRC}"/ -j"$(nproc)" OS=linux ARCH="${ARCHITECTURE}" USE_ASM="${ASM_BUILD}" BUILDTYPE=Debug libopenh264.a
            make V="${VERBOSE}" -C "${OPENH64_SRC}" SRC_PATH="${OPENH64_SRC}"/ -j"$(nproc)" OS=linux ARCH="${ARCHITECTURE}" USE_ASM="${ASM_BUILD}" BUILDTYPE=Debug PREFIX="${WORK}" install-static
        )
    fi

    # Build libaom (a mixed C/C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static aom --libs
    #    -L/work/lib -laom -lm -lpthread
    if ($enable_aom) && [ -d "${SRC}"/aom ]
    then
        (
            printf "\n\n=== Building libaom...\n"
            AOM_SRC="${SRC}"/aom
            AOM_BUILD="${BUILD}"/aom

            rm -rf "${AOM_BUILD}"
            mkdir -p "${AOM_BUILD}"
            cd "${AOM_BUILD}"

            cmake -G "Unix Makefiles" \
                  -DAOM_MAX_ALLOCABLE_MEMORY=536870912 \
                  -DAOM_TARGET_CPU=generic \
                  -DCMAKE_BUILD_TYPE=Debug \
                  -DCMAKE_CXX_COMPILER="${CXX}" \
                  -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
                  -DCMAKE_C_COMPILER="${CC}" \
                  -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                  -DCMAKE_INSTALL_PREFIX="${WORK}" \
                  -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                  -DCONFIG_PIC=1 \
                  -DCONFIG_SIZE_LIMIT=1 \
                  -DDECODE_HEIGHT_LIMIT=12288 \
                  -DDECODE_WIDTH_LIMIT=12288 \
                  -DDO_RANGE_CHECK_CLAMP=1 \
                  -DENABLE_DOCS=0 \
                  -DENABLE_EXAMPLES=0 \
                  -DENABLE_SHARED:bool=off \
                  -DENABLE_TESTS=0 \
                  "${AOM_SRC}"

            make clean
            make -j"$(nproc)"
            make install
        )
    fi

    # Build OpenJPH
    if ($enable_openjph) && [ -d "${SRC}"/OpenJPH ]
    then
        (
            printf "\n\n=== Building OpenJPH...\n"

            OPENJPH_SRC="${SRC}"/OpenJPH
            OPENJPH_BUILD="${BUILD}/OpenJPH"

            rm -rf "${OPENJPH_BUILD}"
            mkdir -p "${OPENJPH_BUILD}"
            cd "${OPENJPH_BUILD}"

            if [[ ${CXXFLAGS} = *sanitize=memory* ]]; then
                SIMD_DISABLE=TRUE
            else
                SIMD_DISABLE=FALSE
            fi

            cmake \
                -DCMAKE_BUILD_TYPE=Release \
                -DCMAKE_CXX_COMPILER="${CXX}" \
                -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
                -DCMAKE_C_COMPILER="${CC}" \
                -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                -DCMAKE_INSTALL_PREFIX="${WORK}" \
                -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                -DBUILD_SHARED_LIBS=FALSE \
                -DOJPH_ENABLE_TIFF_SUPPORT=OFF \
                -DOJPH_BUILD_EXECUTABLES=ON \
                -DOJPH_DISABLE_SIMD=${SIMD_DISABLE} \
                "${OPENJPH_SRC}"

                make -j"$(nproc)"
                # FIXME: Debug build produces libopenjph_d.a but pkgconfig says -lopenjph
                # At the moment, using a Release build solves it better than using sed.
                #sed -i 's/-lopenjph/-lopenjph_d/' openjph.pc
                make install
            )
    fi

    # Build vvdec
    if ($enable_vvdec) && [ -d "${SRC}"/vvdec ]
    then
        (
            printf "\n\n=== Building vvdec...\n"

            VVDEC_SRC="${SRC}"/vvdec

            VVDEC_BUILD="${BUILD}"/vvdec
            mkdir -p "${VVDEC_BUILD}"
            cd "${VVDEC_BUILD}"

            if [[ ${CXXFLAGS} = *sanitize=memory* ]]; then
                SIMD_ENABLE=FALSE
            else
                SIMD_ENABLE=TRUE
            fi

            cmake \
                -DCMAKE_BUILD_TYPE=Debug \
                -DCMAKE_CXX_COMPILER="${CXX}" \
                -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
                -DCMAKE_C_COMPILER="${CC}" \
                -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                -DCMAKE_INSTALL_PREFIX="${WORK}" \
                -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                -DVVDEC_ENABLE_BITSTREAM_DOWNLOAD=OFF \
                -DBUILD_SHARED_LIBS=FALSE \
                -DVVDEC_ENABLE_X86_SIMD="${SIMD_ENABLE}" \
                "${VVDEC_SRC}"
            make -j"$(nproc)"
            make install
        )
    fi

    # Build vvenc
    if ($enable_vvenc) && [ -d "${SRC}"/vvenc ]
    then
        (
            printf "\n\n=== Building vvenc...\n"

            VVENC_SRC="${SRC}"/vvenc

            VVENC_BUILD="${BUILD}"/vvenc
            mkdir -p "${VVENC_BUILD}"
            cd "${VVENC_BUILD}"

            if [[ ${CXXFLAGS} = *sanitize=memory* ]]; then
                SIMD_ENABLE=FALSE
            else
                SIMD_ENABLE=TRUE
            fi

            # The i386 build fails due to -Wshorten-64-to-32
            #
            # Adding -DVVENC_ENABLE_WERROR=0 to Cmake options keeps it
            # from adding -Werror.

            #CXX_FLAGS_EXTRA=''
            #if [ "${ARCHITECTURE}" = i386 ] ; then
            #    CXX_FLAGS_EXTRA=' -Wno-error=shorten-64-to-32'
            #fi
            CXX_FLAGS_EXTRA=''

            # x86 SIMD intrinsics enabled (using SIMDE for non-x86 targets)
            cmake \
                -DCMAKE_BUILD_TYPE=Debug \
                -DCMAKE_CXX_COMPILER="${CXX}" \
                -DCMAKE_CXX_FLAGS="${CXXFLAGS}${CXX_FLAGS_EXTRA}" \
                -DCMAKE_C_COMPILER="${CC}" \
                -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                -DCMAKE_INSTALL_PREFIX="${WORK}" \
                -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                -DBUILD_SHARED_LIBS=FALSE \
                -DVVENC_ENABLE_X86_SIMD="${SIMD_ENABLE}" \
                -DVVENC_ENABLE_WERROR=0 \
                "${VVENC_SRC}"

            make -j"$(nproc)"
            make install
        )
    fi

    # Build libheif (a C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libheif --libs
    #   -L/work/lib -lheif -lc++ -lde265 -lc++ -lx265 -lc++ -lm -lrt -lm -ldl -lgcc_s -lgcc -lgcc_s -lgcc -lrt -ldl -laom -lm -lpthread -lsharpyuv -lm
    (
        printf "\n\n=== Building libheif...\n"

        LIBHEIF_SRC="${SRC}"/libheif

        LIBHEIF_BUILD="${BUILD}"/libheif
        rm -rf "${LIBHEIF_BUILD}"
        mkdir -p "${LIBHEIF_BUILD}"

        cd "${LIBHEIF_BUILD}"
        #cmake --preset=fuzzing \
            #      -DCMAKE_C_COMPILER="${CC}" \
            #      -DCMAKE_CXX_COMPILER="${CXX}" \
            #      -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
            #      -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
            #      -DCMAKE_INSTALL_PREFIX="${WORK}" \
            #      -DFUZZING_COMPILE_OPTIONS="" \
            #      -DFUZZING_LINKER_OPTIONS="$LIB_FUZZING_ENGINE" \
            #      -DFUZZING_C_COMPILER="${CC}" -DFUZZING_CXX_COMPILER="${CXX}" \
            #      -DWITH_DEFLATE_HEADER_COMPRESSION=OFF \
            #      -DENABLE_SHARED:bool=off \
            #      -DCONFIG_PIC=1 \
            #      "${SRC}/libheif"

        # FIXME: Added -DHAVE_JPEG_WRITE_ICC_PROFILE=1 because libheif
        # failed to detect that libjpeg-turbo has
        # jpeg_write_icc_profile().  If this is not defined, then
        # there is a duplicate symbol problem.
        cmake \
            -DBUILD_SHARED_LIBS=off \
            -DBUILD_TESTING=off \
            -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_CXX_COMPILER="${CXX}" \
            -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
            -DCMAKE_C_COMPILER="${CC}" \
            -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
            -DCMAKE_INSTALL_PREFIX="${WORK}" \
            -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
            -DENABLE_PLUGIN_LOADING=off \
            -DENABLE_MULTITHREADING_SUPPORT=on \
            -DWITH_AOM_DECODER="$(tv_on_off $enable_aom)" \
            -DWITH_AOM_ENCODER="$(tv_on_off $enable_aom)" \
            -DWITH_DAV1D=off \
            -DWITH_EXAMPLES=off \
            -DWITH_FFMPEG_DECODER=off \
            -DWITH_JPEG_DECODER="$(tv_on_off $enable_jpeg)" \
            -DWITH_JPEG_ENCODER="$(tv_on_off $enable_jpeg)" \
            -DWITH_KVAZAAR=off \
            -DWITH_LIBDE265="$(tv_on_off $enable_libde265)" \
            -DWITH_OpenH264_ENCODER="$(tv_on_off $enable_openh264)" \
            -DWITH_OpenH264_DECODER="$(tv_on_off $enable_openh264)" \
            -DWITH_OPENJPH_DECODER=off \
            -DWITH_OPENJPH_ENCODER="$(tv_on_off $enable_openjph)" \
            -DWITH_OPENJPH_ENCODER_PLUGIN=off \
            -DWITH_OpenJPEG_DECODER="$(tv_on_off $enable_openjpeg)" \
            -DWITH_OpenJPEG_ENCODER="$(tv_on_off $enable_openjpeg)" \
            -DWITH_RAV1E=off \
            -DWITH_SvtEnc=off \
            -DWITH_UNCOMPRESSED_CODEC=on \
            -DWITH_UVG266=off \
            -DWITH_VVDEC="$(tv_on_off $enable_vvdec)" \
            -DWITH_VVDEC_PLUGIN=off \
            -DWITH_VVENC="$(tv_on_off $enable_vvenc)" \
            -DWITH_VVENC_PLUGIN=off \
            -DWITH_WEBCODECS=off \
            -DWITH_X264="$(tv_on_off $enable_x264)" \
            -DWITH_X265="$(tv_on_off $enable_x265)" \
            -DHAVE_JPEG_WRITE_ICC_PROFILE=1 \
            "${LIBHEIF_SRC}"
        make -j"$(nproc)"
        make install
    )
#             -DHAVE_JPEG_WRITE_ICC_PROFILE=1 \

fi

if ($enable_jasper) && [ -d "${SRC}"/jasper ]
then
    printf "\n\n=== Building %s/jasper...\n" "${SRC}"
    (
        # With all extras removed from libjasper
        # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static jasper --libs
        # -L/work/lib -ljasper

        JASPER_SRC="${SRC}"/jasper
        JASPER_BUILD="${BUILD}"/jasper

        rm -rf "${JASPER_BUILD}"
        mkdir -p "${JASPER_BUILD}"
        cd "${JASPER_BUILD}"

        cmake -G "Unix Makefiles" -H"$SRC/jasper" \
              -DCMAKE_BUILD_TYPE=Debug \
              -DCMAKE_CXX_COMPILER="${CXX}" \
              -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
              -DCMAKE_C_COMPILER="${CC}" \
              -DCMAKE_C_FLAGS="${CFLAGS} -fno-sanitize=undefined -fPIC" \
              -DCMAKE_INSTALL_PREFIX="${WORK}" \
              -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
              -DJAS_ENABLE_LIBHEIF=false \
              -DJAS_ENABLE_LIBJPEG=false \
              -DJAS_ENABLE_OPENGL=false \
              -DJAS_ENABLE_PROGRAMS=false \
              -DJAS_ENABLE_SHARED=false \
              -DJAS_ENABLE_BMP_CODEC=off \
              -DJAS_ENABLE_HEIC_CODEC=off \
              -DJAS_ENABLE_JP2_CODEC=on \
              -DJAS_ENABLE_JPC_CODEC=on \
              -DJAS_ENABLE_MIF_CODEC=off \
              -DJAS_ENABLE_PGX_CODEC=on \
              -DJAS_ENABLE_PNM_CODEC=off \
              -DJAS_ENABLE_RAS_CODEC=off \
              -DJAS_INCLUDE_BMP_CODEC=false \
              -DJAS_INCLUDE_JP2_CODEC=true \
              -DJAS_INCLUDE_JPC_CODEC=true \
              -DJAS_INCLUDE_JPG_CODEC=false \
              -DJAS_INCLUDE_MIF_CODEC=false \
              -DJAS_INCLUDE_PGX_CODEC=true \
              -DJAS_INCLUDE_PNM_CODEC=false \
              -DJAS_INCLUDE_RAS_CODEC=false \
              "${JASPER_SRC}"
        make -j"$(nproc)"
        make install
    )
fi

# Libzip also wants Nettle, GnuTLS, MbedTLS, or OpenSSL (checked in
# that order).  Each of these is quite an onerous dependency!
# Hopefully not required in order to work. Libzip's own oss-fuzz build
# seems to dynamically link with OpenSSL and expects the same shared
# library on the fuzzing host.
if ($enable_libzip) && [ -d "${SRC}"/libzip ]
then
    if [ -d "${SRC}"/libzip ]
    then
        printf "\n\n=== Building libzip...\n"
        (
            LIBZIP_SRC="${SRC}"/libzip
            LIBZIP_BUILD="${BUILD}/libzip"

            rm -rf "${LIBZIP_BUILD}"
            mkdir -p "${LIBZIP_BUILD}"
            cd "${LIBZIP_BUILD}"

            cmake \
                -DBUILD_SHARED_LIBS=off \
                -DCMAKE_BUILD_TYPE=Debug \
                -DCMAKE_C_COMPILER="${CC}" \
                -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
                -DCMAKE_INSTALL_PREFIX="${WORK}" \
                -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                -DBUILD_DOC=OFF \
                -DBUILD_EXAMPLES=OFF \
                -DBUILD_OSSFUZZ=OFF \
                -DBUILD_REGRESS=OFF \
                -DBUILD_TOOLS=ON \
                -DENABLE_GNUTLS=OFF \
                -DENABLE_MBEDTLS=OFF \
                -DENABLE_OPENSSL=OFF \
                -DHAVE_CRYPTO=OFF  \
                "${LIBZIP_SRC}"
            make -j"$(nproc)"
            make install
        )
    fi
fi

# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libwmf --libs
# -L/work/lib -lwmf -lwmflite -lfreetype -lbz2 -lpng18 -lm -lz -lm
#
# We only build libwmflite, which has no dependencies.
# There is no pkg-config support for libwmflite (but there is for libwmf).
if ($enable_libwmf) && [ -d "${SRC}"/libwmf ]
then
    printf "\n\n=== Building libwmf...\n"
    (
        LIBWMF_SRC="${SRC}"/libwmf
        LIBWMF_BUILD="${BUILD}"/libwmf

        rm -rf "${LIBWMF_BUILD}"
        mkdir -p "${LIBWMF_BUILD}"

        cd "${LIBWMF_SRC}"
        autoreconf -fiv

        cd "${LIBWMF_BUILD}"
        "${LIBWMF_SRC}"/configure \
                       --prefix="${WORK}" \
                       --disable-heavy \
                       --disable-shared \
                       --enable-static \
                       CPPFLAGS="-I${WORK}/include" \
                       CFLAGS="${CFLAGS} -fPIC" \
                       LDFLAGS="${LDFLAGS:-} -L${WORK}/lib"
        make clean
        make -j"$(nproc)"
        make install
    )
fi

printf "Built libraries:\n"
if [ -d "${WORK}"/lib ] ; then
    ls -l "${WORK}"/lib
else
    printf "  None!\n"
fi

# Re-bootstrap the GraphicsMagick Autotools and scripts. The
# GraphicsMagick repository is already bootstrapped so
# re-bootstrapping is not really necessary.  Sometimes this fails due
# to issues with network access while updating config.guess and
# config.sub.
#
# The --disable-compressed-files option blocks the reading and writing
# of gzip/bzip files.
#
#./bootstrap || printf "Failed to re-bootstrap GraphicsMagick!\n"

# Configure and build GraphicsMagick
{
    GM_SOURCE="${SRC}"/graphicsmagick
    GM_BUILD="${BUILD}"/graphicsmagick

    # freetype-config is in "${WORK}"/bin so we temporarily add "${WORK}"/bin to the path
    # pkg-config names GraphicsMagick, GraphicsMagickWand, GraphicsMagick++
    # -stdlib=libc++'
    printf "\n\n=== Building GraphicsMagick (SANITIZER=\"%s\")...\n" "${SANITIZER}"
    EXTRA_LIBS=''
    case "${SANITIZER}" in
        address)
            EXTRA_LIBS='-lc++'
            ;;
        none)
            EXTRA_LIBS='-lc++'
            ;;
        memory)
            EXTRA_LIBS='-lc++'
            ;;
        undefined)
            EXTRA_LIBS='-lubsan -lc++'
            ;;
        *)
            EXTRA_LIBS='-lc++'
            ;;
    esac

    if (true) ; then
        # In a static build, libheif omits dependencies for some libraries!
        if ($enable_vvdec) && [ -d "${BUILD}"/vvdec ] ; then
            LIB_VVDEC=$(pkg-config --libs-only-l libvvdec)
            if [ -n "${LIB_VVDEC}" ] ; then
                EXTRA_LIBS="${LIB_VVDEC} ${EXTRA_LIBS}"
            fi
        fi

        if ($enable_vvenc) && [ -d "${BUILD}"/vvenc ] ; then
            LIB_VVENC=$(pkg-config --libs-only-l libvvenc)
            if [ -n "${LIB_VVENC}" ] ; then
                EXTRA_LIBS="${LIB_VVENC} ${EXTRA_LIBS}"
            fi
        fi
    fi

    if (false) ; then
        # A strange thing about x264 is its pkg-config Cflags says "Cflags: -I${prefix}/include -DX264_API_IMPORTS"
        if ($enable_x264) && [ -d "${BUILD}"/x264 ] ; then
            LIB_X264=$(pkg-config --libs-only-l x264)
            if [ -n "${LIB_X264}" ] ; then
                EXTRA_LIBS="${LIB_X264} ${EXTRA_LIBS}"
            fi
        fi
    fi

    rm -rf "${GM_BUILD}"
    mkdir -p "${GM_BUILD}"
    cd "${GM_BUILD}"

    # -I"${WORK}"/include/libpng16 -I"${WORK}"/include/freetype2 -I"${WORK}"/include/libxml2
    PATH="${WORK}"/bin:$PATH  \
        "${GM_SOURCE}"/configure \
        CPPFLAGS="-DEXPERIMENTAL_EXIF_TAGS=1 -I${WORK}/include" \
        CFLAGS="${CFLAGS}" \
        LDFLAGS="${LDFLAGS:-} -L${WORK}/lib" \
        LIBS="${EXTRA_LIBS}" \
        --prefix="${WORK}" \
        --disable-compressed-files \
        --disable-installed \
        --without-perl \
        --with-quantum-depth=16
    make -j"$(nproc)"
    make install

    printf "\nInstalling GraphicsMagick config files to %s...\n" "${OUT}"
    # /out/lib/GraphicsMagick-1.4/config/
    mkdir -p "${OUT}"/lib/GraphicsMagick-1.4/config
    cp -p "${WORK}"/lib/GraphicsMagick-1.4/config/* "${OUT}"/lib/GraphicsMagick-1.4/config/
    # /out/share/GraphicsMagick-1.4/
    mkdir -p "${OUT}"/share/GraphicsMagick-1.4/config
    cp -p "${WORK}"/share/GraphicsMagick-1.4/config/* "${OUT}"/share/GraphicsMagick-1.4/config/

    set +x # Turn off tracing

    #
    # Build oss-fuzz fuzzers
    #

    # Order libraries in linkage dependency order so libraries on the
    # right provide symbols needed by libraries to the left, to the
    # maximum extent possible.
    #
    # GraphicsMagick, GraphicsMagickWand, GraphicsMagick++
    MAGICK_LIBS="$(pkg-config --static --libs-only-L GraphicsMagick++) $(pkg-config --static --libs-only-other GraphicsMagick++) $(pkg-config pkg-config --static --libs-only-l GraphicsMagick++)"
    printf "MAGICK_LIBS=%s\n" "${MAGICK_LIBS}"

    # FUZZ_GRAPHICSMAGICK_CODER_READANY

    printf "\n\n=== Building fuzzers...\n"
    for f in "${GM_SOURCE}"/fuzzing/*_fuzzer.cc; do
        fuzzer=$(basename "$f" _fuzzer.cc)
        # coder_fuzzer is handled specially below.
        if [ "$fuzzer" == "coder" ]; then
            continue
        fi

        target="$OUT/${fuzzer}_fuzzer"
        printf "\n\n=== Building %s...\n" "${target}"
        set -x
        # shellcheck disable=SC2086
        "${CXX}" ${CXXFLAGS} -std=c++11 -I"${WORK}/include/GraphicsMagick" \
             "$f" -o "${target}" \
             $LIB_FUZZING_ENGINE $MAGICK_LIBS
        set +x
    done

    target="${WORK}/coder_list"
    printf "\n\n=== Building %s...\n" "${target}"
    set -x
     # shellcheck disable=SC2086
    "${CXX}" ${CXXFLAGS} -std=c++11 -I"${WORK}/include/GraphicsMagick" \
         "${GM_SOURCE}"/fuzzing/coder_list.cc -o "${target}" $MAGICK_LIBS
    set +x

    for item in $("${WORK}/coder_list"); do
        coder="${item:1}"
        coder_flags="-DFUZZ_GRAPHICSMAGICK_CODER=${coder}"
        if [ "${item:0:1}" == "+" ]; then
            coder_flags="${coder_flags} -DFUZZ_GRAPHICSMAGICK_CODER_WRITE=1"
        fi

        # Build fuzzers which force the input format
        target="${OUT}/coder_${coder}_fuzzer"
        printf "\n\n=== Building %s...\n" "${target}"
        set -x
         # shellcheck disable=SC2086
        "${CXX}" ${CXXFLAGS} -std=c++11 -I"${WORK}/include/GraphicsMagick" \
             "${GM_SOURCE}"/fuzzing/coder_fuzzer.cc -o "${target}" \
             ${coder_flags} $LIB_FUZZING_ENGINE $MAGICK_LIBS
        set +x

        # Additionally build fuzzers which auto-detect input for coders which write output
        if [ "${coder}" == 'TIFF' ]; then
            coder_flags="$coder_flags -DFUZZ_GRAPHICSMAGICK_CODER_READANY=1"
            target="${OUT}/coder_${coder}_any_fuzzer"

            printf "\n\n=== Building %s...\n" "${target}"
            set -x
             # shellcheck disable=SC2086
            "${CXX}" ${CXXFLAGS} -std=c++11 -I"${WORK}/include/GraphicsMagick" \
                 "${GM_SOURCE}"/fuzzing/coder_fuzzer.cc -o "${target}" \
                 ${coder_flags} $LIB_FUZZING_ENGINE $MAGICK_LIBS
            set +x
        fi

        # Copy over any fuzzing dictionaries
        if [ -f "${GM_SOURCE}/fuzzing/dictionaries/${coder}.dict" ]; then
            set -x
            cp "${GM_SOURCE}/fuzzing/dictionaries/${coder}.dict" "${OUT}/coder_${coder}_fuzzer.dict"
            set +x
        fi
    done

    # Add fuzzer settings for specific coders
    #
    # libfuzzer supports these:
    #
    # timeout = <seconds>: Specifies the maximum time in seconds the fuzzer should run a single input before considering it a timeout bug
    #
    # rss_limit_mb = <megabytes>: Sets the maximum memory usage in megabytes for the fuzzer process. Exceeding this limit results in an OOM (Out-Of-Memory) bug.
    #
    # dict = <dict_file>: Specifies the path to a dictionary file to help the fuzzer discover deeper code paths.
    #
    # max_len = <bytes>: Sets the maximum length of the input data that the fuzzer will generate.
    #
    # It seems that ClusterFuzz hard-limits the maximum timeout value to 65 seconds.
    cat << 'MARKER' > "${OUT}/coder_JBIG_fuzzer.options"
[libfuzzer]
timeout = 65
MARKER

    if true ; then
       #
       # Add a seed corpus
       #
       # https://google.github.io/oss-fuzz/getting-started/new-project-guide/#efficient-fuzzing
       #
       set -x
       CPREFIX='coder_'
       CSUFFIX='_fuzzer_seed_corpus'
       zip -rj "${OUT}"/"${CPREFIX}"AAI"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.aai
       zip -rj "${OUT}"/"${CPREFIX}"ART"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.art
       zip -rj "${OUT}"/"${CPREFIX}"BMP"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.bmp
       zip -rj "${OUT}"/"${CPREFIX}"CALS"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/tiff/*.cals
       zip -rj "${OUT}"/"${CPREFIX}"CIN"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.cin
       zip -rj "${OUT}"/"${CPREFIX}"DIB"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.dib
       zip -rj "${OUT}"/"${CPREFIX}"FITS"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.fits
       zip -rj "${OUT}"/"${CPREFIX}"GIF"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.gif
       zip -rj "${OUT}"/"${CPREFIX}"HEIF"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/heif/*.* "${SRC}"/libheif/fuzzing/data/corpus/*.heic
       zip -rj "${OUT}"/"${CPREFIX}"ICO"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.ico
       zip -rj "${OUT}"/"${CPREFIX}"JBIG"${CSUFFIX}".zip "${SRC}"/jbigkit/examples/*.jbg "${SRC}"/graphicsmagick/PerlMagick/t/jbig/*.jbig
       zip -rj "${OUT}"/"${CPREFIX}"JNG"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/jng/*
       zip -rj "${OUT}"/"${CPREFIX}"JNX"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.jnx
       zip -rj "${OUT}"/"${CPREFIX}"JP2"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/jp2/*.jp2
       zip -rj "${OUT}"/"${CPREFIX}"JPC"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/jp2/*.jpc
       zip -rj "${OUT}"/"${CPREFIX}"JPEG"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/jpeg/*
       zip -rj "${OUT}"/"${CPREFIX}"JXL"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/jxl/*.jxl
       zip -rj "${OUT}"/"${CPREFIX}"MAT"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.mat "${SRC}"/graphicsmagick/PerlMagick/t/zlib/*.mat
       zip -rj  "${OUT}"/"${CPREFIX}"MIFF"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.miff "${SRC}"/graphicsmagick/PerlMagick/t/zlib/*.miff
       zip -rj "${OUT}"/"${CPREFIX}"MTV"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.mtv
       zip -rj "${OUT}"/"${CPREFIX}"ORA"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.ora
       zip -rj "${OUT}"/"${CPREFIX}"P7"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.p7
       zip -rj "${OUT}"/"${CPREFIX}"PALM"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.palm
       zip -rj "${OUT}"/"${CPREFIX}"PAM"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.pam
       zip -rj "${OUT}"/"${CPREFIX}"PBM"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.pbm
       zip -rj "${OUT}"/"${CPREFIX}"PCT"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.pct
       zip -rj "${OUT}"/"${CPREFIX}"PCX"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.pcx
       zip -rj "${OUT}"/"${CPREFIX}"PGM"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.pgm
       zip -rj "${OUT}"/"${CPREFIX}"PGX"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/jp2/*.pgx
       zip -rj "${OUT}"/"${CPREFIX}"PNG"${CSUFFIX}".zip "$(find "${SRC}"/libpng -name '*.png' -print)" "${SRC}"/graphicsmagick/PerlMagick/t/png/*.png
       zip -rj "${OUT}"/"${CPREFIX}"PPM"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.ppm
       zip -rj "${OUT}"/"${CPREFIX}"PS"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/ps/*
       #zip -rj "${OUT}"/"${CPREFIX}"PXR"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.pxr
       zip -rj "${OUT}"/"${CPREFIX}"RLA"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.rla
       zip -rj "${OUT}"/"${CPREFIX}"RLE"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.rle
       zip -rj "${OUT}"/"${CPREFIX}"SUN"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.im1 "${SRC}"/graphicsmagick/PerlMagick/t/*.im8 "${SRC}"/graphicsmagick/PerlMagick/t/*.im24
       zip -rj "${OUT}"/"${CPREFIX}"TGA"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.tga
       zip -rj "${OUT}"/"${CPREFIX}"TIFF"${CSUFFIX}".zip "${SRC}"/libtiff/test/images/*.tiff "${SRC}"/graphicsmagick/PerlMagick/t/tiff/*.tif*
       zip -rj "${OUT}"/"${CPREFIX}"TOPOL"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/topol*
       zip -rj "${OUT}"/"${CPREFIX}"TTF"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/ttf/*
       zip -rj "${OUT}"/"${CPREFIX}"WBMP"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.wbmp
       zip -rj "${OUT}"/"${CPREFIX}"WMF"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/wmf/*
       zip -rj "${OUT}"/"${CPREFIX}"WPG"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.wpg
       zip -rj "${OUT}"/"${CPREFIX}"XBM"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.xbm
       zip -rj "${OUT}"/"${CPREFIX}"XPM"${CSUFFIX}".zip "${SRC}"/graphicsmagick/PerlMagick/t/*.xpm
       set +x
    fi
}

set +x
