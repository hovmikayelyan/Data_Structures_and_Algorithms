/**
 * @file hash_substring.cpp
 * @author Hovhannes Mikayelyan (hovmikayelyan@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-17
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief
 * To track time limit
 */
auto start = chrono::steady_clock::now();
bool returnStatement(bool var)
{
    cout << "\n";
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Used Time - 0," << chrono::duration<double, milli>(diff).count() << " s" << endl;

    return var;
}

/**
 * @brief
 * Main Program
 */

#define d 256

void rabinKarp(string pattern, string text, int inputBase)
{
    int patternLen = pattern.size();
    int textLen = text.size();
    int i, j;
    int patternHash = 0;
    int textHash = 0;
    int patternLenOut = 1;

    for (i = 0; i < patternLen - 1; i++)
        patternLenOut = (patternLenOut * d) % inputBase;

    for (i = 0; i < patternLen; i++)
    {
        patternHash = (d * patternHash + pattern[i]) % inputBase;
        textHash = (d * textHash + text[i]) % inputBase;
    }

    for (i = 0; i <= textLen - patternLen; i++)
    {
        if (patternHash == textHash)
        {
            for (j = 0; j < patternLen; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    break;
                }
            }

            if (j == patternLen)
                cout << i << " ";
        }

        if (i < textLen - patternLen)
        {
            textHash = (d * (textHash - text[i] * patternLenOut) + text[i + patternLen]) % inputBase;

            if (textHash < 0)
                textHash = (textHash + inputBase);
        }
    }
}

int main()
{

    string pattern, text;
    cin >> pattern >> text;
    int q = 101;
    rabinKarp(pattern, text, q);

    return 0;
}