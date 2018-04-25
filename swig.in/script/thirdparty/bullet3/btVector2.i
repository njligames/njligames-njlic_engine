// ./btVector2.i

//Factory

//Extend
%extend btVector2
{
    const char *__str__()
    {
        static char buffer[1024];
        sprintf(buffer,"{\"btVector2\":[{\"x\":\"%f\", \"y\":\"%f\"}]}", self->x(),self->y());
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
        static char buffer[1024];
        sprintf(buffer,"{\"btVector2\":[{\"x\":\"%f\", \"y\":\"%f\"}]}", self->x(),self->y());
        return strcat(buffer, s);
    }
    bool __eq__(const btVector2& b){return *self == b;}
    bool __lt__( btVector2& b){return *self < b;}
    bool __le__( btVector2& b){return *self <= b;}
};

