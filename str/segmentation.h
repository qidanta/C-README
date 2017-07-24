//
// Created by eric on 17-7-5.
//
#include <string>
#include <vector>
using namespace std;

#ifndef README_SEGMENTATION_H
#define README_SEGMENTATION_H

/**
 * same funcs as str.split in `python`, split string s by string c, and the
 * ...result is stored in vector<string> v
 *
 * @Params:
 * - s: string type, split the s
 * - v: vector type, the result of s after split was stored here
 * - c: split s by c
 *
 * @Returns:
 * return the split result
 */
void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

#endif //README_SEGMENTATION_H


