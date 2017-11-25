#! /bin/sh

./configure

make MODE=release

cd examples/veins

# seed = date +%s
# for i in 05 10 15 20 25 30 35 40 45 50 55 60
#for i in 45 50 55 60
#do
    for i in 0 1 2 3 4 5 6 7 8 9
	do
    # for j in 250
	for j in 150 200 250 300 350 400 450 500
		do
			 ./run -u Cmdenv -f omnetpp.ini -r $i -c VehNumber_$j
			#./run -u Cmdenv -f omnetpp_express_SCMAC.ini -r $j -c Density_$i
	
			mv VADDResults/AngleBasedForw_VADDCASE.csv VADDResults/AngleBasedForw_VADDCASE"$i"_n_"$j".csv
			#mv result/SCMAC_Mac_Result.csv result/SCMAC_Mac_Result_d_"$i"_s_"$j".csv
  	  done
	done

date

