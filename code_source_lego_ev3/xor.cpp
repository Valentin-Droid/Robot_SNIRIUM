#include <iostream>

using namespace std;

string Xor(string trame)
{
    string encoder;
    char key[9] = {2,9,8,7,1,4,6,5,3};
    for (int i = 0 ; i < trame.size(); i++)
    {
       encoder += trame[i] ^ (int(key[i%9])+ i) % 20;
    }

    return encoder;
}

int main() 
{
   string trame;

   trame = "20;0;6.757;39.2;0,0";

   cout << trame << endl;

   cout << Xor(trame) << endl;
   

   /*for (int i = 0; i < encoder.size(); i++)
   {
       decoder += encoder[i] ^(int(key[i%9]) +i) % 20;
   }

   cout << decoder << endl;*/

   return 0;
}