.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See https://docutils.sourceforge.net/rst.html for details.

==========================================
 GraphicsMagick vs ImageMagick Benchmarks
==========================================

.. _`Hyperfine` : https://github.com/sharkdp/hyperfine

.. contents::
  :local:


A Simple Benchmark
==================

This benchmark is quite simple. It reads a list of commands to execute
from a file named "commands.txt" and times how long it takes to
execute each command 40 times using GraphicsMagick and ImageMagick.
ImageMagick 7.X no longer provides a 'convert' command since its
'magick' command is implicitly the same as convert by default.

A sample set of commands to test with (not all of which will work with
ImageMagick) may be found in the GraphicsMagick source tree as
"utilities/tests/convert-cmds.txt".  You can provide your own list of
commands based on what you use in your workflow.

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

  # ImageMagick 7
  convert2='/usr/local/bin/magick'

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

produces output like this on my laptop::

  % gm convert rose: -resize 5000% -verbose rose.pnm
  ROSE PPM 70x46=>3500x2300+0+0 DirectClass 8-bit 0.000u 0m:0.000057s
  rose.pnm PNM 70x46=>3500x2300+0+0 DirectClass 8-bit 23.0Mi 0.120u 0m:0.018557s (169.4Ki pixels/s)

  % hyperfine --warmup 2 --min-runs 20 'gm convert rose.pnm -rotate 92 output.pnm' --cleanup 'rm -f output.pnm'
  Benchmark 1: gm convert rose.pnm -rotate 92 output.pnm
    Time (mean ± σ):     155.1 ms ±   3.9 ms    [User: 712.2 ms, System: 140.5 ms]
    Range (min … max):   151.2 ms … 170.2 ms    20 runs

  % hyperfine --warmup 2 --min-runs 20 'magick rose.pnm -rotate 92 output.pnm' --cleanup 'rm -f output.pnm'
  Benchmark 1: magick rose.pnm -rotate 92 output.pnm
    Time (mean ± σ):     623.5 ms ±  44.6 ms    [User: 3621.7 ms, System: 66.5 ms]
    Range (min … max):   556.7 ms … 724.7 ms    20 runs

From the above, we can see that GraphicsMagick is four times as fast!

Now we test with an ImageMagick HDRI version by adding
the --enable-hdri configuration option::

  % hyperfine --warmup 2 --min-runs 20 'magick rose.pnm -rotate 92 output.pnm' --cleanup 'rm -f output.pnm'
  Benchmark 1: magick rose.pnm -rotate 92 output.pnm
    Time (mean ± σ):     728.7 ms ±  15.3 ms    [User: 3918.3 ms, System: 128.4 ms]
    Range (min … max):   699.4 ms … 751.7 ms    20 runs

And we see that the GraphicsMagick Q16 build is 4.7 times as fast as a
q16hdri build of ImageMagick!

Now we test ImageMagick 6.9.13-59 so we can see how legacy ImageMagick fares::

  % hyperfine --warmup 2 --min-runs 20 'convert rose.pnm -rotate 92 output.pnm' --cleanup 'rm -f output.pnm'
  Benchmark 1: convert rose.pnm -rotate 92 output.pnm
    Time (mean ± σ):     633.5 ms ±  35.9 ms    [User: 3611.1 ms, System: 88.5 ms]
    Range (min … max):   571.8 ms … 696.7 ms    20 runs

From the above, we see that legacy ImageMagick 6 is a little bit
faster than the latest ImageMagick 7, but still very slow.
