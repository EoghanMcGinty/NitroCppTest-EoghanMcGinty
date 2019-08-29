# Eoghan McGinty's C++ test for Nitro

Development was done in Windows using VisualStudio with a CMake plugin.

To build open VisualStudio go File > Open > CMake.. 
	
Browse to NitroCppTest-EoghanMcGinty\IntersectingRectangles\CMakeLists.txt and open

Click on the CMake option on the top bar and select Generate and then Build.

Although not tested on Linux as I had no available Linux machine or one suitable for a VM it potentially works there also using cmake on the command line.

Two third party libraries were used, "nlohmann::json" for json parsing and "catch" for test.

Both are single header include files included in the project.

Two executables and a library will be created in the build, one executable for test, and the required executable.

They will be found in build\test\IntersectingTest.exe and build\source\IntersectingRectangles.exe