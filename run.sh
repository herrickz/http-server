#!/bin/bash

clean=false
test=false

while getopts "drvct" opt; do
  case $opt in
    d)
      BUILD_TYPE=Debug
      ;;
    r)
      BUILD_TYPE=Release
      ;;
    v)
      verbose=true
      ;;
    c)
      clean=true
      ;;
    t)
      test=true
      ;;
    \?)
      echo "Invalid option: -$OPTARG"
      ;;
  esac
done

# if ["$clean" == true]; then
if $clean; then
  rm -rf build
  mkdir build
  conan install . \
    --output-folder=build \
    --build=missing \
    --settings=build_type=$BUILD_TYPE \
    --profile=default
fi

cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE

cmake --build . --verbose

if [ $? -ne 0 ]; then
  echo "Build failure"
  exit 1
fi

if $test; then
  ctest -C $BUILD_TYPE --verbose
else
  ./http-server
fi
