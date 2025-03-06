#! /bin/bash

curr_path="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $curr_path


cd Tests/LLVM_Learner_Libs/build
cmake ..
make -j8
for file in `find -name *.a`
do 
    rm -f ../$(basename $file)
    cp $file ../
done 

cd $curr_path/Tests

for folder in `ls`
do
    if [ -d ./$folder ]
    then
        cd $folder
        if [ ! -d ./build ]
        then
            mkdir build
        fi
        cd  build
        cmake ..
        make -j4 
        cd ../../
    fi
done

