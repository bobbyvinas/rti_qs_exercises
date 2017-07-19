

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ShapesType.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef ShapesType_95528855_h
#define ShapesType_95528855_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

static const DDS_Char * SHAPETYPE_LIBRARY= "ShapeType_Library";
static const DDS_Char * SHAPETYPE_PROFILE= "ShapeType_Profile";

extern const char *ShapeTypeTYPENAME;

struct ShapeTypeSeq;
#ifndef NDDS_STANDALONE_TYPE
class ShapeTypeTypeSupport;
class ShapeTypeDataWriter;
class ShapeTypeDataReader;
#endif

class ShapeType 
{
  public:
    typedef struct ShapeTypeSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef ShapeTypeTypeSupport TypeSupport;
    typedef ShapeTypeDataWriter DataWriter;
    typedef ShapeTypeDataReader DataReader;
    #endif

    DDS_Char *   color ;
    DDS_Long   x ;
    DDS_Long   y ;
    DDS_Long   shapesize ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* ShapeType_get_typecode(void); /* Type code */

DDS_SEQUENCE(ShapeTypeSeq, ShapeType);

NDDSUSERDllExport
RTIBool ShapeType_initialize(
    ShapeType* self);

NDDSUSERDllExport
RTIBool ShapeType_initialize_ex(
    ShapeType* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool ShapeType_initialize_w_params(
    ShapeType* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void ShapeType_finalize(
    ShapeType* self);

NDDSUSERDllExport
void ShapeType_finalize_ex(
    ShapeType* self,RTIBool deletePointers);

NDDSUSERDllExport
void ShapeType_finalize_w_params(
    ShapeType* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ShapeType_finalize_optional_members(
    ShapeType* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool ShapeType_copy(
    ShapeType* dst,
    const ShapeType* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
typedef enum ShapeFillKind
{
    SOLID_FILL  = 0,      
    TRANSPARENT_FILL  = 1,      
    HORIZONTAL_HATCH_FILL  = 2,      
    VERTICAL_HATCH_FILL  = 3     
} ShapeFillKind;
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* ShapeFillKind_get_typecode(void); /* Type code */

DDS_SEQUENCE(ShapeFillKindSeq, ShapeFillKind);

NDDSUSERDllExport
RTIBool ShapeFillKind_initialize(
    ShapeFillKind* self);

NDDSUSERDllExport
RTIBool ShapeFillKind_initialize_ex(
    ShapeFillKind* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool ShapeFillKind_initialize_w_params(
    ShapeFillKind* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void ShapeFillKind_finalize(
    ShapeFillKind* self);

NDDSUSERDllExport
void ShapeFillKind_finalize_ex(
    ShapeFillKind* self,RTIBool deletePointers);

NDDSUSERDllExport
void ShapeFillKind_finalize_w_params(
    ShapeFillKind* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ShapeFillKind_finalize_optional_members(
    ShapeFillKind* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool ShapeFillKind_copy(
    ShapeFillKind* dst,
    const ShapeFillKind* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern const char *ShapeTypeExtendedTYPENAME;

struct ShapeTypeExtendedSeq;
#ifndef NDDS_STANDALONE_TYPE
class ShapeTypeExtendedTypeSupport;
class ShapeTypeExtendedDataWriter;
class ShapeTypeExtendedDataReader;
#endif

class ShapeTypeExtended 
: public ShapeType{
  public:
    typedef struct ShapeTypeExtendedSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef ShapeTypeExtendedTypeSupport TypeSupport;
    typedef ShapeTypeExtendedDataWriter DataWriter;
    typedef ShapeTypeExtendedDataReader DataReader;
    #endif

    ShapeFillKind   fillKind ;
    DDS_Float   angle ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* ShapeTypeExtended_get_typecode(void); /* Type code */

DDS_SEQUENCE(ShapeTypeExtendedSeq, ShapeTypeExtended);

NDDSUSERDllExport
RTIBool ShapeTypeExtended_initialize(
    ShapeTypeExtended* self);

NDDSUSERDllExport
RTIBool ShapeTypeExtended_initialize_ex(
    ShapeTypeExtended* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool ShapeTypeExtended_initialize_w_params(
    ShapeTypeExtended* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void ShapeTypeExtended_finalize(
    ShapeTypeExtended* self);

NDDSUSERDllExport
void ShapeTypeExtended_finalize_ex(
    ShapeTypeExtended* self,RTIBool deletePointers);

NDDSUSERDllExport
void ShapeTypeExtended_finalize_w_params(
    ShapeTypeExtended* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ShapeTypeExtended_finalize_optional_members(
    ShapeTypeExtended* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool ShapeTypeExtended_copy(
    ShapeTypeExtended* dst,
    const ShapeTypeExtended* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ShapesType */

