AirScheduling
=============

Com compilar?
==============
Dins la carpeta `src` executar la comanda `make`

Com executar?
============
./airSchedule input_file output_file version algorithm [-t or -s]

optional arguments:
-h: shows this help message
-t: prints only input file name and time to compute solution
-s: prints only input file name and number of pilots in solution

version {1,2}
algorithm {ek,di} ek = Edmond Karp's, di = Dinic's
