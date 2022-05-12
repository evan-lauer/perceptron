/**
 * @file print_bytes.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 * This file implements the procedure for loading MNIST training data into a usable data structure.
 * The datasets contain images of handwritten single digits, encoded into ubyte files.
 * 
 * Each image is 28 x 28 pixels, for a total of 784
 * 
 * 
 * 
 * path to 10k images: "C:\\Users\\lauer\\projects\\perceptron\\read_idx\\test_files\\t10k-images.idx3-ubyte";
 * path to 10k labels: "C:\\Users\\lauer\\projects\\perceptron\\read_idx\\test_files\\t10k-labels.idx1-ubyte";
 * 
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;


typedef unsigned char Scalar;
typedef Matrix<Scalar, 1, 784> ImageVector; // row vector for a single image

/**
 * @brief Loads file, checks for failure, and returns.
 * 
 * @param absolute_file_path 
 * @return FILE* 
 */
FILE* load_file(string absolute_file_path)
{
    FILE* f = fopen(absolute_file_path.c_str(), "r");
    if (f == nullptr)
    {
        cout << "Error: Training file at " << absolute_file_path << " failed to load.\n";
        exit(-1);
    }
    return f;
}

/**
 * @brief Get the number of files in the training set, and sets FILE* f to the start of the raw data.
 * 
 * @param f 
 * @return uint32_t 
 */
uint32_t get_num_files(FILE* f)
{
    int success = fseek(f, 4, SEEK_SET);
    if (success != 0)
    {
        cout << "Error: fseek failed.\n";
        exit(-1);
    }
    uint32_t num_files = 0;
    for (int i = 0; i < 4; ++i)
    {
        unsigned char c = fgetc(f);
        num_files = num_files << 8 | c;
    } // f now points to offset of 8 bytes
    return num_files;
}

/**
 * @brief This method allows me to print a digit to cout instead of using a rendering software.
 * It's hard to visualize the images from bytecode.
 * 
 * @param img 
 */
void print_img_vector(ImageVector* img)
{
    for (int i = 0; i < 28; ++i)
    {
        for (int j = 0; j < 28; ++j)
        {
            Scalar ch = (*img)(i*28 + j);
            if (ch < 10) { cout << "00"; }
            else if (ch < 100) { cout << "0"; }
            cout << +ch; // + is added to visualize the actual numerical char
        }
        cout << "\n";
    }
}

/**
 * @brief This method loads an array of bytes (default is unsigned char) from the given absolute file path.
 * Currently expects encoding according to MNIST database, but this could change if necessary. Returns
 * a vector containing row vectors containing unsigned chars.
 * 
 * Note to self: This method allocates lots of memory. Figure out how to free it properly!
 * 
 * @param absolute_file_path 
 * @return vector<ImageVector*>* 
 */
vector<ImageVector*>* load_byte_array(string absolute_file_path, bool is_image_file)
{
    FILE* f = load_file(absolute_file_path);
    

    uint32_t num_files = get_num_files(f);
    if (is_image_file)
    {
        int success = fseek(f, 8, SEEK_CUR);
        if (success != 0)
        {
            cout << "Error: fseek failed.\n";
            exit(-1);
        }
    }

    vector<ImageVector*>* byte_array = new vector<ImageVector*>();

    for (int i = 0; i < num_files; ++i)
    {
        ImageVector* row_vector = new Matrix<Scalar, 1, 784>();
        for (int j = 0; j < 784; ++j)
        {
            Scalar ch = getc(f);
            (*row_vector)(j) = ch;
        }
        byte_array->push_back(row_vector);
    }


    return byte_array;
}

/*
int main()
{
    string filename = "C:\\Users\\lauer\\projects\\perceptron\\read_idx\\test_files\\t10k-images.idx3-ubyte";
    vector<ImageVector*>* vec = load_byte_array(filename, 1);
    ImageVector* img = vec->at(0);
    print_img_vector(img);
    return 1;
}
*/