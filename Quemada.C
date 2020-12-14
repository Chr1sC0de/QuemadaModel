/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "Quemada.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(Quemada, 0);
    addToRunTimeSelectionTable
    (
        viscosityModel,
        Quemada,
        dictionary
    );
}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::viscosityModels::Quemada::calcNu() const
{
    return
        sqr(sqrt(muInf_) + sqrt(tau0_)/(sqrt(lambda_) + sqrt(strainRate())))/rho_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::Quemada::Quemada
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    viscosityModel(name, viscosityProperties, U, phi),
    // get the switch
    switchOn_(viscosityProperties.lookupOrDefault<scalar>("switchOn", 0.)),
    // get the newtonian viscoscity
    nuNewtonian0_(viscosityProperties_.lookup("nu")),
    // get the non newtonian viscosity
    QuemadaCoeffs_(viscosityProperties.subDict(typeName + "Coeffs")),
    tau0_(QuemadaCoeffs_.lookup("tau0")),
    muInf_(QuemadaCoeffs_.lookup("muInf")),
    lambda_(QuemadaCoeffs_.lookup("lambda")),
    rho_(QuemadaCoeffs_.lookup("rho")),
    nu_
    (
        IOobject
        (
            "nu",
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        U_.mesh(),
        nuNewtonian0_
    )
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::Quemada::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModel::read(viscosityProperties);

    viscosityProperties.lookup("nu") >> nuNewtonian0_;

    QuemadaCoeffs_ = viscosityProperties.subDict(typeName + "Coeffs");

    QuemadaCoeffs_.lookup("tau0") >> tau0_;
    QuemadaCoeffs_.lookup("muInf") >> muInf_;
    QuemadaCoeffs_.lookup("lambda") >> lambda_;
    QuemadaCoeffs_.lookup("rho") >> rho_;

    return true;
}


// ************************************************************************* //
