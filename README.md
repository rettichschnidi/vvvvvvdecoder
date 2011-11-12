About vvvvvvdecoder
===================

A simple tool for VVVVVV to extract the ogg files in vvvvvvmusic.vvv

Install
=======

with cmake:

	cd vvvvvvdecoder
	mkdir build
	cd build
	cmake ..
	make

without cmake:

	g++ vvvvvvdecoder.cpp -o vvvvvvdecoder -lboost_filesystem -lboost_program_options

Requirements
============

* Boost 1.44+ (filesystem and program_options)
* Optional: cmake 2.8+

Usage
=====

	./vvvvvvdecoder [path to vvvvvvmusic.vvv (default is ./vvvvvvmusic.vvv)] [output directory] [--overwrite]
