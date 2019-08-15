// ./btVector2.i

//Factory

//Extend
%extend btVector2
{
    const char *__str__()
    {
        std::string temp = btVector2Decorator(self);
        static char buffer[1024];
        sprintf(buffer, "%s", temp.c_str());
        return buffer;
    }
    
    btVector2 __add__(const btVector2& b){return *self + b;}
    btVector2 __sub__(const btVector2& b){return *self - b;}
    btVector2 __mul__(const btVector2& b){return *self * b;}
    btVector2 __mul__(const btScalar& b){return *self * b;}
    btVector2 __div__(const btVector2& b){return *self / b;}
    btVector2 __div__(const btScalar& b){return *self / b;}
    btVector2 __neg__(){return -(*self);}
    
    const char *__concat__(const char *s) {
        std::string _temp = btVector2Decorator(self);
        static char buffer[1024];
        sprintf(buffer, "%s", _temp.c_str());
        
        static std::string temp;
        std::string t1(buffer);
        std::string t2(s);
        
        temp = string_format("[%s,%s]", t1.c_str(), t2.c_str());
        return temp.c_str();
    }
    bool __eq__(const btVector2& b){return *self == b;}
    bool __lt__( btVector2& b){return *self < b;}
    bool __le__( btVector2& b){return *self <= b;}
};

