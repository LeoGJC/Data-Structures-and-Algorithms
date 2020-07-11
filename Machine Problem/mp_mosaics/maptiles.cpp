/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas *answer = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> kopcol={};
    map<Point<3>, int> mapped={};
    unsigned i = 0;
    do {
        Point<3> pt = convertToXYZ(theTiles[i].getAverageColor());
        kopcol.push_back(pt);
        mapped[pt] = i;
        i++;
    } while (i < theTiles.size());

    KDTree<3> kD(kopcol);
    int m = 0;
    while(m < theSource.getRows()) {
        int n = 0;
        do{
            Point<3> final_ = kD.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(m, n)));
            answer->setTile(m, n, &(theTiles[mapped[final_]]));
            n++;
        }
        while (n < theSource.getColumns());
      m++;
    }
    return answer;

}


