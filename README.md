MPI_Prime
=========

Prime number calculation with MPI

### Compilation

```bash
 16:43:01 jade > mpic++ -std=c++11 mpiprime.cpp -o mpiprime
``` 

### Execution
```bash
 16:43:39 jade > mpiexec -n 4 ./mpiprime
  Number given:		  100000
  Number of primes:	  9592
  Sum of primes:	  454396537
  Sum mod 123:		  97
  Time spent:		  0.612129
```



```bash
 16:43:42 jade > mpiexec -n 4 ./mpiprime
  Number given:		  100000
  Number of primes:	  9592
  Sum of primes:	  454396537
  Sum mod 123:		  97
  Time spent:		  0.687557
```
