#  !bash
# type './build.sh'  for release build
# type './build.sh debug'  for debug build

#########
# Please change the following home directories of your LLVM builds
# In my projects folder I have: llvm-5-build/       llvm-5-debug-build/ llvm-5.0.0.src/     llvm-5.0.0.src.tar  
########
LLVMRELEASE=/Users/jaredcarlson/Projects/llvm-5-build
LLVMDEBUG=/Users/jaredcarlson/Projects/llvm-5-debug-build

if [[ $1 == 'debug' ]]
then
BuildTY='Debug'
export LLVM_DIR=$LLVMDEBUG
else
BuildTY='Release'
export LLVM_DIR=$LLVMRELEASE
fi

export PATH=$LLVM_DIR/bin:$PATH
Build=$BuildTY'-build'

rm -rf $Build
mkdir $Build
pushd $Build

if [[ $1 == 'debug' ]]
then
cmake -D CMAKE_BUILD_TYPE:STRING=Debug ../
else
cmake ../
fi

make -j4
popd
