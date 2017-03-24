./i_generator
./d_generator
cp dimage.bin ../residence_of_golden/dimage.bin
cp iimage.bin ../residence_of_golden/iimage.bin
cp dimage.bin ../simulator/dimage.bin
cp iimage.bin ../simulator/iimage.bin
../residence_of_golden/single_cycle
../simulator/single_cycle
diff ../residence_of_golden/snapshot.rpt ../simulator/snapshot.rpt
diff ../residence_of_golden/error_dump.rpt ../simulator/error_dump.rpt
