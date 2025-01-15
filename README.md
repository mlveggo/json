# Json Writer for C++

### Just add json.h and then compose your Json file using a very crude but simple api.

```
#include <json.h>

int main()
{
    json::Writer w;
    w.BeginObject("vehicles");
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
}
```
