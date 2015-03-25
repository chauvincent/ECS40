Authors: Vincent Chau and Kevin Chan
Homework 2: changing mscp.c to mscp.cpp
---------------------------------------
• Changed C libraries to C++ libraries. (line 27-37)

• We referred to an online website for C++ functions and their parameters. (www.cplusplus.com/reference)

• We added "inline" to some #defines that we made into functions. In an attempt to hint the compiler to run faster. 

• We changed more #defines that are constant values to const int values

• friend is a reserved word in C++, so we changed it to friendly

• We referred to the Piazza post about the static union of struts(post by Jagdeep Singh/Zachary Karkazis/Josuhua Basch)
  and changed our struct tt and struct bk to transpositionTable, bookEntry, and had a separate static union declaration 
  to combined the transpositionTable and bookEntry. In addition, we refered to our TA: Vehbi Esref Bayraktar's post on piazza with 
  examples of struct unions inside his main.cpp

•We changed all printf's/and puts to couts

•We got rid of some errors through type casting. We refered to a post by Christopher Fong on Piazza
