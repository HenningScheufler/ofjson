/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019-2021 OpenCFD Ltd.
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

\*---------------------------------------------------------------------------*/

#include "jsonEntryMapper.H"
// #include "error.H"
// #include "json.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(jsonEntryMapper, 0);
    defineRunTimeSelectionTable(jsonEntryMapper, word);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::entry> Foam::jsonEntryMapper::New
(
    const word& jsonEntry,
    const json& j,
    dictionary& parentDict 
)
{
    for (const word& type : wordConstructorTablePtr_->toc())
    {
        auto ctorPtr = wordConstructorTablePtr_->cfind(type);
        autoPtr<jsonEntryMapper> jsonType(ctorPtr()(jsonEntry,j,parentDict));
        Foam::autoPtr<Foam::entry> entryType = jsonType->getEntry();
        if (entryType)
        {
            return entryType;
        }
    }

    FatalErrorInFunction
        << "unable to classify jsonEntry " << jsonEntry << nl
        << "available types are " << nl
        << wordConstructorTablePtr_->sortedToc()
        << exit(FatalError);

    return autoPtr<entry>();
}

Foam::jsonEntryMapper::jsonEntryMapper
(
    const word& jsonEntry,
    const json& j,
    dictionary& parentDict 
)
:
    jsonEntry_(jsonEntry),
    j_(j),
    parentDict_(parentDict) 
{}

// ************************************************************************* //
