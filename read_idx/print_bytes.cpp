#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

vector<char>* get_byte_vector(FILE* file, vector<char>* char_vector)
{
    unsigned char ch = 0;
    while (!feof(file))
    {
        ch = getc(file);
        char_vector->push_back(ch);
        // cout << character??????
    }

    return char_vector;
}


char** get_byte_array(string absolute_file_path)
{
    return nullptr;
}


int main()
{

    /*
        Data is stored as 28 x 28 pixel arrays, with each pixel being [0,255]

        28^2 = 784
    */
    MatrixXd m = MatrixXd::Random(3,3);
    cout << m;
   

    string filename_ten_thousand_images = "C:\\Users\\lauer\\projects\\perceptron\\read_idx\\test_files\\t10k-images.idx3-ubyte";
    string filename_ten_thousand_labels = "C:\\Users\\lauer\\projects\\perceptron\\read_idx\\test_files\\t10k-labels.idx1-ubyte";

    vector<char>* image_bytes = new vector<char>(); // 
    vector<char>* label_bytes = new vector<char>(); // each char is 1 byte, 8 bits in a byte. 1 byte is [0,255]

    FILE* image_file = fopen(filename_ten_thousand_images.c_str(), "r");
    FILE* label_file = fopen(filename_ten_thousand_labels.c_str(), "r");

    if (image_file == nullptr)
    {
        cout << "Image (and perhaps label) file(s) failed to open\n";
        return 1;
    }

    if (label_file == nullptr)
    {
        cout << "Label file failed to open\n";
        return 1;
    }

    image_bytes = get_byte_vector(image_file, image_bytes);
    label_bytes = get_byte_vector(label_file, label_bytes);

    int num_image_offset = 1;
    int offset = 16 + num_image_offset * 784; // num bytes

    // for (int i = 0; i < 28; ++i)
    // {
    //     for (int j = 0; j < 28; ++j)
    //     {
    //         unsigned char ch = image_bytes->at(i * 28 + j + offset);
    //         if (ch < 10)
    //         {
    //             cout << "00";
    //         } else
    //         if (ch < 100)
    //         {
    //             cout << "0"; 
    //         }
    //         cout << +ch;
    //         cout << " ";
    //     }
    //     cout << "\n";
    // } // this works!

    return 0;
}