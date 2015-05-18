#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T12:43:02
#
#-------------------------------------------------

QT       -= core gui

TARGET = PdfReader
TEMPLATE = lib

DEFINES += PDFREADER_LIBRARY

linux-g++ | linux-g++-64 | linux-g++-32 {
    DEFINES += \
    HAVE_UNISTD_H \
    LINUX \
    _LINUX \
    _LINUX_QT

    CONFIG += c++11

    message(linux)
}

INCLUDEPATH += \
    ../DesktopEditor/agg-2.4/include \
    ../DesktopEditor/freetype-2.5.2/include \
    ../DesktopEditor/cximage/jasper/include \
    ../DesktopEditor/cximage/jpeg \
    ../DesktopEditor/cximage/png \
    ../DesktopEditor/cximage/zlib

SOURCES += \
    Src/Annot.cpp \
    Src/Array.cpp \
    Src/Catalog.cpp \
    Src/CharCodeToUnicode.cpp \
    Src/CMap.cpp \
    Src/Decrypt.cpp \
    Src/Dict.cpp \
    Src/ExtractImageOutputDev.cpp \
    Src/FontFileBase.cpp \
    Src/FontFileTrueType.cpp \
    Src/FontFileType1.cpp \
    Src/FontFileType1C.cpp \
    Src/Function.cpp \
    Src/GFont.cpp \
    Src/GlobalParams.cpp \
    Src/Graphics.cpp \
    Src/GState.cpp \
    Src/Hash.cpp \
    Src/JArithmeticDecoder.cpp \
    Src/JBIG2Stream.cpp \
    Src/JPXStream.cpp \
    Src/Lexer.cpp \
    Src/Link.cpp \
    Src/List.cpp \
    Src/NameToCharCode.cpp \
    Src/Object.cpp \
    Src/Outline.cpp \
    Src/OutputDevice.cpp \
    Src/Page.cpp \
    Src/Parser.cpp \
    Src/PDFDoc.cpp \
    Src/PSLexer.cpp \
    Src/RendererOutputDev.cpp \
    Src/SecurityHandler.cpp \
    Src/Stream.cpp \
    Src/StringExt.cpp \
    Src/UnicodeMap.cpp \
    Src/XRef.cpp \
    PdfReader.cpp

HEADERS +=\
    Resources/Fontd050000l.h \
    Resources/Fontn019003l.h \
    Resources/Fontn019004l.h \
    Resources/Fontn019023l.h \
    Resources/Fontn019024l.h \
    Resources/Fontn021003l.h \
    Resources/Fontn021004l.h \
    Resources/Fontn021023l.h \
    Resources/Fontn021024l.h \
    Resources/Fontn022003l.h \
    Resources/Fontn022004l.h \
    Resources/Fontn022023l.h \
    Resources/Fontn022024l.h \
    Resources/Fonts050000l.h \
    Src/Annot.h \
    Src/Array.h \
    Src/BuiltinFont.h \
    Src/BuiltinFontTables.h \
    Src/Catalog.h \
    Src/CCITT-Tables.h \
    Src/CharCodeToUnicode.h \
    Src/CharTypes.h \
    Src/CMap.h \
    Src/Constants.h \
    Src/Decrypt.h \
    Src/Dict.h \
    Src/EncodingTables.h \
    Src/ErrorConstants.h \
    Src/ExtractImageOutputDev.h \
    Src/File.h \
    Src/FontFileBase.h \
    Src/FontFileEncodings.h \
    Src/FontFileTrueType.h \
    Src/FontFileType1.h \
    Src/FontFileType1C.h \
    Src/Function.h \
    Src/GFont.h \
    Src/GlobalParams.h \
    Src/Graphics.h \
    Src/GState.h \
    Src/Hash.h \
    Src/JArithmeticDecoder.h \
    Src/JBIG2Stream.h \
    Src/JPXStream.h \
    Src/Lexer.h \
    Src/Link.h \
    Src/List.h \
    Src/MemoryUtils.h \
    Src/NameToCharCode.h \
    Src/NameToUnicodeTable.h \
    Src/Object.h \
    Src/Outline.h \
    Src/OutputDevice.h \
    Src/Page.h \
    Src/Parser.h \
    Src/PDFDoc.h \
    Src/PDFDocEncoding.h \
    Src/PSLexer.h \
    Src/RendererOutputDev.h \
    Src/SecurityHandler.h \
    Src/Stream.h \
    Src/StringExt.h \
    Src/UnicodeMap.h \
    Src/UnicodeMapTables.h \
    Src/UTF8.h \
    Src/XmlUtils.h \
    Src/XRef.h \
    PdfReader.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}