

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for protoss.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 28251)
#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __protoss_h__
#define __protoss_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGameObject_FWD_DEFINED__
#define __IGameObject_FWD_DEFINED__
typedef interface IGameObject IGameObject;

#endif 	/* __IGameObject_FWD_DEFINED__ */


#ifndef __INexus_FWD_DEFINED__
#define __INexus_FWD_DEFINED__
typedef interface INexus INexus;

#endif 	/* __INexus_FWD_DEFINED__ */


#ifndef __IProbe_FWD_DEFINED__
#define __IProbe_FWD_DEFINED__
typedef interface IProbe IProbe;

#endif 	/* __IProbe_FWD_DEFINED__ */


#ifndef __INexus_FWD_DEFINED__
#define __INexus_FWD_DEFINED__
typedef interface INexus INexus;

#endif 	/* __INexus_FWD_DEFINED__ */


#ifndef __IProbe_FWD_DEFINED__
#define __IProbe_FWD_DEFINED__
typedef interface IProbe IProbe;

#endif 	/* __IProbe_FWD_DEFINED__ */


#ifndef __Nexus_FWD_DEFINED__
#define __Nexus_FWD_DEFINED__

#ifdef __cplusplus
typedef class Nexus Nexus;
#else
typedef struct Nexus Nexus;
#endif /* __cplusplus */

#endif 	/* __Nexus_FWD_DEFINED__ */


#ifndef __Probe_FWD_DEFINED__
#define __Probe_FWD_DEFINED__

#ifdef __cplusplus
typedef class Probe Probe;
#else
typedef struct Probe Probe;
#endif /* __cplusplus */

#endif 	/* __Probe_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IGameObject_INTERFACE_DEFINED__
#define __IGameObject_INTERFACE_DEFINED__

/* interface IGameObject */
/* [uuid][object] */ 


EXTERN_C const IID IID_IGameObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59644217-3e52-4202-ba49-f473590cc61a")
    IGameObject : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Minerals( 
            /* [retval][out] */ LONG *minerals) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BuildTime( 
            /* [retval][out] */ LONG *buildtime) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGameObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGameObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGameObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGameObject * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGameObject * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Minerals )( 
            IGameObject * This,
            /* [retval][out] */ LONG *minerals);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BuildTime )( 
            IGameObject * This,
            /* [retval][out] */ LONG *buildtime);
        
        END_INTERFACE
    } IGameObjectVtbl;

    interface IGameObject
    {
        CONST_VTBL struct IGameObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGameObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGameObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGameObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGameObject_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IGameObject_get_Minerals(This,minerals)	\
    ( (This)->lpVtbl -> get_Minerals(This,minerals) ) 

#define IGameObject_get_BuildTime(This,buildtime)	\
    ( (This)->lpVtbl -> get_BuildTime(This,buildtime) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGameObject_INTERFACE_DEFINED__ */


#ifndef __INexus_INTERFACE_DEFINED__
#define __INexus_INTERFACE_DEFINED__

/* interface INexus */
/* [uuid][object] */ 


EXTERN_C const IID IID_INexus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5F45CBC-4439-418C-A9F9-05AC67525E43")
    INexus : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateUnit( 
            /* [in] */ BSTR unit_name,
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct INexusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INexus * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INexus * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INexus * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateUnit )( 
            INexus * This,
            /* [in] */ BSTR unit_name,
            /* [retval][out] */ IUnknown **ppUnk);
        
        END_INTERFACE
    } INexusVtbl;

    interface INexus
    {
        CONST_VTBL struct INexusVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INexus_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INexus_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INexus_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INexus_CreateUnit(This,unit_name,ppUnk)	\
    ( (This)->lpVtbl -> CreateUnit(This,unit_name,ppUnk) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INexus_INTERFACE_DEFINED__ */


#ifndef __IProbe_INTERFACE_DEFINED__
#define __IProbe_INTERFACE_DEFINED__

/* interface IProbe */
/* [uuid][object] */ 


EXTERN_C const IID IID_IProbe;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("246A22D5-CF02-44B2-BF09-AAB95A34E0CF")
    IProbe : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ConstructBuilding( 
            /* [in] */ BSTR building_name,
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProbeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProbe * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProbe * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProbe * This);
        
        HRESULT ( STDMETHODCALLTYPE *ConstructBuilding )( 
            IProbe * This,
            /* [in] */ BSTR building_name,
            /* [retval][out] */ IUnknown **ppUnk);
        
        END_INTERFACE
    } IProbeVtbl;

    interface IProbe
    {
        CONST_VTBL struct IProbeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProbe_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProbe_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProbe_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProbe_ConstructBuilding(This,building_name,ppUnk)	\
    ( (This)->lpVtbl -> ConstructBuilding(This,building_name,ppUnk) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProbe_INTERFACE_DEFINED__ */



#ifndef __ProtossLib_LIBRARY_DEFINED__
#define __ProtossLib_LIBRARY_DEFINED__

/* library ProtossLib */
/* [helpstring][version][uuid] */ 




EXTERN_C const IID LIBID_ProtossLib;

EXTERN_C const CLSID CLSID_Nexus;

#ifdef __cplusplus

class DECLSPEC_UUID("F5353C58-CFD9-4204-8D92-D274C7578B53")
Nexus;
#endif

EXTERN_C const CLSID CLSID_Probe;

#ifdef __cplusplus

class DECLSPEC_UUID("EFF8970E-C50F-45E0-9284-291CE5A6F771")
Probe;
#endif
#endif /* __ProtossLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


