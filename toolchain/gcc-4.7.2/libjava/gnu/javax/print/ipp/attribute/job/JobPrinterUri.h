
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_javax_print_ipp_attribute_job_JobPrinterUri__
#define __gnu_javax_print_ipp_attribute_job_JobPrinterUri__

#pragma interface

#include <javax/print/attribute/URISyntax.h>
extern "Java"
{
  namespace gnu
  {
    namespace javax
    {
      namespace print
      {
        namespace ipp
        {
          namespace attribute
          {
            namespace job
            {
                class JobPrinterUri;
            }
          }
        }
      }
    }
  }
  namespace java
  {
    namespace net
    {
        class URI;
    }
  }
}

class gnu::javax::print::ipp::attribute::job::JobPrinterUri : public ::javax::print::attribute::URISyntax
{

public:
  JobPrinterUri(::java::net::URI *);
  ::java::lang::Class * getCategory();
  ::java::lang::String * getName();
  static ::java::lang::Class class$;
};

#endif // __gnu_javax_print_ipp_attribute_job_JobPrinterUri__
