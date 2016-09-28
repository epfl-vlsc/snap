// Goal: replace char* as representation of a base, without lose of efficiency
// Goal: allow compaction of representation to 4-bits
// Goal: make code clearer

#pragma once

#include "Util.h"

class BaseRef; // Forward pointer

class BaseSeq {
    friend class BaseRef;

public:
    const static BYTE BS_uninit = 0;
    const static BYTE BS_C = 1;
    const static BYTE BS_G = 2;
    const static BYTE BS_A = 3;
    const static BYTE BS_T = 4;
    const static BYTE BS_N = 5;
    const static BYTE BS_n = 6;  // n is padding, but N is unknown bases. They are not the same.

    BaseSeq(uint64_t length);
    BaseSeq(uint64_t length, const char *bases, bool destructivelyReuseString);

    char* toChars(uint64_t offset);

    void dealloc(void* memory);

    inline  BYTE get(const uint64_t index) const {
        _ASSERT(index < repLength);
        return (BYTE) (index & 0x1 ? rep[index >> 1] >> 4 : rep[index >> 1] & 0xf);
    }

    inline const BYTE* getPtr(const uint64_t index) const {
        _ASSERT(index < repLength);
        return &rep[index >> 1];
    }

    inline void put(const uint64_t index, const BYTE val) {
        _ASSERT(index < repLength);
        if (index & 0x1) {
            rep[index >> 1] = (BYTE) ((rep[index >> 1] & 0xf0) | (val << 4));
        } else {
            rep[index >> 1] = (BYTE) ((rep[index >> 1] & 0x0f) | (val & 0xf));
        }
    }

    void adjustStart(uint64_t offset);

    void baseSet(uint64_t start, char fill, uint64_t length);
    void baseSet(uint64_t start, const char* fill, uint64_t length);

    static BYTE
    CharToRep(const char c)  {
        switch (c) {
            case 'C':
                return BaseSeq::BS_C;

            case 'G':
                return BaseSeq::BS_G;

            case 'A':
                return BaseSeq::BS_A;

            case 'T':
                return BaseSeq::BS_T;

            case 'N':
                return BaseSeq::BS_N;

            case 'n':
                return BaseSeq::BS_n;

            default:
                return BS_uninit;
        }
    }

    static char
    RepToChar(const BYTE r) {
        switch (r) {
            case BaseSeq::BS_C:
                return 'C';

            case BaseSeq::BS_G:
                return 'G';

            case BaseSeq::BS_A:
                return 'A';

            case BaseSeq::BS_T:
                return 'T';

            case BaseSeq::BS_N:
                return 'N';

            case BaseSeq::BS_n:
                return 'n';

            default:
                return '?';
        }
    }

private:
    void initializeRep(char *basesAsChars, uint64_t length);

    void initializeTranslationTables();
    static BYTE *twoCharsToByte;
    static short *byteToTwoChars;

    BYTE *rep; // sequence of nibbles (4 bits)

    uint64_t repLength; // in nibbles
};


// C pointers have at minimum a byte granularity, which isn't fine enough for nibbles. This
// is a replacement for char* that allows nibble granularity.
class BaseRef {
    friend class BaseSeq;

public:
    BaseRef(BaseSeq *bs) : baseSequence(bs), offset(0) {};
    BaseRef(BaseSeq *bs, uint64_t o) : baseSequence(bs), offset(o) {};

    // Assign one of: 'C', 'G', 'A', 'T', 'N' only
    inline BaseRef &operator=(const char x) {
        baseSequence->put(offset, baseSequence->CharToRep(x));
        return *this;
    }

    // Assign nibble, encoded as above
    inline BaseRef &operator=(const BYTE x) {
        baseSequence->put(offset, x);
        return *this;
    }

    inline BaseRef &operator=(const BaseRef &x) {
        baseSequence = x.baseSequence;
        offset = x.offset;
        return *this;
    }

    inline bool operator==(const BaseRef &x) const {
        return this->baseSequence == x.baseSequence && this->offset == x.offset;
    }

    inline bool equal(const BaseRef *x) const {
        return this->baseSequence == x->baseSequence && this->offset == x->offset;
    }

    inline bool isLowerNibble() const {
        return !(offset & 0x1);
    }
    inline bool isUpperNibble() const {
        return offset & 0x1;
    }

    char* toChars() const {
        return baseSequence->toChars(0);
    }

    // Can't overload pointer dereference operator (*), so need to explicitly get/put
    inline const BYTE get() {
        return baseSequence->get(offset);
    }

    inline const BYTE get(const uint64_t index) const {
        return baseSequence->get(offset + index);
    }

    inline const BYTE* getPtr() const {
        return baseSequence->getPtr(offset);
    }

    inline const BYTE* getPtr(const uint64_t delta) const {
        return baseSequence->getPtr(offset + delta);
    }

    inline BaseRef &put(const BYTE val) {
        baseSequence->put(offset, val);
        return *this;
    }

    inline BaseRef &put(const uint64_t delta, const BYTE val) {
        baseSequence->put(offset + delta, val);
        return *this;
    }

    inline BaseRef &operator++() {
        offset++;
        return *this;
    }

    inline BaseRef* operator+(int arg) {
        return new BaseRef(baseSequence, offset + arg);
    }

    inline BaseRef* operator-(int arg) {
        return new BaseRef(baseSequence, offset - arg);
    }

private:
    BaseSeq *baseSequence;
    uint64_t offset;
};
