
#ifndef __JLIGameEngineTest__WorldAd__
#define __JLIGameEngineTest__WorldAd__

#include "AbstractObject.h"
#include "DeviceMouse.h"
#include "DeviceTouch.h"
#include <string>
#include <unordered_map>
#include <queue>

namespace njli
{

    class AdUnit;
  class WorldAd : public njli::AbstractObject
  {
      friend class World;
  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
      using AbstractDecorator::getUuid;

    WorldAd();
    virtual ~WorldAd();

    virtual const char *getClassName() const;
    virtual s32 getType() const;
    operator std::string() const;

      void show();
      
      void addKeyword(const std::string &keyword);
      void clearKeywords();
      
      int numKeyWords()const;
      const char **getKeyWords();
  protected:
      void update();

  private:
    WorldAd(const WorldAd &)=delete;
    WorldAd &operator=(const WorldAd &)=delete;
      std::queue<AdUnit*> *mAdUnitQueue;
      AdUnit *mCurrenAdUnit;
      bool mShow;
      std::vector<const char*> mKeyWords;
  };
}

#endif /* defined(__JLIGameEngineTest__WorldAd__) */
