// This may look like C code, but it is really -*- C++ -*-
//
// Copyright Bob Friesenhahn, 1999-2026
// SPDX-License-Identifier: MIT
//
// Tests for throwing exceptions
//

#include <Magick++.h>
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

using namespace Magick;

int main( int /*argc*/, char ** argv)
{
  // Trace exception events to help diagnose issues.
  SetLogDefaultEventType("exception");

  // Initialize/Deinitialize GraphicsMagick (scope based)
  InitializeMagickSentinel sentinel(*argv);

  volatile int failures=0;

  cout << "Checking for working exceptions (may crash and burn) ..." << endl;
  cout.flush();

  {
    // Basic exception test
    try
      {
        failures = failures+1;
        cout << "Throwing native 'int' exception" << endl;
        cout.flush();
        throw int(100);
      }
    catch ( int /*value_*/ )
      {
        cout << "Successfully caught native 'int' exception" << endl;
        cout.flush();
        failures = failures-1;
      }

    // Throw a Magick++ exception class.
    try
      {
        failures = failures+1;
        cout << "Throwing 'Magick::WarningResourceLimit' exception" << endl;
        cout.flush();
        throw WarningResourceLimit("How now brown cow?");
      }
    catch( Exception & /*error_*/ )
      {
        cout << "Successfully caught 'Magick::WarningResourceLimit' exception" << endl;
        cout.flush();
        failures = failures-1;
      }

    // A more complex test
    try
      {
        unsigned int columns = 640;
        unsigned int rows = 480;
        Geometry geometry(columns,rows);
        Color canvasColor( "red" );
        Image image( geometry, canvasColor);
        {
          try
            {
              failures = failures+1;
              cout << "Throwing library 'Magick::Exception' exception" << endl;
              cout.flush();
              image.directory();
            }
          catch ( Exception& /*error_*/ )
            {
              cout << "Successfully caught library 'Magick::Exception' exception" << endl;
              cout.flush();
              failures = failures-1;
            }
        }

      }
    catch( Exception &error_ )
      {
        cout << "Bogus catch: Caught exception: " << error_.what() << endl;
        cout.flush();
        return EXIT_FAILURE;
      }
    catch( exception &error_ )
      {
        cout << "Bogus catch: Caught exception: " << error_.what() << endl;
        cout.flush();
        return EXIT_FAILURE;
      }

    if ( failures )
      {
        cout << failures << " failures" << endl;
        cout.flush();
        return EXIT_FAILURE;
      }

    cout << "Exception testing passed!" << endl;
  }

  return EXIT_SUCCESS;
}
