//Factory
%newobject njli::Material::create;
%delobject njli::Material::destroy;
%factory(njli::Material *njli::Material::create, njli::Material /*Add the children to the njli::Material class*/);
%factory(njli::Material *njli::Material::clone, njli::Material /*Add the children to the njli::Material class*/);
%factory(njli::Material *njli::Material::copy, njli::Material /*Add the children to the njli::Material class*/);

//Extend
%extend njli::Material
{
    const char *__concat__(const char *s) {
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
