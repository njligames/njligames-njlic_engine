// ./BulletCollision/NarrowPhaseCollision/btManifoldPoint.i

//Factory

//Extend
%extend btManifoldPoint
{
    const char *__str__()
    {
        static char pointOnABuffer[1024];
        sprintf(pointOnABuffer,
                "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}",
                self->getPositionWorldOnA().x(), self->getPositionWorldOnA().y(), self->getPositionWorldOnA().z());
        
        static char pointOnBBuffer[1024];
        sprintf(pointOnBBuffer,
                "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}",
                self->getPositionWorldOnB().x(), self->getPositionWorldOnB().y(), self->getPositionWorldOnB().z());
        
        static char buffer[2048];
        sprintf(buffer,
                "{\"btManifoldPoint\":[{\"distance\":\"%f\", \"lifetime\":\"%d\", \"Position On A\":%s, \"Position On B\":%s, \"Applied Impulse\":\"%f\"}]}",
                self->getDistance(),
                self->getLifeTime(),
                pointOnABuffer,
                pointOnBBuffer,
                self->getAppliedImpulse());
        
        return buffer;
    }
    
    const char *__concat__(const char *s)
    {
        static char pointOnABuffer[1024];
        sprintf(pointOnABuffer,
                "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}",
                self->getPositionWorldOnA().x(), self->getPositionWorldOnA().y(), self->getPositionWorldOnA().z());
        
        static char pointOnBBuffer[1024];
        sprintf(pointOnBBuffer,
                "{\"btVector3\":[{\"x\":\"%f\", \"y\":\"%f\", \"z\":\"%f\"}]}",
                self->getPositionWorldOnB().x(), self->getPositionWorldOnB().y(), self->getPositionWorldOnB().z());
        
        static char buffer[2048];
        sprintf(buffer,
                "{\"btManifoldPoint\":[{\"distance\":\"%f\", \"lifetime\":\"%d\", \"Position On A\":%s, \"Position On B\":%s, \"Applied Impulse\":\"%f\"}]}",
                self->getDistance(),
                self->getLifeTime(),
                pointOnABuffer,
                pointOnBBuffer,
                self->getAppliedImpulse());
        
        return strcat(buffer, s);
    }
}
