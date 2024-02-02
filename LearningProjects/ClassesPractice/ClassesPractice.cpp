
#include <iostream>
#include "Rectangle.h"
#include "Date.h"

int main()
{
    /*Rectangle rect;
    rect.SetHeight(5);
    rect.SetWidth(4.5f);
    std::cout << rect.GetArea();*/

    Date firstDate(2, 2, 2024);
    firstDate.PrintDate();
    firstDate.SetDate(35, 4, 2003);
    firstDate.PrintDate();
}

