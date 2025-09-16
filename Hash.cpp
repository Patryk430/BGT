#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>

std::string Random_String (int length)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(65, 122); // A-65, z-122

    std::string string = "";

    for (int i = 0; i<length; i++)
    {
        char c = distr(gen);
        string+=c;
    }

    return string;
}

std::string Similar_String (std::string string)
{   
    char old_c = string.back();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(65, 122); // A-65, z-122

    char new_c = distr(gen);

    while (new_c == old_c)  {char new_c = distr(gen);}

    string.pop_back();
    string.push_back(new_c);

    return string;
}

std::string Hash (std::string input)
{
    int output [64];
    std::fill_n(output, 64, 15);
    
    int sum = 0;

    for (char character : input)
    {
        std::mt19937 chargen(character);
        sum+=chargen();
    };

    std::mt19937 gen(sum);
    std::uniform_int_distribution<> distr(0, 15);

    std::stringstream stream;
    for (int num : output)
    {   
        stream << std::hex << num-distr(gen);
    };
    
    return stream.str();
}

int String_Similarity (std::string str1, std::string str2)
{
    int count = 0;

    if (str1.size() != str2.size()) std::cout<<"oops!\n";
    else
    {
        for (int i=0; i<str1.size(); i++)
        {
            if (str1[i]==str2[i]) count++;
        }
    }

    return count;
}

void Test_2_strings (int test_count,int string_length)
{
    int max_hash_similarity = 0;
    int min_hash_similarity = 64;

    for (int i=0; i<test_count; i++)
    {
        std::string string_1 = Random_String(string_length);
        std::string string_2 = Random_String(string_length);

        std::cout << string_1 << " " << string_2 << " Panašumas: " << String_Similarity(string_1, string_2) << "/" << string_length << std::endl;
        
        std::string hash_1 = Hash(string_1);
        std::string hash_2 = Hash(string_2);

        int similarity = String_Similarity(hash_1, hash_2);

        std::cout << hash_1 << " " << hash_2 << " Panašumas: " << similarity << "/64\n";

        if (max_hash_similarity < similarity) max_hash_similarity = similarity;
        if (min_hash_similarity > similarity) min_hash_similarity = similarity;
    }

    std::cout << "Didžiausias Hash'ų panašumas: " << max_hash_similarity << "/64\n" << "Mažiausias Hash'ų panašumas: " << min_hash_similarity << "/64\n";   
}

main()
{  
    Test_2_strings(40, 20);

    return 0;
}



