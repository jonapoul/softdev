# Software Development 2018

## Requirements
You'll need `gcc` with a version of at least 5.0, because the use of `std::experimental::filesystem` doesn't seem to be part of the system include path before then. I have no idea about other compilers (clang, MSVC, etc.).

## Installation
First decide if you want to build using Qt. Barely any of the UI has been built beyond the title screen, but the option is there in `config.h`.

### CLI-Only (recommended)
Make sure `ENABLE_QT_UI` is **not** defined in `config.h`. Then:
```
make
```
That will :
1. `git clone` the parameter-reading library
2. Put it all together in `bin/softdev`

### Qt (barely worth trying)
Make sure `ENABLE_QT_UI` is **defined** in `config.h`, and you've installed Qmake (and probably the rest of Qt Creator too, I've not tested on a clean machine). Then:
```
chmod +x BuildWithQt.sh
./BuildWithQt.sh
```
That will :
1. `git clone` the parameter-reading library
2. Use `qmake` to build a custom makefile for Qt projects
3. Put it all together in `bin/softdev_qt`

## Acknowledgements
Eric Tittley, for letting me use/update his quite handy C library [libPF](https://bitbucket.org/eric_tittley/libpf "libPF")
 for reading parameter files.

 You may want to look at his examples (`lib/libpf/test/test1.c`) for a simple walk through the idea beforehand. I'm sorry for throwing it into this quite so whole-heartedly, by the way :P
