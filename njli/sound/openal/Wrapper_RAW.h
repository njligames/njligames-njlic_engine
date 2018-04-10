#ifndef WRAPPER_RAW_H
#define WRAPPER_RAW_H

#define RAW_BUFFER_SIZE 2048

#include <vector>
//#include "../../Macros.h"
#include <cstring>

#include "ISoundFileWrapper.h"
#include "Sound.h"

typedef struct raw_file
{
  FILE *f;
  char *curPtr;
  char *filePtr;
  size_t fileSize;
  size_t processedSize;

} raw_file;

namespace njli
{

  class WrapperRaw : public ISoundFileWrapper
  {
  public:
    WrapperRaw(SoundInfo info, int minDecompressLengthAtOnce = -1);
    ~WrapperRaw();

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
    raw_file t;
    char bufArray[RAW_BUFFER_SIZE];

    int minProcesssLengthAtOnce;

    SoundInfo info;
    int curBufSize;

    u64 remainDataSize;

    void ReadData(void *dst, size_t size);
  };
}

#endif
