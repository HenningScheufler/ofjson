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
    Foam::jsonEntryMapper

Description
    Base class for implicit functions

    Original code supplied by Henning Scheufler, DLR (2019)

SourceFiles
    jsonEntryMapper.C

\*---------------------------------------------------------------------------*/

#ifndef jsonEntryMapper_H
#define jsonEntryMapper_H

#include "autoPtr.H"
#include "dictionary.H"
//#include "json.H"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class jsonEntryMapper Declaration
\*---------------------------------------------------------------------------*/

class jsonEntryMapper
{
protected:

    word jsonEntry_;
    const json& j_;
    dictionary& parentDict_;

public:

    //- Runtime type information
    TypeName("jsonEntryMapper");

    //- Declare run-time constructor selection table
    declareRunTimeSelectionTable
    (
        autoPtr,
        jsonEntryMapper,
        word,
        (
            const word& jsonEntry,
            const json& j,
            dictionary& parentDict
        ),
        (jsonEntry,j,parentDict)
    );


    // Constructors

        //- construct from components
        explicit jsonEntryMapper
        (
            const word& jsonEntry,
            const json& j,
            dictionary& parentDict 
        );


        //- Return a reference to the selected jsonEntryMapper
        static autoPtr<entry> New
        (
            const word& jsonEntry,
            const json& j,
            dictionary& parentDict
        );


    //- Destructor
    virtual ~jsonEntryMapper() = default;


    // Member Functions

        virtual autoPtr<entry> getEntry() const
        {
            autoPtr<entry> e;
            return e;
        }

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
