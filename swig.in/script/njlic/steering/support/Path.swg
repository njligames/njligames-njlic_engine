//Factory

//Array

//Extend
%extend njli::Path
{
    const char *__concat__(const char *s) {
//Calvin
        static std::string temp;
        std::string t1(*self);
        std::string t2(s);
        
        temp = (t1 + t2);
        return temp.c_str();
    }
    
    const char *__str__()
    {
        static std::string temp(*self);
        return temp.c_str();
    }
};

//Typemap
