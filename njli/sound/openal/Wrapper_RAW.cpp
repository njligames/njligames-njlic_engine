#include "Wrapper_RAW.h"
#include "Sound.h"

//#include "../../Utils/header/Logger.h"

#include <algorithm>
#include <climits>
#include <string.h>

using namespace njli;

WrapperRaw::WrapperRaw(SoundInfo info, int minProcesssLengthAtOnce)
{
  this->minProcesssLengthAtOnce = minProcesssLengthAtOnce;

  if (this->minProcesssLengthAtOnce == -1)
    {
      this->minProcesssLengthAtOnce = INT_MAX;
    }

  this->info = info;

  memset(&this->t, 0, sizeof(raw_file));
}

WrapperRaw::~WrapperRaw()
{
  if (this->t.filePtr)
    delete[] this->t.filePtr;
}

void WrapperRaw::LoadFromMemory(char *data, int dataSize, SoundInfo *soundInfo)
{

  this->t.filePtr = new char[dataSize];
  memcpy(this->t.filePtr, data, dataSize);

  this->t.curPtr = this->t.filePtr;

  this->t.fileSize = dataSize;
  this->t.processedSize = 0;

  memcpy(soundInfo, &this->info, sizeof(SoundInfo));

  soundInfo->seekable = true;

  this->ResetStream();
}

void WrapperRaw::LoadFromFile(FILE *f, SoundInfo *soundInfo)
{

  // TO DO
}

void WrapperRaw::ResetStream()
{

  if (this->t.f != NULL)
    {
      fseek(this->t.f, 0, SEEK_SET);
    }
  else
    {
      this->t.curPtr = this->t.filePtr;
    }

  this->t.processedSize = 0;

  this->remainDataSize = this->t.fileSize;
}

void WrapperRaw::ReadData(void *dst, size_t size)
{

  if (this->t.f != NULL)
    {
      // read from file directly
      fread(dst, sizeof(u8), size, this->t.f);
    }
  else
    {
      // read from memory stream
      memcpy(dst, this->t.curPtr, size);
      this->t.curPtr += size;
    }

  this->t.processedSize += size;
}

void WrapperRaw::Seek(size_t size, SEEK_POS start)
{
  if (start == SEEK_POS::START)
    {
      this->ResetStream();
    }

  if (this->t.f != NULL)
    {
      // read from file directly
      // fread(dst, sizeof(uint8), size, this->t.f);
      fseek(this->t.f, size, SEEK_CUR);
    }
  else
    {
      // read from memory stream
      this->t.curPtr += size;
    }

  this->t.processedSize += size;
}

size_t WrapperRaw::GetCurrentStreamPos() const
{

  if (this->t.f != NULL)
    {
      return ftell(this->t.f);
    }
  else
    {
      return (this->t.curPtr - this->t.filePtr);
    }
}

float WrapperRaw::GetTime() const
{
  float pos = static_cast<float>(this->GetCurrentStreamPos());

  return pos / (this->info.freqency * this->info.channels *
                this->info.bitsPerChannel / 8);
}

float WrapperRaw::GetTotalTime() const
{
  float pos = this->t.fileSize;

  float t = pos / (this->info.freqency * this->info.channels *
                   this->info.bitsPerChannel / 8);

  return t;
}

void WrapperRaw::DecompressAll(std::vector<char> &decompressBuffer)
{

  // backup current state
  char bufArrayBckp[RAW_BUFFER_SIZE];
  memcpy(bufArrayBckp, this->bufArray, sizeof(char) * RAW_BUFFER_SIZE);

  int curBufSizeBckp = this->curBufSize;

  size_t pos = this->GetCurrentStreamPos();
  this->ResetStream();

  std::vector<char> rawBuffer;
  decompressBuffer.clear();

  // run fill data

  while (true)
    {
      this->DecompressStream(rawBuffer, false);

      if (rawBuffer.size() == 0)
        {
          break;
        }

      decompressBuffer.insert(decompressBuffer.end(), rawBuffer.begin(),
                              rawBuffer.end());
    }

  // restore backup
  this->Seek(pos, ISoundFileWrapper::SEEK_POS::START);

  memcpy(this->bufArray, bufArrayBckp, sizeof(char) * RAW_BUFFER_SIZE);

  this->curBufSize = curBufSizeBckp;
}

void WrapperRaw::DecompressStream(std::vector<char> &decompressBuffer,
                                  bool inLoop)
{
  decompressBuffer.clear();

  bool eof = false;
  int curBufSize = 0;

  do
    {
      do
        {

          curBufSize = 0;

          while (curBufSize < RAW_BUFFER_SIZE)
            {

              u64 remainToRead = RAW_BUFFER_SIZE - curBufSize;

              u64 readSize = std::min(
                  this->remainDataSize,
                  remainToRead); // how many data can we read in current chunk

              this->ReadData(this->bufArray + curBufSize, readSize);

              curBufSize += readSize; // buffer filled from [0...curBufSize]
              this->remainDataSize -=
                  readSize; // in current chunk, remain to read

              if (this->t.processedSize >= this->t.fileSize)
                {
                  eof = true;
                  break;
                }
            }

          // Append to end of buffer
          decompressBuffer.insert(decompressBuffer.end(), this->bufArray,
                                  this->bufArray + curBufSize);

          if (static_cast<int>(decompressBuffer.size()) >=
              this->minProcesssLengthAtOnce)
            {
              return;
            }
        }
      while (!eof);

      if (inLoop)
        {
          this->ResetStream();
        }

      if (this->minProcesssLengthAtOnce == INT_MAX)
        {
          return;
        }
    }
  while (inLoop);
}
