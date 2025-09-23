#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <chrono>

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

std::string Random_String ()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(65, 122); // A-65, z-122
    std::uniform_int_distribution<> l_distr(500, 1500); // A-65, z-122

    std::string string = "";
    int length = l_distr(gen);

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

    while (new_c == old_c)  {new_c = distr(gen);}

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

int Bit_Similarity(std::string hex1, std::string hex2) 
{
    int bit_similarity = 0;

    for (int i = 0; i < 64; i++) 
    {
        unsigned int val1 = std::stoi(std::string(1, hex1[i]), nullptr, 16);
        unsigned int val2 = std::stoi(std::string(1, hex2[i]), nullptr, 16);

        unsigned int diff = val1 ^ val2;

        bit_similarity += 4 - __builtin_popcount(diff);
    }

    return bit_similarity;
}

void Test_2_strings (int test_count,int string_length)
{
    int max_hash_similarity = 0;
    int min_hash_similarity = 64;
    int sum_hash_similarity = 0;

    std::ofstream O ("Same_Length_String_Test_Results.txt");

    for (int i=0; i<test_count; i++)
    {
        std::string string_1 = Random_String(string_length);
        std::string string_2 = Random_String(string_length);

        O << string_1 << " " << string_2 << " Panašumas: " << String_Similarity(string_1, string_2) << "/" << string_length << std::endl;
        
        std::string hash_1 = Hash(string_1);
        std::string hash_2 = Hash(string_2);

        int similarity = String_Similarity(hash_1, hash_2);

        O << hash_1 << " " << hash_2 << " Panašumas: " << similarity << "/64\n";

        sum_hash_similarity += similarity;

        if (max_hash_similarity < similarity) max_hash_similarity = similarity;
        if (min_hash_similarity > similarity) min_hash_similarity = similarity;
    }

    O << "\nDidžiausias Hash'ų panašumas: " << max_hash_similarity << "/64\n" << "Mažiausias Hash'ų panašumas: " << min_hash_similarity << "/64\n" << "Vidutinis Hash'ų panašumas: " << (double)sum_hash_similarity/test_count;

    O.close();   
}

void Test_2_different_strings (int test_count)
{
    int max_hash_similarity = 0;
    int min_hash_similarity = 64;
    int sum_hash_similarity = 0;

    std::ofstream O ("Different_String_Test_Results.txt");

    for (int i=0; i<test_count; i++)
    {
        std::string string_1 = Random_String();
        std::string string_2 = Random_String();

        O << string_1 << " " << string_2 << std::endl;
        
        std::string hash_1 = Hash(string_1);
        std::string hash_2 = Hash(string_2);

        int similarity = String_Similarity(hash_1, hash_2);

        O << hash_1 << " " << hash_2 << " Panašumas: " << similarity << "/64\n";

        sum_hash_similarity += similarity;

        if (max_hash_similarity < similarity) max_hash_similarity = similarity;
        if (min_hash_similarity > similarity) min_hash_similarity = similarity;
    }

    O << "\nDidžiausias Hash'ų panašumas: " << max_hash_similarity << "/64\n" << "Mažiausias Hash'ų panašumas: " << min_hash_similarity << "/64\n" << "Vidutinis Hash'ų panašumas: " << (double)sum_hash_similarity/test_count;

    O.close();
}

void Test_2_simillar_strings (int test_count,int string_length)
{
    int max_hash_similarity = 0;
    int min_hash_similarity = 64;
    int sum_hash_similarity = 0;

    int min_bit_similarity = 256;
    int max_bit_similarity = 0;
    int sum_bit_similarity = 0;

    std::ofstream O ("Simillar_String_Test_Results.txt");

    for (int i=0; i<test_count; i++)
    {
        std::string string_1 = Random_String(string_length);
        std::string string_2 = Similar_String(string_1);

        O << string_1 << " " << string_2 /*<< " Panašumas: " << String_Similarity(string_1, string_2) << "/" << string_length*/ << std::endl;
        
        std::string hash_1 = Hash(string_1);
        std::string hash_2 = Hash(string_2);

        int similarity = String_Similarity(hash_1, hash_2);
        int bit_similarity = Bit_Similarity(hash_1, hash_2);

        O << hash_1 << " " << hash_2 << " Panašumas: " << similarity << "/64 Bitais: " << bit_similarity << "/256 \n";

        sum_hash_similarity += similarity;
        sum_bit_similarity += bit_similarity;

        if (max_hash_similarity < similarity) max_hash_similarity = similarity;
        if (min_hash_similarity > similarity) min_hash_similarity = similarity;

        if (max_bit_similarity < bit_similarity) max_bit_similarity = bit_similarity;
        if (min_bit_similarity > bit_similarity) min_bit_similarity = bit_similarity;
    }

    O << "\nDidžiausias Hash'ų panašumas: " << max_hash_similarity << "/64\n" << "Mažiausias Hash'ų panašumas: " << min_hash_similarity << "/64\n" << "Vidutinis Hash'ų panašumas: " << (double)sum_hash_similarity/test_count;

    O << "\nDidžiausias Bit'ų panašumas: " << max_bit_similarity << "/256\n" << "Mažiausias Bit'ų panašumas: " << min_bit_similarity << "/256\n" << "Vidutinis Hash'ų panašumas: " << (double)sum_bit_similarity/test_count;

    O.close();
}

void Test_salt ()
{
    std::string input = "password123";
    std::string salt  = Random_String (10);

    std::cout << "Input: " << input << " Salt: " << salt << "\n Hash be salt: " << Hash (input) << "\n Hash su salt: " << Hash (input+salt);
}

void Test_deter (int test_count)
{
    std::ofstream O ("Determenistic_Test_Log.txt");

    int error_count = 0;

    for (int i = 0; i < test_count; i++)
    {
        std::string string_1 = Random_String ();

        std::string hash_1 = Hash (string_1);
        std::string hash_2 = Hash (string_1);

        O << string_1 << " : \nhash 1:" << hash_1 << " \nhash 2:" << hash_2 << "\n";

        if (hash_1 != hash_2) { error_count++; std::cout << "Nesutampa at " << i << std::endl;}

    }

    O << "Nesutapimu skaičius: " << error_count;
    O.close();

}

void Test_file ()
{
    std::string input = "";
	std::string line  = "";

	std::ifstream I ("konstitucija.txt");
    
    int count = 0;
    while(getline(I, line))
    {
        input += line + "\n";
        count++;

        if ((count & (count - 1)) == 0)
        {   std::chrono::duration<double> duration_sum;

            for (int j = 0; j < 3; j++)
            {
                auto start = std::chrono::high_resolution_clock::now();

                std::string hash = Hash (input);

                auto end = std::chrono::high_resolution_clock::now();

                std::chrono::duration<double> duration = end - start;
  	            duration_sum += duration;
            }
            std::cout << count << " linijos vidutiniškai užhash'uotos per " << duration_sum.count()/3 << "\n";
        }
    }

    I.close();
}

int main()
{  
    int choice = 0;
    
    std::cout << "SVEIKI\n" 
    << "--------------------------------------------------------------------------------------------------\n" 
    << "1 - Patikrinti 10 000 to pačio ilgio skirtingų string'ų porų\n"
    << "2 - Patikrinti 10 000 to pačio ilgio panašių (1 simbolio skirtumas) string'ų porų\n"
    << "3 - Patikrinti 10 000 skirtingo ilgio string'ų porų\n"
    << "4 - Testas su failų 'konstitucija.txt'\n"
    << "5 - Patikrinti deterministiškumą\n"
    << "6 - Salting testas\n";

    std::cin >> choice;

    switch (choice)
    {
    case 1:
        Test_2_strings (10000, 500);
        break;
    
    case 2:
        Test_2_simillar_strings (100000, 500);
        break;

    case 3:
        Test_2_different_strings (10000);
        break;

    case 4:
        Test_file();
        break;

    case 5:
        Test_deter(10000);
        break;

    case 6:
        Test_salt();
        break;

    default:
        break;
    }
    return 0;
}






