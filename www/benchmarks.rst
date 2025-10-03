.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See https://docutils.sourceforge.net/rst.html for details.

=============================================================
GraphicsMagick vs ImageMagick Benchmarks
=============================================================

.. _`Hyperfine` : https://github.com/sharkdp/hyperfine

.. contents::
  :local:

Foreword
=========

This page used to document benchmark results which compared
GraphicsMagick 1.3.8 performance to ImageMagick 6.5.8-10 performance.
We found that GraphicsMagick was usually considerably faster at
executing image processing operations from the command line than
ImageMagick 6.5.8-10 was. One ImageMagick algorithm ran as much as 770
times slower.  GraphicsMagick clearly ran much more efficiently under
Microsoft Windows.

We now find that a simple head to head performance comparison between
GraphicsMagick and recent ImageMagick is no longer possible because
ImageMagick has changed the meanings of the existing arguments.  In
particular, we discovered that ImageMagick filter arguments producing
convolution matrices are now producing lower-order convolution
matrices representing perhaps an order of magnitude less work given
the same arguments.  The resulting images are visually substantially
less filtered.  Using the same command-line filter arguments causes
GraphicsMagick to appear slower when it is actually doing far more
work than ImageMagick.

Due to it not being feasible to do a head to head performance
measurement between GraphicsMagick and ImageMagick, we have decided to
not post results at the moment.  However, the strategy and a simple
benchmark driver script are still provided for those who want to do
their own performance comparisons between GraphicsMagick and
ImageMagick.

Strategy
========

The benchmark focuses on the ability to process many medium sized
HD-resolution (1920x1080 pixels) images. In order to prevent disk I/O
from being a factor, we use a small input image and tile it to create
a larger input image via the "tile:" coder. The processed image is
sent to the "null:" coder so that file writes to a slow disk are also
not a factor.  Static executables are used and executed via full paths
in order to minimize variability from the execution environment. In
order to obtain accurate and useful timing, we use the bash shell to
execute the command 40 times and see how long it takes. This is a very
simple benchmark approach which is quite representative of the
performance that the typical user observes.

This new benchmark reveals the following performance criteria:

  * Basic execution overhead of the software.

  * Image processing algorithmic efficiency.

  * Efficacy of OpenMP enhancements.

The Simple Benchmark
====================

The benchmark is quite simple. It reads a list of commands to execute
from a file named "commands.txt" and times how long it takes to
execute each command 40 times using GraphicsMagick and ImageMagick.
This script will work with ImageMagick up to version 6.X, but not with
ImageMagick 7.X given that there is no longer a 'convert' command.

A sample set of commands to test with (not all of which will work with
ImageMagick) may be found in the GraphicsMagick source tree as
"utilities/tests/convert-cmds.txt".

Here is the simple benchmark script::

  #!/usr/bin/env bash
  #
  # Measure the performance between two 'convert' commands by
  # executing a subcommand through many iterations and seeing
  # the total time that it takes.
  #
  # Written by Bob Friesenhahn, October 2008
  #

  # GraphicsMagick
  convert1='/usr/local/bin/gm convert'
  #convert1='/c/Program\ Files/GraphicsMagick-1.3.8-Q16/gm.exe convert'

  # ImageMagick
  convert2='/usr/local/bin/convert'
  #convert2='/c/Program\ Files/ImageMagick-6.5.9-Q16/convert.exe'

  # Input file specification
  input_image='-size 1920x1080 tile:model.pnm'

  # Output file specification
  output_image="null:"

  # Should not need to change any of the rest
  typeset -i iterations=40
  echo "Convert-1:   ${convert1}"
  echo "Version:     `eval "${convert1}" -version | head -1`"
  echo "Convert-2:   ${convert2}"
  echo "Version:     `eval "${convert2}" -version | head -1`"
  echo "Date:        `date`"
  echo "Host:        `uname -n`"
  echo "OS:          `uname -s`"
  echo "Release:     `uname -r`"
  echo "Arch:        `uname -p`"
  echo "Input File:  ${input_image}"
  echo "Output File: ${output_image}"
  echo "Threads:     ${OMP_NUM_THREADS:-1}"
  echo "Iterations:  ${iterations}"
  echo "========================================================================================"
  echo
  typeset -i count=0 i=0
  cat commands.txt | while read subcommand
  do
    echo ${subcommand}

    command1="${convert1} ${input_image} ${subcommand} ${output_image}"
    i=0
    count=$iterations
    time while ((i < count))
    do
      eval "${command1}"
      let i=i+1
    done
    sleep 1

    command2="${convert2} ${input_image} ${subcommand} ${output_image}"
    i=0
    count=$iterations
    time while ((i < count))
    do
      eval "${command2}"
      let i=i+1
    done

    echo
    sleep 1
  done 2>&1

Performance testing with 'hyperfine'
====================================

Recently I learned about a Linux benchmark utility called
`Hyperfine`_. Hyperfine is available via GitHub, or as a package in
Linux distributions.

Hyperfine_ provides a handy way to evaluate the performance of two commands.
For example to evaluate the performance of a rotate request::

  cd /tmp
  gm convert rose: -resize 5000% -verbose rose.pnm
  hyperfine --warmup 2 --min-runs 20 'gm convert rose.pnm -rotate 92 output.pnm' --cleanup 'rm -f output.pnm'
  hyperfine --warmup 2 --min-runs 20 'magick rose.pnm -rotate 92 output.pnm' --cleanup 'rm -f output.pnm'
  hyperfine --warmup 2 --min-runs 20 'gm convert rose.pnm -rotate 90 output.pnm' --cleanup 'rm -f output.pnm'
  hyperfine --warmup 2 --min-runs 20 'magick rose.pnm -rotate 90 output.pnm' --cleanup 'rm -f output.pnm'

produces output like this on my laptop::

  ROSE PPM 70x46=>3500x2300+0+0 DirectClass 8-bit 0.000u 0m:0.000056s
  rose.pnm PNM 70x46=>3500x2300+0+0 DirectClass 8-bit 23.0Mi 0.130u 0m:0.021209s (148.3Ki pixels/s)
  Benchmark 1: gm convert rose.pnm -rotate 92 output.pnm
    Time (mean ± σ):     178.0 ms ±  15.4 ms    [User: 787.9 ms, System: 151.0 ms]
    Range (min … max):   165.6 ms … 224.1 ms    20 runs

  Benchmark 1: magick rose.pnm -rotate 92 output.pnm
    Time (mean ± σ):     785.3 ms ±  62.0 ms    [User: 2039.6 ms, System: 93.3 ms]
    Range (min … max):   714.9 ms … 921.5 ms    20 runs

  Benchmark 1: gm convert rose.pnm -rotate 90 output.pnm
    Time (mean ± σ):      77.1 ms ±   3.1 ms    [User: 75.7 ms, System: 63.6 ms]
    Range (min … max):    70.6 ms …  81.6 ms    41 runs

  Benchmark 1: magick rose.pnm -rotate 90 output.pnm
    Time (mean ± σ):     187.8 ms ±   9.5 ms    [User: 128.0 ms, System: 78.3 ms]
    Range (min … max):   177.0 ms … 206.6 ms    20 runs
