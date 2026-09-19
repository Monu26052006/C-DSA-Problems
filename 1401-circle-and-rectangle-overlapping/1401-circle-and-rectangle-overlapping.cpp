#include <cmath>
class Solution {
public:
    bool checkOverlap(int r, int x, int y, int x1, int y1, int x2, int y2) {
        bool inRect = (x>=x1-r && x<=x2+r) && (y>=y1-r && y<=y2+r);
        bool inSec1 = ((x<=x1 && x>=x1-r) && (y>=y2 && y<=y2+r)) && (pow(x1-x,2)+pow(y2-y,2)-pow(r,2) > 0);
        bool inSec2 = ((x<=x2+r && x>=x2) && (y>=y2 && y<=y2+r)) && (pow(x2-x,2)+pow(y2-y,2)-pow(r,2) > 0);
        bool inSec3 = ((x<=x1 && x>=x1-r) && (y>=y1-r && y<=y1)) && (pow(x1-x,2)+pow(y1-y,2)-pow(r,2) > 0);
        bool inSec4 = ((x<=x2+r && x>=x2) && (y>=y1-r && y<=y1)) && (pow(x2-x,2)+pow(y1-y,2)-pow(r,2) > 0);

        return inRect && !inSec1 && !inSec2 && !inSec3 && !inSec4;
    }
};