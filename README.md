n64-emu
=======

A WIP emulator for the Nintendo 64

Dependencies
------------

This project has a number of dependencies:

Dependency   | Description                  | License
-----------: | :--------------------------: | -------
[sdl2][1]    | Windowing and input          | Zlib
[sqlite3][2] | Data storage and persistance | Public domain
[cubeb][3]   | Audio management             | ISC
[bgfx][4]    | 3D accelerated graphics      | BSD 2-Clause
[imgui][5]   | Immediate mode UI            | MIT

[1]: https://libsdl.org
[2]: https://sqlite.org/index.html
[3]: https://github.com/kinetiknz/cubeb
[4]: https://github.com/bkaradzic/bgfx
[5]: https://github.com/ocornut/imgui

Nothing is optional: all are meant to serve as cross platform abstraction
layers to prevent the need for a bunch of different platform specific backends
or modules. If your distro has them packaged, install from there, or else
install them from source. We do not plan on vendoring them within our repo.

Having all of our dependencies permissively licensed was intentional. Having
them all under unique permissive licenses was not intentional, but is amusing.

Building
--------

Your distro will almost certainly have Sqlite and SDL2 packaged. For the
remaining three, building from source can be done as follows:

```sh
mkdir ~/path/to/deps
cd ~/path/to/deps

git clone --depth=1 --recursive https://github.com/widberg/bgfx.cmake
mkdir bgfx-build
cd bgfx-build
cmake ../bgfx.cmake
make
sudo make install
cd ..

git clone --depth=1 --recursive https://github.com/kinetiknz/cubeb
mkdir cubeb-build
cd cubeb-build
cmake ../cubeb
make
sudo make install
cd ..

git clone --depth=1 https://github.com/ocornut/imgui
cd imgui
```

License
-------

The project is officially licensed under BSD-2-Clause, and all new code that
we write will be under such a license. We may include code from outside
sources, so check the license at the top of each file for more details. We
will only import code under a permissive license.

If you write new code for the project, we ask that you (re-)license it under
BSD-2-Clause to match the rest of the project.

See `LICENSE` for the specific terms.
