# EMP-ag2pc[![Build Status](https://travis-ci.org/emp-toolkit/emp-ag2pc.svg?branch=master)](https://travis-ci.org/emp-toolkit/emp-ag2pc)
## Authenticated Garbling and Efficient Maliciously Secure Two-Party Computation 

More details of the protocol can be found in the [paper](https://eprint.iacr.org/2017/030).

<img src="https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/art/logo-full.jpg" width=300px/>


# Installation
1. `wget https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/scripts/install.py`
2. `python install.py -install -tool -ot -ag2pc`
    1. By default it will build for Release. `-DCMAKE_BUILD_TYPE=[Release|Debug]` option is also available.
    2. No sudo? Change [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/v2.8.8/cmake.html#variable%3aCMAKE_INSTALL_PREFIX).


## Test

* If you want to test the code in local machine, type

   `./run ./bin/[binaries] 12345 [more opts]`
* IF you want to test the code over two machine, type

  `./bin/[binaries] 1 12345 [more opts]` on one machine and 
  
  `./bin/[binaries] 2 12345 [more opts]` on the other.
  
  IP address is hardcoded in the test files. Please replace
  IP variable to the real ip.
  
## Run
  ```
   bin/single_execution_run  
      -h [ --help ]                         produce help message.   
      -k [ --party ] arg (=1)               party id: 1 for garbler, 2 for evaluator.   
      -c [ --circuit_file ] arg (=/usr/local/include/emp-tool/circuits/files/adder_32bit.txt) circuit file address.   
      -p [ --port ] arg (=1234)             socket port.   
      -s [ --server_ip ] arg (=127.0.0.1)   server's IP.   
      -i [ --input ] arg                    hexadecimal input (little endian).
   ```

### Question
Please send email to wangxiao1254@gmail.com

## Acknowledgement
This work was supported in part by the National Science Foundation under Awards #1111599 and #1563722.
