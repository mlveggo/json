// Json.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\Json.h"

int main()
{
    json::Writer w;
    w.BeginObject("pp");
    w.BeginArray("cars");
    w.AddArrayValue("Volvo");
    w.AddArrayValue("Opel");
    w.AddArrayValue("Mazda");
    w.AddArrayValue("Kia");
    w.EndArray();
    w.BeginArray("boats");
    w.AddArrayValue("BoatA");
    w.AddArrayValue("BoatB");
    w.AddArrayValue("BoatC");
    w.EndArray();
    w.EndObject();
    auto json1 = w.GetJson();
    w.BeginObject("pp2");
    w.BeginArray("cars");
    w.AddArrayValue("Volvo");
    w.AddArrayValue("Opel");
    w.AddArrayValue("Mazda");
    w.AddArrayValue("Kia");
    w.EndArray();
    w.BeginArray("boats");
    w.AddArrayValue("BoatA");
    w.AddArrayValue("BoatB");
    w.AddArrayValue("BoatC");
    w.EndArray();
    w.EndObject();
    auto json2 = w.GetJson();


    std::cout << json1 << std::endl;
    std::cout << json2 << std::endl;
}