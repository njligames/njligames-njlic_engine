#ifndef WRAPPER_OGG_H
#define WRAPPER_OGG_H

struct SoundInfo;

struct OggVorbis_File;

#define OGG_BUFFER_SIZE 2048

#include <vector>
//#include "../../Macros.h"
#include <cstring>

#include "ISoundFileWrapper.h"

typedef struct ogg_file
{
  char *curPtr;
  char *filePtr;
  size_t fileSize;
} ogg_file;

namespace njli
{

  class WrapperOgg : public ISoundFileWrapper
  {
  public:
    WrapperOgg(int minDecompressLengthAtOnce = -1);
    ~WrapperOgg();

    virtual void LoadFromMemory(char *data, int dataSize, SoundInfo *soundInfo);
    virtual void LoadFromFile(FILE *f, SoundInfo *soundInfo);
    virtual void DecompressStream(std::vector<char> &decompressBuffer,
                                  bool inLoop = false);
    virtual void DecompressAll(std::vector<char> &decompressBuffer);
    virtual void ResetStream();

    virtual void Seek(size_t pos, SEEK_POS start);
    virtual size_t GetCurrentStreamPos() const;

    virtual float GetTime() const;
    virtual float GetTotalTime() const;

  private:
    OggVorbis_File *ov;
    ogg_file t;
    char bufArray[OGG_BUFFER_SIZE];
    int minDecompressLengthAtOnce;

    bool seekable;
  };
}

#endif
