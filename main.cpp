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
void encodePGMA(int imageArr[H][W], int &h, int &w, int grayLvl)
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

    //skip pgma comments
    while((infile >> std::ws).peek() == '#')
    {
        infile.ignore(4096, '\n');
    }
    infile >> w;
    infile >> h;

    infile >> scale;

    //Copy ASCII values form the .pgma to a 2d array
    for(int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            infile >> imageArr[i][j];
        }
    }
    if(grayLvl == 2)
    {
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
            {
                if(imageArr[i][j] < 128)
                {
                    imageArr[i][j] = 0;
                }
                else
                    imageArr[i][j] = 1;
            }
    }
/*    else
    {
        for (int i = 0; i < h, i++)
            for (int j = 0; j < w; j++) {
                if (imageArr[i][j] < 128) {
                    imageArr[i][j] = 0;
                } else
                    imageArr[i][j] = 1;
            }
    }
    */
    infile.close();
}

void writeEncodedPGMA(int imageArr[H][W], int &h, int &w, int grayLvl)
{
    std::ofstream outFile;
    outFile.open("EncodedBaboon.pgma");
    if(outFile.fail())
    {
        std::cout << "Could not write to file.";
        exit(1);
    }
    //Write the P2 Header and comments
    outFile << "P2" << std::endl;
    outFile << "# Encoded Image" << std::endl;
    outFile << w << ' ';
    outFile << h << std::endl;
    outFile << grayLvl - 1 << std::endl;
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
            outFile << imageArr[i][j] << ' ';
        }
    outFile.close();
}

int main()
{
    int imageArr[H][W];
    int h, w;
    int grayLvl, choice;
    std::cout << "Please select a gray level value. \n";
    std::cout << "---------------------------------. \n";
    std::cout << "1. Gray Level 2 \n";
    std::cout << "2. Gray Level 15 \n";
    std::cout << "Enter 1 or 2: ";
    std::cin >> choice;
    if(choice > 0 && choice <=2)
    {
        if(choice == 1)
        {
            grayLvl = 2;
        }
        else
            grayLvl = 15;
    }
    else
    {
        std::cerr << "Invalid Choice \n";
        std::exit(-1);
    }
    w = W;
    h = H;

    encodePGMA(imageArr, h, w, grayLvl);
    writeEncodedPGMA(imageArr, h, w, grayLvl);
    return 0;
}
