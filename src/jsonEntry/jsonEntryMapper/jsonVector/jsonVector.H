/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019 OpenCFD Ltd.
    Copyright (C) 2019-2020 DLR
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

Class
    Foam::implicitFunctions::jsonVector

Description
    Creates a sphere

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    jsonVector.C

\*---------------------------------------------------------------------------*/

#ifndef jsonVector_H
#define jsonVector_H

#include "jsonEntryMapper.H"
#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


/*---------------------------------------------------------------------------*\
                   Class jsonVector Declaration
\*---------------------------------------------------------------------------*/

class jsonVector
:
    public jsonEntryMapper
{

public:

    //- Runtime type information
    TypeName("vector");


    // Constructors
        //- Construct from components
        explicit jsonVector
        (
            const word& jsonEntry,
            const json& j,
            dictionary& parentDict
        );


    //- Destructor
    virtual ~jsonVector() = default;


    // Member Functions

        virtual autoPtr<entry> getEntry() const
        {
            autoPtr<entry> e;
            if (j_[jsonEntry_].type() == json::value_t::array)
            { 
                if (j_[jsonEntry_].size() == 3)
                {
                    vector val(j_[jsonEntry_][0],j_[jsonEntry_][1],j_[jsonEntry_][2]);
                    e.set(new primitiveEntry(jsonEntry_,val));
                }
                // {
                //     return true;
                // }
            }
            return e;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
