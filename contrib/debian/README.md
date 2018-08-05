
Debian
====================
This directory contains files used to package RÜNESd/RÜNES-qt
for Debian-based Linux systems. If you compile RÜNESd/RÜNES-qt yourself, there are some useful files here.

## RÜNES: URI support ##


RÜNES-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install RÜNES-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your RÜNESqt binary to `/usr/bin`
and the `../../share/pixmaps/RÜNES128.png` to `/usr/share/pixmaps`

RÜNES-qt.protocol (KDE)

