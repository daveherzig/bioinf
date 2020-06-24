# C++ Bioinformatics Library
April-2020, David Herzig
Version 0.2

## Compile Command
```
git clone URL
cd bioinf
cmake .
make
```

## Version History
0.1, December 2019
- Basic Ideas

0.2, June 2020
- Included Boost Library 1.73
- Genome Assembly

0.3, July 2020
- Iterative Version DFS
- Levenstein Distance


## Boost Library (some hints to build boost on windows)
Here are some information on how the Boost library is used on the Windows
environment:
1. Download boost from: https://www.boost.org/users/download/
2. Execute command described on: https://www.boost.org/doc/libs/1_73_0/more/getting_started/windows.html
(see chapter build binaries)
3. Create the b2.exe (as described)
4. tools\build\b2 install --toolset=gcc (from root directory)
