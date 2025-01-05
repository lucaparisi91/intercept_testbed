INSTALL_PREFIX=/work/z19/z19/lparisi/courses/io/intercept_testbed/opt

mkdir build
cd build
CXX=CC CC=cc FC=ftn cmake ../GOTCHA  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}/gotcha/1.07
make
