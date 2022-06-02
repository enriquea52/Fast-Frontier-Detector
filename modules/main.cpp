
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include <deque>




namespace py = pybind11;




std::vector<int>  neighbors(int index)
{   
    switch(index) {

    case 0 :
        return {0, -1};
    case 1 :
        return {-1, -1};
    case 2 :
        return {-1, 0};
    case 3 :
        return {-1, 1};
    case 4 :
        return {0, 1};
    case 5 :
        return {1, 1};
    case 6:
        return {1, 0};
    case 7:
        return {1, -1};
    case 8:
        return {0, 0};

    }

}



// x rows, y cols
std::vector<std::vector<int>>  FFD(py::array_t<int, py::array::c_style | py::array::forcecast> cells,  py::array_t<int, py::array::c_style | py::array::forcecast> map)
{

    std::deque<std::vector<int>>  Q;

    std::vector<int> x_(2, 0);// Array to store the current state
    std::vector<int> x_p(2, 0);// Array to store the neighbor

    std::vector<int> x_f(2, 0);// Array to store the neighbor of the neighbor

    std::vector<int> n_(2, 0); // array used to store the current neighbor
    std::vector<int> nn_(2, 0); // array used to store the current neighbor of another neighbor


    py::buffer_info map_buff = map.request();
    py::buffer_info cell_buff = cells.request();


    int *map_ptr = static_cast<int *>(map_buff.ptr);
    int *cell_ptr = static_cast<int *>(cell_buff.ptr);


    int map_Rows = map_buff.shape[0];int map_Cols = map_buff.shape[1];

    int cells_Rows = cell_buff.shape[0];int cells_Cols = cell_buff.shape[1];

    std::vector<std::vector<int>> frontiers;




    for (int m = 0; m < cells_Rows*cells_Cols; m+=2)
    {
        Q.push_back({cell_ptr[m],cell_ptr[m+1]});
    }


    while (!Q.empty())
    {
        x_ = Q.front(); Q.pop_front();

        for(int i = 0; i < 9; i++)
        {
            n_ = neighbors(i);

            x_p[0] = x_[0] + n_[0]; x_p[1] = x_[1] + n_[1];

            if((x_p[0] >= 0) && (x_p[0] < map_Rows) && (x_p[1] >= 0) && (x_p[1] < map_Cols) && (map_ptr[x_p[0]*map_Cols + x_p[1]] == 0))
            {
                for(int j = 0; j < 8; j++)
                {
                    nn_ = neighbors(j);

                    x_f[0] = x_p[0] + nn_[0]; x_f[1] = x_p[1] + nn_[1];

                    if((x_f[0] >= 0) && (x_f[0] < map_Rows) && (x_f[1] >= 0) && (x_f[1] < map_Cols) && (map_ptr[x_f[0]*map_Cols + x_f[1]] < 0))
                    {
                        map_ptr[x_p[0]*map_Cols + x_p[1]] = 1;

                        frontiers.push_back({x_p[0], x_p[1]});

                        Q.push_back({x_p[0], x_p[1]});

                    }

                }

            }

        }

    }

    return frontiers;

}









PYBIND11_MODULE(frontier_detector, handle) {

    handle.doc() = "There is no wrong time to rock";

    py::bind_vector<std::vector<std::vector<int>>>(handle, "IntVector2D");

    handle.def("FFD", &FFD);


}
