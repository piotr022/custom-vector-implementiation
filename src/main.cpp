#include <iostream>
#include <gtest/gtest.h>
#include "vec_training.hpp"
#include "vec_training.cpp" //dont know what is wrong in cmakelists.txt

#define VEC_TEST_SIZE 200000

TEST(Vec_main, operator_assignment)
{
  Vector<int> vec1(VEC_TEST_SIZE);
  Vector<int> vec2_c1(4);

  for (int i = 0; i < vec1.size(); i++)
  {
    vec1.at(i) = i; //filing with values
  }

  vec2_c1 = vec1; // copy assigment

  for (int i : vec1)
  {
    EXPECT_EQ(vec1[i], vec2_c1[i]);
    
  }
}

TEST(Vec_main, constructor_copy)
{
  Vector<int> vec1(VEC_TEST_SIZE);

  for (int i = 0; i < vec1.size(); i++)
  {
    vec1.at(i) = i; //filing with values
  }

  Vector<int> vec2_c1(&vec1); // copy assigment

  for (int i : vec1)
  {
    EXPECT_EQ(vec1[i], vec2_c1[i]);
  }
}

TEST(Vec_main, dyn_push_back_and_operatorEqual)
{
  Vector<int> vec1;

  for (int i = 0; i < VEC_TEST_SIZE; i++)
  {
   vec1.push_back(i); //filing with values
  }

  Vector<int> vec2_c1;
  vec2_c1 = vec1; // additionaly copy vec1 to vec2

  for(int i : vec2_c1)
  {
    EXPECT_EQ(vec1[i], vec2_c1[i]);
    EXPECT_EQ(vec2_c1[i] , i);
  }
}

TEST(Vec_main, pop_back_and_empty)
{
    Vector<int> vec1;

  for (int i = 0; i < VEC_TEST_SIZE; i++)
  {
   vec1.push_back(i); //filing with values
  }

  Vector<int> vec2;
  size_t temp_size = vec1.size();
  int cycles = 0;
  while(!vec1.empty())
  {
    vec2.push_back(vec1.back());
    vec1.pop_back();
    cycles++;
  }
//checking if num of cycles is equal to first size
  EXPECT_EQ(cycles, temp_size);
  //checking if vec2 size == tempsize
  EXPECT_EQ(vec2.size(), temp_size);

  for(int i : vec2)
  {
    //checkig if vec2 elements are in reverse order
    EXPECT_EQ(vec2[i], (vec2.size()-1)-i);
  }

}
TEST(Vec_Iterator, Iterator_read_test)
{
  Vector<int> vec1(VEC_TEST_SIZE);
  for (int i = 0; i < vec1.size(); i++)
  {
    vec1.at(i) = i; //filing with values
  }
 

  Vector<int>::iterator it_test;
  it_test = vec1;
  for (int i : vec1)
  {
    EXPECT_EQ(vec1[i], *(++it_test -1));
  }
  // EXPECT_EQ(vec1[i], i);
}

int main(int argc, char **argv)
{
  //init test vars
  ::testing::InitGoogleTest(&argc, argv);

  Vector<int> vec1(11);

  for (int i = 0; i < vec1.size(); i++)
  {
    vec1.at(i) = i;
  //  vec1.push_back(i);
  }
  Vector<int> vec2_c1(4);
  vec2_c1 = vec1; //(&vec1);
  for (int i = 0; i < vec2_c1.size(); i++)
  {
    std::cout << "vec1= " << vec1[i];
    std::cout << "   "
              << "vec2= " << vec2_c1[i] << std::endl;
  }

  std::cout << "\ntesting range-based for loop\n";
  Vector<int>::iterator it;
  it = vec1;
  for (int i : vec1)
  {
    std::cout << i << ". vec1= " << vec1[i] << "  -  ";
    std::cout << *(++it - 1) << std::endl;
    //++it;
  }

  // int *test_ptr = (int*)malloc(8);

  // size_t vec_size = vec1.size();

  return RUN_ALL_TESTS();
}