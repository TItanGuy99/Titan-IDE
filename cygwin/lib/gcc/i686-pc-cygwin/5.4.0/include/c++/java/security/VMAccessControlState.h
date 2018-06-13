
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_security_VMAccessControlState__
#define __java_security_VMAccessControlState__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace java
  {
    namespace security
    {
        class VMAccessControlState;
    }
  }
}

class java::security::VMAccessControlState : public ::java::lang::Object
{

  VMAccessControlState();
public: // actually package-private
  static ::java::security::VMAccessControlState * getThreadState();
  virtual jboolean isInGetContext();
  virtual void setInGetContext(jboolean);
  virtual ::java::util::LinkedList * getContexts();
private:
  ::java::util::LinkedList * __attribute__((aligned(__alignof__( ::java::lang::Object)))) contexts;
  jboolean inGetContext;
public:
  static ::java::lang::Class class$;
};

#endif // __java_security_VMAccessControlState__
