# Software Development 2018

## Install
First decide if you want to build using Qt. Barely any of the UI has been built beyond the title screen, but the option is there in `config.h`.

### Without Qt
First **uncomment** `#define ENABLE_QT_UI` in `config.h`. Then:
```
make
```
That will :
1. `git clone` the libPF parameter-reading library
2. Put it all together in `bin/softdev`

### With Qt
Make sure `#define ENABLE_QT_UI` is **commented** in `config.h`. Then:
```
chmod +x BuildWithQt.sh
./BuildWithQt.sh
```
That will :
1. `git clone` the libPF parameter-reading library
2. Build a custom makefile for Qt projects
3. Put it all together in `bin/softdev_qt`

## Acknowledgements
Eric Tittley, for letting me use/update his library for reading parameter files.
