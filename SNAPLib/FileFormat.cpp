
#include "stdafx.h"
#include "Compat.h"
#include "FileFormat.h"
#include "AlignerOptions.h"
#include "Error.h"
#include "exit.h"

std::map<FileType, FileFormat**> FileFormat::FORMATS;

const FileFormat* FileFormat::getFormat(AlignerOptions* options) {
    if (FORMATS.count(options->outputFile.fileType) == 1) {
        return FORMATS.at(options->outputFile.fileType)[options->useM];
    }

    //
    // This shouldn't happen, because the command line parser should catch it.  Perhaps you've added a new output file format and just
    // forgoten to add it here.
    //
    WriteErrorMessage("unknown file type %d for '%s'\n", options->outputFile.fileType, options->outputFile.fileName);
    soft_exit(1);
    return NULL;
}