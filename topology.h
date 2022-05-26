#include <vector>
#include <Eigen/Dense>
#include "print_bytes.h"

#ifndef _TOPOLOGY
#define _TOPOLOGY

using namespace std;
using namespace Eigen;


/**
 * @brief Notes to self::
 * 
 * 
 * These class definitions need a lot of work. One on hand, [1] we need to represent the activations of individual nodes as Eigen-brand column vectors,
 * so that we can do linear algebra with them quickly. On the other hand, [2] each node is linked to an Eigen-brand column vector of weights,
 * and we need to be able to do stuff with this quickly (i think). 
 * 
 * But for [1], we need our Nodes in a vector. But if, for [2], we have a bunch of weights for every node, then [1] will be super slow.
 * So we need a way of linking each node to the corresponding vector of weights it's attached to without slowing things down. Option [A]
 * would be to put a pointer from each node to a Vector of weights. Option [B] would be to simply index the nodes in a vector, and index the
 * weight vectors in another vector, where both vectors have the same indices. I think [B] > [A].
 * 
 * TODO:
 * Definitely worth walking through a simple example and doing all of the calculus. Then create a list of the most expensive operations that occur,
 * so that you can resolve problems as above (figure out what info you need, make sure every operation has no more memory involved than absolutely
 * necessary)
 * 
 * TODON'T:
 * DON'T just start writing more code without understanding *why* you are writing it.
 * 
 */

class Node
{
    double bias;

    // This is a column vector containing the weights between this Node and every node in the previous layer
    Matrix<double, Dynamic, 1> weights;
};

class Layer
{
    vector<Node*> layer;
};

class Network
{
    vector<Layer*> net;
};

// Returns number of hidden layers in the network (total layers - 2)
int num_hidden_layers(Network* net);

// Returns the number of nodes in the i-th layer (or -1 if layer doesn't exist)
int size_ith_layer(Network* net, int i);





#endif