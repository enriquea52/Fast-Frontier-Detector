#!/usr/bin/env python3

import frontier_detector as fd
import numpy as np
import matplotlib.pyplot as plt





def detect_frontiers(grid_map, robot, origin, resolution): # robot and origin have to be numpy arrays

    # robot = __position_to_cell__(robot, origin, resolution)

    # frontiers = np.asarray(fd.wfd(grid_map, robot[0], robot[1]))

    # print("frontiers computed correctly!!!!")

    # frontiers = __cell_to_position__(frontiers, origin, resolution)

    # print("frontier cell numbers:", frontiers.shape)

    #return frontiers
    print("hurra!!!!!!!!")





def __position_to_cell__(p, origin, resolution): # P and origin has to be a numpy array
    # convert world position to map coordinates
    uv = (p - origin) / resolution

    return uv.astype(int)

def __cell_to_position__(cell, origin, resolution):

    # convert map coordinates to world position
    p = cell* resolution + origin

    return p.astype(float)








if __name__ == "__main__":

    # Rows is x and Cols is Y

    map = np.ones((100,50))*-1

    #map[0:4, :] = -1      # Unknown states
    map[10:100-10, 10:100-10] = 0      # Obstacle states

    cells = np.array([[1, 1, 1], [2, 2, 2], [3, 3, 3], [4, 4, 4], [5, 5, 5]])

    map = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12], [13, 14, 15]])


    # map[20:60, 20:30] = -1      # Obstacle states
    # map[0:60, 40:50] = -1      # Obstacle states


    

    frontiers = np.asarray(fd.wfd(map.astype(int), map.astype(int)))
    print(frontiers.shape)

    #map[frontiers[:,0],frontiers[:,1]] = 0.5


    plt.matshow(map) 

    plt.matshow(frontiers) 



    plt.show()

