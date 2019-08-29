# Eoghan McGinty's C++ test for Nitro

Development was done in Windows using VisualStudio with a cmake plugin.

Project is built using CMake.

Open VisualStudio go File > Open > CMake.. 
	> Browse to NitroCppTest-EoghanMcGinty\IntersectingRectangles\CMakeLists.txt and open

To build simply click on the CMake option on the top bar and select Generate and then Build.

Although not tested on Linux as I had no available Linux machine or one suitable for a VM it should work.

Two thirdparty libraries were used, "nlohmann::json" for json parsing and "catch" for test.

Both are single header include files included in the project.