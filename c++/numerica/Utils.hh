//
// Created by ernesto on 14/05/17.
//

#ifndef NUMERICA_UTILS_HH
#define NUMERICA_UTILS_HH

#include <cmath>
#include <utility>
#include <cstdlib>

class Utils {
public:
    template <typename Func> static std::pair<double, double> minimize(Func function, double increment, double start, double end) {
        double min, min_f = INFINITY;
        for (double ac = start; ac <= end; ac += increment) {
            double res = function(ac);
            if (res < min_f) {
                min = ac;
                min_f = res;
            }
        }
        return std::make_pair(min, min_f);
    }
};


#endif //NUMERICA_UTILS_HH
