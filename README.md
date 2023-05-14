# Entropy Coding Toolbox

Entropy Coding Toolbox is a toolbox that implements different entropy coding techniques.

## Background

The term "entropy coding" refers to a lossless coding technique that uses coded representations to replace data elements. This technique is commonly used in compression standards to reduce the size of compressed data. However, various compression standards use different types of entropy coding techniques. Additionally, there are not many publicly available applications or software specifically for entropy coding, as it is usually implemented within a larger compression technique. Thus we decided to implement at least three entropy coding algorithms by C++, including Huffman coding, arithmetic coding and context-adaptive binary arithmetic coding.

## Installation

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install Entropy Coding Toolbox.

```bash
//write the code here
```

## Usage

### Huffman Coding
```c++
#include"Huffman.h"

Huffman("input.txt", "output.txt", "output");
```
### Arithmetic Coding
```c++
#include"Arithmetic.h"

Arithmetic("input.txt", "output.txt", "output");
```


## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License