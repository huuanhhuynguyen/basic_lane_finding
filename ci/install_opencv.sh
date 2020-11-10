#!/bin/bash

##############################################################################
#                            Install OpenCV
# source: https://gist.github.com/Randommood/478ccd806511d45febc1
##############################################################################

# OpenCV dependencies
sudo apt-get install -y build-essential
sudo apt-get install -y cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

# Download v3.0.0 .zip file and extract.
curl -sL https://github.com/Itseez/opencv/archive/3.0.0-beta.zip > opencv.zip
unzip opencv.zip
cd opencv-3.0.0-beta

# Create a new 'build' folder.
mkdir build && cd build

# Set build instructions for Ubuntu.
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..

# Run 'make' with four threads.
make -j4

# Install to OS.
sudo make install

# Add configuration to OpenCV to tell it where the library files are located on the file system (/usr/local/lib)
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'

sudo ldconfig
echo "OpenCV installed."

# We need to return to the repo "root" folder, so we can then 'cd' into the C++ project folder.
cd ../../
