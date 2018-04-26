// ./LinearMath/btTransform.i

//Factory

//Extend
%extend btTransform
{
    const char *__str__()
    {
        static char buffer[1024];
        btScalar *m = new btScalar[16];
        self->getOpenGLMatrix(m);
        sprintf(buffer,"{\"btTransform\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", \"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", \"ww\":\"%f\"}]}",
                m[0],
                m[1],
                m[2],
                m[3],
                m[4],
                m[5],
                m[6],
                m[7],
                m[8],
                m[9],
                m[10],
                m[11],
                m[12],
                m[13],
                m[14],
                m[15]);
        
        delete [] m;
        return buffer;
    }
    
    btVector3 __mul__(const btVector3& b){return *self * b;}
    btQuaternion __mul__(const btQuaternion& b){return *self * b;}
    btTransform __mul__(const btTransform& b){return *self * b;}
    bool __eq__(const btTransform& b){return *self == b;}
    
    const char *__concat__(const char *s) {
        static char buffer[1024];
        btScalar *m = new btScalar[16];
        self->getOpenGLMatrix(m);
        sprintf(buffer,"{\"btTransform\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", \"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", \"ww\":\"%f\"}]}",
                m[0],
                m[1],
                m[2],
                m[3],
                m[4],
                m[5],
                m[6],
                m[7],
                m[8],
                m[9],
                m[10],
                m[11],
                m[12],
                m[13],
                m[14],
                m[15]);
        
        delete [] m;
        return buffer;
        
        strcat(buffer, s);
    }
};
