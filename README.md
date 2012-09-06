![wb logo](http://s3.amazonaws.com/ksr/projects/306704/photo-full.jpg?1345667807)

NOTE: These instructions are tailored for Ubuntu-based distributions.

Of course, first checkout this repository.

You'll then need to checkout v8 in the lib directory.

	cd lib
	git clone git://github.com/v8/v8.git v8
	cd v8

It'll take a bit to download. I provided a patch to fix v8.
This is because their team does not care about clean compilation: http://code.google.com/p/v8/issues/detail?id=2302
You need to apply the patch to compile v8 cleanly. Go into the v8 directory and apply the patch:

	patch -p1 < ../v8.patch
	
You'll need to set up the system a bit.

	sudo apt-get install libc6-dev-i386 libsdl1.2-dev libsdl-gfx1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev libboost-regex-dev libboost-filesystem-dev libboost-system-dev
	make dependencies

If you're on a 32-bit system run:

	make ia32.release

Otherwise if you're on a 64-bit system, run:
	
	make ia64.release

It will build for a while. Once it's done, rename the libraries:

	mv out/ia32.release/obj.target/tools/gyp/libv8_base.a libv8-wb.a
	mv out/ia32.release/obj.target/tools/gyp/libv8_snapshot.a libv8_snapshot-wb.a

After this, you need to run qmake to generate the Makefile:

	cd ../..
	qmake CONFIG+=release CONFIG-=debug

Now, compile:

	make -j4
	
Download the zip file with the content folder at http://www.bridgeunitorzo.com/sites/default/files/WB.zip

Extract the content folder to your base directory, and launch your brand new Worlds Beyond application!

P.S. As I'm providing a binary for Windows, and documenting how I did it is a PITA, I'm skipping it for now. Eventually I'd like to get it compiling for VC++ anyways. I'd appreciate any help in that direction!
