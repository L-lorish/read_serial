#include "uwb_read/lib.hpp"

#include <sstream>
#include <stdexcept>

bool extractDoubleField(const std::string& s, const std::string& key, double& out)
{
    /*
      这个函数的作用是对于字符串s，给定键值key，找到其后对应的值，并转换成double形式。
      eg. {"code":70,"tag_id":"deca030210e3cfad","anc_id":"deca031204d35021","a":82.8,"d":46.9,"vbat":90.0,"IO":0}
      找到"a":和"d":后面的字符串形式的值，然后提取出来进一步转换成double形式
     */
    const std::string pattern = "\"" + key + "\":";
    size_t pos = s.find(pattern);
    if (pos == std::string::npos) return false;

    pos += pattern.size();

    size_t end = s.find(",",pos);
    if (end == std::string::npos)
    {
        return false;
    }

    const std::string num_str = s.substr(pos, end - pos);

    try
    {
        out = std::stod(num_str);
    }
    catch(const std::exception&)
    {
        return false;
    }
    
    return true;
}