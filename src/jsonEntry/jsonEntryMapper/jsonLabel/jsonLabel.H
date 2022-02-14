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
    Foam::implicitFunctions::jsonLabel

Description
    Creates a sphere

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    jsonLabel.C

\*---------------------------------------------------------------------------*/

#ifndef jsonLabel_H
#define jsonLabel_H

#include "jsonEntryMapper.H"
#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


/*---------------------------------------------------------------------------*\
                   Class jsonLabel Declaration
\*---------------------------------------------------------------------------*/

class jsonLabel
:
    public jsonEntryMapper
{

public:

    //- Runtime type information
    TypeName("label");


    // Constructors
        //- Construct from components
        explicit jsonLabel
        (
            const word& jsonEntry,
            const json& j,
            dictionary& parentDict
        );


    //- Destructor
    virtual ~jsonLabel() = default;


    // Member Functions

        virtual autoPtr<entry> getEntry() const
        {
            autoPtr<entry> e;
            // std::cout << "j_[jsonEntry_].type() " << j_[jsonEntry_].type() << std::endl;
            if
            (
                j_[jsonEntry_].type() == json::value_t::number_integer
             || j_[jsonEntry_].type() == json::value_t::number_unsigned
            )
            {
                label val(j_[jsonEntry_]);
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
