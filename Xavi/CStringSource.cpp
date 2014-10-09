/*
 * StringSource.cpp: Class to input data from a string.
 * Copyright 2014 Vincent Damewood
 *
 * This file is part of Xavi.
 *
 * Xavi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Xavi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Xavi. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstring>

#include "CStringSource.hpp"

Xavi::StringSource::StringSource(const char *NewSource)
{
	Source = new char[std::strlen(NewSource) + 1];
	std::strcpy(Source, NewSource);
	Index = 0;
}

Xavi::StringSource::~StringSource()
{
	delete[] Source;
}

bool Xavi::StringSource::Advance()
{
	if (Source[Index] != '\0')
	{
		Index++;
		return true;
	}
	else
	{
		return false;
	}
}

char Xavi::StringSource::GetCurrent()
{
	return Source[Index];
}