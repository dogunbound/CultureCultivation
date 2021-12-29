import numpy as np
import cv2
from argparse import ArgumentParser
from random import randint

"""
This program takes a colors file (colors.txt) that have rgb and weight values on each line (like a csv file) and makes a randomized square texture.
This might be useful for grass textures.
"""
def main():
    parser = ArgumentParser()
    parser.add_argument('-c', '--colors-file', help='Put the colors txt file indicating what RGB and weights you want to randomize in your image', dest='colors')
    parser.add_argument('-x', '--x-size', help='size in x direction of new image', dest='x')
    parser.add_argument('-y', '--y-size', help='size in y direction of new image', dest='y')

    options = parser.parse_args()
    newImage = np.zeros((int(options.x), int(options.y),3), np.uint8)
    
    colors = []
    weights = []
    with open(options.colors, 'r') as file:
        lines = file.readlines()

        for line in lines:
            arr = line.split(' ')
            colors.append([int(arr[2]), int(arr[1]), int(arr[0])])
            for i in range(int(arr[3])):
                weights.append(len(colors)-1)

        file.close()

    for x in range(newImage.shape[0]):
        for y in range(newImage.shape[1]):
            newImage[x][y] = colors[weights[randint(0, len(weights)-1)]]

    newImage = cv2.rotate(newImage, cv2.cv2.ROTATE_90_CLOCKWISE)
    cv2.imwrite('autogenImage.png', newImage)

if __name__ == "__main__":
    main()
