#include "./Buffer_orc.h"

#include <stdio.h>


Sgl$Buffer*  Sgl$Buffer_readFile(Sgl$Buffer **  __outRef__, const char *  path){
    Sgl$Buffer* ret = Sgl$Buffer_new(__outRef__);


    FILE *f = fopen(path, "rb");
    if (f){
        unsigned char buf[10240];
        while (!feof(f)){
            int nread = fread(buf, 1, 10240, f);

            if (nread > 0){
                // printf("rad bufnread:%d\n", nread);
                Sgl$Buffer$append(ret, buf, nread);
            }
        }
        fclose(f);
    }

    return ret;
}
