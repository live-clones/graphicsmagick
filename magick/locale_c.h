#ifndef _LOCAL_C_H
#define _LOCAL_C_H

extern MagickExport const char *GetLocaleMessageFromID(const int) MAGICK_FUNC_CONST;

#define MAX_LOCALE_MSGS 615

#define MGK_BlobErrorUnableToCreateBlob 1
#define MGK_BlobErrorUnableToDeduceImageFormat 2
#define MGK_BlobErrorUnableToObtainOffset 3
#define MGK_BlobErrorUnableToOpenFile 4
#define MGK_BlobErrorUnableToReadFile 5
#define MGK_BlobErrorUnableToReadToOffset 6
#define MGK_BlobErrorUnableToSeekToOffset 7
#define MGK_BlobErrorUnableToWriteBlob 8
#define MGK_BlobErrorUnrecognizedImageFormat 9
#define MGK_BlobFatalErrorDefault 10
#define MGK_BlobWarningDefault 11
#define MGK_CacheErrorEmptyCacheNexus 12
#define MGK_CacheErrorInconsistentPersistentCacheDepth 13
#define MGK_CacheErrorPixelCacheDimensionsMisMatch 14
#define MGK_CacheErrorPixelCacheIsNotOpen 15
#define MGK_CacheErrorUnableToAllocateCacheView 16
#define MGK_CacheErrorUnableToCloneCache 17
#define MGK_CacheErrorUnableToExtendCache 18
#define MGK_CacheErrorUnableToGetCacheNexus 19
#define MGK_CacheErrorUnableToGetPixelsFromCache 20
#define MGK_CacheErrorUnableToOpenCache 21
#define MGK_CacheErrorUnableToPeristPixelCache 22
#define MGK_CacheErrorUnableToReadPixelCache 23
#define MGK_CacheErrorUnableToSyncCache 24
#define MGK_CacheFatalErrorDiskAllocationFailed 25
#define MGK_CacheFatalErrorUnableToExtendPixelCache 26
#define MGK_CacheWarningDefault 27
#define MGK_CoderErrorArithmeticOverflow 28
#define MGK_CoderErrorColormapTooLarge 29
#define MGK_CoderErrorColormapTypeNotSupported 30
#define MGK_CoderErrorColorspaceModelIsNotSupported 31
#define MGK_CoderErrorColorTypeNotSupported 32
#define MGK_CoderErrorCompressionNotValid 33
#define MGK_CoderErrorDataEncodingSchemeIsNotSupported 34
#define MGK_CoderErrorDataStorageTypeIsNotSupported 35
#define MGK_CoderErrorDecodedImageNotReturned 36
#define MGK_CoderErrorDeltaPNGNotSupported 37
#define MGK_CoderErrorDivisionByZero 38
#define MGK_CoderErrorEncryptedWPGImageFileNotSupported 39
#define MGK_CoderErrorFractalCompressionNotSupported 40
#define MGK_CoderErrorImageColumnOrRowSizeIsNotSupported 41
#define MGK_CoderErrorImageDoesNotHaveAMatteChannel 42
#define MGK_CoderErrorImageIsNotTiled 43
#define MGK_CoderErrorImageTypeNotSupported 44
#define MGK_CoderErrorIncompatibleSizeOfDouble 45
#define MGK_CoderErrorIrregularChannelGeometryNotSupported 46
#define MGK_CoderErrorJNGCompressionNotSupported 47
#define MGK_CoderErrorJPEGCompressionNotSupported 48
#define MGK_CoderErrorJPEGEmbeddingFailed 49
#define MGK_CoderErrorJXLDecoderAPIFailure 50
#define MGK_CoderErrorJXLEncoderAPIFailure 51
#define MGK_CoderErrorLocationTypeIsNotSupported 52
#define MGK_CoderErrorMapStorageTypeIsNotSupported 53
#define MGK_CoderErrorMSBByteOrderNotSupported 54
#define MGK_CoderErrorMultidimensionalMatricesAreNotSupported 55
#define MGK_CoderErrorMultipleRecordListNotSupported 56
#define MGK_CoderErrorNo8BIMDataIsAvailable 57
#define MGK_CoderErrorNoAPP1DataIsAvailable 58
#define MGK_CoderErrorNoBitmapOnClipboard 59
#define MGK_CoderErrorNoColorProfileAvailable 60
#define MGK_CoderErrorNoDataReturned 61
#define MGK_CoderErrorNoImageVectorGraphics 62
#define MGK_CoderErrorNoIPTCInfoWasFound 63
#define MGK_CoderErrorNoIPTCProfileAvailable 64
#define MGK_CoderErrorNumberOfImagesIsNotSupported 65
#define MGK_CoderErrorOnlyContinuousTonePictureSupported 66
#define MGK_CoderErrorOnlyLevelZerofilesSupported 67
#define MGK_CoderErrorPNGCompressionNotSupported 68
#define MGK_CoderErrorPNGLibraryTooOld 69
#define MGK_CoderErrorRLECompressionNotSupported 70
#define MGK_CoderErrorSubsamplingRequiresEvenWidth 71
#define MGK_CoderErrorUnableToCopyProfile 72
#define MGK_CoderErrorUnableToCreateADC 73
#define MGK_CoderErrorUnableToCreateBitmap 74
#define MGK_CoderErrorUnableToDecodeImage 75
#define MGK_CoderErrorUnableToDecompressImage 76
#define MGK_CoderErrorUnableToGetImageCharacteristics 77
#define MGK_CoderErrorUnableToInitializeFPXLibrary 78
#define MGK_CoderErrorUnableToOpenBlob 79
#define MGK_CoderErrorUnableToOpenFile 80
#define MGK_CoderErrorUnableToReadAspectRatio 81
#define MGK_CoderErrorUnableToReadCIELABImages 82
#define MGK_CoderErrorUnableToReadSummaryInfo 83
#define MGK_CoderErrorUnableToResizeImage 84
#define MGK_CoderErrorUnableToSetAffineMatrix 85
#define MGK_CoderErrorUnableToSetAspectRatio 86
#define MGK_CoderErrorUnableToSetColorTwist 87
#define MGK_CoderErrorUnableToSetContrast 88
#define MGK_CoderErrorUnableToSetFilteringValue 89
#define MGK_CoderErrorUnableToSetImageComments 90
#define MGK_CoderErrorUnableToSetImageOpacity 91
#define MGK_CoderErrorUnableToSetImageTitle 92
#define MGK_CoderErrorUnableToSetImageType 93
#define MGK_CoderErrorUnableToSetJPEGLevel 94
#define MGK_CoderErrorUnableToSetRegionOfInterest 95
#define MGK_CoderErrorUnableToSetSummaryInfo 96
#define MGK_CoderErrorUnableToTransformColorspace 97
#define MGK_CoderErrorUnableToTranslateText 98
#define MGK_CoderErrorUnableToWriteMPEGParameters 99
#define MGK_CoderErrorUnableToWriteTemporaryFile 100
#define MGK_CoderErrorUnableToZipCompressImage 101
#define MGK_CoderErrorUnsupportedBitsPerSample 102
#define MGK_CoderErrorUnsupportedCellTypeInTheMatrix 103
#define MGK_CoderErrorUnsupportedNumberOfColumns 104
#define MGK_CoderErrorUnsupportedNumberOfRows 105
#define MGK_CoderErrorUnsupportedSamplesPerPixel 106
#define MGK_CoderErrorWebPDecodingFailedUserAbort 107
#define MGK_CoderErrorWebPEncodingFailed 108
#define MGK_CoderErrorWebPEncodingFailedBadDimension 109
#define MGK_CoderErrorWebPEncodingFailedBadWrite 110
#define MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory 111
#define MGK_CoderErrorWebPEncodingFailedFileTooBig 112
#define MGK_CoderErrorWebPEncodingFailedInvalidConfiguration 113
#define MGK_CoderErrorWebPEncodingFailedNULLParameter 114
#define MGK_CoderErrorWebPEncodingFailedOutOfMemory 115
#define MGK_CoderErrorWebPEncodingFailedPartition0Overflow 116
#define MGK_CoderErrorWebPEncodingFailedPartitionOverflow 117
#define MGK_CoderErrorWebPEncodingFailedUserAbort 118
#define MGK_CoderErrorWebPInvalidConfiguration 119
#define MGK_CoderErrorWebPInvalidParameter 120
#define MGK_CoderErrorXMLParserFailure 121
#define MGK_CoderErrorZipCompressionNotSupported 122
#define MGK_CoderFatalErrorDefault 123
#define MGK_CoderWarningLosslessToLossyJPEGConversion 124
#define MGK_ConfigureErrorIncludeElementNestedTooDeeply 125
#define MGK_ConfigureErrorRegistryKeyLookupFailed 126
#define MGK_ConfigureErrorStringTokenLengthExceeded 127
#define MGK_ConfigureErrorUnableToAccessConfigureFile 128
#define MGK_ConfigureErrorUnableToAccessFontFile 129
#define MGK_ConfigureErrorUnableToAccessLogFile 130
#define MGK_ConfigureErrorUnableToAccessModuleFile 131
#define MGK_ConfigureFatalErrorDefault 132
#define MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory 133
#define MGK_ConfigureFatalErrorUnableToGetCurrentDirectory 134
#define MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory 135
#define MGK_ConfigureWarningDefault 136
#define MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile 137
#define MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile 138
#define MGK_CorruptImageErrorColormapExceedsColorsLimit 139
#define MGK_CorruptImageErrorCompressionNotValid 140
#define MGK_CorruptImageErrorCorruptImage 141
#define MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData 142
#define MGK_CorruptImageErrorImageFileHasNoScenes 143
#define MGK_CorruptImageErrorImageTypeNotSupported 144
#define MGK_CorruptImageErrorImproperImageHeader 145
#define MGK_CorruptImageErrorInsufficientImageDataInFile 146
#define MGK_CorruptImageErrorInvalidColormapIndex 147
#define MGK_CorruptImageErrorInvalidFileFormatVersion 148
#define MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch 149
#define MGK_CorruptImageErrorMissingImageChannel 150
#define MGK_CorruptImageErrorNegativeOrZeroImageSize 151
#define MGK_CorruptImageErrorNonOS2HeaderSizeError 152
#define MGK_CorruptImageErrorNotEnoughTiles 153
#define MGK_CorruptImageErrorRecursionDetected 154
#define MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne 155
#define MGK_CorruptImageErrorSubsamplingRequiresEvenWidth 156
#define MGK_CorruptImageErrorTooMuchImageDataInFile 157
#define MGK_CorruptImageErrorUnableToReadColormapFromDumpFile 158
#define MGK_CorruptImageErrorUnableToReadColorProfile 159
#define MGK_CorruptImageErrorUnableToReadExtensionBlock 160
#define MGK_CorruptImageErrorUnableToReadGenericProfile 161
#define MGK_CorruptImageErrorUnableToReadImageData 162
#define MGK_CorruptImageErrorUnableToReadImageHeader 163
#define MGK_CorruptImageErrorUnableToReadIPTCProfile 164
#define MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile 165
#define MGK_CorruptImageErrorUnableToReadSubImageData 166
#define MGK_CorruptImageErrorUnableToReadVIDImage 167
#define MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile 168
#define MGK_CorruptImageErrorUnableToRunlengthDecodeImage 169
#define MGK_CorruptImageErrorUnableToUncompressImage 170
#define MGK_CorruptImageErrorUnexpectedEndOfFile 171
#define MGK_CorruptImageErrorUnexpectedSamplingFactor 172
#define MGK_CorruptImageErrorUnknownPatternType 173
#define MGK_CorruptImageErrorUnrecognizedBitsPerPixel 174
#define MGK_CorruptImageErrorUnrecognizedImageCompression 175
#define MGK_CorruptImageErrorUnrecognizedNumberOfColors 176
#define MGK_CorruptImageErrorUnrecognizedXWDHeader 177
#define MGK_CorruptImageErrorUnsupportedBitsPerSample 178
#define MGK_CorruptImageErrorUnsupportedNumberOfPlanes 179
#define MGK_CorruptImageFatalErrorUnableToPersistKey 180
#define MGK_CorruptImageWarningCompressionNotValid 181
#define MGK_CorruptImageWarningCorruptImage 182
#define MGK_CorruptImageWarningImproperImageHeader 183
#define MGK_CorruptImageWarningInvalidColormapIndex 184
#define MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch 185
#define MGK_CorruptImageWarningNegativeOrZeroImageSize 186
#define MGK_CorruptImageWarningNonOS2HeaderSizeError 187
#define MGK_CorruptImageWarningSkipToSyncByte 188
#define MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne 189
#define MGK_CorruptImageWarningUnableToParseEmbeddedProfile 190
#define MGK_CorruptImageWarningUnrecognizedBitsPerPixel 191
#define MGK_CorruptImageWarningUnrecognizedImageCompression 192
#define MGK_DelegateErrorDelegateFailed 193
#define MGK_DelegateErrorFailedToAllocateArgumentList 194
#define MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter 195
#define MGK_DelegateErrorFailedToComputeOutputSize 196
#define MGK_DelegateErrorFailedToFindGhostscript 197
#define MGK_DelegateErrorFailedToRenderFile 198
#define MGK_DelegateErrorFailedToScanFile 199
#define MGK_DelegateErrorNoTagFound 200
#define MGK_DelegateErrorPostscriptDelegateFailed 201
#define MGK_DelegateErrorUnableToCreateImage 202
#define MGK_DelegateErrorUnableToCreateImageComponent 203
#define MGK_DelegateErrorUnableToDecodeImageFile 204
#define MGK_DelegateErrorUnableToEncodeImageFile 205
#define MGK_DelegateErrorUnableToInitializeFPXLibrary 206
#define MGK_DelegateErrorUnableToInitializeWMFLibrary 207
#define MGK_DelegateErrorUnableToManageJP2Stream 208
#define MGK_DelegateErrorUnableToWriteSVGFormat 209
#define MGK_DelegateErrorWebPABIMismatch 210
#define MGK_DelegateFatalErrorDefault 211
#define MGK_DelegateWarningDefault 212
#define MGK_DrawErrorAlreadyPushingPatternDefinition 213
#define MGK_DrawErrorArithmeticOverflow 214
#define MGK_DrawErrorDrawingRecursionDetected 215
#define MGK_DrawErrorFloatValueConversionError 216
#define MGK_DrawErrorIntegerValueConversionError 217
#define MGK_DrawErrorInvalidAttributeArgument 218
#define MGK_DrawErrorInvalidClassName 219
#define MGK_DrawErrorInvalidElementIdentifier 220
#define MGK_DrawErrorInvalidPrimitiveArgument 221
#define MGK_DrawErrorNonconformingDrawingPrimitiveDefinition 222
#define MGK_DrawErrorPrimitiveArithmeticOverflow 223
#define MGK_DrawErrorTextStringTruncation 224
#define MGK_DrawErrorTooManyCoordinates 225
#define MGK_DrawErrorUnableToDrawOnImage 226
#define MGK_DrawErrorUnableToFloodFillImageDueToClipMask 227
#define MGK_DrawErrorUnableToPrint 228
#define MGK_DrawErrorUnbalancedGraphicContextPushPop 229
#define MGK_DrawErrorUnbalancedPushPop 230
#define MGK_DrawErrorUnreasonableAffineMatrix 231
#define MGK_DrawErrorUnreasonableDashPolygonLength 232
#define MGK_DrawErrorUnreasonableGradientSize 233
#define MGK_DrawErrorVectorPathTruncated 234
#define MGK_DrawFatalErrorDefault 235
#define MGK_DrawWarningFuzzingBuildUnsafeForProduction 236
#define MGK_DrawWarningNotARelativeURL 237
#define MGK_DrawWarningNotCurrentlyPushingPatternDefinition 238
#define MGK_DrawWarningURLNotFound 239
#define MGK_FileOpenErrorUnableToCreateTemporaryFile 240
#define MGK_FileOpenErrorUnableToOpenFile 241
#define MGK_FileOpenErrorUnableToWriteFile 242
#define MGK_FileOpenFatalErrorDefault 243
#define MGK_FileOpenWarningDefault 244
#define MGK_ImageErrorAngleIsDiscontinuous 245
#define MGK_ImageErrorCMYKAImageLacksAlphaChannel 246
#define MGK_ImageErrorColorspaceColorProfileMismatch 247
#define MGK_ImageErrorImageColorspaceDiffers 248
#define MGK_ImageErrorImageColorspaceMismatch 249
#define MGK_ImageErrorImageDifferenceExceedsLimit 250
#define MGK_ImageErrorImageDoesNotContainResolution 251
#define MGK_ImageErrorImageIsNotColormapped 252
#define MGK_ImageErrorImageOpacityDiffers 253
#define MGK_ImageErrorImageSequenceIsRequired 254
#define MGK_ImageErrorImageSizeDiffers 255
#define MGK_ImageErrorInvalidColormapIndex 256
#define MGK_ImageErrorLeftAndRightImageSizesDiffer 257
#define MGK_ImageErrorNoImagesWereFound 258
#define MGK_ImageErrorNoImagesWereLoaded 259
#define MGK_ImageErrorNoLocaleImageAttribute 260
#define MGK_ImageErrorTooManyClusters 261
#define MGK_ImageErrorUnableToAppendImage 262
#define MGK_ImageErrorUnableToAssignProfile 263
#define MGK_ImageErrorUnableToAverageImage 264
#define MGK_ImageErrorUnableToCoalesceImage 265
#define MGK_ImageErrorUnableToCompareImages 266
#define MGK_ImageErrorUnableToCreateImageMosaic 267
#define MGK_ImageErrorUnableToCreateStereoImage 268
#define MGK_ImageErrorUnableToDeconstructImageSequence 269
#define MGK_ImageErrorUnableToExportImagePixels 270
#define MGK_ImageErrorUnableToFlattenImage 271
#define MGK_ImageErrorUnableToGetClipMask 272
#define MGK_ImageErrorUnableToGetCompositeMask 273
#define MGK_ImageErrorUnableToHandleImageChannel 274
#define MGK_ImageErrorUnableToImportImagePixels 275
#define MGK_ImageErrorUnableToResizeImage 276
#define MGK_ImageErrorUnableToSegmentImage 277
#define MGK_ImageErrorUnableToSetClipMask 278
#define MGK_ImageErrorUnableToSetCompositeMask 279
#define MGK_ImageErrorUnableToShearImage 280
#define MGK_ImageErrorWidthOrHeightExceedsLimit 281
#define MGK_ImageFatalErrorUnableToPersistKey 282
#define MGK_ImageWarningDefault 283
#define MGK_MissingDelegateErrorFPXLibraryIsNotAvailable 284
#define MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable 285
#define MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable 286
#define MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable 287
#define MGK_MissingDelegateErrorLZWEncodingNotEnabled 288
#define MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat 289
#define MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat 290
#define MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable 291
#define MGK_MissingDelegateErrorXMLLibraryIsNotAvailable 292
#define MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable 293
#define MGK_MissingDelegateErrorZipLibraryIsNotAvailable 294
#define MGK_MissingDelegateFatalErrorDefault 295
#define MGK_MissingDelegateWarningDefault 296
#define MGK_ModuleErrorFailedToCloseModule 297
#define MGK_ModuleErrorFailedToFindSymbol 298
#define MGK_ModuleErrorUnableToLoadModule 299
#define MGK_ModuleErrorUnableToRegisterImageFormat 300
#define MGK_ModuleErrorUnrecognizedModule 301
#define MGK_ModuleFatalErrorUnableToInitializeModuleLoader 302
#define MGK_ModuleWarningDefault 303
#define MGK_MonitorErrorDefault 304
#define MGK_MonitorFatalErrorDefault 305
#define MGK_MonitorFatalErrorUserRequestedTerminationBySignal 306
#define MGK_MonitorWarningDefault 307
#define MGK_OptionErrorBevelWidthIsNegative 308
#define MGK_OptionErrorColorSeparatedImageRequired 309
#define MGK_OptionErrorDisplayGammaIsOutOfRange 310
#define MGK_OptionErrorFilmGammaIsOutOfRange 311
#define MGK_OptionErrorFrameIsLessThanImageSize 312
#define MGK_OptionErrorGeometryDimensionsAreZero 313
#define MGK_OptionErrorGeometryDoesNotContainImage 314
#define MGK_OptionErrorHaldClutImageDimensionsInvalid 315
#define MGK_OptionErrorImagesAreNotTheSameSize 316
#define MGK_OptionErrorImageSizeMustExceedBevelWidth 317
#define MGK_OptionErrorImageSmallerThanKernelWidth 318
#define MGK_OptionErrorImageSmallerThanRadius 319
#define MGK_OptionErrorImageWidthsOrHeightsDiffer 320
#define MGK_OptionErrorInputImagesAlreadySpecified 321
#define MGK_OptionErrorInvalidSubimageSpecification 322
#define MGK_OptionErrorKernelRadiusIsTooSmall 323
#define MGK_OptionErrorKernelWidthMustBeAnOddNumber 324
#define MGK_OptionErrorMatrixIsNotSquare 325
#define MGK_OptionErrorMatrixOrderOutOfRange 326
#define MGK_OptionErrorMissingAnImageFilename 327
#define MGK_OptionErrorMissingArgument 328
#define MGK_OptionErrorMustSpecifyAnImageName 329
#define MGK_OptionErrorMustSpecifyImageSize 330
#define MGK_OptionErrorNoBlobDefined 331
#define MGK_OptionErrorNoImagesDefined 332
#define MGK_OptionErrorNonzeroWidthAndHeightRequired 333
#define MGK_OptionErrorNoProfileNameWasGiven 334
#define MGK_OptionErrorNullBlobArgument 335
#define MGK_OptionErrorReferenceBlackIsOutOfRange 336
#define MGK_OptionErrorReferenceImageRequired 337
#define MGK_OptionErrorReferenceIsNotMyType 338
#define MGK_OptionErrorReferenceWhiteIsOutOfRange 339
#define MGK_OptionErrorRegionAreaExceedsLimit 340
#define MGK_OptionErrorRequestDidNotReturnAnImage 341
#define MGK_OptionErrorSoftClipOffsetIsOutOfRange 342
#define MGK_OptionErrorSteganoImageRequired 343
#define MGK_OptionErrorStereoImageRequired 344
#define MGK_OptionErrorSubimageSpecificationReturnsNoImages 345
#define MGK_OptionErrorTileNotBoundedByImageDimensions 346
#define MGK_OptionErrorUnableToAddOrRemoveProfile 347
#define MGK_OptionErrorUnableToAverageImageSequence 348
#define MGK_OptionErrorUnableToBlurImage 349
#define MGK_OptionErrorUnableToChopImage 350
#define MGK_OptionErrorUnableToCineonLogRGBTransformColorspace 351
#define MGK_OptionErrorUnableToColorMatrixImage 352
#define MGK_OptionErrorUnableToConstituteImage 353
#define MGK_OptionErrorUnableToConvolveImage 354
#define MGK_OptionErrorUnableToEdgeImage 355
#define MGK_OptionErrorUnableToEqualizeImage 356
#define MGK_OptionErrorUnableToFilterImage 357
#define MGK_OptionErrorUnableToFormatImageMetadata 358
#define MGK_OptionErrorUnableToFrameImage 359
#define MGK_OptionErrorUnableToOilPaintImage 360
#define MGK_OptionErrorUnableToPaintImage 361
#define MGK_OptionErrorUnableToRaiseImage 362
#define MGK_OptionErrorUnableToSharpenImage 363
#define MGK_OptionErrorUnableToSpreadImage 364
#define MGK_OptionErrorUnableToThresholdImage 365
#define MGK_OptionErrorUnableToWaveImage 366
#define MGK_OptionErrorUnrecognizedAttribute 367
#define MGK_OptionErrorUnrecognizedChannelType 368
#define MGK_OptionErrorUnrecognizedColor 369
#define MGK_OptionErrorUnrecognizedColormapType 370
#define MGK_OptionErrorUnrecognizedColorspace 371
#define MGK_OptionErrorUnrecognizedCommand 372
#define MGK_OptionErrorUnrecognizedComposeOperator 373
#define MGK_OptionErrorUnrecognizedDisposeMethod 374
#define MGK_OptionErrorUnrecognizedElement 375
#define MGK_OptionErrorUnrecognizedEndianType 376
#define MGK_OptionErrorUnrecognizedGravityType 377
#define MGK_OptionErrorUnrecognizedHighlightStyle 378
#define MGK_OptionErrorUnrecognizedImageCompression 379
#define MGK_OptionErrorUnrecognizedImageFilter 380
#define MGK_OptionErrorUnrecognizedImageFormat 381
#define MGK_OptionErrorUnrecognizedImageMode 382
#define MGK_OptionErrorUnrecognizedImageType 383
#define MGK_OptionErrorUnrecognizedIntentType 384
#define MGK_OptionErrorUnrecognizedInterlaceType 385
#define MGK_OptionErrorUnrecognizedListType 386
#define MGK_OptionErrorUnrecognizedMetric 387
#define MGK_OptionErrorUnrecognizedModeType 388
#define MGK_OptionErrorUnrecognizedNoiseType 389
#define MGK_OptionErrorUnrecognizedOperator 390
#define MGK_OptionErrorUnrecognizedOption 391
#define MGK_OptionErrorUnrecognizedPerlMagickMethod 392
#define MGK_OptionErrorUnrecognizedPixelMap 393
#define MGK_OptionErrorUnrecognizedPreviewType 394
#define MGK_OptionErrorUnrecognizedResourceType 395
#define MGK_OptionErrorUnrecognizedType 396
#define MGK_OptionErrorUnrecognizedUnitsType 397
#define MGK_OptionErrorUnrecognizedVirtualPixelMethod 398
#define MGK_OptionErrorUnsupportedSamplingFactor 399
#define MGK_OptionErrorUsageError 400
#define MGK_OptionFatalErrorInvalidColorspaceType 401
#define MGK_OptionFatalErrorInvalidEndianType 402
#define MGK_OptionFatalErrorInvalidImageType 403
#define MGK_OptionFatalErrorInvalidInterlaceType 404
#define MGK_OptionFatalErrorMissingAnImageFilename 405
#define MGK_OptionFatalErrorMissingArgument 406
#define MGK_OptionFatalErrorNoImagesWereLoaded 407
#define MGK_OptionFatalErrorOptionLengthExceedsLimit 408
#define MGK_OptionFatalErrorRequestDidNotReturnAnImage 409
#define MGK_OptionFatalErrorUnableToOpenXServer 410
#define MGK_OptionFatalErrorUnableToPersistKey 411
#define MGK_OptionFatalErrorUnrecognizedColormapType 412
#define MGK_OptionFatalErrorUnrecognizedColorspaceType 413
#define MGK_OptionFatalErrorUnrecognizedDisposeMethod 414
#define MGK_OptionFatalErrorUnrecognizedEndianType 415
#define MGK_OptionFatalErrorUnrecognizedFilterType 416
#define MGK_OptionFatalErrorUnrecognizedImageCompressionType 417
#define MGK_OptionFatalErrorUnrecognizedImageType 418
#define MGK_OptionFatalErrorUnrecognizedInterlaceType 419
#define MGK_OptionFatalErrorUnrecognizedOption 420
#define MGK_OptionFatalErrorUnrecognizedResourceType 421
#define MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod 422
#define MGK_OptionWarningUnrecognizedColor 423
#define MGK_RegistryErrorImageExpected 424
#define MGK_RegistryErrorImageInfoExpected 425
#define MGK_RegistryErrorStructureSizeMismatch 426
#define MGK_RegistryErrorUnableToGetRegistryID 427
#define MGK_RegistryErrorUnableToLocateImage 428
#define MGK_RegistryErrorUnableToSetRegistry 429
#define MGK_RegistryFatalErrorDefault 430
#define MGK_RegistryWarningDefault 431
#define MGK_ResourceLimitErrorCacheResourcesExhausted 432
#define MGK_ResourceLimitErrorImagePixelHeightLimitExceeded 433
#define MGK_ResourceLimitErrorImagePixelLimitExceeded 434
#define MGK_ResourceLimitErrorImagePixelWidthLimitExceeded 435
#define MGK_ResourceLimitErrorImagesLimitExceeded 436
#define MGK_ResourceLimitErrorMemoryAllocationFailed 437
#define MGK_ResourceLimitErrorNexusPixelHeightLimitExceeded 438
#define MGK_ResourceLimitErrorNexusPixelLimitExceeded 439
#define MGK_ResourceLimitErrorNexusPixelWidthLimitExceeded 440
#define MGK_ResourceLimitErrorNoPixelsDefinedInCache 441
#define MGK_ResourceLimitErrorPixelCacheAllocationFailed 442
#define MGK_ResourceLimitErrorProfilesLimitExceeded 443
#define MGK_ResourceLimitErrorReadLimitExceeded 444
#define MGK_ResourceLimitErrorUnableToAddColorProfile 445
#define MGK_ResourceLimitErrorUnableToAddGenericProfile 446
#define MGK_ResourceLimitErrorUnableToAddIPTCProfile 447
#define MGK_ResourceLimitErrorUnableToAddOrRemoveProfile 448
#define MGK_ResourceLimitErrorUnableToAllocateCoefficients 449
#define MGK_ResourceLimitErrorUnableToAllocateColormap 450
#define MGK_ResourceLimitErrorUnableToAllocateICCProfile 451
#define MGK_ResourceLimitErrorUnableToAllocateImage 452
#define MGK_ResourceLimitErrorUnableToAllocateString 453
#define MGK_ResourceLimitErrorUnableToAnnotateImage 454
#define MGK_ResourceLimitErrorUnableToAverageImageSequence 455
#define MGK_ResourceLimitErrorUnableToCloneDrawingContext 456
#define MGK_ResourceLimitErrorUnableToCloneImage 457
#define MGK_ResourceLimitErrorUnableToComputeImageSignature 458
#define MGK_ResourceLimitErrorUnableToConstituteImage 459
#define MGK_ResourceLimitErrorUnableToConvertFont 460
#define MGK_ResourceLimitErrorUnableToConvertStringToTokens 461
#define MGK_ResourceLimitErrorUnableToCreateColormap 462
#define MGK_ResourceLimitErrorUnableToCreateColorTransform 463
#define MGK_ResourceLimitErrorUnableToCreateCommandWidget 464
#define MGK_ResourceLimitErrorUnableToCreateImageGroup 465
#define MGK_ResourceLimitErrorUnableToCreateImageMontage 466
#define MGK_ResourceLimitErrorUnableToCreateXWindow 467
#define MGK_ResourceLimitErrorUnableToCropImage 468
#define MGK_ResourceLimitErrorUnableToDespeckleImage 469
#define MGK_ResourceLimitErrorUnableToDetermineImageClass 470
#define MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors 471
#define MGK_ResourceLimitErrorUnableToDitherImage 472
#define MGK_ResourceLimitErrorUnableToDrawOnImage 473
#define MGK_ResourceLimitErrorUnableToEdgeImage 474
#define MGK_ResourceLimitErrorUnableToEmbossImage 475
#define MGK_ResourceLimitErrorUnableToEnhanceImage 476
#define MGK_ResourceLimitErrorUnableToFloodfillImage 477
#define MGK_ResourceLimitErrorUnableToGammaCorrectImage 478
#define MGK_ResourceLimitErrorUnableToGetBestIconSize 479
#define MGK_ResourceLimitErrorUnableToGetFromRegistry 480
#define MGK_ResourceLimitErrorUnableToGetPackageInfo 481
#define MGK_ResourceLimitErrorUnableToInterpretMSLImage 482
#define MGK_ResourceLimitErrorUnableToLevelImage 483
#define MGK_ResourceLimitErrorUnableToMagnifyImage 484
#define MGK_ResourceLimitErrorUnableToManageColor 485
#define MGK_ResourceLimitErrorUnableToMapImage 486
#define MGK_ResourceLimitErrorUnableToMapImageSequence 487
#define MGK_ResourceLimitErrorUnableToMedianFilterImage 488
#define MGK_ResourceLimitErrorUnableToMotionBlurImage 489
#define MGK_ResourceLimitErrorUnableToNoiseFilterImage 490
#define MGK_ResourceLimitErrorUnableToNormalizeImage 491
#define MGK_ResourceLimitErrorUnableToOpenColorProfile 492
#define MGK_ResourceLimitErrorUnableToQuantizeImage 493
#define MGK_ResourceLimitErrorUnableToQuantizeImageSequence 494
#define MGK_ResourceLimitErrorUnableToReadTextChunk 495
#define MGK_ResourceLimitErrorUnableToReadXImage 496
#define MGK_ResourceLimitErrorUnableToReadXServerColormap 497
#define MGK_ResourceLimitErrorUnableToResizeImage 498
#define MGK_ResourceLimitErrorUnableToRotateImage 499
#define MGK_ResourceLimitErrorUnableToSampleImage 500
#define MGK_ResourceLimitErrorUnableToScaleImage 501
#define MGK_ResourceLimitErrorUnableToSegmentImage 502
#define MGK_ResourceLimitErrorUnableToSelectImage 503
#define MGK_ResourceLimitErrorUnableToSetImageBackgroundColor 504
#define MGK_ResourceLimitErrorUnableToSharpenImage 505
#define MGK_ResourceLimitErrorUnableToShaveImage 506
#define MGK_ResourceLimitErrorUnableToShearImage 507
#define MGK_ResourceLimitErrorUnableToSortImageColormap 508
#define MGK_ResourceLimitErrorUnableToThresholdImage 509
#define MGK_ResourceLimitErrorUnableToTransformColorspace 510
#define MGK_ResourceLimitErrorWriteLimitExceeded 511
#define MGK_ResourceLimitFatalErrorMemoryAllocationFailed 512
#define MGK_ResourceLimitFatalErrorSemaporeOperationFailed 513
#define MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info 514
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo 515
#define MGK_ResourceLimitFatalErrorUnableToAllocateCacheView 516
#define MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo 517
#define MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern 518
#define MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo 519
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext 520
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo 521
#define MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand 522
#define MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap 523
#define MGK_ResourceLimitFatalErrorUnableToAllocateImage 524
#define MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels 525
#define MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo 526
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo 527
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo 528
#define MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap 529
#define MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo 530
#define MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo 531
#define MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo 532
#define MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel 533
#define MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo 534
#define MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo 535
#define MGK_ResourceLimitFatalErrorUnableToAllocateString 536
#define MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo 537
#define MGK_ResourceLimitFatalErrorUnableToAllocateWand 538
#define MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence 539
#define MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo 540
#define MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo 541
#define MGK_ResourceLimitFatalErrorUnableToCloneImage 542
#define MGK_ResourceLimitFatalErrorUnableToCloneImageInfo 543
#define MGK_ResourceLimitFatalErrorUnableToConcatenateString 544
#define MGK_ResourceLimitFatalErrorUnableToConvertText 545
#define MGK_ResourceLimitFatalErrorUnableToCreateColormap 546
#define MGK_ResourceLimitFatalErrorUnableToDestroySemaphore 547
#define MGK_ResourceLimitFatalErrorUnableToDisplayImage 548
#define MGK_ResourceLimitFatalErrorUnableToEscapeString 549
#define MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore 550
#define MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage 551
#define MGK_ResourceLimitFatalErrorUnableToLockSemaphore 552
#define MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy 553
#define MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore 554
#define MGK_ResourceLimitWarningMemoryAllocationFailed 555
#define MGK_StreamErrorImageDoesNotContainTheStreamGeometry 556
#define MGK_StreamErrorNoStreamHandlerIsDefined 557
#define MGK_StreamErrorPixelCacheIsNotOpen 558
#define MGK_StreamErrorUnableToAcquirePixelStream 559
#define MGK_StreamErrorUnableToSetPixelStream 560
#define MGK_StreamErrorUnableToSyncPixelStream 561
#define MGK_StreamFatalErrorDefault 562
#define MGK_StreamWarningDefault 563
#define MGK_TypeErrorFontNotSpecified 564
#define MGK_TypeErrorFontSubstitutionRequired 565
#define MGK_TypeErrorUnableToGetTypeMetrics 566
#define MGK_TypeErrorUnableToInitializeFreetypeLibrary 567
#define MGK_TypeErrorUnableToReadFont 568
#define MGK_TypeErrorUnrecognizedFontEncoding 569
#define MGK_TypeFatalErrorDefault 570
#define MGK_TypeWarningDefault 571
#define MGK_WandErrorInvalidColormapIndex 572
#define MGK_WandErrorWandAPINotImplemented 573
#define MGK_WandErrorWandContainsNoImageIndexs 574
#define MGK_WandErrorWandContainsNoImages 575
#define MGK_XServerErrorColorIsNotKnownToServer 576
#define MGK_XServerErrorNoWindowWithSpecifiedIDExists 577
#define MGK_XServerErrorStandardColormapIsNotInitialized 578
#define MGK_XServerErrorUnableToConnectToRemoteDisplay 579
#define MGK_XServerErrorUnableToCreateBitmap 580
#define MGK_XServerErrorUnableToCreateColormap 581
#define MGK_XServerErrorUnableToCreatePixmap 582
#define MGK_XServerErrorUnableToCreateProperty 583
#define MGK_XServerErrorUnableToCreateStandardColormap 584
#define MGK_XServerErrorUnableToDisplayImageInfo 585
#define MGK_XServerErrorUnableToGetProperty 586
#define MGK_XServerErrorUnableToGetStandardColormap 587
#define MGK_XServerErrorUnableToGetVisual 588
#define MGK_XServerErrorUnableToGrabMouse 589
#define MGK_XServerErrorUnableToLoadFont 590
#define MGK_XServerErrorUnableToMatchVisualToStandardColormap 591
#define MGK_XServerErrorUnableToOpenXServer 592
#define MGK_XServerErrorUnableToReadXAttributes 593
#define MGK_XServerErrorUnableToReadXWindowImage 594
#define MGK_XServerErrorUnrecognizedColormapType 595
#define MGK_XServerErrorUnrecognizedGravityType 596
#define MGK_XServerErrorUnrecognizedVisualSpecifier 597
#define MGK_XServerFatalErrorUnableToAllocateXHints 598
#define MGK_XServerFatalErrorUnableToCreateCursor 599
#define MGK_XServerFatalErrorUnableToCreateGraphicContext 600
#define MGK_XServerFatalErrorUnableToCreateStandardColormap 601
#define MGK_XServerFatalErrorUnableToCreateTextProperty 602
#define MGK_XServerFatalErrorUnableToCreateXImage 603
#define MGK_XServerFatalErrorUnableToCreateXPixmap 604
#define MGK_XServerFatalErrorUnableToCreateXWindow 605
#define MGK_XServerFatalErrorUnableToDisplayImage 606
#define MGK_XServerFatalErrorUnableToDitherImage 607
#define MGK_XServerFatalErrorUnableToGetPixelInfo 608
#define MGK_XServerFatalErrorUnableToGetVisual 609
#define MGK_XServerFatalErrorUnableToLoadFont 610
#define MGK_XServerFatalErrorUnableToMakeXWindow 611
#define MGK_XServerFatalErrorUnableToOpenXServer 612
#define MGK_XServerFatalErrorUnableToViewFonts 613
#define MGK_XServerWarningUnableToGetVisual 614
#define MGK_XServerWarningUsingDefaultVisual 615

#endif

#if defined(_INCLUDE_CATEGORYMAP_TABLE_)
typedef struct _CategoryInfo{
  const char name[17];
  unsigned int offset;
} CategoryInfo;

static const CategoryInfo category_map[] =
  {
    { "Blob", 0 },
    { "Cache", 3 },
    { "Coder", 6 },
    { "Configure", 9 },
    { "Corrupt/Image", 12 },
    { "Delegate", 15 },
    { "Draw", 18 },
    { "File/Open", 21 },
    { "Image", 24 },
    { "Missing/Delegate", 27 },
    { "Module", 30 },
    { "Monitor", 33 },
    { "Option", 36 },
    { "Registry", 39 },
    { "Resource/Limit", 42 },
    { "Stream", 45 },
    { "Type", 48 },
    { "Wand", 51 },
    { "XServer", 52 },
    { "", 54 }
  };
#endif

#if defined(_INCLUDE_SEVERITYMAP_TABLE_)
typedef struct _SeverityInfo{
  const char name[28];
  unsigned int offset;
  ExceptionType severityid;
} SeverityInfo;

static const SeverityInfo severity_map[] =
  {
    { "Blob/Error", 0, BlobError },
    { "Blob/FatalError", 9, BlobFatalError },
    { "Blob/Warning", 10, BlobWarning },
    { "Cache/Error", 11, CacheError },
    { "Cache/FatalError", 24, CacheFatalError },
    { "Cache/Warning", 26, CacheWarning },
    { "Coder/Error", 27, CoderError },
    { "Coder/FatalError", 122, CoderFatalError },
    { "Coder/Warning", 123, CoderWarning },
    { "Configure/Error", 124, ConfigureError },
    { "Configure/FatalError", 131, ConfigureFatalError },
    { "Configure/Warning", 135, ConfigureWarning },
    { "Corrupt/Image/Error", 136, CorruptImageError },
    { "Corrupt/Image/FatalError", 179, CorruptImageFatalError },
    { "Corrupt/Image/Warning", 180, CorruptImageWarning },
    { "Delegate/Error", 192, DelegateError },
    { "Delegate/FatalError", 210, DelegateFatalError },
    { "Delegate/Warning", 211, DelegateWarning },
    { "Draw/Error", 212, DrawError },
    { "Draw/FatalError", 234, DrawFatalError },
    { "Draw/Warning", 235, DrawWarning },
    { "File/Open/Error", 239, FileOpenError },
    { "File/Open/FatalError", 242, FileOpenFatalError },
    { "File/Open/Warning", 243, FileOpenWarning },
    { "Image/Error", 244, ImageError },
    { "Image/FatalError", 281, ImageFatalError },
    { "Image/Warning", 282, ImageWarning },
    { "Missing/Delegate/Error", 283, MissingDelegateError },
    { "Missing/Delegate/FatalError", 294, MissingDelegateFatalError },
    { "Missing/Delegate/Warning", 295, MissingDelegateWarning },
    { "Module/Error", 296, ModuleError },
    { "Module/FatalError", 301, ModuleFatalError },
    { "Module/Warning", 302, ModuleWarning },
    { "Monitor/Error", 303, MonitorError },
    { "Monitor/FatalError", 304, MonitorFatalError },
    { "Monitor/Warning", 306, MonitorWarning },
    { "Option/Error", 307, OptionError },
    { "Option/FatalError", 400, OptionFatalError },
    { "Option/Warning", 422, OptionWarning },
    { "Registry/Error", 423, RegistryError },
    { "Registry/FatalError", 429, RegistryFatalError },
    { "Registry/Warning", 430, RegistryWarning },
    { "Resource/Limit/Error", 431, ResourceLimitError },
    { "Resource/Limit/FatalError", 511, ResourceLimitFatalError },
    { "Resource/Limit/Warning", 554, ResourceLimitWarning },
    { "Stream/Error", 555, StreamError },
    { "Stream/FatalError", 561, StreamFatalError },
    { "Stream/Warning", 562, StreamWarning },
    { "Type/Error", 563, TypeError },
    { "Type/FatalError", 569, TypeFatalError },
    { "Type/Warning", 570, TypeWarning },
    { "Wand/Error", 571, WandError },
    { "XServer/Error", 575, XServerError },
    { "XServer/FatalError", 597, XServerFatalError },
    { "XServer/Warning", 613, XServerWarning },
    { "", 615, UndefinedException }
  };
#endif

#if defined(_INCLUDE_TAGMAP_TABLE_)
typedef struct _MessageInfo
{
  const char name[40];
  unsigned int messageid;
} MessageInfo;

static const MessageInfo message_map[] =
  {
    { "UnableToCreateBlob", MGK_BlobErrorUnableToCreateBlob },
    { "UnableToDeduceImageFormat", MGK_BlobErrorUnableToDeduceImageFormat },
    { "UnableToObtainOffset", MGK_BlobErrorUnableToObtainOffset },
    { "UnableToOpenFile", MGK_BlobErrorUnableToOpenFile },
    { "UnableToReadFile", MGK_BlobErrorUnableToReadFile },
    { "UnableToReadToOffset", MGK_BlobErrorUnableToReadToOffset },
    { "UnableToSeekToOffset", MGK_BlobErrorUnableToSeekToOffset },
    { "UnableToWriteBlob", MGK_BlobErrorUnableToWriteBlob },
    { "UnrecognizedImageFormat", MGK_BlobErrorUnrecognizedImageFormat },
    { "Default", MGK_BlobFatalErrorDefault },
    { "Default", MGK_BlobWarningDefault },
    { "EmptyCacheNexus", MGK_CacheErrorEmptyCacheNexus },
    { "InconsistentPersistentCacheDepth", MGK_CacheErrorInconsistentPersistentCacheDepth },
    { "PixelCacheDimensionsMisMatch", MGK_CacheErrorPixelCacheDimensionsMisMatch },
    { "PixelCacheIsNotOpen", MGK_CacheErrorPixelCacheIsNotOpen },
    { "UnableToAllocateCacheView", MGK_CacheErrorUnableToAllocateCacheView },
    { "UnableToCloneCache", MGK_CacheErrorUnableToCloneCache },
    { "UnableToExtendCache", MGK_CacheErrorUnableToExtendCache },
    { "UnableToGetCacheNexus", MGK_CacheErrorUnableToGetCacheNexus },
    { "UnableToGetPixelsFromCache", MGK_CacheErrorUnableToGetPixelsFromCache },
    { "UnableToOpenCache", MGK_CacheErrorUnableToOpenCache },
    { "UnableToPeristPixelCache", MGK_CacheErrorUnableToPeristPixelCache },
    { "UnableToReadPixelCache", MGK_CacheErrorUnableToReadPixelCache },
    { "UnableToSyncCache", MGK_CacheErrorUnableToSyncCache },
    { "DiskAllocationFailed", MGK_CacheFatalErrorDiskAllocationFailed },
    { "UnableToExtendPixelCache", MGK_CacheFatalErrorUnableToExtendPixelCache },
    { "Default", MGK_CacheWarningDefault },
    { "ArithmeticOverflow", MGK_CoderErrorArithmeticOverflow },
    { "ColormapTooLarge", MGK_CoderErrorColormapTooLarge },
    { "ColormapTypeNotSupported", MGK_CoderErrorColormapTypeNotSupported },
    { "ColorspaceModelIsNotSupported", MGK_CoderErrorColorspaceModelIsNotSupported },
    { "ColorTypeNotSupported", MGK_CoderErrorColorTypeNotSupported },
    { "CompressionNotValid", MGK_CoderErrorCompressionNotValid },
    { "DataEncodingSchemeIsNotSupported", MGK_CoderErrorDataEncodingSchemeIsNotSupported },
    { "DataStorageTypeIsNotSupported", MGK_CoderErrorDataStorageTypeIsNotSupported },
    { "DecodedImageNotReturned", MGK_CoderErrorDecodedImageNotReturned },
    { "DeltaPNGNotSupported", MGK_CoderErrorDeltaPNGNotSupported },
    { "DivisionByZero", MGK_CoderErrorDivisionByZero },
    { "EncryptedWPGImageFileNotSupported", MGK_CoderErrorEncryptedWPGImageFileNotSupported },
    { "FractalCompressionNotSupported", MGK_CoderErrorFractalCompressionNotSupported },
    { "ImageColumnOrRowSizeIsNotSupported", MGK_CoderErrorImageColumnOrRowSizeIsNotSupported },
    { "ImageDoesNotHaveAMatteChannel", MGK_CoderErrorImageDoesNotHaveAMatteChannel },
    { "ImageIsNotTiled", MGK_CoderErrorImageIsNotTiled },
    { "ImageTypeNotSupported", MGK_CoderErrorImageTypeNotSupported },
    { "IncompatibleSizeOfDouble", MGK_CoderErrorIncompatibleSizeOfDouble },
    { "IrregularChannelGeometryNotSupported", MGK_CoderErrorIrregularChannelGeometryNotSupported },
    { "JNGCompressionNotSupported", MGK_CoderErrorJNGCompressionNotSupported },
    { "JPEGCompressionNotSupported", MGK_CoderErrorJPEGCompressionNotSupported },
    { "JPEGEmbeddingFailed", MGK_CoderErrorJPEGEmbeddingFailed },
    { "JXLDecoderAPIFailure", MGK_CoderErrorJXLDecoderAPIFailure },
    { "JXLEncoderAPIFailure", MGK_CoderErrorJXLEncoderAPIFailure },
    { "LocationTypeIsNotSupported", MGK_CoderErrorLocationTypeIsNotSupported },
    { "MapStorageTypeIsNotSupported", MGK_CoderErrorMapStorageTypeIsNotSupported },
    { "MSBByteOrderNotSupported", MGK_CoderErrorMSBByteOrderNotSupported },
    { "MultidimensionalMatricesAreNotSupported", MGK_CoderErrorMultidimensionalMatricesAreNotSupported },
    { "MultipleRecordListNotSupported", MGK_CoderErrorMultipleRecordListNotSupported },
    { "No8BIMDataIsAvailable", MGK_CoderErrorNo8BIMDataIsAvailable },
    { "NoAPP1DataIsAvailable", MGK_CoderErrorNoAPP1DataIsAvailable },
    { "NoBitmapOnClipboard", MGK_CoderErrorNoBitmapOnClipboard },
    { "NoColorProfileAvailable", MGK_CoderErrorNoColorProfileAvailable },
    { "NoDataReturned", MGK_CoderErrorNoDataReturned },
    { "NoImageVectorGraphics", MGK_CoderErrorNoImageVectorGraphics },
    { "NoIPTCInfoWasFound", MGK_CoderErrorNoIPTCInfoWasFound },
    { "NoIPTCProfileAvailable", MGK_CoderErrorNoIPTCProfileAvailable },
    { "NumberOfImagesIsNotSupported", MGK_CoderErrorNumberOfImagesIsNotSupported },
    { "OnlyContinuousTonePictureSupported", MGK_CoderErrorOnlyContinuousTonePictureSupported },
    { "OnlyLevelZerofilesSupported", MGK_CoderErrorOnlyLevelZerofilesSupported },
    { "PNGCompressionNotSupported", MGK_CoderErrorPNGCompressionNotSupported },
    { "PNGLibraryTooOld", MGK_CoderErrorPNGLibraryTooOld },
    { "RLECompressionNotSupported", MGK_CoderErrorRLECompressionNotSupported },
    { "SubsamplingRequiresEvenWidth", MGK_CoderErrorSubsamplingRequiresEvenWidth },
    { "UnableToCopyProfile", MGK_CoderErrorUnableToCopyProfile },
    { "UnableToCreateADC", MGK_CoderErrorUnableToCreateADC },
    { "UnableToCreateBitmap", MGK_CoderErrorUnableToCreateBitmap },
    { "UnableToDecodeImage", MGK_CoderErrorUnableToDecodeImage },
    { "UnableToDecompressImage", MGK_CoderErrorUnableToDecompressImage },
    { "UnableToGetImageCharacteristics", MGK_CoderErrorUnableToGetImageCharacteristics },
    { "UnableToInitializeFPXLibrary", MGK_CoderErrorUnableToInitializeFPXLibrary },
    { "UnableToOpenBlob", MGK_CoderErrorUnableToOpenBlob },
    { "UnableToOpenFile", MGK_CoderErrorUnableToOpenFile },
    { "UnableToReadAspectRatio", MGK_CoderErrorUnableToReadAspectRatio },
    { "UnableToReadCIELABImages", MGK_CoderErrorUnableToReadCIELABImages },
    { "UnableToReadSummaryInfo", MGK_CoderErrorUnableToReadSummaryInfo },
    { "UnableToResizeImage", MGK_CoderErrorUnableToResizeImage },
    { "UnableToSetAffineMatrix", MGK_CoderErrorUnableToSetAffineMatrix },
    { "UnableToSetAspectRatio", MGK_CoderErrorUnableToSetAspectRatio },
    { "UnableToSetColorTwist", MGK_CoderErrorUnableToSetColorTwist },
    { "UnableToSetContrast", MGK_CoderErrorUnableToSetContrast },
    { "UnableToSetFilteringValue", MGK_CoderErrorUnableToSetFilteringValue },
    { "UnableToSetImageComments", MGK_CoderErrorUnableToSetImageComments },
    { "UnableToSetImageOpacity", MGK_CoderErrorUnableToSetImageOpacity },
    { "UnableToSetImageTitle", MGK_CoderErrorUnableToSetImageTitle },
    { "UnableToSetImageType", MGK_CoderErrorUnableToSetImageType },
    { "UnableToSetJPEGLevel", MGK_CoderErrorUnableToSetJPEGLevel },
    { "UnableToSetRegionOfInterest", MGK_CoderErrorUnableToSetRegionOfInterest },
    { "UnableToSetSummaryInfo", MGK_CoderErrorUnableToSetSummaryInfo },
    { "UnableToTransformColorspace", MGK_CoderErrorUnableToTransformColorspace },
    { "UnableToTranslateText", MGK_CoderErrorUnableToTranslateText },
    { "UnableToWriteMPEGParameters", MGK_CoderErrorUnableToWriteMPEGParameters },
    { "UnableToWriteTemporaryFile", MGK_CoderErrorUnableToWriteTemporaryFile },
    { "UnableToZipCompressImage", MGK_CoderErrorUnableToZipCompressImage },
    { "UnsupportedBitsPerSample", MGK_CoderErrorUnsupportedBitsPerSample },
    { "UnsupportedCellTypeInTheMatrix", MGK_CoderErrorUnsupportedCellTypeInTheMatrix },
    { "UnsupportedNumberOfColumns", MGK_CoderErrorUnsupportedNumberOfColumns },
    { "UnsupportedNumberOfRows", MGK_CoderErrorUnsupportedNumberOfRows },
    { "UnsupportedSamplesPerPixel", MGK_CoderErrorUnsupportedSamplesPerPixel },
    { "WebPDecodingFailedUserAbort", MGK_CoderErrorWebPDecodingFailedUserAbort },
    { "WebPEncodingFailed", MGK_CoderErrorWebPEncodingFailed },
    { "WebPEncodingFailedBadDimension", MGK_CoderErrorWebPEncodingFailedBadDimension },
    { "WebPEncodingFailedBadWrite", MGK_CoderErrorWebPEncodingFailedBadWrite },
    { "WebPEncodingFailedBitstreamOutOfMemory", MGK_CoderErrorWebPEncodingFailedBitstreamOutOfMemory },
    { "WebPEncodingFailedFileTooBig", MGK_CoderErrorWebPEncodingFailedFileTooBig },
    { "WebPEncodingFailedInvalidConfiguration", MGK_CoderErrorWebPEncodingFailedInvalidConfiguration },
    { "WebPEncodingFailedNULLParameter", MGK_CoderErrorWebPEncodingFailedNULLParameter },
    { "WebPEncodingFailedOutOfMemory", MGK_CoderErrorWebPEncodingFailedOutOfMemory },
    { "WebPEncodingFailedPartition0Overflow", MGK_CoderErrorWebPEncodingFailedPartition0Overflow },
    { "WebPEncodingFailedPartitionOverflow", MGK_CoderErrorWebPEncodingFailedPartitionOverflow },
    { "WebPEncodingFailedUserAbort", MGK_CoderErrorWebPEncodingFailedUserAbort },
    { "WebPInvalidConfiguration", MGK_CoderErrorWebPInvalidConfiguration },
    { "WebPInvalidParameter", MGK_CoderErrorWebPInvalidParameter },
    { "XMLParserFailure", MGK_CoderErrorXMLParserFailure },
    { "ZipCompressionNotSupported", MGK_CoderErrorZipCompressionNotSupported },
    { "Default", MGK_CoderFatalErrorDefault },
    { "LosslessToLossyJPEGConversion", MGK_CoderWarningLosslessToLossyJPEGConversion },
    { "IncludeElementNestedTooDeeply", MGK_ConfigureErrorIncludeElementNestedTooDeeply },
    { "RegistryKeyLookupFailed", MGK_ConfigureErrorRegistryKeyLookupFailed },
    { "StringTokenLengthExceeded", MGK_ConfigureErrorStringTokenLengthExceeded },
    { "UnableToAccessConfigureFile", MGK_ConfigureErrorUnableToAccessConfigureFile },
    { "UnableToAccessFontFile", MGK_ConfigureErrorUnableToAccessFontFile },
    { "UnableToAccessLogFile", MGK_ConfigureErrorUnableToAccessLogFile },
    { "UnableToAccessModuleFile", MGK_ConfigureErrorUnableToAccessModuleFile },
    { "Default", MGK_ConfigureFatalErrorDefault },
    { "UnableToChangeToWorkingDirectory", MGK_ConfigureFatalErrorUnableToChangeToWorkingDirectory },
    { "UnableToGetCurrentDirectory", MGK_ConfigureFatalErrorUnableToGetCurrentDirectory },
    { "UnableToRestoreCurrentDirectory", MGK_ConfigureFatalErrorUnableToRestoreCurrentDirectory },
    { "Default", MGK_ConfigureWarningDefault },
    { "AnErrorHasOccurredReadingFromFile", MGK_CorruptImageErrorAnErrorHasOccurredReadingFromFile },
    { "AnErrorHasOccurredWritingToFile", MGK_CorruptImageErrorAnErrorHasOccurredWritingToFile },
    { "ColormapExceedsColorsLimit", MGK_CorruptImageErrorColormapExceedsColorsLimit },
    { "CompressionNotValid", MGK_CorruptImageErrorCompressionNotValid },
    { "CorruptImage", MGK_CorruptImageErrorCorruptImage },
    { "ImageFileDoesNotContainAnyImageData", MGK_CorruptImageErrorImageFileDoesNotContainAnyImageData },
    { "ImageFileHasNoScenes", MGK_CorruptImageErrorImageFileHasNoScenes },
    { "ImageTypeNotSupported", MGK_CorruptImageErrorImageTypeNotSupported },
    { "ImproperImageHeader", MGK_CorruptImageErrorImproperImageHeader },
    { "InsufficientImageDataInFile", MGK_CorruptImageErrorInsufficientImageDataInFile },
    { "InvalidColormapIndex", MGK_CorruptImageErrorInvalidColormapIndex },
    { "InvalidFileFormatVersion", MGK_CorruptImageErrorInvalidFileFormatVersion },
    { "LengthAndFilesizeDoNotMatch", MGK_CorruptImageErrorLengthAndFilesizeDoNotMatch },
    { "MissingImageChannel", MGK_CorruptImageErrorMissingImageChannel },
    { "NegativeOrZeroImageSize", MGK_CorruptImageErrorNegativeOrZeroImageSize },
    { "NonOS2HeaderSizeError", MGK_CorruptImageErrorNonOS2HeaderSizeError },
    { "NotEnoughTiles", MGK_CorruptImageErrorNotEnoughTiles },
    { "RecursionDetected", MGK_CorruptImageErrorRecursionDetected },
    { "StaticPlanesValueNotEqualToOne", MGK_CorruptImageErrorStaticPlanesValueNotEqualToOne },
    { "SubsamplingRequiresEvenWidth", MGK_CorruptImageErrorSubsamplingRequiresEvenWidth },
    { "TooMuchImageDataInFile", MGK_CorruptImageErrorTooMuchImageDataInFile },
    { "UnableToReadColormapFromDumpFile", MGK_CorruptImageErrorUnableToReadColormapFromDumpFile },
    { "UnableToReadColorProfile", MGK_CorruptImageErrorUnableToReadColorProfile },
    { "UnableToReadExtensionBlock", MGK_CorruptImageErrorUnableToReadExtensionBlock },
    { "UnableToReadGenericProfile", MGK_CorruptImageErrorUnableToReadGenericProfile },
    { "UnableToReadImageData", MGK_CorruptImageErrorUnableToReadImageData },
    { "UnableToReadImageHeader", MGK_CorruptImageErrorUnableToReadImageHeader },
    { "UnableToReadIPTCProfile", MGK_CorruptImageErrorUnableToReadIPTCProfile },
    { "UnableToReadPixmapFromDumpFile", MGK_CorruptImageErrorUnableToReadPixmapFromDumpFile },
    { "UnableToReadSubImageData", MGK_CorruptImageErrorUnableToReadSubImageData },
    { "UnableToReadVIDImage", MGK_CorruptImageErrorUnableToReadVIDImage },
    { "UnableToReadWindowNameFromDumpFile", MGK_CorruptImageErrorUnableToReadWindowNameFromDumpFile },
    { "UnableToRunlengthDecodeImage", MGK_CorruptImageErrorUnableToRunlengthDecodeImage },
    { "UnableToUncompressImage", MGK_CorruptImageErrorUnableToUncompressImage },
    { "UnexpectedEndOfFile", MGK_CorruptImageErrorUnexpectedEndOfFile },
    { "UnexpectedSamplingFactor", MGK_CorruptImageErrorUnexpectedSamplingFactor },
    { "UnknownPatternType", MGK_CorruptImageErrorUnknownPatternType },
    { "UnrecognizedBitsPerPixel", MGK_CorruptImageErrorUnrecognizedBitsPerPixel },
    { "UnrecognizedImageCompression", MGK_CorruptImageErrorUnrecognizedImageCompression },
    { "UnrecognizedNumberOfColors", MGK_CorruptImageErrorUnrecognizedNumberOfColors },
    { "UnrecognizedXWDHeader", MGK_CorruptImageErrorUnrecognizedXWDHeader },
    { "UnsupportedBitsPerSample", MGK_CorruptImageErrorUnsupportedBitsPerSample },
    { "UnsupportedNumberOfPlanes", MGK_CorruptImageErrorUnsupportedNumberOfPlanes },
    { "UnableToPersistKey", MGK_CorruptImageFatalErrorUnableToPersistKey },
    { "CompressionNotValid", MGK_CorruptImageWarningCompressionNotValid },
    { "CorruptImage", MGK_CorruptImageWarningCorruptImage },
    { "ImproperImageHeader", MGK_CorruptImageWarningImproperImageHeader },
    { "InvalidColormapIndex", MGK_CorruptImageWarningInvalidColormapIndex },
    { "LengthAndFilesizeDoNotMatch", MGK_CorruptImageWarningLengthAndFilesizeDoNotMatch },
    { "NegativeOrZeroImageSize", MGK_CorruptImageWarningNegativeOrZeroImageSize },
    { "NonOS2HeaderSizeError", MGK_CorruptImageWarningNonOS2HeaderSizeError },
    { "SkipToSyncByte", MGK_CorruptImageWarningSkipToSyncByte },
    { "StaticPlanesValueNotEqualToOne", MGK_CorruptImageWarningStaticPlanesValueNotEqualToOne },
    { "UnableToParseEmbeddedProfile", MGK_CorruptImageWarningUnableToParseEmbeddedProfile },
    { "UnrecognizedBitsPerPixel", MGK_CorruptImageWarningUnrecognizedBitsPerPixel },
    { "UnrecognizedImageCompression", MGK_CorruptImageWarningUnrecognizedImageCompression },
    { "DelegateFailed", MGK_DelegateErrorDelegateFailed },
    { "FailedToAllocateArgumentList", MGK_DelegateErrorFailedToAllocateArgumentList },
    { "FailedToAllocateGhostscriptInterpreter", MGK_DelegateErrorFailedToAllocateGhostscriptInterpreter },
    { "FailedToComputeOutputSize", MGK_DelegateErrorFailedToComputeOutputSize },
    { "FailedToFindGhostscript", MGK_DelegateErrorFailedToFindGhostscript },
    { "FailedToRenderFile", MGK_DelegateErrorFailedToRenderFile },
    { "FailedToScanFile", MGK_DelegateErrorFailedToScanFile },
    { "NoTagFound", MGK_DelegateErrorNoTagFound },
    { "PostscriptDelegateFailed", MGK_DelegateErrorPostscriptDelegateFailed },
    { "UnableToCreateImage", MGK_DelegateErrorUnableToCreateImage },
    { "UnableToCreateImageComponent", MGK_DelegateErrorUnableToCreateImageComponent },
    { "UnableToDecodeImageFile", MGK_DelegateErrorUnableToDecodeImageFile },
    { "UnableToEncodeImageFile", MGK_DelegateErrorUnableToEncodeImageFile },
    { "UnableToInitializeFPXLibrary", MGK_DelegateErrorUnableToInitializeFPXLibrary },
    { "UnableToInitializeWMFLibrary", MGK_DelegateErrorUnableToInitializeWMFLibrary },
    { "UnableToManageJP2Stream", MGK_DelegateErrorUnableToManageJP2Stream },
    { "UnableToWriteSVGFormat", MGK_DelegateErrorUnableToWriteSVGFormat },
    { "WebPABIMismatch", MGK_DelegateErrorWebPABIMismatch },
    { "Default", MGK_DelegateFatalErrorDefault },
    { "Default", MGK_DelegateWarningDefault },
    { "AlreadyPushingPatternDefinition", MGK_DrawErrorAlreadyPushingPatternDefinition },
    { "ArithmeticOverflow", MGK_DrawErrorArithmeticOverflow },
    { "DrawingRecursionDetected", MGK_DrawErrorDrawingRecursionDetected },
    { "FloatValueConversionError", MGK_DrawErrorFloatValueConversionError },
    { "IntegerValueConversionError", MGK_DrawErrorIntegerValueConversionError },
    { "InvalidAttributeArgument", MGK_DrawErrorInvalidAttributeArgument },
    { "InvalidClassName", MGK_DrawErrorInvalidClassName },
    { "InvalidElementIdentifier", MGK_DrawErrorInvalidElementIdentifier },
    { "InvalidPrimitiveArgument", MGK_DrawErrorInvalidPrimitiveArgument },
    { "NonconformingDrawingPrimitiveDefinition", MGK_DrawErrorNonconformingDrawingPrimitiveDefinition },
    { "PrimitiveArithmeticOverflow", MGK_DrawErrorPrimitiveArithmeticOverflow },
    { "TextStringTruncation", MGK_DrawErrorTextStringTruncation },
    { "TooManyCoordinates", MGK_DrawErrorTooManyCoordinates },
    { "UnableToDrawOnImage", MGK_DrawErrorUnableToDrawOnImage },
    { "UnableToFloodFillImageDueToClipMask", MGK_DrawErrorUnableToFloodFillImageDueToClipMask },
    { "UnableToPrint", MGK_DrawErrorUnableToPrint },
    { "UnbalancedGraphicContextPushPop", MGK_DrawErrorUnbalancedGraphicContextPushPop },
    { "UnbalancedPushPop", MGK_DrawErrorUnbalancedPushPop },
    { "UnreasonableAffineMatrix", MGK_DrawErrorUnreasonableAffineMatrix },
    { "UnreasonableDashPolygonLength", MGK_DrawErrorUnreasonableDashPolygonLength },
    { "UnreasonableGradientSize", MGK_DrawErrorUnreasonableGradientSize },
    { "VectorPathTruncated", MGK_DrawErrorVectorPathTruncated },
    { "Default", MGK_DrawFatalErrorDefault },
    { "FuzzingBuildUnsafeForProduction", MGK_DrawWarningFuzzingBuildUnsafeForProduction },
    { "NotARelativeURL", MGK_DrawWarningNotARelativeURL },
    { "NotCurrentlyPushingPatternDefinition", MGK_DrawWarningNotCurrentlyPushingPatternDefinition },
    { "URLNotFound", MGK_DrawWarningURLNotFound },
    { "UnableToCreateTemporaryFile", MGK_FileOpenErrorUnableToCreateTemporaryFile },
    { "UnableToOpenFile", MGK_FileOpenErrorUnableToOpenFile },
    { "UnableToWriteFile", MGK_FileOpenErrorUnableToWriteFile },
    { "Default", MGK_FileOpenFatalErrorDefault },
    { "Default", MGK_FileOpenWarningDefault },
    { "AngleIsDiscontinuous", MGK_ImageErrorAngleIsDiscontinuous },
    { "CMYKAImageLacksAlphaChannel", MGK_ImageErrorCMYKAImageLacksAlphaChannel },
    { "ColorspaceColorProfileMismatch", MGK_ImageErrorColorspaceColorProfileMismatch },
    { "ImageColorspaceDiffers", MGK_ImageErrorImageColorspaceDiffers },
    { "ImageColorspaceMismatch", MGK_ImageErrorImageColorspaceMismatch },
    { "ImageDifferenceExceedsLimit", MGK_ImageErrorImageDifferenceExceedsLimit },
    { "ImageDoesNotContainResolution", MGK_ImageErrorImageDoesNotContainResolution },
    { "ImageIsNotColormapped", MGK_ImageErrorImageIsNotColormapped },
    { "ImageOpacityDiffers", MGK_ImageErrorImageOpacityDiffers },
    { "ImageSequenceIsRequired", MGK_ImageErrorImageSequenceIsRequired },
    { "ImageSizeDiffers", MGK_ImageErrorImageSizeDiffers },
    { "InvalidColormapIndex", MGK_ImageErrorInvalidColormapIndex },
    { "LeftAndRightImageSizesDiffer", MGK_ImageErrorLeftAndRightImageSizesDiffer },
    { "NoImagesWereFound", MGK_ImageErrorNoImagesWereFound },
    { "NoImagesWereLoaded", MGK_ImageErrorNoImagesWereLoaded },
    { "NoLocaleImageAttribute", MGK_ImageErrorNoLocaleImageAttribute },
    { "TooManyClusters", MGK_ImageErrorTooManyClusters },
    { "UnableToAppendImage", MGK_ImageErrorUnableToAppendImage },
    { "UnableToAssignProfile", MGK_ImageErrorUnableToAssignProfile },
    { "UnableToAverageImage", MGK_ImageErrorUnableToAverageImage },
    { "UnableToCoalesceImage", MGK_ImageErrorUnableToCoalesceImage },
    { "UnableToCompareImages", MGK_ImageErrorUnableToCompareImages },
    { "UnableToCreateImageMosaic", MGK_ImageErrorUnableToCreateImageMosaic },
    { "UnableToCreateStereoImage", MGK_ImageErrorUnableToCreateStereoImage },
    { "UnableToDeconstructImageSequence", MGK_ImageErrorUnableToDeconstructImageSequence },
    { "UnableToExportImagePixels", MGK_ImageErrorUnableToExportImagePixels },
    { "UnableToFlattenImage", MGK_ImageErrorUnableToFlattenImage },
    { "UnableToGetClipMask", MGK_ImageErrorUnableToGetClipMask },
    { "UnableToGetCompositeMask", MGK_ImageErrorUnableToGetCompositeMask },
    { "UnableToHandleImageChannel", MGK_ImageErrorUnableToHandleImageChannel },
    { "UnableToImportImagePixels", MGK_ImageErrorUnableToImportImagePixels },
    { "UnableToResizeImage", MGK_ImageErrorUnableToResizeImage },
    { "UnableToSegmentImage", MGK_ImageErrorUnableToSegmentImage },
    { "UnableToSetClipMask", MGK_ImageErrorUnableToSetClipMask },
    { "UnableToSetCompositeMask", MGK_ImageErrorUnableToSetCompositeMask },
    { "UnableToShearImage", MGK_ImageErrorUnableToShearImage },
    { "WidthOrHeightExceedsLimit", MGK_ImageErrorWidthOrHeightExceedsLimit },
    { "UnableToPersistKey", MGK_ImageFatalErrorUnableToPersistKey },
    { "Default", MGK_ImageWarningDefault },
    { "FPXLibraryIsNotAvailable", MGK_MissingDelegateErrorFPXLibraryIsNotAvailable },
    { "FreeTypeLibraryIsNotAvailable", MGK_MissingDelegateErrorFreeTypeLibraryIsNotAvailable },
    { "JPEGLibraryIsNotAvailable", MGK_MissingDelegateErrorJPEGLibraryIsNotAvailable },
    { "LCMSLibraryIsNotAvailable", MGK_MissingDelegateErrorLCMSLibraryIsNotAvailable },
    { "LZWEncodingNotEnabled", MGK_MissingDelegateErrorLZWEncodingNotEnabled },
    { "NoDecodeDelegateForThisImageFormat", MGK_MissingDelegateErrorNoDecodeDelegateForThisImageFormat },
    { "NoEncodeDelegateForThisImageFormat", MGK_MissingDelegateErrorNoEncodeDelegateForThisImageFormat },
    { "TIFFLibraryIsNotAvailable", MGK_MissingDelegateErrorTIFFLibraryIsNotAvailable },
    { "XMLLibraryIsNotAvailable", MGK_MissingDelegateErrorXMLLibraryIsNotAvailable },
    { "XWindowLibraryIsNotAvailable", MGK_MissingDelegateErrorXWindowLibraryIsNotAvailable },
    { "ZipLibraryIsNotAvailable", MGK_MissingDelegateErrorZipLibraryIsNotAvailable },
    { "Default", MGK_MissingDelegateFatalErrorDefault },
    { "Default", MGK_MissingDelegateWarningDefault },
    { "FailedToCloseModule", MGK_ModuleErrorFailedToCloseModule },
    { "FailedToFindSymbol", MGK_ModuleErrorFailedToFindSymbol },
    { "UnableToLoadModule", MGK_ModuleErrorUnableToLoadModule },
    { "UnableToRegisterImageFormat", MGK_ModuleErrorUnableToRegisterImageFormat },
    { "UnrecognizedModule", MGK_ModuleErrorUnrecognizedModule },
    { "UnableToInitializeModuleLoader", MGK_ModuleFatalErrorUnableToInitializeModuleLoader },
    { "Default", MGK_ModuleWarningDefault },
    { "Default", MGK_MonitorErrorDefault },
    { "Default", MGK_MonitorFatalErrorDefault },
    { "UserRequestedTerminationBySignal", MGK_MonitorFatalErrorUserRequestedTerminationBySignal },
    { "Default", MGK_MonitorWarningDefault },
    { "BevelWidthIsNegative", MGK_OptionErrorBevelWidthIsNegative },
    { "ColorSeparatedImageRequired", MGK_OptionErrorColorSeparatedImageRequired },
    { "DisplayGammaIsOutOfRange", MGK_OptionErrorDisplayGammaIsOutOfRange },
    { "FilmGammaIsOutOfRange", MGK_OptionErrorFilmGammaIsOutOfRange },
    { "FrameIsLessThanImageSize", MGK_OptionErrorFrameIsLessThanImageSize },
    { "GeometryDimensionsAreZero", MGK_OptionErrorGeometryDimensionsAreZero },
    { "GeometryDoesNotContainImage", MGK_OptionErrorGeometryDoesNotContainImage },
    { "HaldClutImageDimensionsInvalid", MGK_OptionErrorHaldClutImageDimensionsInvalid },
    { "ImagesAreNotTheSameSize", MGK_OptionErrorImagesAreNotTheSameSize },
    { "ImageSizeMustExceedBevelWidth", MGK_OptionErrorImageSizeMustExceedBevelWidth },
    { "ImageSmallerThanKernelWidth", MGK_OptionErrorImageSmallerThanKernelWidth },
    { "ImageSmallerThanRadius", MGK_OptionErrorImageSmallerThanRadius },
    { "ImageWidthsOrHeightsDiffer", MGK_OptionErrorImageWidthsOrHeightsDiffer },
    { "InputImagesAlreadySpecified", MGK_OptionErrorInputImagesAlreadySpecified },
    { "InvalidSubimageSpecification", MGK_OptionErrorInvalidSubimageSpecification },
    { "KernelRadiusIsTooSmall", MGK_OptionErrorKernelRadiusIsTooSmall },
    { "KernelWidthMustBeAnOddNumber", MGK_OptionErrorKernelWidthMustBeAnOddNumber },
    { "MatrixIsNotSquare", MGK_OptionErrorMatrixIsNotSquare },
    { "MatrixOrderOutOfRange", MGK_OptionErrorMatrixOrderOutOfRange },
    { "MissingAnImageFilename", MGK_OptionErrorMissingAnImageFilename },
    { "MissingArgument", MGK_OptionErrorMissingArgument },
    { "MustSpecifyAnImageName", MGK_OptionErrorMustSpecifyAnImageName },
    { "MustSpecifyImageSize", MGK_OptionErrorMustSpecifyImageSize },
    { "NoBlobDefined", MGK_OptionErrorNoBlobDefined },
    { "NoImagesDefined", MGK_OptionErrorNoImagesDefined },
    { "NonzeroWidthAndHeightRequired", MGK_OptionErrorNonzeroWidthAndHeightRequired },
    { "NoProfileNameWasGiven", MGK_OptionErrorNoProfileNameWasGiven },
    { "NullBlobArgument", MGK_OptionErrorNullBlobArgument },
    { "ReferenceBlackIsOutOfRange", MGK_OptionErrorReferenceBlackIsOutOfRange },
    { "ReferenceImageRequired", MGK_OptionErrorReferenceImageRequired },
    { "ReferenceIsNotMyType", MGK_OptionErrorReferenceIsNotMyType },
    { "ReferenceWhiteIsOutOfRange", MGK_OptionErrorReferenceWhiteIsOutOfRange },
    { "RegionAreaExceedsLimit", MGK_OptionErrorRegionAreaExceedsLimit },
    { "RequestDidNotReturnAnImage", MGK_OptionErrorRequestDidNotReturnAnImage },
    { "SoftClipOffsetIsOutOfRange", MGK_OptionErrorSoftClipOffsetIsOutOfRange },
    { "SteganoImageRequired", MGK_OptionErrorSteganoImageRequired },
    { "StereoImageRequired", MGK_OptionErrorStereoImageRequired },
    { "SubimageSpecificationReturnsNoImages", MGK_OptionErrorSubimageSpecificationReturnsNoImages },
    { "TileNotBoundedByImageDimensions", MGK_OptionErrorTileNotBoundedByImageDimensions },
    { "UnableToAddOrRemoveProfile", MGK_OptionErrorUnableToAddOrRemoveProfile },
    { "UnableToAverageImageSequence", MGK_OptionErrorUnableToAverageImageSequence },
    { "UnableToBlurImage", MGK_OptionErrorUnableToBlurImage },
    { "UnableToChopImage", MGK_OptionErrorUnableToChopImage },
    { "UnableToCineonLogRGBTransformColorspace", MGK_OptionErrorUnableToCineonLogRGBTransformColorspace },
    { "UnableToColorMatrixImage", MGK_OptionErrorUnableToColorMatrixImage },
    { "UnableToConstituteImage", MGK_OptionErrorUnableToConstituteImage },
    { "UnableToConvolveImage", MGK_OptionErrorUnableToConvolveImage },
    { "UnableToEdgeImage", MGK_OptionErrorUnableToEdgeImage },
    { "UnableToEqualizeImage", MGK_OptionErrorUnableToEqualizeImage },
    { "UnableToFilterImage", MGK_OptionErrorUnableToFilterImage },
    { "UnableToFormatImageMetadata", MGK_OptionErrorUnableToFormatImageMetadata },
    { "UnableToFrameImage", MGK_OptionErrorUnableToFrameImage },
    { "UnableToOilPaintImage", MGK_OptionErrorUnableToOilPaintImage },
    { "UnableToPaintImage", MGK_OptionErrorUnableToPaintImage },
    { "UnableToRaiseImage", MGK_OptionErrorUnableToRaiseImage },
    { "UnableToSharpenImage", MGK_OptionErrorUnableToSharpenImage },
    { "UnableToSpreadImage", MGK_OptionErrorUnableToSpreadImage },
    { "UnableToThresholdImage", MGK_OptionErrorUnableToThresholdImage },
    { "UnableToWaveImage", MGK_OptionErrorUnableToWaveImage },
    { "UnrecognizedAttribute", MGK_OptionErrorUnrecognizedAttribute },
    { "UnrecognizedChannelType", MGK_OptionErrorUnrecognizedChannelType },
    { "UnrecognizedColor", MGK_OptionErrorUnrecognizedColor },
    { "UnrecognizedColormapType", MGK_OptionErrorUnrecognizedColormapType },
    { "UnrecognizedColorspace", MGK_OptionErrorUnrecognizedColorspace },
    { "UnrecognizedCommand", MGK_OptionErrorUnrecognizedCommand },
    { "UnrecognizedComposeOperator", MGK_OptionErrorUnrecognizedComposeOperator },
    { "UnrecognizedDisposeMethod", MGK_OptionErrorUnrecognizedDisposeMethod },
    { "UnrecognizedElement", MGK_OptionErrorUnrecognizedElement },
    { "UnrecognizedEndianType", MGK_OptionErrorUnrecognizedEndianType },
    { "UnrecognizedGravityType", MGK_OptionErrorUnrecognizedGravityType },
    { "UnrecognizedHighlightStyle", MGK_OptionErrorUnrecognizedHighlightStyle },
    { "UnrecognizedImageCompression", MGK_OptionErrorUnrecognizedImageCompression },
    { "UnrecognizedImageFilter", MGK_OptionErrorUnrecognizedImageFilter },
    { "UnrecognizedImageFormat", MGK_OptionErrorUnrecognizedImageFormat },
    { "UnrecognizedImageMode", MGK_OptionErrorUnrecognizedImageMode },
    { "UnrecognizedImageType", MGK_OptionErrorUnrecognizedImageType },
    { "UnrecognizedIntentType", MGK_OptionErrorUnrecognizedIntentType },
    { "UnrecognizedInterlaceType", MGK_OptionErrorUnrecognizedInterlaceType },
    { "UnrecognizedListType", MGK_OptionErrorUnrecognizedListType },
    { "UnrecognizedMetric", MGK_OptionErrorUnrecognizedMetric },
    { "UnrecognizedModeType", MGK_OptionErrorUnrecognizedModeType },
    { "UnrecognizedNoiseType", MGK_OptionErrorUnrecognizedNoiseType },
    { "UnrecognizedOperator", MGK_OptionErrorUnrecognizedOperator },
    { "UnrecognizedOption", MGK_OptionErrorUnrecognizedOption },
    { "UnrecognizedPerlMagickMethod", MGK_OptionErrorUnrecognizedPerlMagickMethod },
    { "UnrecognizedPixelMap", MGK_OptionErrorUnrecognizedPixelMap },
    { "UnrecognizedPreviewType", MGK_OptionErrorUnrecognizedPreviewType },
    { "UnrecognizedResourceType", MGK_OptionErrorUnrecognizedResourceType },
    { "UnrecognizedType", MGK_OptionErrorUnrecognizedType },
    { "UnrecognizedUnitsType", MGK_OptionErrorUnrecognizedUnitsType },
    { "UnrecognizedVirtualPixelMethod", MGK_OptionErrorUnrecognizedVirtualPixelMethod },
    { "UnsupportedSamplingFactor", MGK_OptionErrorUnsupportedSamplingFactor },
    { "UsageError", MGK_OptionErrorUsageError },
    { "InvalidColorspaceType", MGK_OptionFatalErrorInvalidColorspaceType },
    { "InvalidEndianType", MGK_OptionFatalErrorInvalidEndianType },
    { "InvalidImageType", MGK_OptionFatalErrorInvalidImageType },
    { "InvalidInterlaceType", MGK_OptionFatalErrorInvalidInterlaceType },
    { "MissingAnImageFilename", MGK_OptionFatalErrorMissingAnImageFilename },
    { "MissingArgument", MGK_OptionFatalErrorMissingArgument },
    { "NoImagesWereLoaded", MGK_OptionFatalErrorNoImagesWereLoaded },
    { "OptionLengthExceedsLimit", MGK_OptionFatalErrorOptionLengthExceedsLimit },
    { "RequestDidNotReturnAnImage", MGK_OptionFatalErrorRequestDidNotReturnAnImage },
    { "UnableToOpenXServer", MGK_OptionFatalErrorUnableToOpenXServer },
    { "UnableToPersistKey", MGK_OptionFatalErrorUnableToPersistKey },
    { "UnrecognizedColormapType", MGK_OptionFatalErrorUnrecognizedColormapType },
    { "UnrecognizedColorspaceType", MGK_OptionFatalErrorUnrecognizedColorspaceType },
    { "UnrecognizedDisposeMethod", MGK_OptionFatalErrorUnrecognizedDisposeMethod },
    { "UnrecognizedEndianType", MGK_OptionFatalErrorUnrecognizedEndianType },
    { "UnrecognizedFilterType", MGK_OptionFatalErrorUnrecognizedFilterType },
    { "UnrecognizedImageCompressionType", MGK_OptionFatalErrorUnrecognizedImageCompressionType },
    { "UnrecognizedImageType", MGK_OptionFatalErrorUnrecognizedImageType },
    { "UnrecognizedInterlaceType", MGK_OptionFatalErrorUnrecognizedInterlaceType },
    { "UnrecognizedOption", MGK_OptionFatalErrorUnrecognizedOption },
    { "UnrecognizedResourceType", MGK_OptionFatalErrorUnrecognizedResourceType },
    { "UnrecognizedVirtualPixelMethod", MGK_OptionFatalErrorUnrecognizedVirtualPixelMethod },
    { "UnrecognizedColor", MGK_OptionWarningUnrecognizedColor },
    { "ImageExpected", MGK_RegistryErrorImageExpected },
    { "ImageInfoExpected", MGK_RegistryErrorImageInfoExpected },
    { "StructureSizeMismatch", MGK_RegistryErrorStructureSizeMismatch },
    { "UnableToGetRegistryID", MGK_RegistryErrorUnableToGetRegistryID },
    { "UnableToLocateImage", MGK_RegistryErrorUnableToLocateImage },
    { "UnableToSetRegistry", MGK_RegistryErrorUnableToSetRegistry },
    { "Default", MGK_RegistryFatalErrorDefault },
    { "Default", MGK_RegistryWarningDefault },
    { "CacheResourcesExhausted", MGK_ResourceLimitErrorCacheResourcesExhausted },
    { "ImagePixelHeightLimitExceeded", MGK_ResourceLimitErrorImagePixelHeightLimitExceeded },
    { "ImagePixelLimitExceeded", MGK_ResourceLimitErrorImagePixelLimitExceeded },
    { "ImagePixelWidthLimitExceeded", MGK_ResourceLimitErrorImagePixelWidthLimitExceeded },
    { "ImagesLimitExceeded", MGK_ResourceLimitErrorImagesLimitExceeded },
    { "MemoryAllocationFailed", MGK_ResourceLimitErrorMemoryAllocationFailed },
    { "NexusPixelHeightLimitExceeded", MGK_ResourceLimitErrorNexusPixelHeightLimitExceeded },
    { "NexusPixelLimitExceeded", MGK_ResourceLimitErrorNexusPixelLimitExceeded },
    { "NexusPixelWidthLimitExceeded", MGK_ResourceLimitErrorNexusPixelWidthLimitExceeded },
    { "NoPixelsDefinedInCache", MGK_ResourceLimitErrorNoPixelsDefinedInCache },
    { "PixelCacheAllocationFailed", MGK_ResourceLimitErrorPixelCacheAllocationFailed },
    { "ProfilesLimitExceeded", MGK_ResourceLimitErrorProfilesLimitExceeded },
    { "ReadLimitExceeded", MGK_ResourceLimitErrorReadLimitExceeded },
    { "UnableToAddColorProfile", MGK_ResourceLimitErrorUnableToAddColorProfile },
    { "UnableToAddGenericProfile", MGK_ResourceLimitErrorUnableToAddGenericProfile },
    { "UnableToAddIPTCProfile", MGK_ResourceLimitErrorUnableToAddIPTCProfile },
    { "UnableToAddOrRemoveProfile", MGK_ResourceLimitErrorUnableToAddOrRemoveProfile },
    { "UnableToAllocateCoefficients", MGK_ResourceLimitErrorUnableToAllocateCoefficients },
    { "UnableToAllocateColormap", MGK_ResourceLimitErrorUnableToAllocateColormap },
    { "UnableToAllocateICCProfile", MGK_ResourceLimitErrorUnableToAllocateICCProfile },
    { "UnableToAllocateImage", MGK_ResourceLimitErrorUnableToAllocateImage },
    { "UnableToAllocateString", MGK_ResourceLimitErrorUnableToAllocateString },
    { "UnableToAnnotateImage", MGK_ResourceLimitErrorUnableToAnnotateImage },
    { "UnableToAverageImageSequence", MGK_ResourceLimitErrorUnableToAverageImageSequence },
    { "UnableToCloneDrawingContext", MGK_ResourceLimitErrorUnableToCloneDrawingContext },
    { "UnableToCloneImage", MGK_ResourceLimitErrorUnableToCloneImage },
    { "UnableToComputeImageSignature", MGK_ResourceLimitErrorUnableToComputeImageSignature },
    { "UnableToConstituteImage", MGK_ResourceLimitErrorUnableToConstituteImage },
    { "UnableToConvertFont", MGK_ResourceLimitErrorUnableToConvertFont },
    { "UnableToConvertStringToTokens", MGK_ResourceLimitErrorUnableToConvertStringToTokens },
    { "UnableToCreateColormap", MGK_ResourceLimitErrorUnableToCreateColormap },
    { "UnableToCreateColorTransform", MGK_ResourceLimitErrorUnableToCreateColorTransform },
    { "UnableToCreateCommandWidget", MGK_ResourceLimitErrorUnableToCreateCommandWidget },
    { "UnableToCreateImageGroup", MGK_ResourceLimitErrorUnableToCreateImageGroup },
    { "UnableToCreateImageMontage", MGK_ResourceLimitErrorUnableToCreateImageMontage },
    { "UnableToCreateXWindow", MGK_ResourceLimitErrorUnableToCreateXWindow },
    { "UnableToCropImage", MGK_ResourceLimitErrorUnableToCropImage },
    { "UnableToDespeckleImage", MGK_ResourceLimitErrorUnableToDespeckleImage },
    { "UnableToDetermineImageClass", MGK_ResourceLimitErrorUnableToDetermineImageClass },
    { "UnableToDetermineTheNumberOfImageColors", MGK_ResourceLimitErrorUnableToDetermineTheNumberOfImageColors },
    { "UnableToDitherImage", MGK_ResourceLimitErrorUnableToDitherImage },
    { "UnableToDrawOnImage", MGK_ResourceLimitErrorUnableToDrawOnImage },
    { "UnableToEdgeImage", MGK_ResourceLimitErrorUnableToEdgeImage },
    { "UnableToEmbossImage", MGK_ResourceLimitErrorUnableToEmbossImage },
    { "UnableToEnhanceImage", MGK_ResourceLimitErrorUnableToEnhanceImage },
    { "UnableToFloodfillImage", MGK_ResourceLimitErrorUnableToFloodfillImage },
    { "UnableToGammaCorrectImage", MGK_ResourceLimitErrorUnableToGammaCorrectImage },
    { "UnableToGetBestIconSize", MGK_ResourceLimitErrorUnableToGetBestIconSize },
    { "UnableToGetFromRegistry", MGK_ResourceLimitErrorUnableToGetFromRegistry },
    { "UnableToGetPackageInfo", MGK_ResourceLimitErrorUnableToGetPackageInfo },
    { "UnableToInterpretMSLImage", MGK_ResourceLimitErrorUnableToInterpretMSLImage },
    { "UnableToLevelImage", MGK_ResourceLimitErrorUnableToLevelImage },
    { "UnableToMagnifyImage", MGK_ResourceLimitErrorUnableToMagnifyImage },
    { "UnableToManageColor", MGK_ResourceLimitErrorUnableToManageColor },
    { "UnableToMapImage", MGK_ResourceLimitErrorUnableToMapImage },
    { "UnableToMapImageSequence", MGK_ResourceLimitErrorUnableToMapImageSequence },
    { "UnableToMedianFilterImage", MGK_ResourceLimitErrorUnableToMedianFilterImage },
    { "UnableToMotionBlurImage", MGK_ResourceLimitErrorUnableToMotionBlurImage },
    { "UnableToNoiseFilterImage", MGK_ResourceLimitErrorUnableToNoiseFilterImage },
    { "UnableToNormalizeImage", MGK_ResourceLimitErrorUnableToNormalizeImage },
    { "UnableToOpenColorProfile", MGK_ResourceLimitErrorUnableToOpenColorProfile },
    { "UnableToQuantizeImage", MGK_ResourceLimitErrorUnableToQuantizeImage },
    { "UnableToQuantizeImageSequence", MGK_ResourceLimitErrorUnableToQuantizeImageSequence },
    { "UnableToReadTextChunk", MGK_ResourceLimitErrorUnableToReadTextChunk },
    { "UnableToReadXImage", MGK_ResourceLimitErrorUnableToReadXImage },
    { "UnableToReadXServerColormap", MGK_ResourceLimitErrorUnableToReadXServerColormap },
    { "UnableToResizeImage", MGK_ResourceLimitErrorUnableToResizeImage },
    { "UnableToRotateImage", MGK_ResourceLimitErrorUnableToRotateImage },
    { "UnableToSampleImage", MGK_ResourceLimitErrorUnableToSampleImage },
    { "UnableToScaleImage", MGK_ResourceLimitErrorUnableToScaleImage },
    { "UnableToSegmentImage", MGK_ResourceLimitErrorUnableToSegmentImage },
    { "UnableToSelectImage", MGK_ResourceLimitErrorUnableToSelectImage },
    { "UnableToSetImageBackgroundColor", MGK_ResourceLimitErrorUnableToSetImageBackgroundColor },
    { "UnableToSharpenImage", MGK_ResourceLimitErrorUnableToSharpenImage },
    { "UnableToShaveImage", MGK_ResourceLimitErrorUnableToShaveImage },
    { "UnableToShearImage", MGK_ResourceLimitErrorUnableToShearImage },
    { "UnableToSortImageColormap", MGK_ResourceLimitErrorUnableToSortImageColormap },
    { "UnableToThresholdImage", MGK_ResourceLimitErrorUnableToThresholdImage },
    { "UnableToTransformColorspace", MGK_ResourceLimitErrorUnableToTransformColorspace },
    { "WriteLimitExceeded", MGK_ResourceLimitErrorWriteLimitExceeded },
    { "MemoryAllocationFailed", MGK_ResourceLimitFatalErrorMemoryAllocationFailed },
    { "SemaporeOperationFailed", MGK_ResourceLimitFatalErrorSemaporeOperationFailed },
    { "UnableToAllocateAscii85Info", MGK_ResourceLimitFatalErrorUnableToAllocateAscii85Info },
    { "UnableToAllocateCacheInfo", MGK_ResourceLimitFatalErrorUnableToAllocateCacheInfo },
    { "UnableToAllocateCacheView", MGK_ResourceLimitFatalErrorUnableToAllocateCacheView },
    { "UnableToAllocateColorInfo", MGK_ResourceLimitFatalErrorUnableToAllocateColorInfo },
    { "UnableToAllocateDashPattern", MGK_ResourceLimitFatalErrorUnableToAllocateDashPattern },
    { "UnableToAllocateDelegateInfo", MGK_ResourceLimitFatalErrorUnableToAllocateDelegateInfo },
    { "UnableToAllocateDrawContext", MGK_ResourceLimitFatalErrorUnableToAllocateDrawContext },
    { "UnableToAllocateDrawInfo", MGK_ResourceLimitFatalErrorUnableToAllocateDrawInfo },
    { "UnableToAllocateDrawingWand", MGK_ResourceLimitFatalErrorUnableToAllocateDrawingWand },
    { "UnableToAllocateGammaMap", MGK_ResourceLimitFatalErrorUnableToAllocateGammaMap },
    { "UnableToAllocateImage", MGK_ResourceLimitFatalErrorUnableToAllocateImage },
    { "UnableToAllocateImagePixels", MGK_ResourceLimitFatalErrorUnableToAllocateImagePixels },
    { "UnableToAllocateLogInfo", MGK_ResourceLimitFatalErrorUnableToAllocateLogInfo },
    { "UnableToAllocateMagicInfo", MGK_ResourceLimitFatalErrorUnableToAllocateMagicInfo },
    { "UnableToAllocateMagickInfo", MGK_ResourceLimitFatalErrorUnableToAllocateMagickInfo },
    { "UnableToAllocateMagickMap", MGK_ResourceLimitFatalErrorUnableToAllocateMagickMap },
    { "UnableToAllocateModuleInfo", MGK_ResourceLimitFatalErrorUnableToAllocateModuleInfo },
    { "UnableToAllocateMontageInfo", MGK_ResourceLimitFatalErrorUnableToAllocateMontageInfo },
    { "UnableToAllocateQuantizeInfo", MGK_ResourceLimitFatalErrorUnableToAllocateQuantizeInfo },
    { "UnableToAllocateRandomKernel", MGK_ResourceLimitFatalErrorUnableToAllocateRandomKernel },
    { "UnableToAllocateRegistryInfo", MGK_ResourceLimitFatalErrorUnableToAllocateRegistryInfo },
    { "UnableToAllocateSemaphoreInfo", MGK_ResourceLimitFatalErrorUnableToAllocateSemaphoreInfo },
    { "UnableToAllocateString", MGK_ResourceLimitFatalErrorUnableToAllocateString },
    { "UnableToAllocateTypeInfo", MGK_ResourceLimitFatalErrorUnableToAllocateTypeInfo },
    { "UnableToAllocateWand", MGK_ResourceLimitFatalErrorUnableToAllocateWand },
    { "UnableToAnimateImageSequence", MGK_ResourceLimitFatalErrorUnableToAnimateImageSequence },
    { "UnableToCloneBlobInfo", MGK_ResourceLimitFatalErrorUnableToCloneBlobInfo },
    { "UnableToCloneCacheInfo", MGK_ResourceLimitFatalErrorUnableToCloneCacheInfo },
    { "UnableToCloneImage", MGK_ResourceLimitFatalErrorUnableToCloneImage },
    { "UnableToCloneImageInfo", MGK_ResourceLimitFatalErrorUnableToCloneImageInfo },
    { "UnableToConcatenateString", MGK_ResourceLimitFatalErrorUnableToConcatenateString },
    { "UnableToConvertText", MGK_ResourceLimitFatalErrorUnableToConvertText },
    { "UnableToCreateColormap", MGK_ResourceLimitFatalErrorUnableToCreateColormap },
    { "UnableToDestroySemaphore", MGK_ResourceLimitFatalErrorUnableToDestroySemaphore },
    { "UnableToDisplayImage", MGK_ResourceLimitFatalErrorUnableToDisplayImage },
    { "UnableToEscapeString", MGK_ResourceLimitFatalErrorUnableToEscapeString },
    { "UnableToInitializeSemaphore", MGK_ResourceLimitFatalErrorUnableToInitializeSemaphore },
    { "UnableToInterpretMSLImage", MGK_ResourceLimitFatalErrorUnableToInterpretMSLImage },
    { "UnableToLockSemaphore", MGK_ResourceLimitFatalErrorUnableToLockSemaphore },
    { "UnableToObtainRandomEntropy", MGK_ResourceLimitFatalErrorUnableToObtainRandomEntropy },
    { "UnableToUnlockSemaphore", MGK_ResourceLimitFatalErrorUnableToUnlockSemaphore },
    { "MemoryAllocationFailed", MGK_ResourceLimitWarningMemoryAllocationFailed },
    { "ImageDoesNotContainTheStreamGeometry", MGK_StreamErrorImageDoesNotContainTheStreamGeometry },
    { "NoStreamHandlerIsDefined", MGK_StreamErrorNoStreamHandlerIsDefined },
    { "PixelCacheIsNotOpen", MGK_StreamErrorPixelCacheIsNotOpen },
    { "UnableToAcquirePixelStream", MGK_StreamErrorUnableToAcquirePixelStream },
    { "UnableToSetPixelStream", MGK_StreamErrorUnableToSetPixelStream },
    { "UnableToSyncPixelStream", MGK_StreamErrorUnableToSyncPixelStream },
    { "Default", MGK_StreamFatalErrorDefault },
    { "Default", MGK_StreamWarningDefault },
    { "FontNotSpecified", MGK_TypeErrorFontNotSpecified },
    { "FontSubstitutionRequired", MGK_TypeErrorFontSubstitutionRequired },
    { "UnableToGetTypeMetrics", MGK_TypeErrorUnableToGetTypeMetrics },
    { "UnableToInitializeFreetypeLibrary", MGK_TypeErrorUnableToInitializeFreetypeLibrary },
    { "UnableToReadFont", MGK_TypeErrorUnableToReadFont },
    { "UnrecognizedFontEncoding", MGK_TypeErrorUnrecognizedFontEncoding },
    { "Default", MGK_TypeFatalErrorDefault },
    { "Default", MGK_TypeWarningDefault },
    { "InvalidColormapIndex", MGK_WandErrorInvalidColormapIndex },
    { "WandAPINotImplemented", MGK_WandErrorWandAPINotImplemented },
    { "WandContainsNoImageIndexs", MGK_WandErrorWandContainsNoImageIndexs },
    { "WandContainsNoImages", MGK_WandErrorWandContainsNoImages },
    { "ColorIsNotKnownToServer", MGK_XServerErrorColorIsNotKnownToServer },
    { "NoWindowWithSpecifiedIDExists", MGK_XServerErrorNoWindowWithSpecifiedIDExists },
    { "StandardColormapIsNotInitialized", MGK_XServerErrorStandardColormapIsNotInitialized },
    { "UnableToConnectToRemoteDisplay", MGK_XServerErrorUnableToConnectToRemoteDisplay },
    { "UnableToCreateBitmap", MGK_XServerErrorUnableToCreateBitmap },
    { "UnableToCreateColormap", MGK_XServerErrorUnableToCreateColormap },
    { "UnableToCreatePixmap", MGK_XServerErrorUnableToCreatePixmap },
    { "UnableToCreateProperty", MGK_XServerErrorUnableToCreateProperty },
    { "UnableToCreateStandardColormap", MGK_XServerErrorUnableToCreateStandardColormap },
    { "UnableToDisplayImageInfo", MGK_XServerErrorUnableToDisplayImageInfo },
    { "UnableToGetProperty", MGK_XServerErrorUnableToGetProperty },
    { "UnableToGetStandardColormap", MGK_XServerErrorUnableToGetStandardColormap },
    { "UnableToGetVisual", MGK_XServerErrorUnableToGetVisual },
    { "UnableToGrabMouse", MGK_XServerErrorUnableToGrabMouse },
    { "UnableToLoadFont", MGK_XServerErrorUnableToLoadFont },
    { "UnableToMatchVisualToStandardColormap", MGK_XServerErrorUnableToMatchVisualToStandardColormap },
    { "UnableToOpenXServer", MGK_XServerErrorUnableToOpenXServer },
    { "UnableToReadXAttributes", MGK_XServerErrorUnableToReadXAttributes },
    { "UnableToReadXWindowImage", MGK_XServerErrorUnableToReadXWindowImage },
    { "UnrecognizedColormapType", MGK_XServerErrorUnrecognizedColormapType },
    { "UnrecognizedGravityType", MGK_XServerErrorUnrecognizedGravityType },
    { "UnrecognizedVisualSpecifier", MGK_XServerErrorUnrecognizedVisualSpecifier },
    { "UnableToAllocateXHints", MGK_XServerFatalErrorUnableToAllocateXHints },
    { "UnableToCreateCursor", MGK_XServerFatalErrorUnableToCreateCursor },
    { "UnableToCreateGraphicContext", MGK_XServerFatalErrorUnableToCreateGraphicContext },
    { "UnableToCreateStandardColormap", MGK_XServerFatalErrorUnableToCreateStandardColormap },
    { "UnableToCreateTextProperty", MGK_XServerFatalErrorUnableToCreateTextProperty },
    { "UnableToCreateXImage", MGK_XServerFatalErrorUnableToCreateXImage },
    { "UnableToCreateXPixmap", MGK_XServerFatalErrorUnableToCreateXPixmap },
    { "UnableToCreateXWindow", MGK_XServerFatalErrorUnableToCreateXWindow },
    { "UnableToDisplayImage", MGK_XServerFatalErrorUnableToDisplayImage },
    { "UnableToDitherImage", MGK_XServerFatalErrorUnableToDitherImage },
    { "UnableToGetPixelInfo", MGK_XServerFatalErrorUnableToGetPixelInfo },
    { "UnableToGetVisual", MGK_XServerFatalErrorUnableToGetVisual },
    { "UnableToLoadFont", MGK_XServerFatalErrorUnableToLoadFont },
    { "UnableToMakeXWindow", MGK_XServerFatalErrorUnableToMakeXWindow },
    { "UnableToOpenXServer", MGK_XServerFatalErrorUnableToOpenXServer },
    { "UnableToViewFonts", MGK_XServerFatalErrorUnableToViewFonts },
    { "UnableToGetVisual", MGK_XServerWarningUnableToGetVisual },
    { "UsingDefaultVisual", MGK_XServerWarningUsingDefaultVisual },
    { "", 0 }
  };
#endif /* if defined(_INCLUDE_TAGMAP_TABLE_) */

#if defined(_INCLUDE_MESSAGE_TABLE_)
static const char message_dat[] =
    "%1\0"
    "Unable to create blob\0"
    "Unable to deduce image format\0"
    "Unable to obtain current offset\0"
    "Unable to open file\0"
    "Unable to read file\0"
    "Unable to read to offset\0"
    "Unable to seek to offset\0"
    "Unable to write blob\0"
    "Unrecognized image format\0"
    "default error\0"
    "default warning\0"
    "Cache nexus contains no pixels\0"
    "Inconsistent persistent cache depth\0"
    "Pixel cache dimensions incompatible with image dimensions\0"
    "Pixel cache is not open\0"
    "Unable to allocate cache view\0"
    "Unable to clone cache\0"
    "Unable to extend cache\0"
    "Unable to get cache nexus\0"
    "Unable to get pixels from cache\0"
    "Unable to open cache\0"
    "Unable to persist pixel cache\0"
    "Unable to read pixel cache\0"
    "Unable to sync cache (check temporary file disk space)\0"
    "disk allocation failed\0"
    "Unable to extend pixel cache\0"
    "default warning\0"
    "Arithmetic overflow\0"
    "Colormap size exceeds limit\0"
    "Colormap type not supported\0"
    "Colorspace model is not supported\0"
    "Color type not supported\0"
    "Compression not valid\0"
    "Data encoding scheme is not supported\0"
    "Data storage type is not supported\0"
    "Coder did not return an image (this is a bug, please report it!)\0"
    "Delta-PNG is not supported\0"
    "Division by zero\0"
    "Encrypted WPG image file not supported\0"
    "Fractal compression not supported\0"
    "Image column or row size is not supported\0"
    "Image does not have a matte channel\0"
    "Image is not tiles\0"
    "Image type not supported\0"
    "Incompatible size of double\0"
    "Irregular channel geometry not supported\0"
    "JNG compression is not supported\0"
    "JPEG compression is not supported\0"
    "JPEG embedding failed\0"
    "JXL decoder API failure\0"
    "JXL encoder API failure\0"
    "Location type is not supported\0"
    "Map storage type is not supported\0"
    "MSB order not supported bitmap\0"
    "Multi-dimensional matrices are not supported\0"
    "Multiple record list not supported\0"
    "No 8BIM data is available\0"
    "No APP1 data is available\0"
    "No bitmap on clipboard\0"
    "No color profile available\0"
    "No data returned\0"
    "No image vector graphics\0"
    "No IPTC info was found\0"
    "No IPTC profile available\0"
    "Number of images is not supported\0"
    "Only continuous tone picture supported\0"
    "Only level zero files Supported\0"
    "PNG compression is not supported\0"
    "PNG library is too old\0"
    "RLE compression not supported\0"
    "Subsampling requires that image width be evenly divisible by two\0"
    "Unable to copy profile\0"
    "Unable to create a DC\0"
    "Unable to create bitmap\0"
    "Unable to decode image\0"
    "Unable to decompress image\0"
    "Unable to get image characteristics\0"
    "Unable to Initialize FPX library\0"
    "Unable to open blob\0"
    "Unable to open file\0"
    "Unable to read aspect ratio\0"
    "Unable to read CIELAB images\0"
    "Unable to read summary info\0"
    "Unable to resize image\0"
    "Unable to set affine matrix\0"
    "Unable to set aspect ratio\0"
    "Unable to set color twist\0"
    "Unable to set contrast\0"
    "Unable to set filtering value\0"
    "Unable to set image comment\0"
    "Unable to set image opacity\0"
    "Unable to set image title\0"
    "Unable to set image type\0"
    "Unable to set JPEG level\0"
    "Unable to set region of interest\0"
    "Unable to set summary info\0"
    "Unable to transform image colorspace\0"
    "Unable to translate text\0"
    "Unable to write MPEG parameters\0"
    "Unable to write to temporary file\0"
    "Unable to zip-compress image\0"
    "Unsupported bits per sample\0"
    "Unsupported cell type in the matrix\0"
    "Unsupported number of columns\0"
    "Unsupported number of rows\0"
    "Unsupported samples per pixel\0"
    "WebP decoding failed: user abort\0"
    "WebP encoding failed: unknown reason\0"
    "WebP encoding failed: bad dimension\0"
    "WebP encoding failed: bad write\0"
    "WebP encoding failed: bitstream out of memory\0"
    "WebP encoding failed: File too big (> 4GB)\0"
    "WebP encoding failed: invalid configuration\0"
    "WebP encoding failed: null parameter\0"
    "WebP encoding failed: out of memory\0"
    "WebP encoding failed: partition 0 overflow (> 512K)\0"
    "WebP encoding failed: partition overflow (> 16M)\0"
    "WebP encoding failed: user abort\0"
    "Invalid WebP configuration parameters supplied\0"
    "WebP failed: invalid parameter\0"
    "XML parser failure\0"
    "ZIP compression is not supported\0"
    "default error\0"
    "Lossless to lossy JPEG conversion\0"
    "include element nested too deeply\0"
    "Registry key lookup failed. Package is not properly installed on this machine.\0"
    "String token maximum length exceeded\0"
    "Unable to access configuration file\0"
    "Unable to access font file\0"
    "Unable to access log configuration file\0"
    "Unable to access module file\0"
    "default error\0"
    "Unable to change to working directory\0"
    "Unable to get current working directory\0"
    "Unable to restore current working directory\0"
    "default warning\0"
    "An error has occurred reading from file\0"
    "An error has occurred writing to file\0"
    "Colormap exceeded colors limit\0"
    "Compression not valid\0"
    "Corrupt image\0"
    "Image file or blob does not contain any image data\0"
    "Image file has no scenes\0"
    "Image type not supported\0"
    "Improper image header\0"
    "Insufficient image data in file\0"
    "Invalid colormap index\0"
    "invalid file format version\0"
    "Length and filesize do not match\0"
    "Missing a required image channel\0"
    "Negative or zero image size\0"
    "Non OS2 BMP header size less than 40\0"
    "Not enough tiles found in level\0"
    "excessive recursion detected\0"
    "Static planes value not equal to 1\0"
    "Subsampling requires that image width be evenly divisible by two\0"
    "Too much image data in file\0"
    "Unable to read colormap from dump file\0"
    "Unable to read color profile\0"
    "Unable to read extension block\0"
    "Unable to read generic profile\0"
    "Unable to read image data\0"
    "Unable to read image header\0"
    "Unable to read IPTC profile\0"
    "Unable to read pixmap from dump file\0"
    "Unable to read sub image data\0"
    "Unable to read VID image\0"
    "Unable to read window name from dump file\0"
    "Unable to runlength decode image\0"
    "Unable to uncompress image\0"
    "Unexpected end-of-file\0"
    "Unexpected sampling factor\0"
    "Unknown pattern type\0"
    "Unrecognized bits per pixel\0"
    "Unrecognized compression\0"
    "Unrecognized number of colors\0"
    "Unrecognized XWD header\0"
    "Unsupported bits per sample\0"
    "Unsupported number of planes\0"
    "Unable to persist key\0"
    "Compression not valid\0"
    "Corrupt image (some data returned)\0"
    "Improper image header\0"
    "Invalid colormap index\0"
    "Length and filesize do not match\0"
    "Negative or zero image size\0"
    "Non OS2 header size error\0"
    "Corrupt PCD image, skipping to sync byte\0"
    "Static planes value not equal to one\0"
    "Unable to parse embedded profile\0"
    "Unrecognized bits per pixel\0"
    "Unrecognized image compression\0"
    "Delegate failed\0"
    "Failed to allocate argument list.\0"
    "Failed to allocate Ghostscript interpreter.\0"
    "Failed to compute output size\0"
    "Failed to find Ghostscript (not installed?).\0"
    "Failed to render file\0"
    "Failed to scan file\0"
    "No tag found\0"
    "Postscript delegate failed\0"
    "Unable to create image\0"
    "Unable to create image component\0"
    "Unable to decode image file\0"
    "Unable to encode image file\0"
    "Unable to initialize FPX library\0"
    "Unable to initialize WMF library\0"
    "Unable to manage JP2 stream\0"
    "Unable to write SVG format\0"
    "WebP library ABI does not match header ABI (build issue!)\0"
    "default error\0"
    "default warning\0"
    "Already pushing pattern definition\0"
    "arithmetic overflow\0"
    "drawing recursion detected\0"
    "text value does not convert to float\0"
    "text value does not convert to integer\0"
    "invalid attribute argument\0"
    "invalid class name\0"
    "invalid element identifier\0"
    "invalid primitive argument\0"
    "Non-conforming drawing primitive definition\0"
    "primitive arithmetic overflow\0"
    "string truncation (length exceeds limit)\0"
    "too many coordinates\0"
    "unable to draw on image\0"
    "unable to flood-fill image with clip mask\0"
    "Unable to print\0"
    "unbalanced graphic context push-pop\0"
    "unbalanced push-pop\0"
    "unreasonable affine matrix\0"
    "unreasonable dash polygon length\0"
    "unreasonable gradient image size\0"
    "vector path truncated\0"
    "default error\0"
    "fuzzing build, unsafe for production\0"
    "Not a relative URL\0"
    "Not currently pushing pattern definition\0"
    "URL not found\0"
    "Unable to create temporary file\0"
    "Unable to open file\0"
    "Unable to write file\0"
    "default error\0"
    "default warning\0"
    "angle is discontinuous\0"
    "CMYKA image lacks an alpha channel (indexes)\0"
    "Colorspace color profile mismatch\0"
    "image colorspace differs\0"
    "image colorspace mismatch\0"
    "image difference exceeds limit\0"
    "image does not contain resolution\0"
    "image is not colormapped\0"
    "image opacity differs\0"
    "Image sequence is required\0"
    "image size differs\0"
    "Invalid colormap index\0"
    "left and right image sizes differ\0"
    "no images were found\0"
    "no images were loaded\0"
    "no [LOCALE] image attribute\0"
    "too many cluster\0"
    "unable to append image\0"
    "Unable to assign profile\0"
    "unable to average image\0"
    "unable to coalesce image\0"
    "unable to compare images\0"
    "unable to create image mosaic\0"
    "unable to create stereo image\0"
    "unable to deconstruct image sequence\0"
    "unable to export image pixels\0"
    "unable to flatten image\0"
    "Unable to get clip mask\0"
    "Unable to get composite mask\0"
    "unable to handle image channel\0"
    "unable to import image pixels\0"
    "unable to resize image\0"
    "unable to segment image\0"
    "Unable to set clip mask\0"
    "Unable to set composite mask\0"
    "unable to shear image\0"
    "width or height exceeds limit\0"
    "Unable to persist key\0"
    "default warning\0"
    "FPX library is not available\0"
    "FreeType library is not available\0"
    "JPEG compression library is not available\0"
    "LCMS encoding not enabled\0"
    "LZW encoding not enabled\0"
    "No decode delegate for this image format\0"
    "No encode delegate for this image format\0"
    "TIFF library is not available\0"
    "XML library is not available\0"
    "X Window library is not available\0"
    "ZLIB compression library is not available\0"
    "default error\0"
    "default warning\0"
    "Failed to close module\0"
    "Failed to find symbol\0"
    "Unable to load module\0"
    "Unable to register image format\0"
    "Unrecognized module\0"
    "Unable to initialize module loader\0"
    "default warning\0"
    "default error\0"
    "default error\0"
    "User requested termination (via signal)\0"
    "default warning\0"
    "bevel width is negative\0"
    "color separated image required\0"
    "Display gamma is out of range\0"
    "Film gamma is out of range\0"
    "frame is less than image size\0"
    "geometry dimensions are zero\0"
    "geometry does not contain image\0"
    "hald clut image dimensions are invalid\0"
    "images are not the same size\0"
    "size must exceed bevel width\0"
    "image smaller than kernel width\0"
    "image smaller than radius\0"
    "image widths or heights differ\0"
    "input images already specified\0"
    "Invalid subimage specification\0"
    "kernel radius is too small\0"
    "kernel width must be an odd number\0"
    "Matrix is not square (%s elements)\0"
    "Matrix size is out of range\0"
    "Missing an image filename\0"
    "Option '%s' requires an argument or argument is malformed\0"
    "Must specify a image name\0"
    "Must specify image size\0"
    "No Binary Large OBjects defined\0"
    "No images defined\0"
    "Non-zero width and height required\0"
    "No profile name was given\0"
    "Null blob argument\0"
    "Reference black is out of range\0"
    "Reference image required\0"
    "Reference is not my type\0"
    "Reference white is out of range\0"
    "Region area exceeds implementation limit\0"
    "Request did not return an image\0"
    "Soft clip offset is out of range\0"
    "Stegano image required\0"
    "Stereo image required\0"
    "Subimage specification returns no images\0"
    "Tile is not bounded by image dimensions\0"
    "Unable to add or remove profile\0"
    "unable to average image sequence\0"
    "unable to blur image\0"
    "unable to chop image\0"
    "unable to Cineon Log transform colorspace\0"
    "Unable to color matrix image\0"
    "Unable to constitute image\0"
    "Unable to convolve image\0"
    "Unable to edge image\0"
    "Unable to equalize image\0"
    "Unable to filter image\0"
    "unable to format image meta data\0"
    "Unable to frame image\0"
    "unable to oil paint image\0"
    "Unable to paint image\0"
    "Unable to raise image\0"
    "Unable to sharpen image\0"
    "Unable to spread image\0"
    "Unable to threshold image\0"
    "Unable to wave image\0"
    "Unrecognized attribute\0"
    "Unrecognized channel type\0"
    "Unrecognized color\0"
    "Unrecognized colormap type\0"
    "Unrecognized image colorspace\0"
    "Unrecognized command '%s'. Use -help for a usage summary or see manual.\0"
    "Unrecognized compose operator\0"
    "Unrecognized dispose method\0"
    "Unrecognized element\0"
    "Unrecognized endian type\0"
    "Unrecognized gravity type\0"
    "Unrecognized highlight style\0"
    "Unrecognized image compression\0"
    "Unrecognized image filter\0"
    "Unrecognized image format\0"
    "Unrecognized image mode\0"
    "Unrecognized image type\0"
    "Unrecognized intent type\0"
    "Unrecognized interlace type\0"
    "Unrecognized list type\0"
    "Unrecognized error metric\0"
    "Unrecognized mode type\0"
    "Unrecognized noise type\0"
    "Unrecognized operator\0"
    "Unrecognized option\0"
    "Unrecognized PerlMagick method\0"
    "Unrecognized pixel map\0"
    "Unrecognized preview type\0"
    "Unrecognized resource type\0"
    "Unrecognized type\0"
    "Unrecognized units type\0"
    "Unrecognized virtual pixel method\0"
    "Unsupported sampling factor\0"
    "Improper arguments supplied, please see manual\0"
    "Invalid colorspace type\0"
    "Invalid endian type\0"
    "Invalid image type\0"
    "Invalid interlace type\0"
    "Missing an image filename\0"
    "Option '%s' requires an argument or argument is malformed\0"
    "No images were loaded\0"
    "Option length exceeds limit\0"
    "Request did not return an image\0"
    "Unable to open XServer\0"
    "Unable to persist key\0"
    "Unrecognized colormap type\0"
    "Unrecognized colorspace type\0"
    "unrecognized dispose method\0"
    "Unrecognized endian type\0"
    "Unrecognized filter type\0"
    "unrecognized compression type\0"
    "Unrecognized image type\0"
    "Unrecognized interlace type\0"
    "Unrecognized option\0"
    "Unrecognized resource type\0"
    "Unrecognized virtual pixel method\0"
    "Unrecognized color\0"
    "image expected\0"
    "image info expected\0"
    "structure size mismatch\0"
    "Unable to get registry ID\0"
    "Unable to locate image\0"
    "Unable to set registry\0"
    "default error\0"
    "default warning\0"
    "Disk space limit exceeded (see -limit Disk)\0"
    "Image pixel height limit exceeded (see -limit Height)\0"
    "Image pixel limit exceeded (see -limit Pixels)\0"
    "Image pixel width limit exceeded (see -limit Width)\0"
    "Images limit exceeded (see -limit Images)\0"
    "Memory allocation failed\0"
    "Pixel nexus height limit exceeded (see -limit Height)\0"
    "Pixel nexus limit exceeded (see -limit Pixels)\0"
    "Pixel nexus width limit exceeded (see -limit Width)\0"
    "No pixels defined in cache\0"
    "Pixel cache allocation failed\0"
    "Attached profiles limit exceeded (see -limit Profiles)\0"
    "Read limit exceeded (see -limit Read)\0"
    "unable to add ICC Color profile\0"
    "unable to add generic profile\0"
    "unable to add IPTC profile\0"
    "unable to add or remove profile\0"
    "unable to allocate coefficients\0"
    "Unable to allocate colormap\0"
    "unable to allocate ICC profile\0"
    "Unable to allocate image\0"
    "unable to allocate string\0"
    "Unable to annotate image\0"
    "unable to average image sequence\0"
    "unable to clone drawing context\0"
    "unable to clone image\0"
    "unable to compute image signature\0"
    "unable to constitute image\0"
    "unable to convert font\0"
    "unable to convert strings to tokens\0"
    "Unable to create colormap\0"
    "unable to create color transform\0"
    "unable to create command widget\0"
    "unable to create image group\0"
    "Unable to create image montage\0"
    "unable to create X window\0"
    "unable to crop image\0"
    "unable to despeckle image\0"
    "unable to determine image class\0"
    "unable to determine the number of image colors\0"
    "unable to dither image\0"
    "unable to draw on image\0"
    "unable to edge image\0"
    "unable to emboss image\0"
    "unable to enhance image\0"
    "unable to floodfill image\0"
    "unable to gamma correct image\0"
    "unable to get best icon size\0"
    "unable to get from registry\0"
    "Unable to get package info\0"
    "unable to interpret MSL image\0"
    "unable to level image\0"
    "unable to magnify image\0"
    "Unable to manage color\0"
    "Unable to map image\0"
    "Unable to map image sequence\0"
    "unable to median filter image\0"
    "unable to motion blur image\0"
    "unable to noise filter image\0"
    "unable to normalize image\0"
    "unable to open color profile\0"
    "unable to quantize image\0"
    "unable to quantize image sequence\0"
    "unable to read text chunk\0"
    "unable to read X image\0"
    "unable to read X server colormap\0"
    "unable to resize image\0"
    "unable to rotate image\0"
    "unable to sample image\0"
    "unable to scale image\0"
    "unable to segment image\0"
    "unable to select image\0"
    "unable to set image background color\0"
    "unable to sharpen image\0"
    "unable to shave image\0"
    "unable to shear image\0"
    "unable to sort image colormap\0"
    "unable to threshold image\0"
    "unable to transform colorspace\0"
    "Write limit exceeded (see -limit Write)\0"
    "Memory allocation failed\0"
    "Semaphore operation failed\0"
    "unable to allocate ascii85 info\0"
    "unable to allocate cache info\0"
    "unable to allocate cache view\0"
    "unable to allocate color info\0"
    "unable to allocate dash pattern\0"
    "unable to allocate delegate info\0"
    "unable to allocate draw context\0"
    "unable to allocate draw info\0"
    "unable to allocate drawing wand\0"
    "unable to allocate gamma map\0"
    "unable to allocate image\0"
    "unable to allocate image pixels\0"
    "unable to allocate log info\0"
    "unable to allocate magic info\0"
    "unable to allocate magick info\0"
    "unable to allocate magick map\0"
    "unable to allocate module info\0"
    "unable to allocate montage info\0"
    "unable to allocate quantize info\0"
    "unable to allocate random kernel\0"
    "unable to allocate registry info\0"
    "unable to allocate semaphore info\0"
    "unable to allocate string\0"
    "unable to allocate type info\0"
    "unable to allocate wand\0"
    "unable to animate image sequence\0"
    "unable to clone blob info\0"
    "unable to clone cache info\0"
    "unable to clone image\0"
    "unable to clone image info\0"
    "unable to concatenate string\0"
    "unable to convert text\0"
    "unable to create colormap\0"
    "unable to destroy semaphore\0"
    "unable to display image\0"
    "unable to escape string\0"
    "unable to initialize semaphore\0"
    "unable to interpret MSL image\0"
    "unable to lock semaphore\0"
    "unable to obtain random bytes from operating system\0"
    "unable to unlock semaphore\0"
    "Memory allocation failed\0"
    "image does not contain the stream geometry\0"
    "no stream handler is defined\0"
    "Pixel cache is not open\0"
    "Unable to acquire pixel stream\0"
    "Unable to set pixel stream\0"
    "Unable to sync pixel stream\0"
    "default error\0"
    "default warning\0"
    "Font name not specified\0"
    "Font substitution required\0"
    "Unable to get type metrics\0"
    "Unable to initialize freetype library\0"
    "Unable to read font\0"
    "Unrecognized font encoding\0"
    "default error\0"
    "default warning\0"
    "invalid colormap index `%.1024s\0"
    "Wand API not implemented `%.1024s\0"
    "Wand contains no image indices `%.1024s\0"
    "Wand contains no images `%.1024s\0"
    "Color is not known to server\0"
    "No window with specified ID exists\0"
    "Standard Colormap is not initialized\0"
    "Unable to connect to remote display\0"
    "Unable to create bitmap\0"
    "Unable to create colormap\0"
    "Unable to create pixmap\0"
    "Unable to create property\0"
    "Unable to create standard colormap\0"
    "Unable to display image info\0"
    "Unable to get property\0"
    "Unable to get Standard Colormap\0"
    "Unable to get visual\0"
    "Unable to grab mouse\0"
    "Unable to load font\0"
    "Unable to match visual to Standard Colormap\0"
    "Unable to open X server\0"
    "Unable to read X attributes\0"
    "Unable to read X window image\0"
    "Unrecognized colormap type\0"
    "Unrecognized gravity type\0"
    "Unrecognized visual specifier\0"
    "Unable to allocate X hints\0"
    "Unable to create X cursor\0"
    "Unable to create graphic context\0"
    "unable to create standard colormap\0"
    "Unable to create text property\0"
    "Unable to create X image\0"
    "Unable to create X pixmap\0"
    "Unable to create X window\0"
    "unable to display image\0"
    "unable to dither image\0"
    "Unable to get pixel info\0"
    "Unable to get visual\0"
    "Unable to load font\0"
    "Unable to make X window\0"
    "Unable to open X server\0"
    "Unable to view fonts\0"
    "Unable to get visual\0"
    "UsingDefaultVisual\0"
  ;

static const unsigned short message_dat_offsets[] =
  {
    0,
    3,
    25,
    55,
    87,
    107,
    127,
    152,
    177,
    198,
    224,
    238,
    254,
    285,
    321,
    379,
    403,
    433,
    455,
    478,
    504,
    536,
    557,
    587,
    614,
    669,
    692,
    721,
    737,
    757,
    785,
    813,
    847,
    872,
    894,
    932,
    967,
    1032,
    1059,
    1076,
    1115,
    1149,
    1191,
    1227,
    1246,
    1271,
    1299,
    1340,
    1373,
    1407,
    1429,
    1453,
    1477,
    1508,
    1542,
    1573,
    1618,
    1653,
    1679,
    1705,
    1728,
    1755,
    1772,
    1797,
    1820,
    1846,
    1880,
    1919,
    1951,
    1984,
    2007,
    2037,
    2102,
    2125,
    2147,
    2171,
    2194,
    2221,
    2257,
    2290,
    2310,
    2330,
    2358,
    2387,
    2415,
    2438,
    2466,
    2493,
    2519,
    2542,
    2572,
    2600,
    2628,
    2654,
    2679,
    2704,
    2737,
    2764,
    2801,
    2826,
    2858,
    2892,
    2921,
    2949,
    2985,
    3015,
    3042,
    3072,
    3105,
    3142,
    3178,
    3210,
    3256,
    3299,
    3343,
    3380,
    3416,
    3468,
    3517,
    3550,
    3597,
    3628,
    3647,
    3680,
    3694,
    3728,
    3762,
    3841,
    3878,
    3914,
    3941,
    3981,
    4010,
    4024,
    4062,
    4102,
    4146,
    4162,
    4202,
    4240,
    4271,
    4293,
    4307,
    4358,
    4383,
    4408,
    4430,
    4462,
    4485,
    4513,
    4546,
    4579,
    4607,
    4644,
    4676,
    4705,
    4740,
    4805,
    4833,
    4872,
    4901,
    4932,
    4963,
    4989,
    5017,
    5045,
    5082,
    5112,
    5137,
    5179,
    5212,
    5239,
    5262,
    5289,
    5310,
    5338,
    5363,
    5393,
    5417,
    5445,
    5474,
    5496,
    5518,
    5553,
    5575,
    5598,
    5631,
    5659,
    5685,
    5726,
    5763,
    5796,
    5824,
    5855,
    5871,
    5905,
    5949,
    5979,
    6024,
    6046,
    6066,
    6079,
    6106,
    6129,
    6162,
    6190,
    6218,
    6251,
    6284,
    6312,
    6339,
    6397,
    6411,
    6427,
    6462,
    6482,
    6509,
    6546,
    6585,
    6612,
    6631,
    6658,
    6685,
    6729,
    6759,
    6800,
    6821,
    6845,
    6887,
    6903,
    6939,
    6959,
    6986,
    7019,
    7052,
    7074,
    7088,
    7125,
    7144,
    7185,
    7199,
    7231,
    7251,
    7272,
    7286,
    7302,
    7325,
    7370,
    7404,
    7429,
    7455,
    7486,
    7520,
    7545,
    7567,
    7594,
    7613,
    7636,
    7670,
    7691,
    7713,
    7741,
    7758,
    7781,
    7806,
    7830,
    7855,
    7880,
    7910,
    7940,
    7977,
    8007,
    8031,
    8055,
    8084,
    8115,
    8145,
    8168,
    8192,
    8216,
    8245,
    8267,
    8297,
    8319,
    8335,
    8364,
    8398,
    8440,
    8466,
    8491,
    8532,
    8573,
    8603,
    8632,
    8666,
    8708,
    8722,
    8738,
    8761,
    8783,
    8805,
    8837,
    8857,
    8892,
    8908,
    8922,
    8936,
    8976,
    8992,
    9016,
    9047,
    9077,
    9104,
    9134,
    9163,
    9195,
    9234,
    9263,
    9292,
    9324,
    9350,
    9381,
    9412,
    9443,
    9470,
    9505,
    9540,
    9568,
    9594,
    9652,
    9678,
    9702,
    9734,
    9752,
    9787,
    9813,
    9832,
    9864,
    9889,
    9914,
    9946,
    9987,
    10019,
    10052,
    10075,
    10097,
    10138,
    10178,
    10210,
    10243,
    10264,
    10285,
    10327,
    10356,
    10383,
    10408,
    10429,
    10454,
    10477,
    10510,
    10532,
    10558,
    10580,
    10602,
    10626,
    10649,
    10675,
    10696,
    10719,
    10745,
    10764,
    10791,
    10821,
    10893,
    10923,
    10951,
    10972,
    10997,
    11023,
    11052,
    11083,
    11109,
    11135,
    11159,
    11183,
    11208,
    11236,
    11259,
    11285,
    11308,
    11332,
    11354,
    11374,
    11405,
    11428,
    11454,
    11481,
    11499,
    11523,
    11557,
    11585,
    11632,
    11656,
    11676,
    11695,
    11718,
    11744,
    11802,
    11824,
    11852,
    11884,
    11907,
    11929,
    11956,
    11985,
    12013,
    12038,
    12063,
    12093,
    12117,
    12145,
    12165,
    12192,
    12226,
    12245,
    12260,
    12280,
    12304,
    12330,
    12353,
    12376,
    12390,
    12406,
    12450,
    12504,
    12551,
    12603,
    12645,
    12670,
    12724,
    12771,
    12823,
    12850,
    12880,
    12935,
    12973,
    13005,
    13035,
    13062,
    13094,
    13126,
    13154,
    13185,
    13210,
    13236,
    13261,
    13294,
    13326,
    13348,
    13382,
    13409,
    13432,
    13468,
    13494,
    13527,
    13559,
    13588,
    13619,
    13645,
    13666,
    13692,
    13724,
    13771,
    13794,
    13818,
    13839,
    13862,
    13886,
    13912,
    13942,
    13971,
    13999,
    14026,
    14056,
    14078,
    14102,
    14125,
    14145,
    14174,
    14204,
    14232,
    14261,
    14287,
    14316,
    14341,
    14375,
    14401,
    14424,
    14457,
    14480,
    14503,
    14526,
    14548,
    14572,
    14595,
    14632,
    14656,
    14678,
    14700,
    14730,
    14756,
    14787,
    14827,
    14852,
    14879,
    14911,
    14941,
    14971,
    15001,
    15033,
    15066,
    15098,
    15127,
    15159,
    15188,
    15213,
    15245,
    15273,
    15303,
    15334,
    15364,
    15395,
    15427,
    15460,
    15493,
    15526,
    15560,
    15586,
    15615,
    15639,
    15672,
    15698,
    15725,
    15747,
    15774,
    15803,
    15826,
    15852,
    15880,
    15904,
    15928,
    15959,
    15989,
    16014,
    16066,
    16093,
    16118,
    16161,
    16190,
    16214,
    16245,
    16272,
    16300,
    16314,
    16330,
    16354,
    16381,
    16408,
    16446,
    16466,
    16493,
    16507,
    16523,
    16555,
    16589,
    16629,
    16662,
    16691,
    16726,
    16763,
    16799,
    16823,
    16849,
    16873,
    16899,
    16934,
    16963,
    16986,
    17018,
    17039,
    17060,
    17080,
    17124,
    17148,
    17176,
    17206,
    17233,
    17259,
    17289,
    17316,
    17342,
    17375,
    17410,
    17441,
    17466,
    17492,
    17518,
    17542,
    17565,
    17590,
    17611,
    17631,
    17655,
    17679,
    17700,
    17721,
    17740,
    0
  };
#endif /* if defined(_INCLUDE_MESSAGE_TABLE_) */
