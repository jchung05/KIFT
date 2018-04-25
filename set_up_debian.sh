# Install all the dependencies in a fresh debian based system
sudo apt-get install -y gcc automake autoconf libtool bison swig python-dev libpulse-dev subversion
cd ~/
mkdir buildinsphinx && cd buildinsphinx
mkdir speech_recognition && speech_recognition
git clone https://github.com/cmusphinx/sphinxbase.git
cd sphinxbase
./autogen.sh
./configure
make clean all
make check
sudo make install

## checkpoint kinda make the changes permanent
export LD_LIBRARY_PATH=/usr/local/lib
#sudo vim /etc/ld.so.conf
sudo echo "include /etc/ld.so.conf.d/*.conf" >> /etc/ld.so.conf
sudo echo "/usr/local/lib" >> /etc/ld.so.conf
sudo ldconfig

## done with the first directory Pocketsphinx

cd ..
git clone https://github.com/cmusphinx/pocketsphinx
cd pocketsphinx
./autogen.sh
./configure
make clean all
make check
sudo make install

## cmusphinx-code - you dont really need sphinx train
cd ..
git clone https://github.com/cmusphinx/sphinxtrain.git
cd sphinxtrain
./autogen.sh
./configure
make clean all
make check
sudo make install

# do subversion managment - installing cmusphinx-code
cd ..
svn checkout svn://svn.code.sf.net/p/cmusphinx/code/trunk cmusphinx-code
cd cmusphinx-code
./autogen.sh
./configure
make clean all
make check
sudo make install

echo "after this point you should be able to use pocketsphinx correctly"
