//Factory
%newobject njli::MeshGeometryBuilder::create;
%delobject njli::MeshGeometryBuilder::destroy;
%factory(njli::MeshGeometryBuilder *njli::MeshGeometryBuilder::create, njli::MeshGeometryBuilder /*Add the children to the njli::MeshGeometryBuilder class*/);
%factory(njli::MeshGeometryBuilder *njli::MeshGeometryBuilder::clone, njli::MeshGeometryBuilder /*Add the children to the njli::MeshGeometryBuilder class*/);
%factory(njli::MeshGeometryBuilder *njli::MeshGeometryBuilder::copy, njli::MeshGeometryBuilder /*Add the children to the njli::MeshGeometryBuilder class*/);

//Extend
%extend njli::MeshGeometryBuilder
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
