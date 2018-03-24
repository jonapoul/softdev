# Software Development 2018

## Install
First decide if you want to build using Qt. Barely any of the UI has been built beyond the title screen, but the option is there in `config.h`. Either:
* Leave it commented to build/run using CLI only **(preferred)**
* Uncomment `#define ENABLE_QT_UI` to build with Qt

### Without Qt
```
make
```
That will :
1. `git clone` the libPF parameter-reading library
2. Put it all together in `bin/softdev`

### With Qt
```
chmod +x BuildWithQt.sh
./BuildWithQt.sh
```
That will :
1. `git clone` the libPF parameter-reading library
2. Builds a custom makefile for Qt projects
3. Put it all together in `bin/softdev_qt`

## Acknowledgements
Eric Tittley, for letting me use/update his library for reading parameter files.
