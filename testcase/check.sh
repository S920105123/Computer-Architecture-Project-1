./i_generator
./d_generator
cp dimage.bin ../golden/dimage.bin
cp iimage.bin ../golden/iimage.bin
cp dimage.bin ../simulator/dimage.bin
cp iimage.bin ../simulator/iimage.bin

cd ../golden
./single_cycle
cd ../simulator
./single_cycle
cd ../testcase
diff ../golden/snapshot.rpt ../simulator/snapshot.rpt
diff ../golden/error_dump.rpt ../simulator/error_dump.rpt
