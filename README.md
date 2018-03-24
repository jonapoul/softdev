# Software Development 2018

## Installation
First decide if you want to build using Qt. Barely any of the UI has been built beyond the title screen, but the option is there in `config.h`.

### CLI-Only (recommended)
Make sure `#define ENABLE_QT_UI` is **uncommented** in `config.h`. Then:
```
make
```
That will :
1. `git clone` the parameter-reading library
2. Put it all together in `bin/softdev`

### Qt (barely worth trying)
Make sure `#define ENABLE_QT_UI` is **commented** in `config.h`, and you've installed Qmake (and probably the rest of Qt Creator, I've not tested on a clean machine). Then:
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
