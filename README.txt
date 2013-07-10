Word Fall README
=================

How to Play
============
The goal of Word Fall is to spell words with the highest point values as
fast as you can. Drag the letters that fall from the clouds, and drop
them into the containers at the bottom. Once you have spelled a word,
press the check mark to submit the word and get points. If you drop a
letter into the wrong container and want to erase it, right click on
the letter to delete it. To view your high score, and turn the sound off,
go to the options menu on the main screen.

Contact
========
Send all questions, comments, concerns, and complaints to admin@mopiz.com

Install
========
- Windows
	Use the .exe installer, and follow the installer instructions.
- Mac OS X
	Follow the compile instructions to build Word Fall for your system.
- Linux
	Follow the compile instructions to build Word Fall for your system.

Compile From Source
====================
**Dependencies**
*Note: version numbers lower than listed will work*
- SDL 1.2.15
	<http://www.libsdl.org/download-1.2.php>
- SDL_image 1.2.12
	<http://www.libsdl.org/projects/SDL_image/>
- SDL_ttf 2.0.11
	<http://www.libsdl.org/projects/SDL_ttf/>
- SDL_mixer 1.2.12
	<http://www.libsdl.org/projects/SDL_mixer/>
- Lua 5.2.2
	<http://www.lua.org/download.html>

Linux
------
The easiest way for Linux users to install the dependencies is through
your package manager. Make sure to install the development versions. They
should have a suffix or prefix like -dev or devel.

After the dependencies are installed, just run make linux and then
make install. Running make install will copy the game into the
/usr/local/bin/ folder. To install somewhere else, just 

OS X
-----
OS X users need to either have Xcode installed, or have the command line
utilities from Xcode installed.

OS X users will need to link with the SDL frameworks. Just download
all of the dependencies listed above, and copy teh .framework file
into /Library/Frameworks/ (or another location
of your choice, just make sure it links).

After the frameworks are installed just run make osx. This will build a
version of the game that can be run from the command line. If you want to
create a .app file you will need to create an Xcode project.

Windows
--------
Windows users will need all of the .dll files provided by the windows binary
in order for word fall to work properly. Make sure that the development
versions of all SDL dependencies are installed and linked in your
project file (Visual Studio, Code::Blocks, etc). Import all of the
files except for the SDLMain.m and SDLMain.h files(These are mac specific)
and build the project.

Credits
========
Developed By Charged Productions
http://chargedproductions.com

Sound Effects
"Super Friendly" - Kevin MacLeod
"Click" - Mike Koenig
"Error" - Mike Koenig

"Roboto" font licensed under the Apache License version 2.0

Open Source Projects Used
--------------------------
Lua http://www.lua.org
SDL http://www.libsdl.org

License
--------
Word Fall
Copyright (C) 2013  Kyle Schreiber

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
