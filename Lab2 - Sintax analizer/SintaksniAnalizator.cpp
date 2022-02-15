#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool Program();
bool ListaNaredbi();
bool Naredba();
bool NaredbaPridruzivanja();
bool ZaPetlja();
bool E();
bool ELista();
bool T();
bool TLista();
bool P();

int uvlacenje = 0;
int indeks = 0;

string line = "";
vector<string> tokeni;
vector<string> linije;

string ispis = "";

void obradiGresku()
{
   if (linije.at(indeks) == "$" || linije.at(indeks) == " ")
   {
      cout << "err kraj" << endl;
      exit(0);
   }
   else
   {
      cout << linije.at(indeks) << endl;
      exit(0);
   }
}

void splitByChar(string s, char c, vector<string> &vec)
{
   int i = 0;
   int j;
   j = s.find(c, i);
   int l = s.length();
   while (j != -1)
   {
      vec.push_back(s.substr(i, j - i));
      i = ++j;
      j = s.find(c, i);
   }
   if (i != l)
   {
      vec.push_back(s.substr(i));
   }
   return;
}
void NapraviRazmak()
{
   for (int i = 0; i < uvlacenje; i++)
      ispis += " ";
}

bool Program()
{
   ispis += "<program>\n";

   if (tokeni.at(indeks) == "IDN" || tokeni.at(indeks) == "KR_ZA" || tokeni.at(indeks) == "$")
   { //kraj niza mozda
      uvlacenje++;
      ListaNaredbi();
      uvlacenje--;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool ListaNaredbi()
{
   NapraviRazmak();
   ispis += "<lista_naredbi>\n";
   if (tokeni.at(indeks) == "IDN" || tokeni.at(indeks) == "KR_ZA")
   {
      uvlacenje++;
      Naredba();
      ListaNaredbi();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "KR_AZ" || tokeni.at(indeks) == "$")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += "$\n";
      uvlacenje--;
      return true;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool Naredba()
{
   NapraviRazmak();
   ispis += "<naredba>\n";
   if (tokeni.at(indeks) == "IDN")
   {
      uvlacenje++;
      NaredbaPridruzivanja();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "KR_ZA")
   {
      uvlacenje++;
      ZaPetlja();
      uvlacenje--;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool NaredbaPridruzivanja()
{
   NapraviRazmak();
   ispis += "<naredba_pridruzivanja>\n";
   if (tokeni.at(indeks) == "IDN")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks += 1;

      if (tokeni.at(indeks) == "OP_PRIDRUZI")
      {
         NapraviRazmak();
         ispis += (linije.at(indeks) + "\n");
         indeks++;
         E();
         uvlacenje--;
      }
      else
      {
         obradiGresku();
      }
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool ZaPetlja()
{
   NapraviRazmak();
   ispis += "<za_petlja>\n";
   if (tokeni.at(indeks) == "KR_ZA")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks += 1;

      if (tokeni.at(indeks) == "IDN")
      {
         NapraviRazmak();
         ispis += (linije.at(indeks) + "\n");
         indeks += 1;

         if (tokeni.at(indeks) == "KR_OD")
         {
            NapraviRazmak();
            ispis += (linije.at(indeks) + "\n");
            indeks += 1;
            if (E())
            {
               if (tokeni.at(indeks) == "KR_DO")
               {
                  NapraviRazmak();
                  ispis += (linije.at(indeks) + "\n");
                  indeks++;

                  if (E() && ListaNaredbi())
                  {
                     if (tokeni.at(indeks) == "KR_AZ")
                     {
                        NapraviRazmak();
                        ispis += (linije.at(indeks) + "\n");
                        indeks++;
                        uvlacenje--;
                        return true;
                     }
                     else
                     {
                        obradiGresku();
                     }
                  }
                  else
                  {
                     obradiGresku();
                  }
               }
               else
               {
                  obradiGresku();
               }
            }
            else
            {
               obradiGresku();
            }
         }
         else
         {
            obradiGresku();
         }
      }
      else
      {
         obradiGresku();
      }
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool E()
{
   NapraviRazmak();
   ispis += "<E>\n";
   if (tokeni.at(indeks) == "IDN" || tokeni.at(indeks) == "BROJ" || tokeni.at(indeks) == "OP_PLUS" || tokeni.at(indeks) == "OP_MINUS" || tokeni.at(indeks) == "L_ZAGRADA")
   {
      uvlacenje++;
      T();
      uvlacenje--;
      uvlacenje++;
      ELista();
      uvlacenje--;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool ELista()
{
   NapraviRazmak();
   ispis += "<E_lista>\n";

   if (tokeni.at(indeks) == "OP_PLUS")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      E();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "OP_MINUS")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      E();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "IDN" || tokeni.at(indeks) == "KR_ZA" || tokeni.at(indeks) == "KR_DO" || tokeni.at(indeks) == "KR_AZ" || tokeni.at(indeks) == "D_ZAGRADA" || tokeni.at(indeks) == "$")
   { //kraj?
      uvlacenje++;
      NapraviRazmak();
      ispis += "$\n";
      uvlacenje--;
      return true;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool T()
{
   NapraviRazmak();
   ispis += "<T>\n";

   if (tokeni.at(indeks) == "IDN" || tokeni.at(indeks) == "BROJ" || tokeni.at(indeks) == "OP_PLUS" || tokeni.at(indeks) == "OP_MINUS" || tokeni.at(indeks) == "L_ZAGRADA")
   {
      uvlacenje++;
      P();
      TLista();
      uvlacenje--;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool TLista()
{
   NapraviRazmak();
   ispis += "<T_lista>\n";

   if (tokeni.at(indeks) == "OP_PUTA")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      T();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "OP_DIJELI")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      T();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "IDN" || tokeni.at(indeks) == "KR_ZA" || tokeni.at(indeks) == "KR_DO" || tokeni.at(indeks) == "KR_AZ" || tokeni.at(indeks) == "OP_PLUS" || tokeni.at(indeks) == "OP_MINUS" || tokeni.at(indeks) == "D_ZAGRADA" || tokeni.at(indeks) == "$")
   { //kraj?
      uvlacenje++;
      NapraviRazmak();
      ispis += "$\n";
      uvlacenje--;
      return true;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

bool P()
{
   NapraviRazmak();
   ispis += "<P>\n";

   if (tokeni.at(indeks) == "OP_PLUS")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      P();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "OP_MINUS")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      P();
      uvlacenje--;
   }
   else if (tokeni.at(indeks) == "L_ZAGRADA")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;

      if (E())
      {
         if (tokeni.at(indeks) == "D_ZAGRADA")
         {
            NapraviRazmak();
            ispis += (linije.at(indeks) + "\n");
            indeks++;
            uvlacenje--;
            return true;
         }
         else
         {
            obradiGresku();
         }
      }
      else
      {
         obradiGresku();
      }
   }
   else if (tokeni.at(indeks) == "IDN")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      uvlacenje--;
      return true;
   }
   else if (tokeni.at(indeks) == "BROJ")
   {
      uvlacenje++;
      NapraviRazmak();
      ispis += (linije.at(indeks) + "\n");
      indeks++;
      uvlacenje--;
      return true;
   }
   else
   {
      obradiGresku();
   }
   return true;
}

int main(void)
{
   vector<string> splitani;

   while (getline(cin, line))
   {
      splitByChar(line, ' ', splitani);
      linije.push_back(line);
      tokeni.push_back(splitani.at(0));
      //cout << splitani.at(0) << endl;
      splitani.clear();
   }

   tokeni.push_back("$");
   linije.push_back("$");

   Program();

   cout << ispis;

   return 0;
}