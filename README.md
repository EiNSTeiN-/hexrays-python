Python bindings for the Hexrays Decompiler
==============

Author: EiNSTeiN_ <einstein@g3nius.org>

### What is this?

This is an IDA Pro plugin which provides the python bindings around the Hexrays Decompiler SDK API.

This project largely reuse the foundation provided by IDAPython (build scripts, swig rules, etc). 

### Status

The code wraps the current API and provides a more pythonic approach to the API. For example, most lists structures are iterable, most map structures are indexable like dictionaries, strings are str()-able, etc.

### How to compile

Follow the steps in the BUILDING file.

### License

Because this plugin has its foundation in the IDAPython code base, the original license was kept.
