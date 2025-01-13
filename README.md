# LazyFooSDL
Source Code from roughly following LazyFoo's SDL2 Lessons

## Building
Ensure that SDL is installed.

I'm not super familiar with CMake, so I hacked it up a bit.
To that end, I created a build script `build.sh` that can be used
to build individual lessons.

Usage of `build.sh`:
- ./build.sh clean -- removes all build directories
-./build.sh $FOLDER -- builds a specific folder's CMake.

The binary will be placed in $FOLDER/build, and will be (usually) named
after $FOLDER

At a later point I may fix this and have a root CMake that builds all
lessons and drops them in a build folder.

## No Lesson 3?

Lesson 3 was intended to introduce the event loop. It seems that at one point
LazyFoo intended for lessons 1 and 2 to not use the loop (and instead close after
a short period), but later converted them to use a one-liner event loop.

Since I cleaned up the eventloop for lessons 1 and 2 rather than having them be a one-liner,
I skipped lesson 3 as it added nothing new.
