#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <stdio.h>

// int main(int argc, const char **argv){
//     printf("hi\n");
//     ma_result result;
//     ma_engine engine;

//     result = ma_engine_init(NULL, &engine);
//     printf("hi. result:%d MA_SUCCESS:%d\n", result, MA_SUCCESS);
//     if (result != MA_SUCCESS) {
//         return result;  // Failed to initialize the engine.
//     }
//     // ma_engine_play_sound(&engine, "a.wav", NULL);

//     const char *path = "a.mp3";
//     if (argc >= 2){
//         path = argv[1];
//     }

//     printf("play sound:%s\n", path);
//     ma_engine_play_sound(&engine, path, NULL);
//     getchar();
//     return 0;
// }