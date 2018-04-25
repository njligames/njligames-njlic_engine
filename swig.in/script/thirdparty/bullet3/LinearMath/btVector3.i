// ./LinearMath/btVector3.i

//MARK: btVector3

//Factory

//Extend
%extend btVector3
{
    const char *__str__()
    {
        static char buffer[1024];
        sprintf(buffer,"{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}", self->x(), self->y(), self->z());
        return buffer;
    }
    btVector3(const btVector3 &rhs) {
        btVector3 *v = new btVector3(rhs);
        return v;
    }
    
    
    btVector3 __add__(const btVector3& b){return *self + b;}
    btVector3 __sub__(const btVector3& b){return *self - b;}
    btVector3 __mul__(const btVector3& b){return *self * b;}
    btVector3 __mul__(const btMatrix3x3& b){return *self * b;}
    btVector3 __mul__(const btScalar& b){return *self * b;}
    btQuaternion __mul__(const btQuaternion& b){return *self * b;}
    btVector3 __div__(const btVector3& b){return *self / b;}
    btVector3 __div__(const btScalar& b){return *self / b;}
    btVector3 __neg__(){return -(*self);}
    
    const char *__concat__(const char *s) {
        static char tmp[1024];
        sprintf(tmp,"btVector3(%f,%f,%f)", self->x(),self->y(),self->z());
        
        static std::string temp;
        std::string t1(tmp);
        std::string t2(s);
        
        temp = (t1 + t2);
        return temp.c_str();
    }
    
    bool __eq__(const btVector3& b){return *self == b;}
    bool __lt__( btVector3& b){return *self < b;}
    bool __le__( btVector3& b){return *self <= b;}
    
};


//MARK: btVector4

//Factory

//Extend
%extend btVector4
{
    const char *__str__()
    {
        static char buffer[1024];
        sprintf(buffer,"{\"btVector4\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\", \"w\":\"%f\"}]}", self->x(), self->y(), self->z(), self->w());
        return buffer;
    }
    
    btVector4(const btVector4 &rhs)
    {
        btVector4 *v = new btVector4(rhs);
        return v;
    }
    
    const char *__concat__(const char *s) {
        static char tmp[1024];
        sprintf(tmp,"btVector4(%f,%f,%f,%f)", self->x(),self->y(),self->z(),self->w());
        
        static std::string temp;
        std::string t1(tmp);
        std::string t2(s);
        
        temp = (t1 + t2);
        return temp.c_str();
    }
    
    bool __eq__(const btVector4& b){return *self == b;}
    bool __lt__( btVector4& b){return *self < b;}
    bool __le__( btVector4& b){return *self <= b;}
};

//Typemap

