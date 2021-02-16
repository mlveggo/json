#pragma once

#include <string>

namespace json
{

class Writer
{
public:
    Writer(int decimals = 4)
    {
        mDecimals = std::max(decimals, 0);
        mDecimals = std::min(mDecimals, 11);
    }

    void BeginObject()
    {
        mData += "{";
    }
    void BeginObject(const std::string& key)
    {
        mData += "\"" + key + "\"" + ":{";
    }
    void EndObject()
    {
        if (mData.size() > 0 && mData[mData.size() - 1] == ',')
            mData.erase(mData.begin() + mData.size() - 1);
        mData += "},";
    }
    void AddValue(const std::string& key, double value)
    {
        char s[40];
        sprintf_s(s, "%.*f", mDecimals, value);
        mData += "\"" + key + "\":" + s + ",";
    }
    void AddValue(const std::string& key, float value)
    {
        char s[40];
        sprintf_s(s, "%.*f", mDecimals, value);
        mData += "\"" + key + "\":" + s + ",";
    }
    void AddValue(const std::string& key, uint32_t value)
    {
        mData += "\"" + key + "\":" + std::to_string(value) + ",";
    }
    void AddValue(const std::string& key, int32_t value)
    {
        mData += "\"" + key + "\":" + std::to_string(value) + ",";
    }
    void AddValue(const std::string& key, const std::string& value)
    {
        mData += "\"" + key + "\":";
        mData += "\"" + value + "\"" + ",";
    }

    void BeginArray()
    {
        mData += "[";
    }
    void BeginArray(const std::string& key)
    {
        mData += "\"" + key + "\"" + ":[";
    }
    void EndArray()
    {
        if (mData.size() > 0 && mData[mData.size() - 1] == ',')
            mData.pop_back();
        mData += "],";
    }
    void AddArrayValue(double value)
    {
        char s[40];
        sprintf_s(s, "%.*f", mDecimals, value);
        mData += std::string(s) + ",";
    }
    void AddArrayValue(float value)
    {
        char s[40];
        sprintf_s(s, "%.*f", mDecimals, value);
        mData += std::string(s) + ",";
    }
    void AddArrayValue(uint32_t value)
    {
        mData += std::to_string(value) + ",";
    }
    void AddArrayValue(int32_t value)
    {
        mData += std::to_string(value) + ",";
    }
    void AddArrayValue(const std::string& value)
    {
        mData += "\"" + value + "\"" + ",";
    }

    std::string GetJson() const
    {
        auto data = mData;
        if (data.size() > 0 && data[data.size() - 1] == ',')
            data.pop_back();
        return "{" + data + "}";
    }

    bool ToFile(const std::string& filename) const
    {
        FILE* f;
        auto err = fopen_s(&f, filename.c_str(), "w+");
        if (f == nullptr)
            return false;
        fputs(GetJson().c_str(), f);
        fclose(f);
        return true;
    }

private:

    int mDecimals;
    std::string mData;
};


}


