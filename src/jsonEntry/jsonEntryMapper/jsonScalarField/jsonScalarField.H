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
    Foam::implicitFunctions::jsonScalarField

Description
    Creates a sphere

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    jsonScalarField.C

\*---------------------------------------------------------------------------*/

#ifndef jsonScalarField_H
#define jsonScalarField_H

#include "jsonEntryMapper.H"
#include "Field.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{


/*---------------------------------------------------------------------------*\
                   Class jsonScalarField Declaration
\*---------------------------------------------------------------------------*/

class jsonScalarField
:
    public jsonEntryMapper
{

public:

    //- Runtime type information
    TypeName("scalarField");


    // Constructors
        //- Construct from components
        explicit jsonScalarField
        (
            const word& jsonEntry,
            const json& j,
            dictionary& parentDict
        );


    //- Destructor
    virtual ~jsonScalarField() = default;


    // Member Functions

        virtual autoPtr<entry> getEntry() const
        {
            autoPtr<entry> e;
            std::cout << "jsonEntry_ " << jsonEntry_ << std::endl;
            const json& je = j_[jsonEntry_];
            std::cout << "je " << je.dump(4) << std::endl;
            if
            (
                 je.type() == json::value_t::object
              && je.contains("type") 
            )
            { 
                if (je["type"] == "scalarField")
                {
                    scalarField val(je["value"].size());
                    forAll(val,i)
                    {
                        val[i] = je["value"][i];
                    }
                    e.set(new primitiveEntry(jsonEntry_, val));
                }

              
            }
            return e;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
