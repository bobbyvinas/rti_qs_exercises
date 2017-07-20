
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ShapeType.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#pragma once

struct DDS_TypeCode;

using namespace System;
using namespace DDS;

public ref class SHAPETYPE_LIBRARY sealed {
  public:
    static const System::String^ VALUE =
    "ShapeType_Library";

  private:
    SHAPETYPE_LIBRARY() {}
};

public ref class SHAPETYPE_PROFILE sealed {
  public:
    static const System::String^ VALUE =
    "ShapeType_Profile";

  private:
    SHAPETYPE_PROFILE() {}
};

public ref struct ShapeType
:  public DDS::ICopyable<ShapeType^> {
    // --- Declared members: -------------------------------------------------
  public: 

    System::String^ color;
    System::Int32 x;
    System::Int32 y;
    System::Int32 shapesize;

    // --- Static constants: -------------------------------------    
  public:

    // --- Constructors and destructors: -------------------------------------
  public:
    ShapeType();

    // --- Utility methods: --------------------------------------------------
  public:

    virtual void clear() ;

    virtual System::Boolean copy_from(ShapeType^ src);

    virtual System::Boolean Equals(System::Object^ other) override;
    static DDS::TypeCode^ get_typecode();

  private:
    static DDS::TypeCode^ _typecode;

}; // class ShapeType

public ref class ShapeTypeSeq sealed
: public DDS::UserRefSequence<ShapeType^> {
  public:
    ShapeTypeSeq() :
        DDS::UserRefSequence<ShapeType^>() {
            // empty
    }
    ShapeTypeSeq(System::Int32 max) :
        DDS::UserRefSequence<ShapeType^>(max) {
            // empty
    }
    ShapeTypeSeq(ShapeTypeSeq^ src) :
        DDS::UserRefSequence<ShapeType^>(src) {
            // empty
    }
};

#define NDDSUSERDllExport

NDDSUSERDllExport DDS_TypeCode* ShapeType_get_typecode();

