/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2018 OpenCFD Ltd.
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
    Foam::functionEntries::jsonEntry

Description
    A dictionary directive for including a file, expects a single string
    to follow.

    An example of the \c \#include directive to include a file:
    \verbatim
        #include "includeFileMustExist"
    \endverbatim

    The usual expansion of environment variables and other expansions
    (eg, a leading "<case>/", "<system>/", "<etc>/", ...) are retained.

See also
    fileName, string::expand()

SourceFiles
    jsonEntry.C

\*---------------------------------------------------------------------------*/

#ifndef functionEntries_jsonEntry_H
#define functionEntries_jsonEntry_H

#include "functionEntry.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace functionEntries
{

/*---------------------------------------------------------------------------*\
                        Class jsonEntry Declaration
\*---------------------------------------------------------------------------*/

class jsonEntry
:
    public functionEntry
{
protected:

    // Protected Member Functions

        //- Expand include fileName and return
        static fileName resolveFile
        (
            const fileName& dir,
            const fileName& f,
            const dictionary& dict
        );

public:

    // Member Functions

        //- Include file in a sub-dict context
        static bool execute(dictionary& parentDict, Istream& is);

        //- Include file in a primitiveEntry context
        static bool execute
        (
            const dictionary& parentDict,
            primitiveEntry& entry,
            Istream& is
        );
};



} // End namespace functionEntries
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
