# Sinta - Script In The App

## Introduction

Sinta is a tool to inject and run JavaScript code in a Qt application. It can
be useful to automate tasks such as taking screenshots or doing some functional
testing.

Disclaimer: this is in a very early stage and not usable yet!

## Usage

To run a script inside an application you can use the `sinta` executable.

The job of the `sinta` executable is to:

- Start your application and inject the `libsinta` dynamic library inside it
- Tell libsinta to run your script

The source code contains a test application in the `testapp` directory. This
application lets you pick a font and opens a popup showing a message written
using this font.

By running sinta on it like this:

    sinta <path/to/src/sinta/testapp/test.js> <path/to/build/dir/testapp/testapp>

You can see the application opening, then the test script saves a screenshot of
the main window, then go through the 10 first fonts and for each one it opens
the popup and saves a screenshot of it.  When it's done it quits the
application.

## Writing scripts

Scripts are written in JavaScript and evaluated by [QJSEngine][].

### The `tools` object

Sinta exposes a `tools` object which provides useful functions to interact with
your application.

In particular, `tools.activeWindow()` returns the active window and
`tools.findChild()` lets you find a child of any object by its `objectName`.

For now, you can look at [sinta/Tools.h](sinta/Tools.h) documentation for details.

### Misc

The `console` object is available, so you can make use of `console.log()`.

[QJSEngine]: https://doc.qt.io/qt-5/qjsengine.html

## Building

Sinta depends on Qt 5 and CMake. To build it:

    mkdir build
    cd build
    cmake ..
    make
