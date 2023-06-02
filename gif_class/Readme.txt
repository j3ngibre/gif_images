The main objective is to create a library for handling GIF images in C++ in a simpler way than the complex C libraries.

Later on, it has a method to translate the image into a format  "TAM TAM COLOR1 COLOR2 COLOR3 ...", where the colors are listed in descending order from right to left.

We use 3 differents files to safe information:
	Lcolor ->Local color list(RGB)
	Gcolor ->Global color list(RGB)
	Codigos->Image data

The other files are just to give information when we search for mistakes or bugs in the code
HF
:)