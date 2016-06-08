# Compilation
=============

The easiest way to compile is to use make.

* `make` or `make all` will make hencode, hdecode, and hanalysis
* `make hencode` will make hencode
* `make hdecode` will make hdecode
* `make hanalysis` will make hanalysis

# Running
=========

The easiest way to run this is to use the python wrapper

* `hanalysis compress file` will compress a file and add the extension '.huff'
* `hanalysis decompress file` will decompress a file and remove the extension '.huff'
* `hecode in [out]` will compress in and write to out or stdout
* `hdecode [in|- [out]]` will decompress in or standard in, and write to out or stdout
* `hanalysis file` will analyze the efficiency of a compressed file