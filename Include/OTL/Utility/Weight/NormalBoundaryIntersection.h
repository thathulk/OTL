/*!
Copyright (C) 2014, 申瑞珉 (Ruimin Shen)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
@ARTICLE{,
  author = {Indraneel Das and J. E. Dennis},
  title = {Normal-Boundary Intersection: A New Method for Generating the Pareto
	Surface in Nonlinear Multicriteria Optimization Problems},
  journal = {SIAM Journal on Optimization},
  year = {1998},
  volume = {8},
  pages = {631-657},
  number = {3},
  doi = {10.1137/S1052623496307510}
}
*/

#pragma once

#include <cassert>
#include <vector>
#include <list>
#include <numeric>

namespace otl
{
namespace utility
{
namespace weight
{
template <typename _TReal>
void _NormalBoundaryIntersection(const size_t component, const size_t division, std::vector<_TReal> &point, std::list<std::vector<_TReal> > &points)
{
	assert(0 <= component && component < point.size());
	if (component == point.size() - 1)
	{
		point[component] = 1 - std::accumulate(point.begin(), --point.end(), (_TReal)0);
		points.push_back(point);
	}
	else
	{
		assert(division > 1);
		for (size_t i = 0; i <= division; ++i)
		{
			point[component] = (_TReal)i / division;
			if (std::accumulate(point.begin(), point.begin() + component + 1, (_TReal)0) > 1)
				break;
			_NormalBoundaryIntersection(component + 1, division, point, points);
		}
	}
}

template <typename _TReal>
std::list<std::vector<_TReal> > NormalBoundaryIntersection(const size_t dimension, const size_t division)
{
	assert(dimension > 1);
	std::list<std::vector<_TReal> > points;
	std::vector<_TReal> point(dimension);
	_NormalBoundaryIntersection(0, division, point, points);
	return points;
}
}
}
}
