//%rename(operator_new) operator new;
//%rename(operator_delete) operator delete;
//%rename(operator_new_array) operator new[];
//%rename(operator_delete_array) operator delete[];

%rename(btScalarPtr) operator btScalar*;
%rename(btScalarConstPtr) operator const btScalar*;
%rename(operator_btVector3) operator btVector3;

%rename(getPlane_btVector3_btVector3_int) getPlane(btVector3 &,btVector3 &,int) const;

%rename(str) operator std::string;


#if defined(SWIGEMBIND)
//https://github.com/swig/swig/blob/master/Examples/test-suite/operator_overload.i
%rename(Equal) operator =;
%rename(PlusEqual) operator +=;
%rename(MinusEqual) operator -=;
%rename(MultiplyEqual) operator *=;
%rename(DivideEqual) operator /=;
%rename(PercentEqual) operator %=;
%rename(Plus) operator +;
%rename(Minus) operator -;
%rename(Multiply) operator *;
%rename(Divide) operator /;
%rename(Percent) operator %;
%rename(Not) operator !;
%rename(IndexIntoConst) operator[](unsigned idx) const;
%rename(IndexInto) operator[](unsigned idx);
%rename(Functor) operator ();
%rename(EqualEqual) operator ==;
%rename(NotEqual) operator !=;
%rename(LessThan) operator <;
%rename(LessThanEqual) operator <=;
%rename(GreaterThan) operator >;
%rename(GreaterThanEqual) operator >=;
%rename(And) operator &&;
%rename(Or) operator ||;
%rename(PlusPlusPrefix) operator++();
%rename(PlusPlusPostfix) operator++(int);
%rename(MinusMinusPrefix) operator--();
%rename(MinusMinusPostfix) operator--(int);

%rename(IndexInto) *::operator[](unsigned idx); // some languages have a %rename *::operator[] already in place, which seems to takes precedence over the above %rename operator[].

#endif
