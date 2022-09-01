
# FactGenerator

FactGenerator is a s-p-o-g facts generator (s for subject, p for predicate, o for object and g for graph). It is written in C.


## Description of program folders

 1. The src folder which contains the differents sources files
 2. The executable folder which will contains the executable file (Main)
 3. The data folder which contains three (03) files "observations.txt" (for the observations), "observations_externes.txt" (for external temperature observations) and "facts.ttl (for the s-p-o-g facts that will be generated after execution of the program)"
 4. The serd folder which will contains the differents files of the serd library
 5. The sord folder which will contains the differents files of the sord library
 6. The makefile file
 7. The readme.txt file
 8. The .gitignore file
 9. The .gitmodules file



## Setup and dependencies

To use this program in a Linux environment, one first needs to install its dependencies. These dependencies are ```git``` and ```clang```. The installation procedure depends on one's Linux distribution. On a Ubuntu setup, this would be:

```bash
sudo apt-get install git
sudo apt-get install clang
```

Once the dependencies are installed, open a terminal and clone the repository:

```bash
https://github.com/digitsarl/devC.git
```

Then enter the devC directory:

```bash
cd devC
```

Now download FactGenerator submodules:

```bash
git submodule init
git submodule update
```



## Compiling and running FactGenerator

We provide a Makefile to compile FactGenerator. To compile and run the code presented in this readme, in the root folder run the following commands:
```bash
make
./executable/Main
```

After, go in the data folder and take the facts.ttl file where is written the differents s-p-o-g facts generated.

