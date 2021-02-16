#include "pch.h"
#include "..\Json.h"
#include <iostream>

TEST(JsonWriter, BeginObject) {

    json::Writer w;
    w.BeginObject("pp");
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{}", json);
}

TEST(JsonWriter, EndObject) {

    json::Writer w;
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{}}", json);
}

TEST(JsonWriter, BeginEndObject) {

    json::Writer w;
    w.BeginObject("pp");
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{}}", json);
}

TEST(JsonWriter, BeginArray) {

    json::Writer w;
    w.BeginArray("pp");
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":[}", json);
}

TEST(JsonWriter, Object) {

    json::Writer w;
    w.BeginObject("pp");
    w.AddValue("name", "John");
    w.AddValue("age", 39);
    w.AddValue("income", 104123.35772);
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"name\":\"John\",\"age\":39,\"income\":104123.3577}}", json);
}


TEST(JsonWriter, ObjectAndArray) {

    json::Writer w;
    w.BeginObject("pp");
    w.AddValue("name", "John");
    w.AddValue("age", 39);
    w.AddValue("income", 104123.35772);
    w.BeginArray("cars");
    w.AddArrayValue("Volvo");
    w.AddArrayValue("Opel");
    w.AddArrayValue("Mazda");
    w.AddArrayValue("Kia");
    w.EndArray();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"name\":\"John\",\"age\":39,\"income\":104123.3577,\"cars\":[\"Volvo\",\"Opel\",\"Mazda\",\"Kia\"]}}", json);
}


TEST(JsonWriter, ObjectInObject) {

    json::Writer w;
    w.BeginObject("pp");
    w.AddValue("name", "John");
    w.AddValue("age", 39);
    w.AddValue("income", 104123.35772);
    w.BeginObject("cars");
    w.AddValue("car1", "Lambo");
    w.AddValue("car2", "Ford");
    w.AddValue("car3", "Saab");
    w.EndObject();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"name\":\"John\",\"age\":39,\"income\":104123.3577,\"cars\":{\"car1\":\"Lambo\",\"car2\":\"Ford\",\"car3\":\"Saab\"}}}", json);
}


TEST(JsonWriter, MultipleArray) {

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
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"cars\":[\"Volvo\",\"Opel\",\"Mazda\",\"Kia\"],\"boats\":[\"BoatA\",\"BoatB\",\"BoatC\"]}}", json);
}


TEST(JsonWriter, MultipleObject) {

    json::Writer w;
    w.BeginObject("pp");
    w.BeginObject("abc");
    w.AddValue("car1", "Lambo");
    w.AddValue("car2", "Ford");
    w.AddValue("car3", "Saab");
    w.EndObject();
    w.BeginObject("def");
    w.AddValue("car1", "Lambo");
    w.AddValue("car2", "Ford");
    w.AddValue("car3", "Saab");
    w.EndObject();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"abc\":{\"car1\":\"Lambo\",\"car2\":\"Ford\",\"car3\":\"Saab\"},\"def\":{\"car1\":\"Lambo\",\"car2\":\"Ford\",\"car3\":\"Saab\"}}}", json);
}


TEST(JsonWriter, MultipleArrayRepeated) {

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

    EXPECT_EQ("{\"pp\":{\"cars\":[\"Volvo\",\"Opel\",\"Mazda\",\"Kia\"],\"boats\":[\"BoatA\",\"BoatB\",\"BoatC\"]}}", json1);
    EXPECT_EQ("{\"pp\":{\"cars\":[\"Volvo\",\"Opel\",\"Mazda\",\"Kia\"],\"boats\":[\"BoatA\",\"BoatB\",\"BoatC\"]},\"pp2\":{\"cars\":[\"Volvo\",\"Opel\",\"Mazda\",\"Kia\"],\"boats\":[\"BoatA\",\"BoatB\",\"BoatC\"]}}", json2);
}


TEST(JsonWriter, TwoDecimals) {

    json::Writer w(2);
    w.BeginObject("pp");
    w.BeginObject("abc");
    w.AddValue("car1", 10.0001234);
    w.AddValue("car2", 10.0001234);
    w.AddValue("car3", 10.1234);
    w.EndObject();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"abc\":{\"car1\":10.00,\"car2\":10.00,\"car3\":10.12}}}", json);
}


TEST(JsonWriter, ZeroDecimals) {

    json::Writer w(0);
    w.BeginObject("pp");
    w.BeginObject("abc");
    w.AddValue("car1", 11.0001234);
    w.AddValue("car2", 12.0001234);
    w.AddValue("car3", 13.1234);
    w.EndObject();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"abc\":{\"car1\":11,\"car2\":12,\"car3\":13}}}", json);
}


TEST(JsonWriter, TenDecimals) {

    json::Writer w(10);
    w.BeginObject("pp");
    w.BeginObject("abc");
    w.AddValue("car1", 11.01234567778423);
    w.AddValue("car2", 123456789.123456789123456789);
    w.AddValue("car3", -1111.2222);
    w.EndObject();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"abc\":{\"car1\":11.0123456778,\"car2\":123456789.1234567910,\"car3\":-1111.2222000000}}}", json);
}


TEST(JsonWriter, TwentyDecimals) {

    json::Writer w(20);
    w.BeginObject("pp");
    w.BeginObject("abc");
    w.AddValue("car1", 11.01234567778423);
    w.AddValue("car2", 123456789.123456789123456789);
    w.AddValue("car3", -1111.2222);
    w.EndObject();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"abc\":{\"car1\":11.01234567778,\"car2\":123456789.12345679104,\"car3\":-1111.22220000000}}}", json);
}

TEST(JsonWriter, NegativeDecimals) {

    json::Writer w(-10);
    w.BeginObject("pp");
    w.BeginObject("abc");
    w.AddValue("car1", 11.01234567778423);
    w.AddValue("car2", 123456789.123456789123456789);
    w.AddValue("car3", -1111.2222);
    w.EndObject();
    w.EndObject();
    auto json = w.GetJson();

    EXPECT_EQ("{\"pp\":{\"abc\":{\"car1\":11,\"car2\":123456789,\"car3\":-1111}}}", json);
}

TEST(JsonWriter, EmptyArrayAndObjectNames) {

    json::Writer w;
    w.BeginArray();
    w.BeginObject();
    w.AddValue("symbol", "AAPL");
    w.AddValue("price", 207.1);
    w.EndObject();
    w.BeginObject();
    w.AddValue("symbol", "FB");
    w.AddValue("price", 183.12);
    w.EndObject();
    w.EndArray();
    auto json = w.GetJson();

    EXPECT_EQ("{[{\"symbol\":\"AAPL\",\"price\":207.1000},{\"symbol\":\"FB\",\"price\":183.1200}]}", json);
}