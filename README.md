# FramelessWindow
A frameless window / title bar written in C++ and built for Qt projects. 

The design is loosely based on [CustomWindow](https://github.com/francescmm/SmallPillsOfQt/tree/master/CustomWindow).

However, resizing and other methods are implemented through [Qt::WA_Hover](https://doc.qt.io/qt-6/qt.html#WidgetAttribute-enum) or [QHoverEvent](https://doc.qt.io/qt-6/qhoverevent.html) instead of mouse move related events.

## Features

- Minimize
- Maximize and restore
- Close
- Roll up and roll down
- Move support
- Menubar support
- Resizing from all corners
- Resizing from all edges
- Fullscreen mode
- Edgehit handling(*kinda messy*)

## Style
The frameless window consists of a title bar, central widget and bottom bar, all inheriting QWidget within various layouts([ui](src/FramelessWindow.ui)).

The look and feel of the window is derived from the **"framelesswindow.css"** file, mostly pointing towards a dark theme.

## Documentation
The frameless window class and its methods have been clearly documented in the **"framelesswindow.h"** header file with doxygen format. Latex and PDF files are also provided in [docs](docs) directory.


## Demo
### On Windows 11

https://user-images.githubusercontent.com/38321498/154995309-f0ff0885-6d5a-4fdc-990d-221ec35693ac.mp4

### On Ubuntu 21.10

https://user-images.githubusercontent.com/38321498/154995843-5521a4db-f02e-4875-8966-198e45a90547.mp4

