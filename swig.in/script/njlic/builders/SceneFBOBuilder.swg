// Factory
% newobject njli::SceneFBOBuilder::create;
% delobject njli::SceneFBOBuilder::destroy;
% factory(
      njli::SceneFBOBuilder *njli::SceneFBOBuilder::create, njli::
                                                                SceneFBOBuilder /*Add the children to the njli::SceneFBOBuilder class*/);
% factory(
      njli::SceneFBOBuilder *njli::SceneFBOBuilder::clone, njli::
                                                               SceneFBOBuilder /*Add the children to the njli::SceneFBOBuilder class*/);
% factory(
      njli::SceneFBOBuilder *njli::SceneFBOBuilder::copy, njli::
                                                              SceneFBOBuilder /*Add the children to the njli::SceneFBOBuilder class*/);

// Extend
% extend njli::SceneFBOBuilder
{
  const char *__concat__(const char *s)
  {
    static std::string temp;
    std::string t1(*self);
    std::string t2(s);

    temp = (t1 + t2);
    return temp.c_str();
  }

  const char *__str__()
  {
    std::string s(*self);
    static char tmp[1024];
    sprintf(tmp, "%s", s.c_str());
    return tmp;
  }
}
