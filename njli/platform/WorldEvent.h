
#ifndef __JLIGameEngineTest__WorldEvent__
#define __JLIGameEngineTest__WorldEvent__

#include "AbstractObject.h"
#include "DeviceMouse.h"
#include "DeviceTouch.h"
#include <string>
#include <unordered_map>
#include <queue>

namespace njli
{

    class AdUnit;
  class WorldEvent : public njli::AbstractObject
  {
      friend class World;
  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
      using AbstractDecorator::getUuid;

    WorldEvent();
    virtual ~WorldEvent();

    virtual const char *getClassName() const;
    virtual s32 getType() const;
    operator std::string() const;

      void show();
  protected:
      void update();

  private:
    WorldEvent(const WorldEvent &)=delete;
    WorldEvent &operator=(const WorldEvent &)=delete;
      std::queue<AdUnit*> *mAdUnitQueue;
      AdUnit *mCurrenAdUnit;
      bool mShow;
      
  };
}

#endif /* defined(__JLIGameEngineTest__WorldEvent__) */
