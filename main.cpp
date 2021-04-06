/*
 * Author: Ryan Galloway
 *
 * Class: CS5375 Multimedia Programming
 *
 * Assignment 4:
 *
 * Program to
 */

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>

const int H = 512;
const int W = 512;

//pull the values of the pgma from the file
void readPGM(int imageArr[H][W], int h, int w)
{
    char c;
    int scale;
    std::ifstream infile;
    infile.open("baboon.pgma");

    //read PGM header
    infile >> c;
    assert(c == 'P');
    infile >> c;
    assert(c == '2');

    //skip pgm comments
    while((infile >> std::ws).peek() == '#')
    {
        infile.ignore(4096, '\n');
    }
    infile >> w;
    infile >> h;

    infile >> scale;
    assert(scale == 255);

    //Copy ASCII values form the .pgma to a 2d array
    for(int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            infile >> imageArr[i][j];
        }
    }
    infile.close();
}

void encode(int imageArr[H][W], int h, int w, int graylvl)
{
    //Do something
}

void writePGM(int imageArr[H][W], int h, int w, int grayLvl)
{
    std::ofstream outFile;
    outFile.open("ModifiedBaboon.pgma");
    if(outFile.fail())
    {
        std::cout << "Could not write to file.";
        exit(1);
    }
    //Write the P2 Header and comments
    outFile << "P2" << std::endl;
    outFile << "# modifiedBaboon.pgma using quadtree." << std::endl;
    outFile << w << ' ';
    outFile << h << std::endl;
    outFile << grayLvl << std::endl;

    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
        {
            assert(imageArr[i][j] <= 255);
            assert(imageArr[i][j] >= 0);
            outFile << imageArr[i][j] << ' ';
        }
    outFile.close();
}

int main(int argc, char* argv[])
{
    int imageArr[H][W];
    int h, w;
    int grayLvl;
    if(argc != 2)
    {
        std::cerr << "Usage: Please enter a valid threshold.";
        exit(-1);
    }
    grayLvl = std::stoi(argv[1]);
    if(grayLvl < 2 || grayLvl > 255)
    {
        std::cerr << "Please enter a valid gray level 2-255.";
        exit(-1);
    }
    h = H;
    w = W;

    readPGM(imageArr, h, w);
    writePGM(imageArr, h, w, grayLvl);
    return 0;
}
