/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2022 AUTHOR,AFFILIATION
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

Application
    test-includeJson

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "Field.H"

#define CATCH_CONFIG_MAIN 
#include <catch2/catch.hpp>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// int main(int argc, char *argv[])
TEST_CASE( "load json", "[jsonInclude]" )
{
    int argc = 1;
    char **argv = static_cast<char**>(malloc(sizeof(char*)));
    char executable[] = {'m','a','i','n'};
    argv[0] = executable;
    Foam::argList args(argc, argv,false,false,false);

    // #include "setRootCase.H"
    #include "createTime.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    IOdictionary fvSolutionDict
    (
        IOobject
        (
            "fvSolution",
            runTime.system(),
            runTime,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );


    Info<< nl;
    runTime.printExecutionTime(Info);

    // fvSolutionDict

    Info<< "End\n" << endl;

    REQUIRE( fvSolutionDict.get<word>("string") == "string");
    REQUIRE( fvSolutionDict.get<word>("istream") == "istream");
    REQUIRE( fvSolutionDict.get<label>("label") == 10);
    REQUIRE( fvSolutionDict.get<scalar>("scalar") == 10.1);
    REQUIRE( fvSolutionDict.get<vector>("vector") == vector(1.1,2.2,3.3));
    const dictionary subDict = fvSolutionDict.subDict("subDict");
    REQUIRE( subDict.get<word>("sub_string") == "string");
    REQUIRE( subDict.get<word>("sub_istream") == "istream");
    REQUIRE( subDict.get<label>("sub_label") == 10);
    REQUIRE( subDict.get<scalar>("sub_scalar") == 10.1);
    scalarField sf({1.1, 2.2, 3.3, 4.4});
    REQUIRE( fvSolutionDict.get<scalarField>("scalarField") == sf);
}


// ************************************************************************* //
