# QuemadaModel

In this repository we have the Quemada Model For OpenFOAM 2.1.1 with a Newtonian switch.
When running non-Newtonian simulations to initialize the internal field the simulations 
will be run intially with a newtonian viscocity before running the non-Newtonian viscocity. 

## Installation

```
git clone https://github.com/Chr1sC0de/QuemadaModel.git
chmod -R +x ArteryScalingLawsBC
cd QuemadaModel
./Allwmake
```

to uninstall the library

```
cd QuemadaModel
./Allwclean
```


