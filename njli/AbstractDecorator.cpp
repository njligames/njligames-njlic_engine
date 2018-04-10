//
//  AbstractDecorator.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 3/6/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "AbstractDecorator.h"

namespace njli
{
  AbstractDecorator::AbstractDecorator()
      : m_pParent(NULL), m_Name("<UNSET>"), m_Tag("")
  {
  }

  AbstractDecorator::~AbstractDecorator() { removeFromParent(); }

  AbstractDecorator *AbstractDecorator::getParent() { return m_pParent; }

  const AbstractDecorator *AbstractDecorator::getParent() const
  {
    return m_pParent;
  }

  bool AbstractDecorator::hasParent() const { return (NULL != m_pParent); }

  void AbstractDecorator::setParent(AbstractDecorator *parent)
  {
    //        bool condition = false;
    //        do {
    //            static char logMessage[3584];
    //            memset(logMessage, 0, 3584);
    //            vsnprintf(logMessage, 3584 - 1, fmt, __VA_ARGS__);
    //            SDL_assertCheck(condition, "%s", logMessage);
    //            SDL_assert(condition);
    //        } while (0);
    SDL_assertPrint(parent, "%s", "object is null");

    m_pParent = parent;
  }

  void AbstractDecorator::removeParent() { m_pParent = NULL; }

  bool AbstractDecorator::removeFromParent()
  {
    AbstractDecorator *parent = dynamic_cast<AbstractDecorator *>(getParent());

    if (parent && parent->hasChildren() && parent->hasChild(this))
      {
        parent->removeChild(this);
        return true;
      }
    return false;
  }

  AbstractDecorator *AbstractDecorator::findChild(const char *name)
  {
    if (strcmp(getName(), name) == 0)
      {
        return this;
      }
    else
      {
        for (std::vector<AbstractDecorator *>::const_iterator iter =
                 m_Children.begin();
             iter != m_Children.end(); ++iter)
          {
            AbstractDecorator *n = (*iter)->findChild(name);
            if (NULL != n)
              {
                return n;
              }
          }
      }
    return NULL;
  }

  const AbstractDecorator *AbstractDecorator::findChild(const char *name) const
  {
    if (strcmp(getName(), name) == 0)
      {
        return this;
      }
    else
      {
        for (std::vector<AbstractDecorator *>::const_iterator iter =
                 m_Children.begin();
             iter != m_Children.end(); ++iter)
          {
            AbstractDecorator *n = (*iter)->findChild(name);
            if (NULL != n)
              {
                return n;
              }
          }
      }
    return NULL;
  }

  AbstractDecorator *AbstractDecorator::getChild(const u32 index)
  {
    SDL_assertPrint(index < numberOfChildren(), "%s",
                    "index must be smaller than the size of the array");
    return m_Children.at(index);
  }

  const AbstractDecorator *AbstractDecorator::getChild(const u32 index) const
  {
    SDL_assertPrint(index < numberOfChildren(), "%s",
                    "index must be smaller than the size of the array");
    return m_Children.at(index);
  }

  void AbstractDecorator::getChildren(
      std::vector<AbstractDecorator *> &children) const
  {
    children = m_Children;
  }

  s32 AbstractDecorator::getChildIndex(AbstractDecorator *object) const
  {
    if (m_Children.size() > 0)
      {
        if (object)
          {
            std::vector<AbstractDecorator *>::const_iterator iter =
                std::find(m_Children.begin(), m_Children.end(), object);

            if (iter != m_Children.end())
              {
                return std::distance(m_Children.begin(), iter);
              }
          }
      }

    return -1;
  }

  s32 AbstractDecorator::getChildIndex(const AbstractDecorator *object) const
  {
    if (m_Children.size() > 0)
      {
        if (object)
          {
            std::vector<AbstractDecorator *>::const_iterator iter =
                std::find(m_Children.begin(), m_Children.end(), object);

            if (iter != m_Children.end())
              {
                return std::distance(m_Children.begin(), iter);
              }
          }
      }

    return -1;
  }

  bool AbstractDecorator::hasChild(AbstractDecorator *object) const
  {
    if (object && m_Children.size() > 0)
      {
        std::vector<AbstractDecorator *>::const_iterator iter =
            std::find(m_Children.begin(), m_Children.end(), object);

        if (m_Children.end() != iter)
          return true;

        for (iter = m_Children.begin(); iter != m_Children.end(); ++iter)
          {
            if ((*iter)->hasChild(object))
              {
                return true;
              }
          }
      }

    return false;
  }

  bool AbstractDecorator::hasChildren() const
  {
    s64 numChildren = numberOfChildren();
    return !(numChildren <= 0);
  }

  void AbstractDecorator::addChild(AbstractDecorator *object)
  {
    SDL_assertPrint(this != object, "%s", "cannot decorate self with self");
    //        SDL_assertPrint(!hasChild(object), "already has the decorator");

    object->setParent(this);
    m_Children.push_back(object);
  }

  void AbstractDecorator::removeChild(const u32 index)
  {
    SDL_assertPrint(index < numberOfChildren(), "%s",
                    "index must be smaller than the size of the array");
    removeChild(getChild(index));
  }

  void AbstractDecorator::removeChild(AbstractDecorator *object)
  {
    if (object && m_Children.size() > 0)
      {
        std::vector<AbstractDecorator *>::iterator iter =
            std::find(m_Children.begin(), m_Children.end(), object);

        if (iter != m_Children.end())
          {
            (*iter)->removeParent();
            m_Children.erase(iter);
          }
        /// SDL_assert(iter != m_Children.end());
      }
  }

  void AbstractDecorator::removeChildren() { m_Children.clear(); }

  s64 AbstractDecorator::numberOfChildren() const { return m_Children.size(); }

  void AbstractDecorator::replaceChild(AbstractDecorator *oldChild,
                                       AbstractDecorator *newChild)
  {
    AbstractDecorator *parent =
        dynamic_cast<AbstractDecorator *>(oldChild->getParent());

    parent->removeChild(oldChild);
    parent->addChild(newChild);
  }

  void AbstractDecorator::setName(const char *name)
  {
    SDL_assert(name != NULL);
    m_Name = name;
  }

  const char *AbstractDecorator::getName() const { return m_Name.c_str(); }

  void AbstractDecorator::setTag(const char *tag)
  {
    SDL_assert(tag != NULL);
    m_Tag = tag;
  }
  const char *AbstractDecorator::getTag() const { return m_Tag.c_str(); }
}
