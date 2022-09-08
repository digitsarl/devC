
# FactGenerator

FactGenerator is a s-p-o-g facts generator (s for subject, p for predicate, o for object and g for graph). It is written in C.


## Description of program folders

 1. The ```src``` folder which contains the differents sources files
 2. The ```executable``` folder which will contains the executable file (Main)
 3. The ```data_Input``` folder which contains three (03) files "observations.txt" (for the observations), "observations_externes.txt" (for external temperature observations) and "fichier_input_20s.txt" (which contains more observations ) 
 4. The ```data_Output``` folder which contains three (03) files "facts_observations.ttl" in relation to the "observations.txt" input file, "facts_observations_externes.ttl" in relation to the "observations_externes.txt" input file and "fichier_output_20s.ttl" in relation to the "fichier_input_20s.txt" input file. 
 
 These files represents the s-p-o-g facts that are generated after execution of the program
 
 5. The ```serd folder``` which will contains the differents files of the serd library
 6. The ```sord``` folder which will contains the differents files of the sord library
 7. The ```makefile``` file
 8. The ```src```readme.txt file
 9. The ```.gitignore``` file
 10. The ```.gitmodules``` file
 
 
## Allowed formats of input files

The lines of the input files must respect at least one of the following formats:

 - ```year/month/day hour:minute:second emse/fayol/stair/room/sensors/sensorID/metrics/sensorType ObservedValue``` for a principal observation
 
 Example ```2022/03/23 19:14:16 emse/fayol/e4/S405/sensors/6bd134b6-339c-4168-9aeb-ae7d0f236851/metrics/TEMP 27.37```
 
 - ```year-month-day hour:minute:second emse/fayol/stair/room/sensors/sensorID/metrics/sensorType ObservedValue``` for a principal observation
 
 Example ```2022-03-23 19:14:16 emse/fayol/e4/S405/sensors/6bd134b6-339c-4168-9aeb-ae7d0f236851/metrics/TEMP 27.37```
 
 - ```year/month/day hour:minute:second emse/fayol/stair/room/sensorType/outside ObservedValue``` for an external observation
 
 Example: ```2022/03/23 19:15:20 emse/fayol/4ET/409/TEMP/outside 13.36``` 
 
 - ```year-month-day hour:minute:second emse/fayol/stair/room/sensorType/outside ObservedValue``` for an external observation
 
 Example: ```2022-03-23 19:15:20 emse/fayol/4ET/409/TEMP/outside 13.36``` 



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
./executable/Main data_Input/nameOfFile_Input data_Output/nameOfFile_Output
```

 - ```nameOfFile_Input``` represent the name of the input file (with extension .txt) which must first be contained in the folder ```data_Input``` 
 
 - ```nameOfFile_Output``` represent the name of the output file (with extension .ttl) that will be created in the folder ```data_Output```
 

After, go in the folder ```data_Output``` and take the file where is written the differents s-p-o-g facts generated.


