#include <stdio.h>
#include <utility>
#include "Compat.h"
#include "BaseSeq.h"

int main (int argc, char** argv) {
    char* str = "CCGGAATTNNCGATN";
    BaseSeq* bs = new BaseSeq(15, str, false);
    BaseRef* ref = new BaseRef(bs);
    for (int i = 0; i < 15; i ++) {
        printf("%d %d\n", i, ref->get(i));
    }
    return 0;
}
