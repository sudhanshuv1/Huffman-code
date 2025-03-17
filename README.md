# Huffman Algorithm

### Huffman Algorithm is a widely used data compression technique based on the frequency of characters. It uses variable-length encoding to minimize the overall size of the data. Here's how the algorithm works step by step:

## Steps of the Huffman Algorithm

    1. Frequency Count:

        - Start by calculating the frequency of each character in the input data (e.g., text or symbols).

    2. Priority Queue (Min-Heap):

        - Insert all the characters into a priority queue (or min-heap) based on their frequency. Each character is treated as a tree node.

    3. Build the Huffman Tree:

        - While there is more than one node in the priority queue:

            - Remove the two nodes with the smallest frequency from the queue.

            - Combine these two nodes into a new parent node, where the frequency of the parent is the sum of the two child nodes' frequencies.

            - Insert the new parent node back into the priority queue.

        - Repeat until only one node remains in the queue, which becomes the root of the Huffman tree.

    4. Generate Codes:

        - Traverse the Huffman tree to assign binary codes to each character:

            - Assign 0 for the left child and 1 for the right child during traversal.

            - Each character is given a unique code based on its position in the tree.

    5. Encode the Data:

       -  Replace each character in the input data with its corresponding binary code from the Huffman tree.

    6. Decode the Data:

        - To decompress, use the binary codes to traverse the Huffman tree and retrieve the original characters.

## Key Features

    - *Prefix-Free Codes:* No code is a prefix of another, making decoding unambiguous.

    - *Greedy Algorithm:* The algorithm ensures optimal compression by always merging the least frequent nodes first.

    - *Efficient Representation:* Frequently used characters have shorter codes, minimizing the overall size.