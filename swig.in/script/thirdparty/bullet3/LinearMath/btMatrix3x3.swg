// ./LinearMath/btMatrix3x3.i

//Factory

//Extend
%extend btMatrix3x3
{
    const char *__str__()
    {
        std::string temp = btMatrix3x3Decorator(self);
        static char buffer[1024];
        sprintf(buffer, "%s", temp.c_str());
        return buffer;

    }
    
    
    btMatrix3x3 __add__(const btMatrix3x3& b){return *self + b;}
    btMatrix3x3 __sub__(const btMatrix3x3& b){return *self - b;}
    btMatrix3x3 __mul__(const btMatrix3x3& b){return *self * b;}
    btVector3 __mul__(const btVector3& b){return *self * b;}
    btMatrix3x3 __mul__(const btScalar& b){return *self * b;}
    const char *__concat__(const char *s)
    {
        std::string _temp = btMatrix3x3Decorator(self);
        static char buffer[1024];
        sprintf(buffer, "%s", _temp.c_str());
        
        static std::string temp;
        std::string t1(buffer);
        std::string t2(s);
        
        temp = string_format("[%s,%s]", t1.c_str(), t2.c_str());
        return temp.c_str();
    }
    bool __eq__(const btMatrix3x3& b){return *self == b;}
};

