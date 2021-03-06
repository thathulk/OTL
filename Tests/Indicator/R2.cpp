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

#include <vector>
#include <list>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/math/constants/constants.hpp>
#include <OTL/Indicator/R2.h>
#include <OTL/Utility/Weight/NormalBoundaryIntersection.h>

namespace r2
{
template <typename _TReal>
std::list<std::vector<_TReal> > GenerateCirclePoints(const _TReal radius, const size_t nPoints)
{
	typedef std::vector<_TReal> _TPoint;
	std::list<_TPoint> population;
	for (size_t i = 0; i < nPoints; ++i)
	{
		const _TReal angle = i * boost::math::constants::pi<_TReal>() / 2 / nPoints;
		std::vector<_TReal> point(2);
		point[0] = radius * cos(angle);
		assert(point[0] >= 0);
		point[1] = radius * sin(angle);
		assert(point[1] >= 0);
		population.push_back(point);
	}
	return population;
}

BOOST_AUTO_TEST_CASE(R2)
{
	typedef double _TReal;
	typedef otl::indicator::R2<_TReal> _TIndicator;
	typedef _TIndicator::TMetric _TMetric;
	typedef _TIndicator::TPoint _TPoint;
	auto _weightVectors = otl::utility::weight::NormalBoundaryIntersection<_TReal>(2, 50);
	std::vector<_TPoint> weightVectors(_weightVectors.begin(), _weightVectors.end());
	const std::list<_TPoint> _front = GenerateCirclePoints<_TReal>(2, 100);
	const std::vector<_TPoint> front(_front.begin(), _front.end());
	_TIndicator indicator(_TPoint(2, 0), weightVectors);
	indicator(front);
}
}
