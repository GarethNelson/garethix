
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_nio_CharBuffer__
#define __java_nio_CharBuffer__

#pragma interface

#include <java/nio/Buffer.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace gcj
    {
        class RawData;
    }
  }
  namespace java
  {
    namespace nio
    {
        class ByteOrder;
        class CharBuffer;
    }
  }
}

class java::nio::CharBuffer : public ::java::nio::Buffer
{

public: // actually package-private
  CharBuffer(jint, jint, jint, jint, ::gnu::gcj::RawData *, JArray< jchar > *, jint);
public:
  static ::java::nio::CharBuffer * allocate(jint);
  static ::java::nio::CharBuffer * wrap(JArray< jchar > *, jint, jint);
  static ::java::nio::CharBuffer * wrap(::java::lang::CharSequence *);
  static ::java::nio::CharBuffer * wrap(::java::lang::CharSequence *, jint, jint);
  static ::java::nio::CharBuffer * wrap(JArray< jchar > *);
  virtual ::java::nio::CharBuffer * get(JArray< jchar > *, jint, jint);
  virtual jint read(::java::nio::CharBuffer *);
  virtual ::java::nio::CharBuffer * get(JArray< jchar > *);
  virtual ::java::nio::CharBuffer * put(::java::nio::CharBuffer *);
  virtual ::java::nio::CharBuffer * put(JArray< jchar > *, jint, jint);
  virtual ::java::nio::CharBuffer * put(JArray< jchar > *);
  virtual jboolean hasArray();
  virtual JArray< jchar > * array();
  virtual jint arrayOffset();
  virtual jint hashCode();
  virtual jboolean equals(::java::lang::Object *);
  virtual jint CharBuffer$compareTo(::java::nio::CharBuffer *);
  virtual ::java::nio::ByteOrder * order() = 0;
  virtual jchar get() = 0;
  virtual ::java::nio::CharBuffer * put(jchar) = 0;
  virtual jchar get(jint) = 0;
  virtual ::java::nio::CharBuffer * put(jint, jchar) = 0;
  virtual ::java::nio::CharBuffer * compact() = 0;
  virtual jboolean isDirect() = 0;
  virtual ::java::nio::CharBuffer * slice() = 0;
  virtual ::java::nio::CharBuffer * duplicate() = 0;
  virtual ::java::nio::CharBuffer * asReadOnlyBuffer() = 0;
  virtual ::java::lang::String * toString();
  virtual jint length();
  virtual ::java::lang::CharSequence * subSequence(jint, jint) = 0;
  virtual ::java::nio::CharBuffer * put(::java::lang::String *, jint, jint);
  virtual ::java::nio::CharBuffer * put(::java::lang::String *);
  virtual jchar charAt(jint);
  virtual ::java::nio::CharBuffer * CharBuffer$append(jchar);
  virtual ::java::nio::CharBuffer * CharBuffer$append(::java::lang::CharSequence *);
  virtual ::java::nio::CharBuffer * CharBuffer$append(::java::lang::CharSequence *, jint, jint);
  virtual ::java::lang::Appendable * append(::java::lang::CharSequence *, jint, jint);
  virtual ::java::lang::Appendable * append(::java::lang::CharSequence *);
  virtual ::java::lang::Appendable * append(jchar);
  virtual jint compareTo(::java::lang::Object *);
public: // actually package-private
  jint __attribute__((aligned(__alignof__( ::java::nio::Buffer)))) array_offset;
  JArray< jchar > * backing_buffer;
public:
  static ::java::lang::Class class$;
};

#endif // __java_nio_CharBuffer__
