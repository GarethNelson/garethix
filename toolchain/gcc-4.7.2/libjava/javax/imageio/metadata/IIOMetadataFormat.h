
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_imageio_metadata_IIOMetadataFormat__
#define __javax_imageio_metadata_IIOMetadataFormat__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  namespace javax
  {
    namespace imageio
    {
        class ImageTypeSpecifier;
      namespace metadata
      {
          class IIOMetadataFormat;
      }
    }
  }
}

class javax::imageio::metadata::IIOMetadataFormat : public ::java::lang::Object
{

public:
  virtual jboolean canNodeAppear(::java::lang::String *, ::javax::imageio::ImageTypeSpecifier *) = 0;
  virtual jint getAttributeDataType(::java::lang::String *, ::java::lang::String *) = 0;
  virtual ::java::lang::String * getAttributeDefaultValue(::java::lang::String *, ::java::lang::String *) = 0;
  virtual ::java::lang::String * getAttributeDescription(::java::lang::String *, ::java::lang::String *, ::java::util::Locale *) = 0;
  virtual JArray< ::java::lang::String * > * getAttributeEnumerations(::java::lang::String *, ::java::lang::String *) = 0;
  virtual jint getAttributeListMaxLength(::java::lang::String *, ::java::lang::String *) = 0;
  virtual jint getAttributeListMinLength(::java::lang::String *, ::java::lang::String *) = 0;
  virtual ::java::lang::String * getAttributeMaxValue(::java::lang::String *, ::java::lang::String *) = 0;
  virtual ::java::lang::String * getAttributeMinValue(::java::lang::String *, ::java::lang::String *) = 0;
  virtual JArray< ::java::lang::String * > * getAttributeNames(::java::lang::String *) = 0;
  virtual jint getAttributeValueType(::java::lang::String *, ::java::lang::String *) = 0;
  virtual JArray< ::java::lang::String * > * getChildNames(::java::lang::String *) = 0;
  virtual jint getChildPolicy(::java::lang::String *) = 0;
  virtual ::java::lang::String * getElementDescription(::java::lang::String *, ::java::util::Locale *) = 0;
  virtual jint getElementMaxChildren(::java::lang::String *) = 0;
  virtual jint getElementMinChildren(::java::lang::String *) = 0;
  virtual jint getObjectArrayMaxLength(::java::lang::String *) = 0;
  virtual jint getObjectArrayMinLength(::java::lang::String *) = 0;
  virtual ::java::lang::Class * getObjectClass(::java::lang::String *) = 0;
  virtual ::java::lang::Object * getObjectDefaultValue(::java::lang::String *) = 0;
  virtual JArray< ::java::lang::Object * > * getObjectEnumerations(::java::lang::String *) = 0;
  virtual ::java::lang::Comparable * getObjectMaxValue(::java::lang::String *) = 0;
  virtual ::java::lang::Comparable * getObjectMinValue(::java::lang::String *) = 0;
  virtual jint getObjectValueType(::java::lang::String *) = 0;
  virtual ::java::lang::String * getRootName() = 0;
  virtual jboolean isAttributeRequired(::java::lang::String *, ::java::lang::String *) = 0;
  static const jint CHILD_POLICY_ALL = 1;
  static const jint CHILD_POLICY_CHOICE = 3;
  static const jint CHILD_POLICY_EMPTY = 0;
  static const jint CHILD_POLICY_MAX = 5;
  static const jint CHILD_POLICY_REPEAT = 5;
  static const jint CHILD_POLICY_SEQUENCE = 4;
  static const jint CHILD_POLICY_SOME = 2;
  static const jint DATATYPE_BOOLEAN = 1;
  static const jint DATATYPE_DOUBLE = 4;
  static const jint DATATYPE_FLOAT = 3;
  static const jint DATATYPE_INTEGER = 2;
  static const jint DATATYPE_STRING = 0;
  static const jint VALUE_ARBITRARY = 1;
  static const jint VALUE_ENUMERATION = 16;
  static const jint VALUE_LIST = 32;
  static const jint VALUE_NONE = 0;
  static const jint VALUE_RANGE = 2;
  static const jint VALUE_RANGE_MAX_INCLUSIVE = 10;
  static const jint VALUE_RANGE_MAX_INCLUSIVE_MASK = 8;
  static const jint VALUE_RANGE_MIN_INCLUSIVE = 6;
  static const jint VALUE_RANGE_MIN_INCLUSIVE_MASK = 4;
  static const jint VALUE_RANGE_MIN_MAX_INCLUSIVE = 14;
  static ::java::lang::Class class$;
} __attribute__ ((java_interface));

#endif // __javax_imageio_metadata_IIOMetadataFormat__
