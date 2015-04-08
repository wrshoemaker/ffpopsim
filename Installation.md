# Build and Install #

Make is used to build the FFPopSim library.

## For the impatient ones ##

type
```

make```
and have a look in the pkg folder.

## Full instructions ##

Please open the Makefile and have a look at the first few lines. The
script tries to be smart about your platform and Python installation,
but is expected to fail in most cases, so please set the required
variables in the Makefile according to your operating system.

You can build the various pieces separately:

1. To build only the C++ sources, call

```
make src```

2. To build also the Python bindings, call

```
make python```

3. To build the documentation, call

```
make doc```

4. To build the C++ test programs, call

```
make tests```

To build all of them, just call

```
make```

The C++ library and the Python module files are stored in the pkg
folder. Copy them into your system folders (e.g., /usr/local/lib and
/usr/local/lib/python2.7/site-packages) to make them available to all
users.