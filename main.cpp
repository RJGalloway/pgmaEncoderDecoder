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
#include <cmath>

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
    else
    {
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
            {
                if (imageArr[i][j] >= 0 && imageArr[i][j] <= 16)
                    imageArr[i][j] = 0;
                else if(imageArr[i][j] >= 17 && imageArr[i][j] <= 33)
                    imageArr[i][j] = 1;
                else if(imageArr[i][j] >= 34 && imageArr[i][j] <= 50)
                    imageArr[i][j] = 2;
                else if(imageArr[i][j] >= 51 && imageArr[i][j] <= 67)
                    imageArr[i][j] = 3;
                else if(imageArr[i][j] >= 68 && imageArr[i][j] <= 84)
                    imageArr[i][j] = 4;
                else if(imageArr[i][j] >= 85 && imageArr[i][j] <= 101)
                    imageArr[i][j] = 5;
                else if(imageArr[i][j] >= 102 && imageArr[i][j] <= 118)
                    imageArr[i][j] = 6;
                else if(imageArr[i][j] >= 119 && imageArr[i][j] <= 135)
                    imageArr[i][j] = 7;
                else if(imageArr[i][j] >= 136 && imageArr[i][j] <= 152)
                    imageArr[i][j] = 8;
                else if(imageArr[i][j] >= 153 && imageArr[i][j] <= 169)
                    imageArr[i][j] = 9;
                else if(imageArr[i][j] >= 170 && imageArr[i][j] <= 186)
                    imageArr[i][j] = 10;
                else if(imageArr[i][j] >= 187 && imageArr[i][j] <= 203)
                    imageArr[i][j] = 11;
                else if(imageArr[i][j] >= 204 && imageArr[i][j] <= 220)
                    imageArr[i][j] = 12;
                else if(imageArr[i][j] >= 221 && imageArr[i][j] <= 237)
                    imageArr[i][j] = 13;
                else
                    imageArr[i][j] = 14;
            }
    }
    infile.close();
}

void writeEncodedPGMA(int imageArr[H][W], int &h, int &w, int grayLvl)
{
    std::ofstream outFile;

    if(grayLvl == 2)
        outFile.open("EncodedBaboon2-Levels.pgma");
    else
        outFile.open("EncodedBaboon15-Levels.pgma");

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

    //Gray level == 2
    if(grayLvl == 2)
    {
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
            {
                assert(imageArr[i][j] >= 0);
                assert(imageArr[i][j] <= 1);
                outFile << imageArr[i][j] << ' ';
            }
    }
    //Gray level == 15
    else
    {
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
            {
                assert(imageArr[i][j] >= 0);
                assert(imageArr[i][j] <= 14);
                outFile << imageArr[i][j] << ' ';
            }
    }

    outFile.close();
}

void decodePGMA(int imageArr[H][W], int &h, int &w, int grayLvl) {
    char c;
    int scale;
    std::ifstream inFile;

    //Set output file for appropriate gray level selected
    if (grayLvl == 2)
        inFile.open("EncodedBaboon2-Levels.pgma");
    else
        inFile.open("EncodedBaboon15-Levels.pgma");
    //read PGM header
    inFile >> c;
    assert(c == 'P');
    inFile >> c;
    assert(c == '2');

    //skip pgma comments
    while ((inFile >> std::ws).peek() == '#') {
        inFile.ignore(4096, '\n');
    }

    inFile >> w;
    inFile >> h;

    inFile >> scale;

    //Write the values in the encoded pgma to the imgArr
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            inFile >> imageArr[i][j];
        }
    }

    if (grayLvl == 2) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (imageArr[i][j] == 0)
                    imageArr[i][j] = 63;
                else
                    imageArr[i][j] = 191;
            }
        }
    } else {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (imageArr[i][j] == 0)
                    imageArr[i][j] = 8;
                else if (imageArr[i][j] == 1)
                    imageArr[i][j] = 25;
                else if (imageArr[i][j] == 2)
                    imageArr[i][j] = 42;
                else if (imageArr[i][j] == 3)
                    imageArr[i][j] = 59;
                else if (imageArr[i][j] == 4)
                    imageArr[i][j] = 76;
                else if (imageArr[i][j] == 5)
                    imageArr[i][j] = 93;
                else if (imageArr[i][j] == 6)
                    imageArr[i][j] = 110;
                else if (imageArr[i][j] == 7)
                    imageArr[i][j] = 127;
                else if (imageArr[i][j] == 8)
                    imageArr[i][j] = 144;
                else if (imageArr[i][j] == 9)
                    imageArr[i][j] = 161;
                else if (imageArr[i][j] == 10)
                    imageArr[i][j] = 178;
                else if (imageArr[i][j] == 11)
                    imageArr[i][j] = 195;
                else if (imageArr[i][j] == 12)
                    imageArr[i][j] = 212;
                else if (imageArr[i][j] == 13)
                    imageArr[i][j] = 229;
                else
                    imageArr[i][j] = 246;
            }
        }
    }
}

void writeDecodedPGMA(int imageArr[H][W], int &h, int &w, int grayLvl)
{
    std::ofstream outFile;

    if(grayLvl == 2)
        outFile.open("DecodedBaboon2-Levels.pgma");
    else
        outFile.open("DecodedBaboon15-Levels.pgma");

    if(outFile.fail())
    {
        std::cout << "Could not write to file.";
        exit(1);
    }

    //Write the P2 Header and comments
    outFile << "P2" << std::endl;
    outFile << "# Decoded Baboon Image" << std::endl;
    outFile << w << ' ';
    outFile << h << std::endl;

    if(grayLvl == 2)
        outFile << 191 << std::endl;
    else
        outFile << 247 << std::endl;


    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            outFile << imageArr[i][j] << ' ';
        }
}
void distortion(int imageArr[H][W],  int &h, int &w)
{
    char c;
    int scale;
    double distortion = 0;
    int n = h * w;
    auto tmpArray = new int[H][W];
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
            infile >> tmpArray[i][j];
        }
    }
    for(int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            distortion += pow((tmpArray[i][j] - imageArr[i][j]), 2);
        }
    std::cout << "Distortion = " << distortion/n << std::endl;
    delete [] tmpArray;
}

void generateErrorImage(int imageArr[H][W], int &h, int &w)
{
    char c;
    int scale;
    auto tmpArray = new int[H][W];
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
            infile >> tmpArray[i][j];
        }
    }
    for(int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            imageArr[i][j] = abs((tmpArray[i][j] - imageArr[i][j]));
        }
    delete [] tmpArray;
}

void writeErrorImg(int imageArr[H][W], int &h, int &w, int grayLvl)
{
    std::ofstream outFile;

    if(grayLvl == 2)
        outFile.open("ErrorImage2-Levels.pgma");
    else
        outFile.open("ErrorImage15-Levels.pgma");

    if(outFile.fail())
    {
        std::cout << "Could not write to file.";
        exit(1);
    }

    //Write the P2 Header and comments
    outFile << "P2" << std::endl;
    outFile << "# Decoded Baboon Image" << std::endl;
    outFile << w << ' ';
    outFile << h << std::endl;
    if(grayLvl == 2)
        outFile << 64 << std::endl;
    else
        outFile << 9 << std::endl;


    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            outFile << imageArr[i][j] << ' ';
        }

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
    decodePGMA(imageArr, h, w, grayLvl);
    writeDecodedPGMA(imageArr, h, w, grayLvl);
    distortion(imageArr, h, w);
    generateErrorImage(imageArr, h, w);
    writeErrorImg(imageArr, h, w, grayLvl);

    return 0;
}
