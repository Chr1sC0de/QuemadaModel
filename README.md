# QuemadaModel
In this repository we have the Quemada Model For OpenFOAM 2.1.1 with a Newtonian switch.
When running non-Newtonian simulations to initialize the internal field the simulatiosn 
will be run intially with a newtonian viscocity before running the non-Newtonian viscocity. 

## Installation

```
cd QuemadaModel
wmake libso
```

to uninstall the library

```
cd QuemadaModel
wclean libso
```


