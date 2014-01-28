Python bindings for the Hexrays Decompiler
==============

Author: EiNSTeiN_ <einstein@g3nius.org>

### Note: this plugin has been merged into IDAPython.

Get the latest version here: https://code.google.com/p/idapython/

### What is this?

This is an IDA Pro plugin which provides python bindings around the Hexrays Decompiler SDK API.

This project largely reuse the foundation provided by IDAPython (build scripts, swig rules, etc). 

### Downloads:

**For latest release, see IDAPython: https://code.google.com/p/idapython/**

Windows:
* IDA 6.4: [hexrays-python-0.9.0_ida6.4_py2.7_win32.zip](http://goo.gl/bDVhD)
* IDA 6.3: [hexrays-python-0.9.0_ida6.3_py2.7_win32.zip](http://goo.gl/l9ULb)

Linux:
* IDA 6.4: [hexrays-python-0.9.0_ida6.4_py2.7_linux.zip](http://goo.gl/vnRwT)
* IDA 6.3: [hexrays-python-0.9.0_ida6.3_py2.7_linux.zip](http://goo.gl/9hUSc)

### Quick start

Load any database where the decompiler is available (x86 or ARM assembly), and go to IDA's interactive interpreter (in the output window).

Some examples of how to use this plugin:
```python
# import the module in the interpreter context
import hexrays
# decompile function at 0x402010
c = hexrays.decompile(0x402010)
# print decompiled text
print str(c)
# access local variable names
print [str(v.name) for v in c.lvars]
```

### Status

The code wraps the current API and provides a more pythonic approach to the API. For example, most list-like structures are iterable, most map-like structures are indexable like dictionaries, strings are str()-able, etc.

### How to compile

Follow the steps in the BUILDING file.

### License

Because this plugin has its foundation in the IDAPython code base, the original license was kept.
