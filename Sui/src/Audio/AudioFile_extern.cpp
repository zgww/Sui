#include "./AudioFile.h"


extern "C" void testAudioFile(){
    AudioFile<float> audioFile;
    if (!audioFile.load("../asset/09-37.wav")){
        printf("load wav fail\n");
        return;
    }
    printf("load wav succ\n");
    printf("-bitDepth:%d\n", audioFile.getBitDepth());
    printf("-num chan:%d\n", audioFile.getNumChannels());
    printf("-mono:%d\n", audioFile.isMono());
    printf("-sample rate:%d\n", audioFile.getSampleRate());
    printf("-stereo:%d\n", audioFile.isStereo());
    printf("-num samples per channel:%d\n", audioFile.getNumSamplesPerChannel());
    printf("-length in sec:%f\n", audioFile.getLengthInSeconds());
    audioFile.printSummary();
    // audioFile.play();
}