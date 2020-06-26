for i in `seq 1 10`;

    do

        echo $i 05

		bin/single_execution_run -k 1 -c ~/PUF_Auth/syn/auth_Hamming_TG_syn_yos_05.emp

    done  

for i in `seq 1 10`;

    do

        echo $i 15

		bin/single_execution_run -k 1 -c ~/PUF_Auth/syn/auth_Hamming_TG_syn_yos_10.emp

    done  

for i in `seq 1 10`;

    do

        echo $i 15

		bin/single_execution_run -k 1 -c ~/PUF_Auth/syn/auth_Hamming_TG_syn_yos_15.emp

    done  

	