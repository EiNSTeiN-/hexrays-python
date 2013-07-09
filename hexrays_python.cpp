//---------------------------------------------------------------------
// Hexrays-Python - Python bindings for Hexrays Decompiler
// 
// This plugin makes the `hexrays` module available in the python
// environment of IDA when the Hexrays Decompiler plugin is 
// available.
//
// Author: EiNSTeiN_ <einstein@g3nius.org>
// Copyright (C) 2013 ESET
// 
// Original copyright notice retained below:
//---------------------------------------------------------------------
//
// Copyright (c) The IDAPython Team <idapython@googlegroups.com>
//
// All rights reserved.
//
// For detailed copyright information see the file COPYING in
// the root of the distribution archive.
//---------------------------------------------------------------------
// hexrays_python.cpp - Main plugin code
//---------------------------------------------------------------------
#include <Python.h>

//-------------------------------------------------------------------------
// This define fixes the redefinition of ssize_t
#ifdef HAVE_SSIZE_T
#define _SSIZE_T_DEFINED 1
#endif

#ifdef __LINUX__
#include <dlfcn.h>
#endif
#ifdef __MAC__
#include <mach-o/dyld.h>
#endif
#include <ida.hpp>
#include <idp.hpp>
#include <expr.hpp>
#include <diskio.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <hexrays.hpp>

//#include "pywraps.hpp"

//-------------------------------------------------------------------------
// Defines and constants

// Python-style version tuple comes from the makefile
// Only the serial and status is set here
#define S_IDAPYTHON                              "hexrays_python"


//-------------------------------------------------------------------------
// Global variables
static bool g_initialized = false;

hexdsp_t *hexdsp = NULL;

//-------------------------------------------------------------------------
// Prototypes and forward declarations

// Alias to SWIG_Init
//lint -esym(526,init_idaapi) not defined
extern "C" void init_hexrays(void);

// Plugin run() callback
void idaapi run(int arg);

//-------------------------------------------------------------------------
// Initialize the Python environment
bool HexraysPython_Init(void)
{
  // Already initialized?
  if ( g_initialized  )
    return true;
  
  if( !init_hexrays_plugin(0) ) {
    hexdsp = NULL;
    return false;
  }
  
  {
    const char *hxver = get_hexrays_version();
    msg("hexrays-python: Hex-rays version %s has been detected\n", hxver);
  }
  
#ifdef Py_DEBUG
    msg("HexraysPython: Python compiled with DEBUG enabled.\n");
#endif
  
  // Start the interpreter
  Py_Initialize();

  if ( !Py_IsInitialized() )
  {
    warning("hexrays-python: Py_Initialize() failed");
    return false;
  }

  // Enable multi-threading support
  if ( !PyEval_ThreadsInitialized() )
    PyEval_InitThreads();

  // Init the SWIG wrapper
  init_hexrays();
  
  // Import hexrays in python the dirty way until we can do better.
  PyRun_SimpleString("import hexrays; from hexrays import *;");

  g_initialized = true;

  return true;
}

//-------------------------------------------------------------------------
// Cleaning up Python
void HexraysPython_Term(void)
{
  term_hexrays_plugin();

  // Shut the interpreter down
  Py_Finalize();

  g_initialized = false;
}

//-------------------------------------------------------------------------
// Plugin init routine
int idaapi init(void)
{
  if ( HexraysPython_Init() )
    return PLUGIN_KEEP;
  else
    return PLUGIN_SKIP;
}

//-------------------------------------------------------------------------
// Plugin term routine
void idaapi term(void)
{
  HexraysPython_Term();
}

//-------------------------------------------------------------------------
// Plugin hotkey entry point
void idaapi run(int arg)
{
}

//-------------------------------------------------------------------------
// PLUGIN DESCRIPTION BLOCK
//-------------------------------------------------------------------------
plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  PLUGIN_HIDE, // plugin flags
  init,          // initialize
  term,          // terminate. this pointer may be NULL.
  run,           // invoke plugin
  S_IDAPYTHON,   // long comment about the plugin
                 // it could appear in the status line
                 // or as a hint
  // multiline help about the plugin
  "Hexrays Python Plugin\n",
  // the preferred short name of the plugin
  S_IDAPYTHON,
  // the preferred hotkey to run the plugin
  NULL
};
