//
// See https://llvm.org/docs/LibFuzzer.html
//

#define USE_DYNAMIC_INITIALIZATION 1

#if USE_DYNAMIC_INITIALIZATION

/*
  Deny access to some security-sensitive files.
*/
static MagickPassFail
MagickFuzzerConfirmAccess(const Magick::ConfirmAccessMode mode,
                          const char *path,
                          Magick::ExceptionInfo *exception)
{
  MagickPassFail
    status = MagickPass;

  unsigned int
    i;

  static const char *
    banned_files[] =
    {
      "/etc/passwd",
      "/etc/shadow",
      NULL
    };

  if ((mode == Magick::FileReadConfirmAccessMode) ||
      (mode == Magick::FileWriteConfirmAccessMode))

    {
      i=0;
      while (banned_files[i] != (const char *) NULL)
        {
          if (strcmp(banned_files[i],path) == 0)
            {
              ThrowException(exception,Magick::FileOpenError,"Access denied by policy",path);
              status = MagickFail;
              break;
            }
          i++;
        }
    }

  return(status);
}

// A custom fuzzer initialization function
extern "C" int LLVMFuzzerInitialize(int *argcp,char ***argvp) {
  int argc = *argcp;
  const char* exe_path = (*argvp)[0];
  // fprintf(stderr, "LLVMFuzzerInitialize(): argc=%d, exe_path = %s\n", argc, exe_path);
  Magick::InitializeMagick(exe_path);

  // Trace exception events to help diagnose issues.
  MagickLib::SetLogEventMask("exception");

  // Oss-fuzz itself (ASAN/UBSAN) seems to require memory and
  // the memory limit may be total virtual memory and not based
  // only on memory allocations and actual RSS. Formats like
  // SVG/MVG may make arbitrary requests.  Provide lots of
  // headroom.  Was 1000000000.
  //
  // A Q16 image with dimensions 2048x2048 requires 40,960k of
  // RAM.  Provide enough memory for 6 images, which seems like
  // enough for any reasonable fuzzing purpose.
  //
  // Don't allow using disk-based pixel cache files when the
  // memory resource runs out.
  MagickLib::SetMagickResourceLimit(MagickLib::MemoryResource, 268435456);
  MagickLib::SetMagickResourceLimit(MagickLib::WidthResource, 2048);
  MagickLib::SetMagickResourceLimit(MagickLib::HeightResource, 2048);
  MagickLib::SetMagickResourceLimit(MagickLib::PixelsResource,
                                    MagickLib::GetMagickResourceLimit(MagickLib::WidthResource)*
                                    MagickLib::GetMagickResourceLimit(MagickLib::HeightResource));
  MagickLib::SetMagickResourceLimit(MagickLib::DiskResource, 0);
  MagickLib::SetMagickResourceLimit(MagickLib::ReadResource, 900000);
  MagickLib::SetMagickResourceLimit(MagickLib::WriteResource, 1118720);
  MagickLib::SetMagickResourceLimit(MagickLib::ImagesResource, 1024);

  MagickLib::MagickSetConfirmAccessHandler(MagickFuzzerConfirmAccess);

  return 0;
}

#else

/*
  Use static initialization
*/
class MagickState {
public:
  MagickState() {
    Magick::InitializeMagick(nullptr);

    // Trace exception events to help diagnose issues.
    MagickLib::SetLogEventMask("exception");

    // Oss-fuzz itself (ASAN/UBSAN) seems to require memory and
    // the memory limit may be total virtual memory and not based
    // only on memory allocations and actual RSS. Formats like
    // SVG/MVG may make arbitrary requests.  Provide lots of
    // headroom.  Was 1000000000.
    //
    // A Q16 image with dimensions 2048x2048 requires 40,960k of
    // RAM.  Provide enough memory for 6 images, which seems like
    // enough for any reasonable fuzzing purpose.
    //
    // Don't allow using disk-based pixel cache files when the
    // memory resource runs out.
    MagickLib::SetMagickResourceLimit(MagickLib::MemoryResource, 268435456);
    MagickLib::SetMagickResourceLimit(MagickLib::WidthResource, 2048);
    MagickLib::SetMagickResourceLimit(MagickLib::HeightResource, 2048);
    MagickLib::SetMagickResourceLimit(MagickLib::PixelsResource,
                                      MagickLib::GetMagickResourceLimit(MagickLib::WidthResource)*
                                      MagickLib::GetMagickResourceLimit(MagickLib::HeightResource));
    MagickLib::SetMagickResourceLimit(MagickLib::DiskResource, 0);
    MagickLib::SetMagickResourceLimit(MagickLib::ReadResource, 900000);
    MagickLib::SetMagickResourceLimit(MagickLib::WriteResource, 1118720);
    MagickLib::SetMagickResourceLimit(MagickLib::ImagesResource, 1024);
  }
};

// Static initializer so this code is run once at startup.
MagickState kMagickState;

#endif
