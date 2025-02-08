/*
% Copyright (C) 2003-2025 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                    M   M   AAA    GGGG  IIIII   CCCC                        %
%                    MM MM  A   A  G        I    C                            %
%                    M M M  AAAAA  G GGG    I    C                            %
%                    M   M  A   A  G   G    I    C                            %
%                    M   M  A   A   GGGG  IIIII   CCCC                        %
%                                                                             %
%                                                                             %
%                    GraphicsMagick Image Magic Methods                       %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                              Bob Friesenhahn                                %
%                                 July 2000                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/magic.h"
#include "magick/utility.h"

/*
  Define declarations.
*/

/*
  Static declarations.
*/
static const struct
{
  const char
    name[10];

  const unsigned char
    * const magic;

  const char
    * description;

  unsigned short
    name_size,
    description_size,
    length,
    offset;
}
StaticMagic[] =
{
#define MAGIC(name,description,offset,magic) {name,(const unsigned char * const)magic,description,sizeof(name)-1,sizeof(description)-1,sizeof(magic)-1,offset}
  MAGIC("WEBP", "WebP Image Format", 8, "WEBP"),
  MAGIC("AVIF", "HEIF AV1 image", 4, "ftypavif"),
  MAGIC("AVIF", "HEIF AV1 image sequence", 4, "ftypavis"),
  /* MAGIC("AVI", "", 0, "RIFF"), */
  MAGIC("8BIMWTEXT", "Photoshop resource wide text format", 0, "8\000B\000I\000M\000#"),
  MAGIC("8BIMTEXT", "Photoshop resource text format", 0, "8BIM#"),
  MAGIC("8BIM", "Photoshop resource format", 0, "8BIM"),
  MAGIC("BMP", "BMP (OS/2 struct bitmap array)", 0, "BA"),
  MAGIC("BMP", "BMP (Windows 3.1x, 95, NT, ...)", 0, "BM"),
  MAGIC("BMP", "BMP (OS/2 struct color icon)", 0, "CI"),
  MAGIC("BMP", "BMP (OS/2 const color pointer)", 0, "CP"),
  MAGIC("BMP", "BMP (OS/2 struct icon)", 0, "IC"),
  MAGIC("BMP", "BMP (OS/2 pointer)", 0, "PI"),
  MAGIC("CALS", "CALS (MIL-STD-1840) Type 1 image", 21, "version: MIL-STD-1840"),
  MAGIC("CALS", "CALS (MIL-STD-1840) Type 1 image", 0, "srcdocid:"),
  MAGIC("CALS", "CALS (MIL-STD-1840) Type 1 image", 9, "srcdocid:"),
  MAGIC("CALS", "CALS (MIL-STD-1840) Type 1 image", 8, "rorient:"),
  MAGIC("CGM", "Computer Graphics Metaformat", 0, "BEGMF"),
  MAGIC("CIN", "Kodak Cineon Image File", 0, "\200\052\137\327"),
  MAGIC("DCM", "DICOM medical image", 128, "DICM"),
  MAGIC("DCX", "ZSoft IBM PC multi-page Paintbrush", 0, "\261\150\336\72"),
  MAGIC("DIB", "Microsoft DIB", 0, "\050\000"),
  MAGIC("DOT", "Graphviz DOT", 0, "digraph"),
  MAGIC("DPX", "SMPTE 268M-2003 (DPX 2.0) (BE)", 0, "SDPX"),
  MAGIC("DPX", "SMPTE 268M-2003 (DPX 2.0) (LE)", 0, "XPDS"),
  MAGIC("EMF", "Microsoft EMF", 40, "\040\105\115\106\000\000\001\000"),
  MAGIC("EPT", "Adobe Encapsulated PostScript (with preview)", 0, "\305\320\323\306"),
  MAGIC("FAX", "Group 3 FAX", 0, "DFAX"),
  MAGIC("FIG", "Xfig", 0, "#FIG"),
  MAGIC("FITS", "Flexible Image Transport System", 0, "IT0"),
  MAGIC("FITS", "Flexible Image Transport System", 0, "SIMPLE"),
  MAGIC("FPX", "FlashPIX", 0, "\320\317\021\340"),
  MAGIC("GIF", "CompuServe graphics interchange format", 0, "GIF8"),
  MAGIC("HEIC", "HEIF - A regular heif image", 4, "ftypheic"),
  MAGIC("HEIC", "HEIF - Extended range (>8 bit) image", 4, "ftypheix"),
  MAGIC("HEIF", "HEIF - Image sequence", 4, "ftyphevc"),
  MAGIC("HEIF", "HEIF - Image sequence", 4, "ftypheim"),
  MAGIC("HEIF", "HEIF - Scalable image", 4, "ftypheis"),
  MAGIC("HEIF", "HEIF - Multiview sequence", 4, "ftyphevm"),
  MAGIC("HEIF", "HEIF - Scalable sequence", 4, "ftyphevs"),
  MAGIC("HEIC", "HEIF - Nokia alpha image", 4, "ftypmif1"),
  MAGIC("HEIC", "HEIF - Nokia animation image", 4, "ftypmsf1"),
  /* MAGIC("HDF", "Heirarchical Data Format", 1, "HDF"), */
  MAGIC("HPGL", "HP Graphics Language", 0, "IN;"),
  MAGIC("HTML", "Hypertext Markup Language", 1, "HTML"),
  MAGIC("HTML", "Hypertext Markup Language", 1, "html"),
  MAGIC("ILBM", "", 8, "ILBM"),
  MAGIC("IPTCWTEXT", "IPTC Newsphoto wide text format", 0, "\062\000#\000\060\000=\000\042\000&\000#\000\060\000;\000&\000#\000\062\000;\000\042\000"),
  MAGIC("IPTCTEXT", "IPTC Newsphoto text format", 0, "2#0=\042&#0;&#2;\042"),
  MAGIC("IPTC", "IPTC Newsphoto", 0, "\034\002"),
  MAGIC("JNG", "JPEG Network Graphics", 0, "\213JNG\r\n\032\n"),
  MAGIC("JPEG", "Joint Photographic Experts Group JFIF", 0, "\377\330\377"),
  MAGIC("JPC", "JPEG-2000 Code Stream Syntax", 0, "\377\117"),
  MAGIC("JP2", "JPEG-2000 JP2 File Format", 4, "\152\120\040\040\015"),
  MAGIC("JXL", "JPEG XL Image Format", 0, "\xff\x0a"),
  MAGIC("JXL", "JPEG XL Image Format", 0, "\x00\x00\x00\x0c\x4a\x58\x4c\x20\x0d\x0a\x87\x0a"),
  MAGIC("MAT", "MATLAB Level 4.0-7.0 image format", 0, "MATLAB 5.0 MAT-file,"),
  MAGIC("MIFF", "Magick Image File Format", 0, "Id=ImageMagick"),
  MAGIC("MIFF", "Magick Image File Format", 0, "id=ImageMagick"),
  MAGIC("MNG", "Multiple-image Network Graphics", 0, "\212MNG\r\n\032\n"),
  MAGIC("MPC", "Magick Persistent Cache image", 0, "id=MagickCache"),
  MAGIC("MPEG", "MPEG Video Stream", 0, "\000\000\001\263"),
  MAGIC("PCD", "Adobe Photo CD", 2048, "PCD_"),
  MAGIC("PCL", "HP Page Control Language", 0, "\033E\033"),
  MAGIC("PCX", "ZSoft IBM PC Paintbrush", 0, "\012\002"),
  MAGIC("PCX", "ZSoft IBM PC Paintbrush", 0, "\012\005"),
  MAGIC("PDB", "Palm Database ImageViewer Format", 60, "vIMGView"),
  MAGIC("PDF", "Portable Document Format", 0, "%PDF-"),
  MAGIC("PFA", "Postscript Type 1 font (ASCII)", 0, "%!PS-AdobeFont-1.0"),
  MAGIC("PFB", "Postscript Type 1 font (binary)", 6, "%!PS-AdobeFont-1.0"),
  MAGIC("PGX", "JPEG-2000 VM Format (ML)", 0, "PG ML"),
  MAGIC("PGX", "JPEG-2000 VM Format (LM)", 0, "PG LM"),
  MAGIC("PICT", "Apple Macintosh QuickDraw/PICT", 522, "\000\021\002\377\014\000"),
  MAGIC("PNG", "Portable Network Graphics", 0, "\211PNG\r\n\032\n"),
  MAGIC("PBM", "Portable bitmap file format (text)", 0, "P1"),
  MAGIC("PGM", "Portable graymap file format (text)", 0, "P2"),
  MAGIC("PPM", "Portable pixmap file format (text)", 0, "P3"),
  MAGIC("PBM", "Portable bitmap file format (binary)", 0, "P4"),
  MAGIC("PGM", "Portable graymap file format (binary)", 0, "P5"),
  MAGIC("PPM", "Portable pixmap file format (binary)", 0, "P6"),
  MAGIC("P7", "XV Thumbnail (P7 332)", 0, "P7 332"), /* XV Thumbnail */
  MAGIC("PAM", "XV Thumbnail (P7)", 0, "P7"), /* Should be listed after "P7 332" */
  MAGIC("PS", "Adobe Encapsulated Postscript 3.0", 0, "%!PS-Adobe-3.0 EPSF-3.0"),
  MAGIC("PS", "Adobe Encapsulated Postscript 2.1", 0, "%!PS-Adobe-3.0 EPSF-2.1"),
  MAGIC("PS", "Adobe Encapsulated Postscript 2.0", 0, "%!PS-Adobe-2.0 EPSF-2.0"),
  MAGIC("PS", "Adobe Encapsulated Postscript 1.2", 0, "%!PS-Adobe-2.0 EPSF-1.2"),
  MAGIC("PS", "Adobe Postscript 3.0", 0, "%!PS-Adobe-3.0"),
  MAGIC("PS", "Adobe Postscript 2.0", 0, "%!PS-Adobe-2.0"),
  MAGIC("PS", "Adobe Postscript 2.1", 0, "%!PS-Adobe-2.1"),
  MAGIC("PS", "Adobe Postscript 1.0", 0, "%!PS-Adobe-1.0"),
  MAGIC("PS", "Adobe Postscript", 0, "%!"), /* Generic */
  MAGIC("PS", "Adobe Postscript", 0, "\004%!"), /* EOT character.  Maybe used when printing. */
  MAGIC("PS", "Adobe Encapsulated PostScript Interchange (EPT)", 0, "\305\320\323\306"), /* aka EPT */
  MAGIC("PSD", "Photoshop PSD", 0, "8BPS"),
  MAGIC("PWP", "Seattle Film Works", 0, "SFW95"),
  MAGIC("RAD", "Radiance", 0, "#?RADIANCE"),
  MAGIC("RAD", "Radiance", 0, "VIEW= "),
  MAGIC("RLE", "Utah Run length encoded image", 0, "\122\314"),
  MAGIC("SCT", "Scitex HandShake", 0, "CT"),
  MAGIC("SFW", "Seattle Film Work", 0, "SFW94"),
  MAGIC("SGI", "Irix RGB image", 0, "\001\332"),
  MAGIC("SUN", "SUN Rasterfile", 0, "\131\246\152\225"),
  MAGIC("SVG", "Scalable Vector Graphics", 1, "?XML"),
  MAGIC("SVG", "Scalable Vector Graphics", 1, "?xml"),
  MAGIC("TIFF", "Tagged Image File Format (BE Classic)", 0, "\115\115\000\052"),
  MAGIC("TIFF", "Tagged Image File Format (LE Classic)", 0, "\111\111\052\000"),
  MAGIC("TOPOL", "TopoL X Image", 0, "                    "),
  MAGIC("BIGTIFF", "Tagged Image File Format (BE Big)", 0, "\115\115\000\053\000\010\000\000"),
  MAGIC("BIGTIFF", "Tagged Image File Format (LE Big)", 0, "\111\111\053\000\010\000\000\000"),
  MAGIC("VICAR", "VICAR rasterfile format (LBLSIZE)", 0, "LBLSIZE"),
  MAGIC("VICAR", "VICAR rasterfile format (NJPL1I)", 0, "NJPL1I"),
  MAGIC("VIFF","Khoros Visualization image",  0, "\253\001"),
  MAGIC("WMF", "Windows Meta File", 0, "\327\315\306\232"),
  MAGIC("WMF", "Windows Meta File", 0, "\001\000\011\000"),
  MAGIC("WPG", "Word Perfect Graphics", 0, "\377WPC"),
  MAGIC("XBM", "X Windows system bitmap", 0, "#define"),
  MAGIC("XCF", "GIMP XCF", 0, "gimp xcf"),
  MAGIC("XPM", "X Windows system pixmap", 1, "* XPM *"),
  MAGIC("XWD", "X Windows system window dump", 4, "\007\000\000"),
  MAGIC("XWD", "X Windows system window dump", 5, "\000\000\007")
};

/*
  Forward declarations.
*/

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   D e s t r o y M a g i c I n f o                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method DestroyMagicInfo deallocates memory associated with the magic list.
%
%  The format of the DestroyMagicInfo method is:
%
%      DestroyMagicInfo(void)
%
%
*/
MagickExport void
DestroyMagicInfo(void)
{
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t M a g i c k F i l e F o r m a t                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method GetMagickFileFormat inspects the provided image file/blob header
%  bytes and sets/updates the provided file format string buffer. The value
%  MagickPass is returned if the format was successfully identified.  The
%  value MagickFail is returned if the format was not identified or an
%  exception occurred.
%
%
%  The format of the GetMagickFileFormat method is:
%
%      MagickPassFail GetMagickFileFormat(
%        const unsigned char *header, const size_t header_length,
%        char *postulate, const size_t postulate_length,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o header: A binary string representing the first several
%        thousand bytes of the file/blob header to test.
%
%    o header_length: The length of the binary signature.  Currently
%        2*MaxTextExtent (4106 bytes).
%
%    o format: Format buffer. Updated with actual format if it can be
%        determined.
%
%    o format_length: Format buffer length.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport MagickPassFail
GetMagickFileFormat(const unsigned char *header, const size_t header_length,
                    char *format, const size_t format_length,
                    ExceptionInfo *exception)
{
  register unsigned int
    i;

  MagickPassFail
    status=MagickFail;

  ARG_NOT_USED(exception);

  if (!((header == (const unsigned char *) NULL) || (header_length == 0) ||
        (format_length < 2)))
    {
      /*
        Search for requested magic.
      */
      for (i=0; i < ArraySize(StaticMagic); i++)
        {
          if ((size_t) StaticMagic[i].offset+StaticMagic[i].length <= header_length)
            {
              if ((header[StaticMagic[i].offset] == StaticMagic[i].magic[0]) &&
                  (memcmp(header+StaticMagic[i].offset,StaticMagic[i].magic,
                          StaticMagic[i].length) == 0))
                {
                  if (strlcpy(format,StaticMagic[i].name,format_length) < format_length)
                    {
                      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                            "Magick: %s (\"%s\")",
                                            StaticMagic[i].name,
                                            StaticMagic[i].description);
                      status=MagickPass;
                    }
                  break;
                }
            }
        }
    }
  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   I n i t i a l i z e M a g i c I n f o                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method InitializeMagicInfo initializes the file header magic detection
%  facility.
%
%  The format of the InitializeMagicInfo method is:
%
%      MagickPassFail InitializeMagicInfo(void)
%
%
*/
MagickExport MagickPassFail
InitializeMagicInfo(void)
{
  return MagickPass;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  L i s t M a g i c I n f o                                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ListMagicInfo lists the magic info to a file.
%
%  The format of the ListMagicInfo method is:
%
%      unsigned int ListMagicInfo(FILE *file,ExceptionInfo *exception)
%
%  A description of each parameter follows.
%
%    o file:  An pointer to a FILE.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
MagickExport MagickPassFail
ListMagicInfo(FILE *file,ExceptionInfo *exception)
{
#define NAME_HEADER "Name"
#define DESCRIPTION_HEADER "Description"
#define OFFSET_HEADER "Offset"
#define TARGET_HEADER "Target"
#define OFFSET_TARGET_HEADER "Offset Target"

  const size_t
    description_size=sizeof(DESCRIPTION_HEADER)-1,
    name_size=sizeof(NAME_HEADER)-1,
    offset_size=sizeof(OFFSET_HEADER)-1,
    target_size=sizeof(TARGET_HEADER)-1;

  size_t
    description_size_max=description_size,
    name_size_max=name_size,
    offset_size_max=offset_size,
    target_size_max=Max(target_size,16);

  register unsigned int
    i,
    j;

  for (i=0; i < ArraySize(StaticMagic); i++)
    {
      if (description_size_max < StaticMagic[i].description_size)
        description_size_max = StaticMagic[i].description_size;
      if (name_size_max < StaticMagic[i].name_size)
        name_size_max = StaticMagic[i].name_size;
      /* The following does not account for control code expansion */
      if (target_size_max < StaticMagic[i].length)
        target_size_max = StaticMagic[i].length;
    }

  ARG_NOT_USED(exception);

  if (file == (const FILE *) NULL)
    file=stdout;

  (void) fprintf(file,"%s",NAME_HEADER);
  for (j=name_size; j <= name_size_max; j++)
    (void) fprintf(file," ");

  (void) fprintf(file,"%s",DESCRIPTION_HEADER);
  for (j=description_size; j <= description_size_max; j++)
    (void) fprintf(file," ");

  (void) fprintf(file,"%s",OFFSET_HEADER);
  for (j=offset_size; j <= offset_size_max; j++)
    (void) fprintf(file," ");

  (void) fprintf(file,"%s",TARGET_HEADER);
  for (j=target_size; j <= target_size_max; j++)
    (void) fprintf(file," ");
  (void) fprintf(file,"\n");

  for (j=0; j <= (name_size_max+1+description_size_max+1+offset_size_max+1+target_size_max+1); j++)
    (void) fprintf(file,"-");
  (void) fprintf(file,"\n");

  for (i=0; i < ArraySize(StaticMagic); i++)
    {
      register const unsigned char
        *c;

      (void) fprintf(file,"%.*s",(int) name_size_max,StaticMagic[i].name);
      for (j= (unsigned int) strlen(StaticMagic[i].name); j <= name_size_max; j++)
        (void) fprintf(file," ");
      (void) fprintf(file,"%.*s",(int) description_size_max,StaticMagic[i].description);
      for (j= (unsigned int) strlen(StaticMagic[i].description); j <= description_size_max; j++)
        (void) fprintf(file," ");
      (void) fprintf(file,"%6u ",StaticMagic[i].offset);

      (void) fprintf(file,"\"");
      c=StaticMagic[i].magic;
      for (j=0; j < StaticMagic[i].length; j++)
        {
          /*          else if ('\b' == c[j]) */
          /*            (void) fprintf(file,"\\b"); */
          /*          else if ('\f' == c[j]) */
          /*            (void) fprintf(file,"\\f"); */
          if ('\n' == c[j])
            (void) fprintf(file,"\\n");
          else if ('\r' == c[j])
            (void) fprintf(file,"\\r");
          else if ('\t' == c[j])
            (void) fprintf(file,"\\t");
          /*          else if ('\v' == c[j]) */
          /*            (void) fprintf(file,"\\v"); */
          /*          else if ('\a' == c[j]) */
          /*            (void) fprintf(file,"\\a"); */
          else if ('\\' == c[j])
            (void) fprintf(file,"\\");
          else if ('\?' == c[j])
            (void) fprintf(file,"\\?");
          else if ('"' == c[j])
            (void) fprintf(file,"\\\"");
          else if (isprint((int) c[j]))
            (void) fprintf(file,"%c",(int) c[j]);
          else
            {
              (void) fprintf(file,"\\%03o",c[j]);
            }
        }
      (void) fprintf(file,"\"\n");
    }
  (void) fflush(file);
  return(MagickPass);
}
