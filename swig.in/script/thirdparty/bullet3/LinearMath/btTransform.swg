// ./LinearMath/btTransform.i

//Factory

//Extend
%extend btTransform
{
    const char *__str__()
    {
        std::string temp = btTransformDecorator(self);
        static char buffer[1024];
        sprintf(buffer, "%s", temp.c_str());
        return buffer;
    }
    
    btVector3 __mul__(const btVector3& b){return *self * b;}
    btQuaternion __mul__(const btQuaternion& b){return *self * b;}
    btTransform __mul__(const btTransform& b){return *self * b;}
    bool __eq__(const btTransform& b){return *self == b;}
    
    const char *__concat__(const char *s) {
        std::string _temp = btTransformDecorator(self);
        static char buffer[1024];
        sprintf(buffer, "%s", _temp.c_str());
        
        static std::string temp;
        std::string t1(buffer);
        std::string t2(s);
        
        temp = string_format("[%s,%s]", t1.c_str(), t2.c_str());
        return temp.c_str();
    }
};
