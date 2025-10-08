#include "../utilities/template.h"

#include "../../content/geometry/ConvexHull.h"
namespace ignore {
	#include "../../content/geometry/SegmentDistance.h"
}
#include "../../content/geometry/PointInsideHull.h"
#include "../../content/geometry/InsidePolygon.h"

int main() {
	rep(it,0,100000) {
		int N = rand() % 15;
		vector<P> ps;
		rep(i,0,N) ps.emplace_back(rand() % 20 - 10, rand() % 20 - 10);
		vector<P> ps2 = convexHull(ps);
		if (ps2.empty()) continue;
		rep(it2,0,20) {
			int x = rand() % 22 - 11;
			int y = rand() % 22 - 11;
			P p{x,y};
			assert((inPoly(ps2, p) == 1) == (inHull(ps2, p, true)));
			assert((inPoly(ps2, p) != 0) == (inHull(ps2, p, false)));
		}
	}
	cout<<"Tests passed!"<<endl;
}
