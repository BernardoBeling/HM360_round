python globalExec_360.py
cd ../build/linux/
make clean -j 4
make -j 4
cd ../../bin
python globalExec_normais.py
cd ../../../HM/HM-16.16/HM-360Lib-5.0-build/linux
make clean -j 4
make -j 4
cd ../../bin
python exec_360.py
cd ../build/linux/
make clean -j 4
make -j 4
cd ../../bin
python exec_normais.py
