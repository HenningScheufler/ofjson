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
    Foam::implicitFunctions::jsonScalar

Description
    Creates a sphere

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    jsonScalar.C

\*---------------------------------------------------------------------------*/

#ifndef jsonScalar_H
#define jsonScalar_H

#include "jsonEntryMapper.H"
#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


/*---------------------------------------------------------------------------*\
                   Class jsonScalar Declaration
\*---------------------------------------------------------------------------*/

class jsonScalar
:
    public jsonEntryMapper
{

public:

    //- Runtime type information
    TypeName("scalar");


    // Constructors
        //- Construct from components
        explicit jsonScalar
        (
            const word& jsonEntry,
            const json& j,
            dictionary& parentDict
        );


    //- Destructor
    virtual ~jsonScalar() = default;


    // Member Functions

        virtual autoPtr<entry> getEntry() const
        {
            autoPtr<entry> e;
            if (j_[jsonEntry_].type() == json::value_t::number_float)
            {
                scalar val(j_[jsonEntry_]);
                e.set(new primitiveEntry(jsonEntry_,val));
            }
            return e;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
