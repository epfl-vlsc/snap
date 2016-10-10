//#include <limits.h>
#include "stdafx.h"

#include "Compat.h"
#include "Error.h"
#include "BigAlloc.h"
#include "BaseSeq.h"
#include "limits.h"

BYTE* BaseSeq::twoCharsToByte = NULL;
unsigned short* BaseSeq::byteToTwoChars = NULL;
char BaseSeq::rcTable[256] = {'N'};

BaseSeq::BaseSeq(uint64_t length) : repLength(length) {
    if (twoCharsToByte == NULL) {
        initializeTranslationTables();
    }
    uint64_t sizeInBytes = length / 2 + (length & 1);
    rep = (BYTE *) BigAlloc(length / 2 + (length & 1));
    if (rep == NULL) {
        WriteErrorMessage("BaseSequence::BaseSequence: unable to allocate memory\n");
        soft_exit(1);
    }
    memset(rep, BS_uninit, sizeInBytes);
}

BaseSeq::BaseSeq(uint64_t length, const char *basesAsChars, bool destructivelyReuseString)
        : repLength(length) {
    if (twoCharsToByte == NULL) {
        initializeTranslationTables();
    }
    if (destructivelyReuseString) {
        // Yes, this is OK so long as we write behind where we read
        rep = (BYTE *) basesAsChars;
    } else {
        rep = (BYTE *) new BYTE[length / 2 + (length & 1)];
        if (rep == NULL) {
            WriteErrorMessage("BaseSequence::BaseSequence: unable to allocate memory\n");
            soft_exit(1);
        }
    }
    initializeRep((char *) basesAsChars, length);
}

char *
BaseSeq::toChars(uint64_t offset) {
    if (offset & 0x1) {
        WriteErrorMessage("BaseSequence::toChars: unable to handle odd offset\n");
    }
    char* chars = new char[repLength - offset+1];
    if (chars == NULL) {
        WriteErrorMessage("BaseSequence::toChars: unable to allocate memory\n");
        soft_exit(1);
    }
    unsigned short* c = (unsigned short*)chars;
    BYTE* r = rep + (offset >> 2);
    for (uint64_t len = 0; len < repLength; len += 2) {
        if (repLength-len == 1) {
          *c = ((unsigned short)(RepToChar((*r) & 0xf))) ;
          //printf("char is: %c \n", RepToChar(*r & 0xf)); 
        } else
          *c = byteToTwoChars[*r];
        //printf("r value is: %hhu and c value is: %hu and len is:%u\n", *r, *c, len);
        c++;
        r++;
    }
    chars[repLength-offset] = '\0';
    return chars;
}

void
BaseSeq::dealloc(void* memory) {
    BigDealloc(memory);
}


void
BaseSeq::adjustStart(uint64_t offset) {
    if (offset & 0x1) {
        WriteErrorMessage("BaseSequence::adjustStart: unable to handle odd offset\n");
    }
    rep += offset / 2;
    repLength -= offset;
}

void
BaseSeq::baseSet(uint64_t start, char fill, uint64_t length) {
    if (start & 0x1 || length & 0x1) {
        WriteErrorMessage("BaseSequence::baseSet: unable to handle odd start or length\n"); // lazy
    }

    unsigned short twoFill = (fill << 8) | fill;
    char charFill = twoCharsToByte[twoFill];

    uint64_t lengthInChars = length / 2;
    uint64_t startInChars = start / 2;

    memset(rep + startInChars, charFill, lengthInChars);
}

void
BaseSeq::baseSet(uint64_t start, const char* fill, uint64_t length) {
    initializeRep((char*)fill, length);
}


void
BaseSeq::initializeRep(char *basesAsChars, uint64_t length) {
    printf("initializing rep!\n");
    unsigned short *basesAsShorts = (unsigned short *) basesAsChars;  // 2 bases = 2 chars -> 1 byte
    uint64_t lengthInShorts = length / 2;
    uint64_t repIndex = 0;
    for (uint64_t i = 0; i < lengthInShorts; i++) {
        BYTE repPair = twoCharsToByte[basesAsShorts[i]];
        if (repPair == 0) {
            WriteErrorMessage("BaseSequence::TranslateSequence: bad character (%c, %c) in input at short index %d\n",
                              (char) (basesAsShorts[i] & 0xff),
                              (char) ((basesAsShorts[i] >> 8) & 0xff), i);
            soft_exit(1);
        }
        rep[repIndex] = repPair;
        repIndex++;
    }
    if (length & 1) {
        rep[repIndex] = CharToRep(basesAsChars[length - 1]);
    }
}
    

void
BaseSeq::initializeTranslationTables() {
    BYTE *table = (BYTE *)malloc((UCHAR_MAX+1) * (UCHAR_MAX+1) * sizeof(char));
    unsigned short *iTable = (unsigned short*)malloc((UCHAR_MAX+1) * sizeof(unsigned short));
    printf("Initializing translation tables!\n");
    if (table == NULL || iTable == NULL) {
        WriteErrorMessage("BaseSequence::initializeTranslationTable: unable to allocate memory\n");
        soft_exit(1);
    }
    memset(table, 0, (UCHAR_MAX+1) * (UCHAR_MAX+1) * sizeof(char));
    memset(iTable, 0, (UCHAR_MAX+1) * sizeof(unsigned short));
    for (unsigned int i1 = 0; i1 <= UCHAR_MAX; i1++) {
        for (unsigned int i2 = 0; i2 <= UCHAR_MAX; i2++) {
            BYTE c1 = CharToRep((char) i1);
            BYTE c2 = CharToRep((char) i2);
            if (c1 == 0 || c2 == 0) {
                continue;
            }
            table[i1 * (UCHAR_MAX + 1) + i2] = (c1 << 4) | c2;
            unsigned short is = (unsigned short)i1;
            unsigned short is2 = (unsigned short)i2;
            BYTE index = (c1<<4)|c2;
            if (c1 != 0){
              //printf("setting iTable entry %hhu to %hu\n", index, (is<<8)|is2);
              iTable[index] = (is << 8) | is2;
              //printf("value: %hu\n", iTable[index]);
            }
        }
    }
    //printf("byte to two chars %hhu is: %hu \n", (BYTE)53, iTable[(BYTE)53]);
    twoCharsToByte = table;
    byteToTwoChars = iTable;
    //printf("byte to two chars %hhu is: %hu \n", (BYTE)53, byteToTwoChars[(BYTE)53]);
    //printf("byte to two chars %hhu is: %hu \n", (BYTE)53, iTable[(BYTE)53]);
    
    for (unsigned i = 0; i < 256; i++) {
        //printf("val: %hu \n", iTable[(BYTE)i]);
        rcTable[i] = 'N';
    }

    rcTable['A'] = 'T';
    rcTable['G'] = 'C';
    rcTable['C'] = 'G';
    rcTable['T'] = 'A';
    rcTable['N'] = 'N';

}