/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2018-2021 OpenCFD Ltd.
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

#include "jsonEntry.H"
#include "addToMemberFunctionSelectionTable.H"
#include "stringOps.H"
#include "IFstream.H"
#include "IOstreams.H"
#include "Time.H"
#include "fileOperation.H"

#include <json.H>

// using json = nlohmann::json;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

bool Foam::functionEntries::jsonEntry::log(false);


namespace Foam
{
namespace functionEntries
{
    addNamedToMemberFunctionSelectionTable
    (
        functionEntry,
        jsonEntry,
        execute,
        dictionaryIstream,
        json
    );

    addNamedToMemberFunctionSelectionTable
    (
        functionEntry,
        jsonEntry,
        execute,
        primitiveEntryIstream,
        json
    );


} // End namespace functionEntries
} // End namespace Foam


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

Foam::fileName Foam::functionEntries::jsonEntry::resolveFile
(
    const fileName& dir,
    const fileName& f,
    const dictionary& dict
)
{
    fileName fName(f);

    // Substitute dictionary and environment variables.
    // Allow empty substitutions.
    stringOps::inplaceExpand(fName, dict, true, true);

    if (fName.empty() || fName.isAbsolute())
    {
        return fName;
    }

    // Relative name
    return dir/fName;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::functionEntries::jsonEntry::execute
(
    dictionary& parentDict,
    Istream& is
)
{
    const fileName rawName(is);
    const fileName fName(resolveFile(is.name().path(), rawName, parentDict));

    std::ifstream i(fName);
    json j;
    i >> j;

    from_json(j,parentDict);

    return true;
}


bool Foam::functionEntries::jsonEntry::execute
(
    const dictionary& parentDict,
    primitiveEntry& entry,
    Istream& is
)
{
    const fileName rawName(is);
    const fileName fName(resolveFile(is.name().path(), rawName, parentDict));

    return true;
    
}


// ************************************************************************* //
