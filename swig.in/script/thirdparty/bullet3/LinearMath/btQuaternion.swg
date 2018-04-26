// ./LinearMath/btQuaternion.i

//Factory

//Extend
%extend btQuaternion
{
    const char *__str__()
    {
        static char axisBuffer[1024];
        sprintf(axisBuffer,
                "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}",
                self->getAxis().x(), self->getAxis().y(), self->getAxis().z());
        
        static char buffer[2048];
        sprintf(buffer,"{\"btQuaternion\":[{\"angle\":\"%f\", \"axis\":%s}]}",
                self->getAngle(),
                axisBuffer);
        return buffer;
    }
    btQuaternion(const btQuaternion &rhs)
    {
        btQuaternion *v = new btQuaternion(rhs);
        return v;
    }
    
    btQuaternion __add__(const btQuaternion& b){return *self + b;}
    btQuaternion __sub__(const btQuaternion& b){return *self - b;}
    btQuaternion __mul__(const btQuaternion& b){return *self * b;}
    btQuaternion __mul__(const btVector3& b){return *self * b;}
    btQuaternion __mul__(const btScalar& b){return *self * b;}
    btQuaternion __div__(const btScalar& b){return *self / b;}
    
    const char *__concat__(const char *s)
    {
        static char axisBuffer[1024];
        sprintf(axisBuffer,
                "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}",
                self->getAxis().x(), self->getAxis().y(), self->getAxis().z());
        
        static char bufferA[2048];
        sprintf(bufferA,"{\"btQuaternion\":[{\"angle\":\"%f\", \"axis\":%s}]}",
                self->getAngle(),
                axisBuffer);
        
        return strcat(bufferA, s);
    }
};

