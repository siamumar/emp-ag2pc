# EMP-ag2pc[![Build Status](https://travis-ci.org/emp-toolkit/emp-ag2pc.svg?branch=master)](https://travis-ci.org/emp-toolkit/emp-ag2pc)
## Authenticated Garbling and Efficient Maliciously Secure Two-Party Computation 

More details of the protocol can be found in the [paper](https://eprint.iacr.org/2017/030).

<img src="https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/art/logo-full.jpg" width=300px/>

## Installation

1. Install prerequisites using instructions [here](https://github.com/emp-toolkit/emp-readme).
2. Install [emp-tool](https://github.com/emp-toolkit/emp-tool).
3. Install [emp-ot](https://github.com/emp-toolkit/emp-ot).
4. git clone https://github.com/siamumar/emp-ag2pc/tree/command_line_development
5. cd emp-ag2pc && cmake . && make 

## Test

* If you want to see the help message for command_line_run

   `./bin/command_line_run -h`
* IF you want to test the code over two machine, type

  `./bin/command_line_run -k 1 -i 1 [more opts]` on one machine and 
  
  `./bin/command_line_run -k 2 -i 1 [more opts]` on the other.
  
  Default arguments are stated in the help message. Arguments can be changed if needed.
  
## Run
  ```
   bin/command_line_run  
      -h [ --help ]                         produce help message.   
      -k [ --party ] arg (=1)               party id: 1 for garbler, 2 for evaluator.   
      -c [ --circuit_file ] arg (=/usr/local/include/emp-tool/circuits/files/adder_32bit.txt) circuit file address.   
      -p [ --port ] arg (=1234)             socket port.   
      -s [ --server_ip ] arg (=127.0.0.1)   server's IP.   
      -i [ --input ] arg                    hexadecimal input (little endian).
   ```


## Acknowledgement
This work was supported in part by the National Science Foundation under Awards #1111599 and #1563722.
