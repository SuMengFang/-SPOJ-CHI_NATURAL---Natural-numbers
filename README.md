# SPOJ Solutions in C++
Record solutions of problems on SPOJ in C++.

1. [Natural-numbers](codes/CHI_NATURAL.cpp)
   - Tips: 
     - Before print the result strings, make sure there isn't any '0' head of them. (That made me get "WA" many times.)
     - Try your best to avoid to call "memset" in loop. That will cost a lot of time to execute, and maybe make you get "TLE".

2. [A problem of Backtracking](codes/BTCK.cpp)
   - Tips:
     - If you use pointer to operate the permutation array in recursive function, remember to recover your changes when you leave unless you get the answwer.

3. [Maths is Magic](codes/NJEG1.cpp)
   - Tips:
     - The given 26 cards is put in plate1, and the order is "UPSIDE DOWN"!!
     - Index plus chosen cards will always be 30.
     - Don't forget Card A,Card B and Card C.

4. [Ada and Behives](codes/ADABEHIVE.cpp)
   - Note:
     - I used 2D Binary Indexed Tree, and it only got AC by CPP14 compiler.
     - Here is a very detailed introduction of [BIT on Topcoder](https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees).
