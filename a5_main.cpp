int main()
{
   // problem 1:
   test_is_palindrome();
   cout << "\n";

   // problem 2:
   std::vector<int> v1{ 1 }; // one element
   test_second_max(v1);

   std::vector<int> v2{ 1, 1 }; // all elements equal
   test_second_max(v2);

   std::vector<int> v3{ 1, 1, 3, 3, 7, 7}; // at least with two distict elements
   test_second_max(v3);
   cout << "\n";

   // problem 3:
   std::vector<std::string> vecstr
   { "count_if", "Returns", "the", "number", "of", "elements", "in", "the", 
      "range", "[first", "last)", "for", "which", "pred", "is", "true."
   };
   cout << countStringLambda(vecstr, 5) << endl;
   cout << countStringFreeFun(vecstr, 5) << endl;
   cout << countStringFunctor(vecstr, 5) << endl;
   cout << "\n";

   // problem 4:
   charFrequency();
   cout << "\n";

   // problem 5:
   multisetUsingDefaultComparator();
   cout << "\n";

    return 0;
}
