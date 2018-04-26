// ./LinearMath/btMatrix3x3.i

//Factory

//Extend
%extend btMatrix3x3
{
    const char *__str__()
    {
        static char buffer[1024];
        sprintf(buffer,"{\"btMatrix3x3\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\"}]}",
                self->getRow(0).x(),
                self->getRow(0).y(),
                self->getRow(0).z(),
                self->getRow(1).x(),
                self->getRow(1).y(),
                self->getRow(1).z(),
                self->getRow(2).x(),
                self->getRow(2).y(),
                self->getRow(2).z());
        
        return buffer;

    }
    
    
    btMatrix3x3 __add__(const btMatrix3x3& b){return *self + b;}
    btMatrix3x3 __sub__(const btMatrix3x3& b){return *self - b;}
    btMatrix3x3 __mul__(const btMatrix3x3& b){return *self * b;}
    btVector3 __mul__(const btVector3& b){return *self * b;}
    btMatrix3x3 __mul__(const btScalar& b){return *self * b;}
    const char *__concat__(const btMatrix3x3& b)
    {
        static char tmp[1024];
        sprintf(tmp,"btMatrix3x3(TODO)");
        std::string t1(tmp);
        
        sprintf(tmp,"btMatrix3x3(TODO)");
        std::string t2(tmp);
        
        return (t1 + t2).c_str();
    }
    bool __eq__(const btMatrix3x3& b){return *self == b;}
};

