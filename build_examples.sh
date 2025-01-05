set -e 
set -x

source env.sh
mkdir -p lib
CC example_library.cc -lgotcha -shared -o lib/libtrace.so
CC example_program.cc -L $(pwd)/lib -ltrace -o test
