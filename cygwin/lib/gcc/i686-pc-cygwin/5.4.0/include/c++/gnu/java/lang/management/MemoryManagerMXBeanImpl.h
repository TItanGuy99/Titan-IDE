
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_lang_management_MemoryManagerMXBeanImpl__
#define __gnu_java_lang_management_MemoryManagerMXBeanImpl__

#pragma interface

#include <gnu/java/lang/management/BeanImpl.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace lang
      {
        namespace management
        {
            class MemoryManagerMXBeanImpl;
        }
      }
    }
  }
}

class gnu::java::lang::management::MemoryManagerMXBeanImpl : public ::gnu::java::lang::management::BeanImpl
{

public:
  MemoryManagerMXBeanImpl(::java::lang::String *);
public: // actually protected
  MemoryManagerMXBeanImpl(::java::lang::String *, ::java::lang::Class *);
public:
  virtual JArray< ::java::lang::String * > * getMemoryPoolNames();
  virtual ::java::lang::String * getName();
  virtual jboolean isValid();
public: // actually protected
  ::java::lang::String * __attribute__((aligned(__alignof__( ::gnu::java::lang::management::BeanImpl)))) name;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_java_lang_management_MemoryManagerMXBeanImpl__
