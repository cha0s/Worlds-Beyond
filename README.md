![wb logo](http://s3.amazonaws.com/ksr/projects/306704/photo-full.jpg?1345667807)

NOTE: These instructions are tailored for Ubuntu-based distributions.

Of course, first checkout this repository.

You'll then need to checkout v8 in the lib directory. I'm using an older revision (I know, not ideal :), so I'm recommending you check the specific revision out until I can test compiling against the latest v8. You can check out the revision known to work with the engine like so:

	cd lib
	svn checkout -r 9407 http://v8.googlecode.com/svn/trunk/ v8

It'll take a bit to download. I provided a patch to fix a couple of quirks with this revision of v8. You need to apply the patch to compile v8 cleanly. Go into the v8 directory and apply the patch:

	cd v8/
	patch -p0 < ../v8.patch
	
You'll need some system libraries:

	sudo apt-get install libc6-dev-i386

If you're on a 32-bit system run:

	scons

Otherwise if you're on a 64-bit system, run:
	
	scons arch=x64

It will build for a while. Once it's done, rename the library:

	mv libv8.a libv8-wb.a

After this, you need to run qmake to generate the Makefile:

	cd ../..
	qmake CONFIG+=release CONFIG-=debug

You'll need to gather up some libraries...

	sudo apt-get install libsdl1.2-dev libsdl-gfx1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev libboost-regex-dev libboost-filesystem-dev libboost-system-dev
	
Now, compile:

	make -j4
	
Download the zip file with the content folder at http://www.bridgeunitorzo.com/sites/default/files/WB.zip

Extract the content folder to your base directory, and launch your brand new Worlds Beyond application!

P.S. As I'm providing a binary for Windows, and documenting how I did it is a PITA, I'm skipping it for now. Eventually I'd like to get it compiling for VC++ anyways. I'd appreciate any help in that direction!
