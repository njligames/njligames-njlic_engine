// Factory
% newobject njli::SceneFBO::create;
% delobject njli::SceneFBO::destroy;
% factory(njli::SceneFBO *njli::SceneFBO::create,
          njli::SceneFBO /*Add the children to the njli::SceneFBO class*/);
% factory(njli::SceneFBO *njli::SceneFBO::clone,
          njli::SceneFBO /*Add the children to the njli::SceneFBO class*/);
% factory(njli::SceneFBO *njli::SceneFBO::copy,
          njli::SceneFBO /*Add the children to the njli::SceneFBO class*/);

// Extend
% extend njli::SceneFBO
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
    /*WILL FARRELL*/
    sprintf(tmp, "%s", s.c_str());
    return tmp;
  }
}
