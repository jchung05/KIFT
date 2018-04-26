#!/bin/sh

build_sphinxbase() {
	git clone https://github.com/cmusphinx/sphinxbase.git
	cd sphinxbase
	./autogen.sh
	./configure
	make clean all
	make check
	sudo make install
	cd ..
}

build_pocketsphinx() {
	git clone https://github.com/cmusphinx/pocketsphinx
	cd pocketsphinx
	./autogen.sh
	./configure
	make clean all
	make check
	sudo make install
	cd ..
}

build_sphinxtrain() {
	git clone https://github.com/cmusphinx/sphinxtrain.git
	cd sphinxtrain
	./autogen.sh
	./configure
	make clean all
	make check
	sudo make install
	cd ..
}

build_subversion() {
	svn checkout svn://svn.code.sf.net/p/cmusphinx/code/trunk cmusphinx-code
	cd cmusphinx-code
	cd cmuclmtk
	./autogen.sh
	./configure
	make clean all
	make check
	sudo make install
	cd ..
	cd ..
}


main(){
	sudo apt-get install -y gcc automake autoconf libtool bison swig python-dev libpulse-dev subversion
	echo "if somehow you are running this on docker you might wanted to install sudo"
	echo "or changed to su -"
	echo "gonna run everything in .bashprofile"
	echo "export LD_LIBRARY_PATH=/usr/local/lib" >> ~/.bash_profile
	source ~/.bash_profile
	mkdir speech_recognition && cd speech_recognition
	build_sphinxbase
	build_pocketsphinx
	build_sphinxtrain
	build_subversion
	echo "after this point you should be able to use pocketsphinx correctly"
}

	main
