// test009.cpp - generate new document by row

#include <rapidcsv.h>
#include "unittest.h"

int main()
{
  int rv = 0;

  std::string csvref =
    ",A,B,C,D\n"
    "0,2,4,16,256\n"
    "1,3,9,81,6561\n"
    "2,4,16,256,65536\n"
    "3,5,25,625,390625\n"
    ;

  std::string path = unittest::TempPath();

  try
  {
    rapidcsv::Document doc(rapidcsv::Properties("", 0, 0, false));

    doc.SetRow<int>(0, std::vector<int>({2, 4}));
    doc.SetRow<int>(1, std::vector<int>({3, 9, 81, 6561}));
    doc.SetRow<int>(2, std::vector<int>({4, 16, 256, 65536}));
    doc.SetRow<int>(3, std::vector<int>({5, 25, 625, 390625}));

    doc.SetCell<int>(2, 0, 16);
    doc.SetCell<int>(3, 0, 256);

    doc.SetColumnLabel(0, "A");
    doc.SetColumnLabel(1, "B");
    doc.SetColumnLabel(2, "C");
    doc.SetColumnLabel(3, "D");

    doc.SetRowLabel(0, "0");
    doc.SetRowLabel(1, "1");
    doc.SetRowLabel(2, "2");
    doc.SetRowLabel(3, "3");

    doc.Save(path);

    std::string csvread = unittest::ReadFile(path);

    unittest::ExpectEqual(std::string, csvref, csvread);
  }
  catch(const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    rv = 1;
  }

  unittest::DeleteFile(path);

  return rv;
}

