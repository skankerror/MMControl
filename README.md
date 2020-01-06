# MMControl

MMControl is a [mapmap](https://mapmapteam.github.io/) controller for linux developped with qt, rtmidi and oscpack libraries.
It's very limited, closed to my own needs, works on my manjaro laptop with my Akai apc mini

## Getting Started

These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

You need linux, qt, rtmidi;
If you're on manjaro or arch do

```
$ sudo pacman -Syu qt5-base rtmidi
```

### Installing

Download source archive and untar or clone with git :

```
$ git clone https://gitlab.com/skankerror/MMControl.git
```

Enter the directory and compile

```
$ cd MMControl
$ qmake MMControl.pro
$ make
```

Launch the app

```
$ ./MMControl
```

Have fun (or not)

## Built With

* [oscpack](https://github.com/MariadeAnton/oscpack) - Open Sound Control packet manipulation library A simple C++ library for packing and unpacking OSC packets.
* [Qt](https://www.qt.io/)
* [rtmidi](https://github.com/thestk/rtmidi) - A set of C++ classes that provide a common API for realtime MIDI input/output across Linux (ALSA & JACK), Macintosh OS X (CoreMIDI & JACK) and Windows (Multimedia).

## Contributing

Feel free to contribute (or not)

## Authors

* **Michaël Creusy** - *Initial work* - [skankerror](https://gitlab.com/skankerror)

## License

This project is licensed under the GNU GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks [mapmapteam](https://github.com/mapmapteam) for [mapmap](https://github.com/mapmapteam/mapmap) project.
