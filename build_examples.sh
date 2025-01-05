

source env.sh

set -e 
set -x


mkdir -p lib
CC example_library.cc -lgotcha -llustreapi -shared -o lib/libtrace.so
CC example_program.cc -L $(pwd)/lib -o test
