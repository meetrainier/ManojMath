//This program shows how to call async.
//Key learning: When passing arguments of async by reference, wrap them in std::ref() 
#include "Header.h"

std::vector<P2d>  FindWithin2(double xmin, double ymin, double xmax, double ymax, std::vector<P2d>& vec)

{

    std::vector<P2d> vecLocal;
    for (auto& p : vec)
    {
        if (p.x < xmax && p.x > xmin)
        {
            if (p.y < ymax && p.x > ymin)
            {
                vecLocal.emplace_back(p);
            }
        }
    }
    return vecLocal;
}

int UseAsync1()
{
    std::vector<P2d> vec1{ {6,6}, {1,1 }, {2,2} };
    std::future<std::vector<P2d>> cTask = std::async(FindWithin2, 0.0, 0.0, 5.0, 5.0, std::ref(vec1));//compilation error

    return 0;
}

int UseAsync2()
{
    std::vector<P2d> vec1{ {6,6}, {1,1 }, {2,2} };

    auto the_lambda = [](double xmin, double ymin, double xmax, double ymax, std::vector<P2d>& vec)->std::vector<P2d>
    {

        std::vector<P2d> vecLocal;
        for (auto& p : vec)
        {
            if (p.x < xmax && p.x > xmin)
            {
                if (p.y < ymax && p.x > ymin)
                {
                    vecLocal.emplace_back(p);
                }
            }
        }
        return vecLocal;

    };

    std::future<std::vector<P2d>> cTask = std::async(the_lambda, 0.0, 0.0, 5.0, 5.0, std::ref(vec1));//compilation error

    return 0;
}
