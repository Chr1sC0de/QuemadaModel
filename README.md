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

## Example transportProperties File

``` c++
/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  2.1.1                                 |
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "constant";
    object      transportProperties;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

transportModel  Quemada;

nu              nu [ 0 2 -1 0 0 0 0 ] 3.302E-06;

// time when to activate the Quemada model otherwise the viscoscity is newtonian
switchOn 0.4;

QuemadaCoeffs
{
    tau0            tau0   [ 1 -1 -2 0 0 0 0 ] 7.160E-03;
    muInf           muInf  [ 1 -1 -1 0 0 0 0 ] 4.204E-03;
    lambda          lambda [ 0 0 -1 0 0 0 0 ] 4.367E-03;
    rho 	        rho    [1 -3 0 0 0 0 0] 1060;
}

// ************************************************************************* //

```
