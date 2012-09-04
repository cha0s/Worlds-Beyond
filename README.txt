Of course, first checkout this repository.

You'll then need to checkout v8 in the chi directory. I'm using an older revision (I know, not ideal :), so I'm recommending you check the specific revision out until I can test compiling against the latest v8. You can check out the revision known to work with the engine like so:

cd chi
svn checkout -r 9407 http://v8.googlecode.com/svn/trunk/ v8

It'll take a bit to download. I provided a patch to fix a couple of quirks with this revision of v8. You need to apply the patch to compile v8 cleanly. Go into the v8 directory and apply the patch:

cd v8/
patch -p0 < ../v8.patch

Then run:

scons

It will build for a while. Once it's done, rename the library:

mv libv8.a libv8-chi.a

After this, you need to run qmake to generate the Makefile:

cd ../..
qmake CONFIG+=release CONFIG-=debug

Now, compile:

make -j4
